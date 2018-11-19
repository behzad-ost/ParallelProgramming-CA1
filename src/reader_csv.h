#include "def.h"
#include <fstream>

using namespace std;

// csv Reader

void csv_reader(int numofin, int numoffeat, vector_2d &arr,char* addr)
{
  vector <vector <string> > data;
  ifstream infile( addr );

  while (infile)
  {
    string s;
    if (!getline( infile, s )) break;

    istringstream ss( s );
    vector <string> record;

    while (ss)
    {
      string s;
      if (!getline( ss, s, ',' )) break;
      record.push_back( s );
    }

    data.push_back( record );
  }
  if (!infile.eof())
  {
    cerr << "Error!\n";
  }

arr.resize(numofin ,vector_1d(numoffeat));
for(int q=0;q<numofin;q++)
    for(int w=0;w<numoffeat;w++)
        arr[q][w] = std::stod(data[q][w]);
}