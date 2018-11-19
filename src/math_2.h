#ifndef MAT_2_H
#define MAT_2_H

#include "def.h"
#include <cmath>

using namespace std;

// Math libraries

vector_1d func(string ,vector_1d); // Function for non linearity

vector_1d d_func(string ,vector_1d); // Function for Derivative

vector_1d mat_sum(vector_1d ,vector_1d);

vector_2d mat_sum(vector_2d ,vector_2d);

vector_1d mat_mul(vector_1d ,vector_2d);


vector_2d mat_trans(vector_2d);

vector_1d mat_mul(vector_1d ,vector_1d); // Element by element mul

vector_2d mat_mul_2d(vector_1d ,vector_1d); // 2D <- 1D * 1D

vector_2d mat_mul(double ,vector_2d); // Mul all members to a double

vector_1d mat_mul(double ,vector_1d); // Mul all members to a double

vector_1d cost(string ,vector_1d ,vector_1d); // out ,target

vector_1d d_cost(string ,vector_1d ,vector_1d); // out ,target

//------------------------------SIMD

vector_1d par_mat_sum(vector_1d ,vector_1d);

vector_2d par_mat_sum(vector_2d ,vector_2d);

vector_1d par_mat_mul(vector_1d ,vector_2d);

vector_1d par_mat_mul(vector_1d ,vector_1d);

vector_2d par_mat_mul_2d(vector_1d ,vector_1d);

//----------------------------Random gen

void rand_init();

std::vector<int> perm(int); // similar to perm matlab

unsigned int hash3(unsigned int, unsigned int, unsigned int); // hash for srand setting
 
vector_1d randn(int);

//----------------------------Data preprocessing

double mean(vector_1d);

double stdev(vector_1d); // Standard deviation

vector_1d z_score(vector_1d); // Standard score of data

#endif /* MAT_2_H */