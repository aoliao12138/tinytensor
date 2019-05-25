
#ifndef TINYTENSOR_TENSOR_HPP
#define TINYTENSOR_TENSOR_HPP

#include <vector>
using namespace std;

//if it is 2 dimenson then nz is 1;
class Tensor {
    int nx;
    int ny;
    int nz;



public:
    Tensor(int x=1, int y=1, int z=1);

    int get_nx(){
      return nx;
    }
    int get_ny(){
      return ny;
    }
    int get_nz(){
      return nz;
    }

    //double ***kernel;

    //vector<vector<vector<double> > > kernel (nx, vector<vector<double> >(ny, vector<double>(nz)));
    vector<vector<vector<double> > > kernel;
    int max_tensor_index(); //return the max element in the tensor
};




#endif //TINYTENSOR_TENSOR_HPP
