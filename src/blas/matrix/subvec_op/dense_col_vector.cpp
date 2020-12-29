#include "../../../../include/monolish_blas.hpp"
#include "../../../internal/monolish_internal.hpp"

namespace monolish {
namespace matrix {

// add vector
template <typename T>
void Dense<T>::col_add(const size_t c, const vector<T> &vec) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  const T *vecd = vec.data();

  T *vald = val.data();
  const size_t N = get_col();
  const size_t Len = get_row();

  if (Len != vec.size()) {
    throw std::runtime_error("error vec.size != A.row.size");
  }

  if (gpu_status == true) {
#if MONOLISH_USE_GPU // gpu
#pragma omp target teams distribute parallel for
    for (size_t i = 0; i < Len; i++) {
      vald[N * i + c] += vecd[i];
    }
#else
    throw std::runtime_error("error USE_GPU is false, but gpu_status == true");
#endif
  } else {
#pragma omp parallel for
    for (size_t i = 0; i < Len; i++) {
      vald[N * i + c] += vecd[i];
    }
  }

  logger.func_out();
}
template void
monolish::matrix::Dense<double>::col_add(const size_t c,
                                         const vector<double> &vec);
template void monolish::matrix::Dense<float>::col_add(const size_t c,
                                                      const vector<float> &vec);

// sub vector
template <typename T>
void Dense<T>::col_sub(const size_t c, const vector<T> &vec) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  const T *vecd = vec.data();

  T *vald = val.data();
  const size_t N = get_col();
  const size_t Len = get_row();

  if (Len != vec.size()) {
    throw std::runtime_error("error vec.size != A.row.size");
  }

  if (gpu_status == true) {
#if MONOLISH_USE_GPU // gpu
#pragma omp target teams distribute parallel for
    for (size_t i = 0; i < Len; i++) {
      vald[N * i + c] -= vecd[i];
    }
#else
    throw std::runtime_error("error USE_GPU is false, but gpu_status == true");
#endif
  } else {
#pragma omp parallel for
    for (size_t i = 0; i < Len; i++) {
      vald[N * i + c] -= vecd[i];
    }
  }

  logger.func_out();
}
template void
monolish::matrix::Dense<double>::col_sub(const size_t c,
                                         const vector<double> &vec);
template void monolish::matrix::Dense<float>::col_sub(const size_t c,
                                                      const vector<float> &vec);

// mul vector
template <typename T>
void Dense<T>::col_mul(const size_t c, const vector<T> &vec) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  const T *vecd = vec.data();

  T *vald = val.data();
  const size_t N = get_col();
  const size_t Len = get_row();

  if (Len != vec.size()) {
    throw std::runtime_error("error vec.size != A.row.size");
  }

  if (gpu_status == true) {
#if MONOLISH_USE_GPU // gpu
#pragma omp target teams distribute parallel for
    for (size_t i = 0; i < Len; i++) {
      vald[N * i + c] *= vecd[i];
    }
#else
    throw std::runtime_error("error USE_GPU is false, but gpu_status == true");
#endif
  } else {
#pragma omp parallel for
    for (size_t i = 0; i < Len; i++) {
      vald[N * i + c] *= vecd[i];
    }
  }

  logger.func_out();
}
template void
monolish::matrix::Dense<double>::col_mul(const size_t c,
                                         const vector<double> &vec);
template void monolish::matrix::Dense<float>::col_mul(const size_t c,
                                                      const vector<float> &vec);

// div vector
template <typename T>
void Dense<T>::col_div(const size_t c, const vector<T> &vec) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  const T *vecd = vec.data();

  T *vald = val.data();
  const size_t N = get_col();
  const size_t Len = get_row();

  if (Len != vec.size()) {
    throw std::runtime_error("error vec.size != A.row.size");
  }

  if (gpu_status == true) {
#if MONOLISH_USE_GPU // gpu
#pragma omp target teams distribute parallel for
    for (size_t i = 0; i < Len; i++) {
      vald[N * i + c] /= vecd[i];
    }
#else
    throw std::runtime_error("error USE_GPU is false, but gpu_status == true");
#endif
  } else {
#pragma omp parallel for
    for (size_t i = 0; i < Len; i++) {
      vald[N * i + c] /= vecd[i];
    }
  }

  logger.func_out();
}
template void
monolish::matrix::Dense<double>::col_div(const size_t c,
                                         const vector<double> &vec);
template void monolish::matrix::Dense<float>::col_div(const size_t c,
                                                      const vector<float> &vec);

} // namespace matrix
} // namespace monolish
