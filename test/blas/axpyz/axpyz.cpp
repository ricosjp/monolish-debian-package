#include<iostream>
#include<istream>
#include<chrono>
#include"../../test_utils.hpp"

template <typename T>
void get_ans(double alpha, monolish::vector<T> &mx, monolish::vector<T> &my, monolish::vector<T> &mz){
	if(mx.size() != my.size() || mx.size() != mz.size()){
		std::runtime_error("x.size != y.size");
	}

	for(size_t i = 0; i < mx.size(); i++){
		mz[i] = alpha * mx[i] + my[i];
	}
}

template <typename T>
bool test(double alpha, monolish::vector<T>& x, monolish::vector<T>& y, monolish::vector<T>& z, double tol, const size_t iter, const size_t check_ans){

	monolish::vector<T> ansz;
	ansz = z.copy();

	// check ans
	if(check_ans == 1){
		monolish::blas::axpyz(alpha, x, y, z);
 		get_ans(alpha, x, y, ansz);
		if(ans_check<T>(z.data(), ansz.data(), y.size(), tol) == false){
 			return false;
 		}
	}

	//exec
	auto start = std::chrono::system_clock::now();

	for(size_t i = 0; i < iter; i++){
		monolish::blas::axpyz(alpha, x, y, z);
	}

	auto end = std::chrono::system_clock::now();
	double sec = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()/1.0e+9;

	std::cout << "total average time[sec]: " << sec / iter << std::endl;

	return true;
}

int main(int argc, char** argv){

	if(argc!=4){
		std::cout << "error $1:vector size, $2: iter, $3: error check (1/0)" << std::endl;
		return 1;
	}
	//monolish::util::set_log_level(3);
	//monolish::util::set_log_filename("./monolish_test_log.txt");

	size_t size = atoi(argv[1]);
	size_t iter = atoi(argv[2]);
	size_t check_ans = atoi(argv[3]);

	//create random vector x rand(0~1)
	double alpha = 123.0;
   	monolish::vector<double> x(size, 0.0, 1.0);
   	monolish::vector<double> y(size, 0.0, 1.0);
   	monolish::vector<double> z(size, 0.0, 1.0);

 	// exec and error check
 	if( test<double>(alpha, x, y, z, 1.0e-8, iter, check_ans) == false){ return 1; }

	return 0;
}
