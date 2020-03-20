#include "../../include/common/monolish_matrix.hpp" 
#include "../../include/common/monolish_vector.hpp" 
#include "../../include/common/monolish_logger.hpp" 
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>


//kill cerr 

namespace monolish{
	namespace matrix{

		template<>
			void CRS<double>::convert(COO<double> &coo){
				Logger& logger = Logger::get_instance();
				logger.util_in(monolish_func);

				//todo coo err check (only square)

				row = coo.get_row();
				col = coo.get_col();
				nnz = coo.get_nnz();

				val = coo.val;
				col_ind = coo.col_index;

				// todo not inplace now
				row_ptr.resize(row+1, 0.0);


				row_ptr[0] = 0;
				size_t c_row = 0;
				for (size_t i = 0; i < coo.get_nnz(); i++) {

					if((int)c_row == coo.row_index[i]){
						row_ptr[c_row+1] = i+1;
					}
					else{
						c_row = c_row + 1;
						row_ptr[c_row+1] = i+1;
					}
				}
				logger.util_out();
			}

		template<>
			void CRS<double>::output(){
				Logger& logger = Logger::get_instance();
				logger.util_in(monolish_func);

				for(size_t i = 0; i < row; i++){
					for(size_t j = (size_t)row_ptr[i]; j < (size_t)row_ptr[i+1]; j++){
						std::cout << i+1 << " " << col_ind[j]+1 << " " << val[j] << std::endl;
					}
				}

				logger.util_out();
			}

		template<>
			vector<double> CRS<double>::get_diag(){
				Logger& logger = Logger::get_instance();
				logger.util_in(monolish_func);
				vector<double> vec(row, 1.0);
				logger.util_out();
				return vec;
			}
	}
}
//
// 	template<>
// 		void COO_matrix<double>::output_mm(const char* filename){
// 			Logger& logger = Logger::get_instance();
// 			logger.func_in(monolish_func);
// 			std::ofstream out(filename);
// 			out << std::scientific;
// 			out << std::setprecision(std::numeric_limits<double>::max_digits10);
//
// 			out << (MM_BANNER " " MM_MAT " " MM_FMT " " MM_TYPE_REAL " " MM_TYPE_GENERAL) << std::endl;
// 			out << row << " " << row << " " << nnz << std::endl;
//
// 			for(size_t i=0; i<nnz; i++){
// 				out << row_index[i] << " " << col_index[i] << " " << val[i] << std::endl;
// 			}
// 			logger.func_out();
// 		}
//
// 	template<>
// 		void COO_matrix<double>::output(){
// 			Logger& logger = Logger::get_instance();
// 			logger.func_in(monolish_func);
// 			for(size_t i=0; i<nnz; i++){
// 				std::cout << row_index[i] << " " << col_index[i] << " " << val[i] << std::endl;
// 			}
// 			logger.func_out();
// 		}
//
// 	template<>
// 		double COO_matrix<double>::at(size_t i, size_t j){
// 			Logger& logger = Logger::get_instance();
// 			logger.func_in(monolish_func);
//
// 			if(i < row && j < col){
// 				throw std::runtime_error("error");
// 			}
//
// 			for(size_t i=0; i<nnz; i++){
// 				if( row_index[i] == i && col_index[i] == j){
// 					return val[i];
// 				}
// 			}
// 			logger.func_out();
// 			return 0.0;
// 		}
//
// 	template<>
// 		void COO_matrix<double>::set_ptr(size_t rN, size_t cN, std::vector<size_t> &r, std::vector<size_t> &c, std::vector<double> &v){
// 			col_index = c;
// 			row_index = r;
// 			val = v;
//
// 			row = rN;
// 			col = cN;
// 			nnz = r.size();
// 		}
