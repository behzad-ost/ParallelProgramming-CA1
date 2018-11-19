#include "def.h"
#include "reader_csv.h"
#include "layer_container.h"

using namespace std;

// Main

int main()
{
	cout<<"Reading csv started\n";
	vector_2d samples ,train_samp ,test_samp;
	vector_1d train_targ ,test_targ;
	csv_reader(1030 ,9 ,samples ,"./data/Concrete_Data.csv");
	cout<<"Reading csv ended\n";
	rand_init();
	
	// data augmentation
	for(int a=0;a<samples.size();a++)
		samples[a] = z_score(samples[a]); // zero scores scale input samples and make mean zero

	// split data to test and train
	train_samp.resize(train_sam ,vector_1d(8));
	train_targ.resize(train_sam);
	test_samp.resize(test_sam ,vector_1d(8));
	test_targ.resize(test_sam);

	for(int i=0;i<train_sam;i++)
		for(int g=0;g<8;g++)
			train_samp[i][g] = samples[i][g];
	for(int i=0;i<test_sam;i++)
		for(int g=0;g<8;g++)
			test_samp[i][g] = samples[i+train_sam][g];
	for(int r=0;r<1030;r++)
		if(r<train_sam)
			train_targ[r] = samples[r][8];
		else
			test_targ[r-train_sam] = samples[r][8];

	// define network
	double alfa = 0.01;
	vector <layer_nonlin*> layers;
	layers.push_back(new layer_nonlin("tanh",8,16,alfa));
	layers.push_back(new layer_nonlin("tanh",16,1,alfa));

	// weights init.
	vector_2d temp;
	temp.resize(8 ,vector_1d(16));
	for(int y=0;y<8;y++)
		temp[y] = randn(16);
	layers[0]->set_w(temp);

	temp.resize(16 ,vector_1d(1));
	for(int y=0;y<8;y++)
		temp[y] = randn(1);
	layers[1]->set_w(temp);

	// print model
	cout<<"\nmodel:\n";
	for(int i=0;i<layers.size();i++)
		cout<< layers[i] -> get_config_string();

  	// training start
	int epochs = 20;

	vector_1d tempout ,delta_last ,out ,out_test;
	out.resize(train_sam);
	out_test.resize(test_sam);
	cout<<"\ntrain cost test cost\n";
	for(int e=0;e<epochs;e++)
	{	
		layers[0]->zero_grad();
		layers[1]->zero_grad();
		for(int t=0;t<train_sam;t++)
		{
			tempout = layers[0]->forward(train_samp[t]);
			tempout = layers[1]->forward(tempout);
			out[t] = tempout[0];
			delta_last = d_cost("mse", tempout, vector_1d(1 ,train_targ[t]));
			layers[1]->set_delta_out(par_mat_mul(delta_last,d_func("tanh",tempout)));
			layers[1]->set_delta_in();
			layers[1]->get_delta_in(delta_last);
			layers[0]->set_delta_out(delta_last);
		}
		layers[1]->set_w();
		layers[1]->set_b();  		
		layers[0]->set_w();
		layers[0]->set_b();  
		// calculate train and test cost
		cout<< mean(cost("mse" ,out ,train_targ))<<" ";
		for(int q=0;q<test_sam;q++)
		{
			tempout = layers[0]->forward(test_samp[q]);
			tempout = layers[1]->forward(tempout);
			out_test[q] = tempout[0];
		}
		cout<< mean(cost("mse" ,out_test ,test_targ))<<"\n";
	}
	return 0;
}