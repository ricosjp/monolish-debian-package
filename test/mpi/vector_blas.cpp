#include "blas/sum.hpp"
#include "blas/asum.hpp"
#include "blas/dot.hpp"
#include "blas/nrm1.hpp"
#include "blas/nrm2.hpp"

int main(int argc, char **argv) {

  if (argc != 2) {
    std::cout << "error!, $1:vector size" << std::endl;
    return 1;
  }

  // monolish::util::set_log_level(3);
  // monolish::util::set_log_filename("./monolish_test_log.txt");

  monolish::mpi::Comm &comm = monolish::mpi::Comm::get_instance();
  comm.Init(argc, argv);

  size_t size = atoi(argv[1]);
  std::cout << "size: " << size << std::endl;

  // nosend //
  if (test_sum<double>(size, 1.0e-8) == false) {
    return 1;
  }
  if (test_sum<float>(size, 1.0e-4) == false) {
    return 1;
  }

  // send //
  if (test_sum<double>(size, 1.0e-8) == false) {
    return 1;
  }
  if (test_sum<float>(size, 1.0e-4) == false) {
    return 1;
  }

  // nosend //
  if (test_asum<double>(size, 1.0e-8) == false) {
    return 1;
  }
  if (test_asum<float>(size, 1.0e-4) == false) {
    return 1;
  }

  // send //
  if (test_asum<double>(size, 1.0e-8) == false) {
    return 1;
  }
  if (test_asum<float>(size, 1.0e-4) == false) {
    return 1;
  }

  // nosend //
  if (test_dot<double>(size, 1.0e-8) == false) {
    return 1;
  }
  if (test_dot<float>(size, 1.0e-4) == false) {
    return 1;
  }

  // send //
  if (test_dot<double>(size, 1.0e-8) == false) {
    return 1;
  }
  if (test_dot<float>(size, 1.0e-4) == false) {
    return 1;
  }

  // nosend //
  if (test_nrm1<double>(size, 1.0e-8) == false) {
    return 1;
  }
  if (test_nrm1<float>(size, 1.0e-4) == false) {
    return 1;
  }

  // send //
  if (test_nrm1<double>(size, 1.0e-8) == false) {
    return 1;
  }
  if (test_nrm1<float>(size, 1.0e-4) == false) {
    return 1;
  }

  // nosend //
  if (test_nrm2<double>(size, 1.0e-8) == false) {
    return 1;
  }
  if (test_nrm2<float>(size, 1.0e-4) == false) {
    return 1;
  }

  // send //
  if (test_nrm2<double>(size, 1.0e-8) == false) {
    return 1;
  }
  if (test_nrm2<float>(size, 1.0e-4) == false) {
    return 1;
  }

  comm.Finalize();

  return 0;
}
