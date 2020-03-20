/**
 * @autor RICOS Co. Ltd.
 * @file monolish_vector.h
 * @brief declare vector class
 * @date 2019
 **/

#pragma once
#include<omp.h>
#include<exception>
#include<stdexcept>
#include<vector>

#define MM_BANNER "%%MatrixMarket"
#define MM_MAT "matrix"
#define MM_VEC "vector"
#define MM_FMT "coordinate"
#define MM_TYPE_REAL "real"
#define MM_TYPE_GENERAL "general"
#define MM_TYPE_SYMM "symmetric"

#if defined USE_MPI
#include<mpi.h>
#endif

namespace monolish{
template<typename Float> class vector;
	namespace matrix{

		/**
		 * @brief Coodinate format Matrix (need to sort)
		 */
		template<typename Float>
			class COO{
				private:
					size_t row;

					/**
					 * @brief neet col = row now
					 */
					size_t col;
					size_t nnz;

					bool gpu_flag = false; // not impl

					void set_rowN(const size_t N){row = N;};
					void set_colN(const size_t N){col = N;};
					void set_nnzN(const size_t N){nnz = N;};

				public:

					std::vector<int> row_index;
					std::vector<int> col_index;
					std::vector<Float> val;

					COO(){}

					COO(const size_t N, const size_t nnz, const int* row, const int* col, const double* value){
						set_rowN(N);
						set_colN(N);
						set_nnzN(nnz);

						row_index.resize(nnz);
						col_index.resize(nnz);
						val.resize(nnz);

						std::copy(row, row+nnz, row_index.begin());
						std::copy(col, col+nnz, col_index.begin());
						std::copy(value, value+nnz, val.begin());
					}

					void input_mm(const char* filename);

					COO(const char* filename){
						input_mm(filename);
					}

					void output_mm(const char* filename);
					void output();
					double at(size_t i, size_t j);
					//void insert(size_t i, size_t j, double value);

					void set_ptr(size_t rN, size_t cN, std::vector<int> &r, std::vector<int> &c, std::vector<double> &v);

					//not logging, only square
					size_t size(){return row;}
					size_t get_row(){return row;}
					size_t get_col(){return col;}
					size_t get_nnz(){return nnz;}

					/**
					 * @brief matrix copy
					 * @return copied COO matrix
					 **/
					COO copy(){
						COO tmp(row, nnz, row_index.data(), col_index.data(), val.data());
						return tmp;
					}

					std::vector<int>& get_row_ptr(){return row_index;}
					std::vector<int>& get_col_ptr(){return col_index;}
					std::vector<Float>& get_val_ptr(){return val;}

     				/////////////////////////////////////////////////////////////////////////////

					/**
					 * @brief copy matrix, It is same as copy()
					 * @param[in] filename source
					 * @return output vector
					 **/
					void operator=(const COO<Float>& mat){
						mat = copy();
					}

			};

		/**
		 * @brief CRS format Matrix
		 */
		template<typename Float>
			class CRS{
				private:
					size_t row;

					/**
					 * @brief neet col = row now
					 */
					size_t col;
					size_t nnz;

					bool gpu_flag = false; // not impl

				public:
					std::vector<Float> val;
					std::vector<int> col_ind;
					std::vector<int> row_ptr;

					void convert(COO<double> &coo);

					CRS(){}
					CRS(COO<double> &coo){
						convert(coo);
					}

					void output();

					size_t size(){return row;}
					size_t get_row(){return row;}
					size_t get_col(){return col;}
					size_t get_nnz(){return nnz;}

     				/////////////////////////////////////////////////////////////////////////////
					vector<double> get_diag();
					vector<double> get_row(size_t i);
					vector<double> get_col(size_t j);

     				/////////////////////////////////////////////////////////////////////////////

					/**
					 * @brief matrix copy
					 * @return copied CRS matrix
					 **/
					CRS copy(){
						CRS<double> tmp;
						std::copy(row_ptr.data(), row_ptr.data()+(row+1), tmp.row_ptr.begin());
						std::copy(col_ind.data(), col_ind.data()+nnz, tmp.col_ind.begin());
						std::copy(val.data(), val.data()+nnz, tmp.val.begin());
						return tmp;
					}

					/**
					 * @brief copy matrix, It is same as copy()
					 * @param[in] filename source
					 * @return output vector
					 **/
					void operator=(const COO<Float>& mat){
						mat = copy();
					}

					//mat - vec
					vector<Float> operator*(vector<Float>& vec);

					//mat - scalar
					CRS<Float> operator*(const Float value);
			};
	}
}
