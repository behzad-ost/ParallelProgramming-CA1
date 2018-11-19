#include "math_2.h"

#include "x86intrin.h"

// Math libraries

vector_1d func(string type,vector_1d myvec)
{
// 1D vec <- nonLin(1D vec)
	vector_1d outvec;
	int out_dim=myvec.size();
	outvec.resize(out_dim);

	if(type == "sigmoid")
		for(int i=0;i<out_dim;i++){ outvec[i] = 1.0/(1.0+(exp(-myvec[i]))); } 
	else if(type == "tanh")
		for(int i=0;i<out_dim;i++){ outvec[i] = tanh(myvec[i]); } 
	else
		outvec = myvec; // none

	return outvec;
}

vector_1d d_func(string type,vector_1d myvec)
{
	// 1D vec <- Derivative(1D vec)
	vector_1d outvec;
	int out_dim=myvec.size();
	outvec.resize(out_dim);

	if(type == "sigmoid")
		for(int i=0;i<out_dim;i++){ outvec[i] = myvec[i]*(1.0 - myvec[i]); } 
	else if(type == "tanh")
		for(int i=0;i<out_dim;i++){ outvec[i] = 1.0 - pow(tanh(myvec[i]), 2); } 
	else
		outvec = myvec; // none

	return outvec;
}

vector_1d mat_sum(vector_1d v1,vector_1d v2)
{
	// 1D vec <- 1D vec + 1D vec
	vector_1d outvec;
	int out_dim=v1.size();
	outvec.resize(out_dim);

	for(int i=0;i<out_dim;i++)
		outvec[i] = v1[i] + v2[i];
	return outvec;
}


vector_2d mat_sum(vector_2d v1 ,vector_2d v2)
{
	// 2D vec <- 2D vec + 2D vec
	vector_2d outvec;
	int row = v1.size();
	int col = v1[0].size();
	outvec.resize(row ,vector_1d(col));

	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++)
			outvec[i][j] = v1[i][j] + v2[i][j];
	return outvec;
}


void print_1d(vector_1d v){
	cout<<"V:"<<v.size()<<" = ";
	for (int i = 0; i < v.size(); i++){
		cout<< v[i]<<" ";
	}
	cout<<endl;
}

vector_1d mat_mul(vector_1d v1,vector_2d v2)
{
	// 1D vec <- 1D vec * 2D vec
	int in_dim = v1.size();
	int out_dim = v2[0].size();

	vector_1d outvec;
	outvec.resize(out_dim, 0);

	for(int i=0;i<out_dim;i++){
		for(int j=0;j<in_dim;j++){
			outvec[i] += (v1[j] * v2[j][i]);
		}
	}

	return outvec;
}

vector_2d mat_trans(vector_2d vec)
{
	int row = vec.size();
	int col = vec[0].size();
	vector_2d outvec;
	outvec.resize(col,vector_1d(row));
	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++)
			outvec[j][i] = vec[i][j];
	return outvec;
}

vector_1d mat_mul(vector_1d v1,vector_1d v2)
{
	// 1D vec <- 1D vec .* 1D vec
	int in_dim = v1.size();

	vector_1d outvec;
	outvec.resize(in_dim);

	for(int i=0;i<in_dim;i++)
		outvec[i] = v1[i] * v2[i];

	return outvec;
}



vector_2d mat_mul_2d(vector_1d v1,vector_1d v2)
{
	// 2D vec <- 1D vec * 1D vec
	int in=v1.size();
	int out=v2.size();
	vector_2d outvec;
	outvec.resize(in,vector_1d(out));
	for(int i=0;i<in;i++)
		for(int j=0;j<out;j++)
			outvec[i][j] = v1[i] * v2[j];
	return outvec;
}


vector_2d mat_mul(double val,vector_2d vec)
{
	int row = vec.size();
	int col = vec[0].size();
	vector_2d outvec;
	outvec.resize(row,vector_1d(col));
	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++)
			outvec[i][j] = val * vec[i][j];
	return outvec;
}

vector_1d mat_mul(double val,vector_1d vec)
{
	int row = vec.size();

	vector_1d outvec;
	outvec.resize(row);
	for(int i=0;i<row;i++)
		outvec[i] = val * vec[i];
	return outvec;
}

vector_1d cost(string type ,vector_1d out ,vector_1d target)
{
	vector_1d outvec;
	int out_dim=target.size();
	outvec.resize(out_dim);

	if(type == "mse")
		for(int i=0;i<out_dim;i++){ outvec[i] = 0.5*(pow(out[i]-target[i] ,2)); } 
	//else
	return outvec;
}

vector_1d d_cost(string type ,vector_1d out ,vector_1d target)
{
	vector_1d outvec;
	int out_dim=target.size();
	outvec.resize(out_dim);

	if(type == "mse")
		for(int i=0;i<out_dim;i++){ outvec[i] = out[i]-target[i]; } 
	//else
	return outvec;
}

void rand_init()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	srand(hash3(time.tv_sec, time.tv_usec, getpid()));
}
std::vector<int> perm(int SZ)
{
	std::vector<int> perm(SZ);
	for (int i = 0; i < SZ; i++) perm[i] = i;

	// Random order permutation
	for (int i = 0; i < SZ; i++) {
		int j, t;
		j = rand() % (SZ-i) + i;
		t = perm[j]; perm[j] = perm[i]; perm[i] = t; // Swap i and j
	}

	return perm;
}
unsigned int hash3(unsigned int h1, unsigned int h2, unsigned int h3)
{
    return ((h1 * 2654435789U) + h2) * 2654435789U + h3;
}

vector_1d randn(int len)
{
	std::random_device device_random_;
	std::default_random_engine generator_(device_random_());
	std::normal_distribution<> distribution_x_(0.0, 0.01);
	std::vector<double> vector_x_;
	
	for (int counter_(0); counter_ < len; ++counter_)
	{
		vector_x_.push_back(0.1 * distribution_x_(generator_));
	}
	
	return vector_x_;
}

double mean(vector_1d input)
{
	int num_data = input.size();
	double out = 0;
	for(int i=0;i<num_data;i++)
		out += input[i];

	return out/num_data;
}

double stdev(vector_1d input)
{
	int num_data = input.size();
	double out = 0;
	double mean_val = mean(input);
	for(int i=0;i<num_data;i++)
		out += pow((input[i]-mean_val) ,2);

	return sqrt(out/num_data);
}

vector_1d z_score(vector_1d input)
{
	int num_data = input.size();
	vector_1d outvec;
	outvec.resize(num_data);

	double mean_val = mean(input);
	double std_val = stdev(input);

	for(int i=0;i<num_data;i++)
		outvec[i] = (input[i] - mean_val)/std_val;

	return outvec;
}
