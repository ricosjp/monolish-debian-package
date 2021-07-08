// This code is generated by gen_vector_blas.sh
#include "../internal/monolish_internal.hpp"
#include "Bcast.hpp"
#include "Gather.hpp"
#include "Scatter.hpp"
#include "allreduce.hpp"
#include "isend_irecv.hpp"
#include "send_recv.hpp"

namespace monolish::mpi {

void comm::set_comm(MPI_Comm external_comm) {
  Logger &logger = Logger::get_instance();
  logger.util_in(monolish_func);
  my_comm = external_comm;
  logger.util_out();
}

void comm::Init() {
  Logger &logger = Logger::get_instance();
  logger.util_in(monolish_func);
#if defined MONOLISH_USE_MPI
  assert(MPI_Init(nullptr, nullptr) == MPI_SUCCESS);
  if (get_comm() == 0) {
    set_comm(MPI_COMM_WORLD);
  }
#endif
  logger.util_out();
}

void comm::Init(int argc, char **argv) {
  Logger &logger = Logger::get_instance();
  logger.util_in(monolish_func);
#if defined MONOLISH_USE_MPI
  assert(MPI_Init(&argc, &argv) == MPI_SUCCESS);
  if (get_comm() == 0) {
    set_comm(MPI_COMM_WORLD);
  }
#endif
  logger.util_out();
}

bool comm::Initialized() const {
  Logger &logger = Logger::get_instance();
  logger.util_in(monolish_func);
#if defined MONOLISH_USE_MPI
  int flag;
  assert(MPI_Initialized(&flag) == MPI_SUCCESS);
  logger.util_out();
  return (flag == 0) ? true : false;
#endif
  logger.util_out();
  return true;
}

void comm::Finalize() {
  Logger &logger = Logger::get_instance();
  logger.util_in(monolish_func);
#if defined MONOLISH_USE_MPI
  assert(MPI_Finalize() == MPI_SUCCESS);
#endif
  logger.util_out();
}

///////////////////////////////////////////////

int comm::get_rank() {
  Logger &logger = Logger::get_instance();
  logger.util_in(monolish_func);
  int rank = 0;
#if defined MONOLISH_USE_MPI
  MPI_Comm_rank(get_comm(), &rank);
  logger.util_out();
  return rank;
#endif
  logger.util_out();
  return rank;
}

int comm::get_size() {
  Logger &logger = Logger::get_instance();
  logger.util_in(monolish_func);
  int size = 1;
#if defined MONOLISH_USE_MPI
  MPI_Comm_size(get_comm(), &size);
  logger.util_out();
  return size;
#endif
  logger.util_out();
  return size;
}

///////////////////////////////////////////////

void comm::Barrier() const {
  Logger &logger = Logger::get_instance();
  logger.util_in(monolish_func);
#if defined MONOLISH_USE_MPI
  MPI_Barrier(get_comm());
  logger.util_out();
#endif
  logger.util_out();
}

void comm::Send(double val, int dst, int tag) const {
  Send_core(val, dst, tag, get_comm());
}
void comm::Send(float val, int dst, int tag) const {
  Send_core(val, dst, tag, get_comm());
}
void comm::Send(int val, int dst, int tag) const {
  Send_core(val, dst, tag, get_comm());
}
void comm::Send(size_t val, int dst, int tag) const {
  Send_core(val, dst, tag, get_comm());
}

void comm::Send(std::vector<double> &vec, int dst, int tag) const {
  Send_core(vec, dst, tag, get_comm());
}
void comm::Send(std::vector<float> &vec, int dst, int tag) const {
  Send_core(vec, dst, tag, get_comm());
}
void comm::Send(std::vector<int> &vec, int dst, int tag) const {
  Send_core(vec, dst, tag, get_comm());
}
void comm::Send(std::vector<size_t> &vec, int dst, int tag) const {
  Send_core(vec, dst, tag, get_comm());
}

void comm::Send(monolish::vector<double> &vec, int dst, int tag) const {
  Send_core(vec, dst, tag, get_comm());
}
void comm::Send(monolish::vector<float> &vec, int dst, int tag) const {
  Send_core(vec, dst, tag, get_comm());
}

MPI_Status comm::Recv(double val, int src, int tag) const {
  return Recv_core(val, src, tag, get_comm());
}
MPI_Status comm::Recv(float val, int src, int tag) const {
  return Recv_core(val, src, tag, get_comm());
}
MPI_Status comm::Recv(int val, int src, int tag) const {
  return Recv_core(val, src, tag, get_comm());
}
MPI_Status comm::Recv(size_t val, int src, int tag) const {
  return Recv_core(val, src, tag, get_comm());
}

MPI_Status comm::Recv(std::vector<double> &vec, int src, int tag) const {
  return Recv_core(vec, src, tag, get_comm());
}
MPI_Status comm::Recv(std::vector<float> &vec, int src, int tag) const {
  return Recv_core(vec, src, tag, get_comm());
}
MPI_Status comm::Recv(std::vector<int> &vec, int src, int tag) const {
  return Recv_core(vec, src, tag, get_comm());
}
MPI_Status comm::Recv(std::vector<size_t> &vec, int src, int tag) const {
  return Recv_core(vec, src, tag, get_comm());
}

MPI_Status comm::Recv(monolish::vector<double> &vec, int src, int tag) const {
  return Recv_core(vec, src, tag, get_comm());
}
MPI_Status comm::Recv(monolish::vector<float> &vec, int src, int tag) const {
  return Recv_core(vec, src, tag, get_comm());
}

void comm::Isend(double val, int dst, int tag) {
  Isend_core(val, dst, tag, get_comm(), requests);
}
void comm::Isend(float val, int dst, int tag) {
  Isend_core(val, dst, tag, get_comm(), requests);
}
void comm::Isend(int val, int dst, int tag) {
  Isend_core(val, dst, tag, get_comm(), requests);
}
void comm::Isend(size_t val, int dst, int tag) {
  Isend_core(val, dst, tag, get_comm(), requests);
}

void comm::Isend(const std::vector<double> &vec, int dst, int tag) {
  Isend_core(vec, dst, tag, get_comm(), requests);
}
void comm::Isend(const std::vector<float> &vec, int dst, int tag) {
  Isend_core(vec, dst, tag, get_comm(), requests);
}
void comm::Isend(const std::vector<int> &vec, int dst, int tag) {
  Isend_core(vec, dst, tag, get_comm(), requests);
}
void comm::Isend(const std::vector<size_t> &vec, int dst, int tag) {
  Isend_core(vec, dst, tag, get_comm(), requests);
}

void comm::Isend(const monolish::vector<double> &vec, int dst, int tag) {
  Isend_core(vec, dst, tag, get_comm(), requests);
}
void comm::Isend(const monolish::vector<float> &vec, int dst, int tag) {
  Isend_core(vec, dst, tag, get_comm(), requests);
}

void comm::Irecv(double val, int src, int tag) {
  Irecv_core(val, src, tag, get_comm(), requests);
}
void comm::Irecv(float val, int src, int tag) {
  Irecv_core(val, src, tag, get_comm(), requests);
}
void comm::Irecv(int val, int src, int tag) {
  Irecv_core(val, src, tag, get_comm(), requests);
}
void comm::Irecv(size_t val, int src, int tag) {
  Irecv_core(val, src, tag, get_comm(), requests);
}

void comm::Irecv(std::vector<double> &vec, int src, int tag) {
  Irecv_core(vec, src, tag, get_comm(), requests);
}
void comm::Irecv(std::vector<float> &vec, int src, int tag) {
  Irecv_core(vec, src, tag, get_comm(), requests);
}
void comm::Irecv(std::vector<int> &vec, int src, int tag) {
  Irecv_core(vec, src, tag, get_comm(), requests);
}
void comm::Irecv(std::vector<size_t> &vec, int src, int tag) {
  Irecv_core(vec, src, tag, get_comm(), requests);
}

void comm::Irecv(monolish::vector<double> &vec, int src, int tag) {
  Irecv_core(vec, src, tag, get_comm(), requests);
}
void comm::Irecv(monolish::vector<float> &vec, int src, int tag) {
  Irecv_core(vec, src, tag, get_comm(), requests);
}

void comm::Waitall() { Waitall_core(requests); }

double comm::Allreduce(double val) const {
  return Allreduce_core(val, MPI_SUM, get_comm());
}
float comm::Allreduce(float val) const {
  return Allreduce_core(val, MPI_SUM, get_comm());
}
int comm::Allreduce(int val) const {
  return Allreduce_core(val, MPI_SUM, get_comm());
}
size_t comm::Allreduce(size_t val) const {
  return Allreduce_core(val, MPI_SUM, get_comm());
}

double comm::Allreduce_sum(double val) const {
  return Allreduce_core(val, MPI_SUM, get_comm());
}
float comm::Allreduce_sum(float val) const {
  return Allreduce_core(val, MPI_SUM, get_comm());
}
int comm::Allreduce_sum(int val) const {
  return Allreduce_core(val, MPI_SUM, get_comm());
}
size_t comm::Allreduce_sum(size_t val) const {
  return Allreduce_core(val, MPI_SUM, get_comm());
}

double comm::Allreduce_prod(double val) const {
  return Allreduce_core(val, MPI_PROD, get_comm());
}
float comm::Allreduce_prod(float val) const {
  return Allreduce_core(val, MPI_PROD, get_comm());
}
int comm::Allreduce_prod(int val) const {
  return Allreduce_core(val, MPI_PROD, get_comm());
}
size_t comm::Allreduce_prod(size_t val) const {
  return Allreduce_core(val, MPI_PROD, get_comm());
}

double comm::Allreduce_max(double val) const {
  return Allreduce_core(val, MPI_MAX, get_comm());
}
float comm::Allreduce_max(float val) const {
  return Allreduce_core(val, MPI_MAX, get_comm());
}
int comm::Allreduce_max(int val) const {
  return Allreduce_core(val, MPI_MAX, get_comm());
}
size_t comm::Allreduce_max(size_t val) const {
  return Allreduce_core(val, MPI_MAX, get_comm());
}

double comm::Allreduce_min(double val) const {
  return Allreduce_core(val, MPI_MIN, get_comm());
}
float comm::Allreduce_min(float val) const {
  return Allreduce_core(val, MPI_MIN, get_comm());
}
int comm::Allreduce_min(int val) const {
  return Allreduce_core(val, MPI_MIN, get_comm());
}
size_t comm::Allreduce_min(size_t val) const {
  return Allreduce_core(val, MPI_MIN, get_comm());
}

void comm::Bcast(double &val, int root) const {
  Bcast_core(val, root, get_comm());
}
void comm::Bcast(float &val, int root) const {
  Bcast_core(val, root, get_comm());
}
void comm::Bcast(int &val, int root) const {
  Bcast_core(val, root, get_comm());
}
void comm::Bcast(size_t &val, int root) const {
  Bcast_core(val, root, get_comm());
}

void comm::Bcast(std::vector<double> &vec, int root) const {
  Bcast_core(vec, root, get_comm());
}
void comm::Bcast(std::vector<float> &vec, int root) const {
  Bcast_core(vec, root, get_comm());
}
void comm::Bcast(std::vector<int> &vec, int root) const {
  Bcast_core(vec, root, get_comm());
}
void comm::Bcast(std::vector<size_t> &vec, int root) const {
  Bcast_core(vec, root, get_comm());
}

void comm::Bcast(monolish::vector<double> &vec, int root) const {
  Bcast_core(vec, root, get_comm());
}
void comm::Bcast(monolish::vector<float> &vec, int root) const {
  Bcast_core(vec, root, get_comm());
}

void comm::Gather(monolish::vector<double> &sendvec,
                  monolish::vector<double> &recvvec, int root) const {
  Gather_core(sendvec, recvvec, root, get_comm());
}
void comm::Gather(monolish::vector<float> &sendvec,
                  monolish::vector<float> &recvvec, int root) const {
  Gather_core(sendvec, recvvec, root, get_comm());
}

void comm::Gather(std::vector<double> &sendvec, std::vector<double> &recvvec,
                  int root) const {
  Gather_core(sendvec, recvvec, root, get_comm());
}
void comm::Gather(std::vector<float> &sendvec, std::vector<float> &recvvec,
                  int root) const {
  Gather_core(sendvec, recvvec, root, get_comm());
}
void comm::Gather(std::vector<int> &sendvec, std::vector<int> &recvvec,
                  int root) const {
  Gather_core(sendvec, recvvec, root, get_comm());
}
void comm::Gather(std::vector<size_t> &sendvec, std::vector<size_t> &recvvec,
                  int root) const {
  Gather_core(sendvec, recvvec, root, get_comm());
}

void comm::Scatter(monolish::vector<double> &sendvec,
                   monolish::vector<double> &recvvec, int root) const {
  Scatter_core(sendvec, recvvec, root, get_comm());
}
void comm::Scatter(monolish::vector<float> &sendvec,
                   monolish::vector<float> &recvvec, int root) const {
  Scatter_core(sendvec, recvvec, root, get_comm());
}

void comm::Scatter(std::vector<double> &sendvec, std::vector<double> &recvvec,
                   int root) const {
  Scatter_core(sendvec, recvvec, root, get_comm());
}
void comm::Scatter(std::vector<float> &sendvec, std::vector<float> &recvvec,
                   int root) const {
  Scatter_core(sendvec, recvvec, root, get_comm());
}
void comm::Scatter(std::vector<int> &sendvec, std::vector<int> &recvvec,
                   int root) const {
  Scatter_core(sendvec, recvvec, root, get_comm());
}
void comm::Scatter(std::vector<size_t> &sendvec, std::vector<size_t> &recvvec,
                   int root) const {
  Scatter_core(sendvec, recvvec, root, get_comm());
}

} // namespace monolish::mpi
