#include "layer_container.h"

layer_nonlin:: layer_nonlin(string tpe,int in ,int out ,double alf)
{
	type=tpe; num_in = in; num_out = out; alfa = alf;

	bias.resize(num_out);
	b_grad.resize(num_out);
	weights.resize(num_in ,vector_1d(num_out));
	w_grad.resize(num_in ,vector_1d(num_out));
}

void layer_nonlin:: zero_grad()
{
	w_grad.resize(num_in ,vector_1d(num_out ,0));
	b_grad.resize(num_out ,0);
}

void layer_nonlin:: set_w(vector_2d wei) // for init.
{
	weights = wei;
}

void layer_nonlin:: set_b(vector_1d bia) // for init.
{
	bias = bia;
}
void layer_nonlin:: set_w()
{
	weights = par_mat_sum(weights ,mat_mul(-alfa/train_sam ,w_grad));
}
void layer_nonlin:: set_b()
{
	bias = par_mat_sum(bias ,mat_mul(-alfa/train_sam ,b_grad));
}
void layer_nonlin:: get_w(vector_2d& wei)
{
	wei = weights;
}
void layer_nonlin:: get_b(vector_1d& bia)
{
	bia = bias;
}
string layer_nonlin:: get_config_string()
{
	return type +":\n(" + to_string(num_in) + " , " + to_string(num_out) + ")\n";
}

vector_1d layer_nonlin:: forward(vector_1d inp)
{
	input = inp;
	output = func(type ,par_mat_sum(par_mat_mul(inp ,weights) ,bias));
	return output;
}

void layer_nonlin:: set_delta_out(vector_1d out)
{
	delta_out = out;
	w_grad = par_mat_sum(w_grad ,par_mat_mul_2d(input, delta_out));
	b_grad = par_mat_sum(b_grad ,delta_out);
}
void layer_nonlin:: set_delta_in() // set delta_in for this layer with respect to delta_out
{
	delta_in = par_mat_mul(par_mat_mul(delta_out ,mat_trans(weights)) ,d_func(type ,input));
}
void layer_nonlin:: get_delta_in(vector_1d& in)
{
	in = delta_in;
}