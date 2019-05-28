#include "tensor.hpp"
#include <vector>
using namespace std;

Tensor::Tensor(int x, int y, int z) :
        _nx(x),_ny(y),_nz(z) {
}

Tensor::Tensor(int x, int y, int z,int mode) :
        _nx(x),_ny(y),_nz(z) {
    vector<vector<vector<double > > > k;
    for (int i = 0; i < _nz; ++i) {
        vector<vector<double> > m;
        for (int j = 0; j < _ny; ++j) {
            vector<double> v(_nx,0);
            m.push_back(v);
        }
        k.push_back(m);
    }
    _kernel=k;

}

int Tensor::max_tensor_index() {
    double tmp=_kernel[0][0][0];
    int index=0;
    for (int i = 0; i <_nz ; ++i) {
        for (int j = 0; j < _ny ; ++j) {
            for (int k = 0; k < _nx; ++k) {
                if (_kernel[i][j][k]>tmp){
                    tmp=_kernel[i][j][k];
                    index=k;
                }
            }
        }
    }
    return index;
}

int Tensor::get_nx() {
    return _nx;
}

int Tensor::get_ny() {
    return _ny;
}
int Tensor::get_nz() {
    return _nz;
}

void Tensor::set_kernel(vector<vector<vector<double> > > &my_kernel) {
	_kernel = my_kernel;
}