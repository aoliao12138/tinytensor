
#ifndef TINYTENSOR_TENSOR_HPP
#define TINYTENSOR_TENSOR_HPP

#include <vector>
using namespace std;

/** \brief Tensor is a basic computation data structure in the neural network.
 */
class Tensor {
public:
    Tensor(int x=1, int y=1, int z=1);
    Tensor(int x, int y, int z,double num);
    int get_nx();
    int get_ny();
    int get_nz();
    void set_kernel(vector<vector<vector<double> > > & my_kernel);
    int max_tensor_index(); //return the max element in the tensor

    vector<vector<vector<double> > > _kernel;
private:
    int _nx;
    int _ny;
    int _nz;
};




#endif //TINYTENSOR_TENSOR_HPP
