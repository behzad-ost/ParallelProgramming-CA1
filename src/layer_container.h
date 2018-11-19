#ifndef LAYER_CONTAINER_H
#define LAYER_CONTAINER_H

#include "def.h"
#include "math_2.h"

using namespace std;

//----------------------------layer_nonlin
// All non linear layers are defined here
// type , in_dim , out_dim

class layer_nonlin
{
	string type;
	int num_out ,num_in;
	double alfa;
	vector_2d weights ,w_grad;
	vector_1d bias ,b_grad ,input ,output;

	vector_1d delta_in ,delta_out;

public:

	layer_nonlin(string ,int ,int ,double);
	void zero_grad();
	void set_w(vector_2d);
	void set_b(vector_1d);
	void set_w();
	void set_b();
	void get_w(vector_2d&);
	void get_b(vector_1d&);
	string get_config_string();
	vector_1d forward(vector_1d);
	void set_delta_out(vector_1d);
	void set_delta_in();
	void get_delta_in(vector_1d&);
};

#endif /* LAYER_CONTAINER_H */