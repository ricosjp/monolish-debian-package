#include "../../../../include/monolish_blas.hpp"
#include "../../../internal/monolish_internal.hpp"

namespace monolish {
namespace matrix {

// add vector
template <typename T>
void Dense<T>::row_add(const size_t r, const vector<T> &vec) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  const T *vecd = vec.data();

  T *vald = val.data();
  const size_t N = get_col();
  const size_t Len = get_col();

  if (Len != vec.size()) {
    throw std::runtime_error("error vec.size != A.col.size");
  }

  if (gpu_status == true) {
#if MONOLISH_USE_GPU // gpu
#pragma omp target teams distribute parallel for
    for (size_t i = 0; i < Len; i++) {
      vald[N * r + i] += vecd[i];
    }
#else
    throw std::runtime_error("error USE_GPU is false, but gpu_status == true");
#endif
  } else {
#pragma omp parallel for
    for (size_t i = 0; i < Len; i++) {
      vald[N * r + i] += vecd[i];
    }
  }

  logger.func_out();
}
template void
monolish::matrix::Dense<double>::row_add(const size_t r,
                                         const vector<double> &vec);
template void monolish::matrix::Dense<float>::row_add(const size_t r,
                                                      const vector<float> &vec);

// sub vector
template <typename T>
void Dense<T>::row_sub(const size_t r, const vector<T> &vec) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  const T *vecd = vec.data();

  T *vald = val.data();
  const size_t N = get_col();
  const size_t Len = get_col();

  if (Len != vec.size()) {
    throw std::runtime_error("error vec.size != A.col.size");
  }

  if (gpu_status == true) {
#if MONOLISH_USE_GPU // gpu
#pragma omp target teams distribute parallel for
    for (size_t i = 0; i < Len; i++) {
      vald[N * r + i] -= vecd[i];
    }
#else
    throw std::runtime_error("error USE_GPU is false, but gpu_status == true");
#endif
  } else {
#pragma omp parallel for
    for (size_t i = 0; i < Len; i++) {
      vald[N * r + i] -= vecd[i];
    }
  }

  logger.func_out();
}
template void
monolish::matrix::Dense<double>::row_sub(const size_t r,
                                         const vector<double> &vec);
template void monolish::matrix::Dense<float>::row_sub(const size_t r,
                                                      const vector<float> &vec);

// mul vector
template <typename T>
void Dense<T>::row_mul(const size_t r, const vector<T> &vec) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  const T *vecd = vec.data();

  T *vald = val.data();
  const size_t N = get_col();
  const size_t Len = get_col();

  if (Len != vec.size()) {
    throw std::runtime_error("error vec.size != A.col.size");
  }

  if (gpu_status == true) {
#if MONOLISH_USE_GPU // gpu
#pragma omp target teams distribute parallel for
    for (size_t i = 0; i < Len; i++) {
      vald[N * r + i] *= vecd[i];
    }
#else
    throw std::runtime_error("error USE_GPU is false, but gpu_status == true");
#endif
  } else {
#pragma omp parallel for
    for (size_t i = 0; i < Len; i++) {
      vald[N * r + i] *= vecd[i];
    }
  }

  logger.func_out();
}
template void
monolish::matrix::Dense<double>::row_mul(const size_t r,
                                         const vector<double> &vec);
template void monolish::matrix::Dense<float>::row_mul(const size_t r,
                                                      const vector<float> &vec);

// div vector
template <typename T>
void Dense<T>::row_div(const size_t r, const vector<T> &vec) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  const T *vecd = vec.data();

  T *vald = val.data();
  const size_t N = get_col();
  const size_t Len = get_col();

  if (Len != vec.size()) {
    throw std::runtime_error("error vec.size != A.col.size");
  }

  if (gpu_status == true) {
#if MONOLISH_USE_GPU // gpu
#pragma omp target teams distribute parallel for
    for (size_t i = 0; i < Len; i++) {
      vald[N * r + i] /= vecd[i];
    }
#else
    throw std::runtime_error("error USE_GPU is false, but gpu_status == true");
#endif
  } else {
#pragma omp parallel for
    for (size_t i = 0; i < Len; i++) {
      vald[N * r + i] /= vecd[i];
    }
  }

  logger.func_out();
}
template void
monolish::matrix::Dense<double>::row_div(const size_t r,
                                         const vector<double> &vec);
template void monolish::matrix::Dense<float>::row_div(const size_t r,
                                                      const vector<float> &vec);

} // namespace matrix
} // namespace monolish
