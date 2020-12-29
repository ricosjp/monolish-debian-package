#include "../../../../include/monolish_blas.hpp"
#include "../../../internal/monolish_internal.hpp"

namespace monolish {

void blas::matvec(const matrix::CRS<double> &A, const vector<double> &x,
                  vector<double> &y) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  // err, M = MN * N
  if (A.get_row() != y.size() && A.get_col() != x.size()) {
    throw std::runtime_error("error vector size is not same");
  }
  if (A.get_device_mem_stat() != x.get_device_mem_stat() ||
      A.get_device_mem_stat() != y.get_device_mem_stat()) {
    throw std::runtime_error("error get_device_mem_stat() is not same");
  }

  const double *vald = A.val.data();
  const double *xd = x.data();

  if (A.get_device_mem_stat() == true) {
#if MONOLISH_USE_GPU // gpu
    size_t m = A.get_row();
    size_t n = A.get_col();
    size_t nnz = A.get_nnz();
    double *yd = y.data();
    const int *rowd = A.row_ptr.data();
    const int *cold = A.col_ind.data();

    cusparseHandle_t sp_handle;
    cusparseCreate(&sp_handle);
    cudaDeviceSynchronize();

    cusparseMatDescr_t descr = 0;
    cusparseCreateMatDescr(&descr);
    cusparseSetMatIndexBase(descr, CUSPARSE_INDEX_BASE_ZERO);
    cusparseSetMatFillMode(descr, CUSPARSE_FILL_MODE_LOWER);
    cusparseSetMatDiagType(descr, CUSPARSE_DIAG_TYPE_UNIT);

    const cusparseOperation_t trans = CUSPARSE_OPERATION_NON_TRANSPOSE;

    const double alpha = 1.0;
    const double beta = 0.0;

#pragma omp target data use_device_ptr(xd, yd, vald, rowd, cold)
    {
      internal::check_CUDA(cusparseDcsrmv(sp_handle, trans, m, n, nnz, &alpha,
                                          descr, vald, rowd, cold, xd, &beta,
                                          yd));
    }
#else
    throw std::runtime_error("error USE_GPU is false, but gpu_status == true");
#endif
  } else {
#pragma omp parallel for
    for (int i = 0; i < (int)A.get_row(); i++) {
      double ytmp = 0.0;
      for (int j = A.row_ptr[i]; j < A.row_ptr[i + 1]; j++) {
        ytmp += vald[j] * xd[A.col_ind[j]];
      }
      y[i] = ytmp;
    }
  }

  logger.func_out();
}

void blas::matvec(const matrix::CRS<float> &A, const vector<float> &x,
                  vector<float> &y) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  // err, M = MN * N
  if (A.get_row() != y.size() && A.get_col() != x.size()) {
    throw std::runtime_error("error vector size is not same");
  }

  if (A.get_device_mem_stat() != x.get_device_mem_stat() ||
      A.get_device_mem_stat() != y.get_device_mem_stat()) {
    throw std::runtime_error("error get_device_mem_stat() is not same");
  }

  const float *vald = A.val.data();
  const float *xd = x.data();

  if (A.get_device_mem_stat() == true) {
#if MONOLISH_USE_GPU // gpu
    size_t m = A.get_row();
    size_t n = A.get_col();
    size_t nnz = A.get_nnz();
    float *yd = y.data();
    const int *rowd = A.row_ptr.data();
    const int *cold = A.col_ind.data();

    cusparseHandle_t sp_handle;
    cusparseCreate(&sp_handle);
    cudaDeviceSynchronize();

    cusparseMatDescr_t descr = 0;
    cusparseCreateMatDescr(&descr);
    cusparseSetMatIndexBase(descr, CUSPARSE_INDEX_BASE_ZERO);
    cusparseSetMatFillMode(descr, CUSPARSE_FILL_MODE_LOWER);
    cusparseSetMatDiagType(descr, CUSPARSE_DIAG_TYPE_UNIT);

    const cusparseOperation_t trans = CUSPARSE_OPERATION_NON_TRANSPOSE;

    const float alpha = 1.0;
    const float beta = 0.0;

#pragma omp target data use_device_ptr(xd, yd, vald, rowd, cold)
    {
      internal::check_CUDA(cusparseScsrmv(sp_handle, trans, m, n, nnz, &alpha,
                                          descr, vald, rowd, cold, xd, &beta,
                                          yd));
    }
#else
    throw std::runtime_error("error USE_GPU is false, but gpu_status == true");
#endif
  } else {
#pragma omp parallel for
    for (int i = 0; i < (int)A.get_row(); i++) {
      double ytmp = 0.0;
      for (int j = A.row_ptr[i]; j < A.row_ptr[i + 1]; j++) {
        ytmp += vald[j] * xd[A.col_ind[j]];
      }
      y[i] = ytmp;
    }
  }

  logger.func_out();
}
} // namespace monolish
