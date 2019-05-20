
#ifndef TINYTENSOR_TENSOR_HPP
#define TINYTENSOR_TENSOR_HPP

#include <vector>
using namespace std;

class Tensor {
    int nx;
    int ny;
    int nz;



public:
    Tensor(int x, int y, int z);
    ~Tensor();

    int get_nx(){
      return nx;
    }
    int get_ny(){
      return ny;
    }
    int get_nz(){
      return nz;
    }

    double ***kernel;
    //compile error wth?
    //vector<vector<vector<double> > > kernel (nx, vector<vector<double> >(ny, vector<double>(nz)));
};




#endif //TINYTENSOR_TENSOR_HPP
