#include "math_2.h"

#include "x86intrin.h"
#include "immintrin.h"


vector_1d par_mat_sum(vector_1d v1,vector_1d v2)
{
	// 1D vec <- 1D vec + 1D vec
	vector_1d outvec;
	int out_dim=v1.size();
	outvec.resize(out_dim);
	__m128d sum = _mm_setzero_pd();
	for (int i = 0; i < out_dim; i+=4){
		sum = _mm_add_pd (_mm_loadu_pd (&v1[i]), _mm_loadu_pd (&v2[i]));
		_mm_store_pd(&outvec[i], sum);
	}

	return outvec;
}

vector_2d par_mat_sum(vector_2d v1 ,vector_2d v2)
{
	// 2D vec <- 2D vec + 2D vec
	vector_2d outvec;
	int row = v1.size();
	int col = v1[0].size();
	outvec.resize(row ,vector_1d(col));

	__m128d sum = _mm_setzero_pd();
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j+=4){
			sum = _mm_add_pd (_mm_loadu_pd (&v1[i][j]), _mm_loadu_pd (&v2[i][j]));
			_mm_store_pd(&outvec[i][j], sum);		
		}
	}
	return outvec;
}


void print_vector_1d(vector_1d v){
	cout<<"V:"<<v.size()<<" = ";
	for (int i = 0; i < v.size(); i++){
		cout<< v[i]<<" ";
	}
	cout<<endl;
}

vector_1d par_mat_mul(vector_1d v1,vector_2d v2)
{
	// 1D vec <- 1D vec * 2D vec
	int in_dim = v1.size();
	int out_dim = v2[0].size();
	vector_1d outvec;
	outvec.resize(out_dim, 0);

	for (int i = 0; i < out_dim; i++) {
		__m128d sum = _mm_set1_pd(0.0f);
		for (int j = 0; j < in_dim; j+=4){
			sum = _mm_add_pd (sum, _mm_mul_pd (_mm_loadu_pd (&v1[j]), _mm_loadu_pd (&v2[j][i])));
		}
		sum = _mm_hadd_pd (sum, sum);
		sum = _mm_hadd_pd (sum, sum);
		_mm_store_sd(&outvec[i], sum);
	}
	return outvec;
}

vector_1d par_mat_mul(vector_1d v1,vector_1d v2)
{
	// 1D vec <- 1D vec .* 1D vec
	int in_dim = v1.size();

	vector_1d outvec;
	outvec.resize(in_dim);

	__m128d mul = _mm_set1_pd(1.0f);
	for (int i = 0; i < in_dim; i+=4){
		mul = _mm_mul_pd (_mm_loadu_pd (&v1[i]), _mm_loadu_pd (&v2[i]));
		_mm_store_pd(&outvec[i], mul);
	}

	return outvec;
}

vector_2d par_mat_mul_2d(vector_1d v1,vector_1d v2)
{
	// 2D vec <- 1D vec * 1D vec
	int in=v1.size();
	int out=v2.size();
	vector_2d outvec;
	outvec.resize(in,vector_1d(out));

	__m128d mul = _mm_set1_pd(1.0f);
	for(int i=0;i<in;i++){
		for(int j=0;j<out;j+=4){
			mul = _mm_mul_pd (_mm_loadu_pd (&v1[j]), _mm_loadu_pd (&v2[j]));
			_mm_store_pd(&outvec[i][j], mul);
		}
	}
	return outvec;
}