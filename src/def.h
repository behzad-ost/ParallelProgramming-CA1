#ifndef DEF_H
#define DEF_H

#include <iostream>
#include <stdlib.h>     // srand, rand
#include <vector>
#include <string>
#include <sstream>
#include <sys/time.h>	// time -> gettimeofday
#include <unistd.h>		// getpid

#include <random> // gausian random
#include <iomanip> // gausian random

using namespace std;

typedef vector<double> vector_1d;
typedef vector<vector_1d> vector_2d;

#define train_sam 700
#define test_sam 330


#endif /* DEF_H */