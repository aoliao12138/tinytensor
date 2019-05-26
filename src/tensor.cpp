#include "tensor.hpp"
#include <vector>
using namespace std;


Tensor::Tensor(int x, int y, int z)
: _nx(x), _ny(y), _nz(z) {}

int Tensor::get_nx() {
    return _nx;
}

int Tensor::get_ny() {
    return _ny;
}
int Tensor::get_nz() {
    return _nz;
}

void Tensor::set_kernel(vector<vector<vector<double> > > my_kernel) {
	_kernel = my_kernel;
}