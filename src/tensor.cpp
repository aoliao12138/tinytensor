#include "tensor.hpp"
#include <vector>
using namespace std;


Tensor::Tensor(int x, int y, int z) :
        nx(x),ny(y),nz(z),kernel(vector<vector<vector<double> > > (nz, vector<vector<double> >(ny, vector<double>(nx)))) {
}

int Tensor::max_tensor_index() {
    double tmp=kernel[0][0][0];
    int index=0;
    for (int i = 0; i <nz ; ++i) {
        for (int j = 0; j < ny ; ++j) {
            for (int k = 0; k < nx; ++k) {
                if (kernel[i][j][k]>tmp){
                    tmp=kernel[i][j][k];
                    index=k;
                }
            }
        }
    }
    return index;
}