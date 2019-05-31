#include "omp.h"
#include "layer.hpp"
#include <vector>
#include <cmath>

using namespace std;

double gradient_descent(double W, double dW, double alpha, double lambda) {
    return W - alpha * (dW + lambda * W);
}

ConvConfigure::ConvConfigure(int input_channels, int output_channels, int kernel_size,  int stride,
                             int padding): _input(input_channels), _output(output_channels),
                             _kernel_size(kernel_size), _stride(stride), _padding(padding){
}

PoolConfigure::PoolConfigure(int kernel_size, int stride, int padding): _kernel_size(kernel_size),
                            _stride(stride), _padding(padding){
}

LinearConfigure::LinearConfigure(int input_features, int output_features):
                            _input(input_features), _output(output_features){
}

Layer* Layer::creator(int mode, Configure *c) {
    if (mode == 0) {
        ConvConfigure *confi = dynamic_cast<ConvConfigure *>(c);
        return new Conv(confi);
    }
    else if (mode == 1) {
        LinearConfigure *confi = dynamic_cast<LinearConfigure *>(c);
        return new Linear(confi);
    }
    else if (mode == 2) {
        PoolConfigure *confi = dynamic_cast<PoolConfigure*>(c);
        return new MaxPool2d(confi);
    }
    else if (mode == 3) {
        return new Relu();
    }
    else if (mode == 4) {
        return new Sigmoid();
    }
    else if (mode == 5) {
        return new Tanh();
    }
    else if (mode == 6) {
        return new Softmax();
    }
    return nullptr;
}


Conv::Conv(ConvConfigure *confi): _confi(*confi) {
    setName("Conv");
    for (int i = 0; i < _confi._output ;++i) {
        _kernel.push_back(Tensor(_confi._kernel_size, _confi._kernel_size, _confi._input));
    }
}

void Conv::setkernel(vector<Tensor> &x) {
    _kernel=x;
}

MaxPool2d::MaxPool2d(PoolConfigure *confi): _confi(*confi) {
    setName("MaxPool2d");
}

Linear::Linear(LinearConfigure *confi): _confi(*confi) {
    setName("Linear");
    Tensor tmp (1, _confi._output, _confi._input);
    _weights = tmp;
}

void Linear::setkernel(vector<vector<vector<double> > > &x) {

    _weights.set_kernel(x);
}

Relu::Relu() {
    setName("Relu");
}

Sigmoid::Sigmoid() {
    setName("Sigmod");
}

Tanh::Tanh() {
    setName("Tanh");
}

Softmax::Softmax() {
    setName("Softmax");
}

Tensor Conv::calculate(Tensor &input) {
    int result_nx = (input.get_nx() + 2 * _confi._padding - _confi._kernel_size) / _confi._stride + 1;
    int result_ny = (input.get_ny() + 2 * _confi._padding - _confi._kernel_size) / _confi._stride + 1;
    Tensor result(result_nx, result_ny, _confi._output, 0);
    if (_confi._padding!=0) {
        input = pad(input, _confi._padding);
    }
    #pragma omp parallel for
    for (int i = 0; i < _confi._output; ++i) {
        for (int j = 0; j < result_ny; ++j) {
            for (int k = 0; k < result_nx; ++k) {
                double tmp =_bias[i];
                for (int n = 0; n < _kernel[i].get_nz(); ++n) {
                    for (int l = 0; l < _kernel[i].get_ny(); ++l) {
                        for (int m = 0; m < _kernel[i].get_nx(); ++m) {
                            tmp += _kernel[i]._kernel[n][l][m] *
                                   input._kernel[n][l + j * _confi._stride][m + k * _confi._stride];
                        }
                    }
                }
                result._kernel[i][j][k] = tmp;
            }
        }
    }

    return result;
}

Tensor Conv::pad(Tensor &x, int _padding) {
    vector<vector<vector<double > > > result;
    for (int i = 0; i < x.get_nz(); ++i) {
        vector<vector<double> > matrix;
        for (int j = 0; j < x.get_ny() + 2 * _padding; ++j) {
            if (j < _padding || j >= x.get_ny() + _padding) {
                vector<double> v(x.get_nx() + 2 * _padding, 0);
                matrix.push_back(v);
            }
            else{
                vector<double > v;
                for (int k = 0; k < x.get_nx() + 2 * _padding; ++k) {
                    if (k < _padding || k >= x.get_nx() + _padding) {
                        v.push_back(0);
                    }
                    else{
                        v.push_back(x._kernel[i][j - _padding][k - _padding]);
                    }
                }
                matrix.push_back(v);
            }
        }
        result.push_back(matrix);
    }
    Tensor r;
    r.set_kernel(result);
    return r;
}

Tensor MaxPool2d::calculate(Tensor &input) {
    int result_nx = input.get_nx() / 2;
    int result_ny = input.get_ny() / 2;
    Tensor result(result_nx, result_ny, input.get_nz(), 0);
    #pragma omp parallel for
    for (int i = 0; i < input.get_nz(); ++i) {
        for (int j = 0; j < result_ny; ++j) {
            for (int k = 0; k < result_nx; ++k) {
                double tmp = max(input._kernel[i][2 * j][2 * k], input._kernel[i][2 * j + 1][2 * k]);
                tmp = max(tmp, input._kernel[i][2 * j][2 * k + 1]);
                tmp = max(tmp, input._kernel[i][2 * j + 1][2 * k + 1]);
                result._kernel[i][j][k] = tmp;
            }
        }
    }
    return result;
}

Tensor Linear::calculate(Tensor &input) {
    Tensor result(_confi._output, 1, 1, 0);
    if (input.get_nz() != 1) {
        int tmpx = input.get_nx();
        int tmpy = input.get_ny();
        int tmpz = input.get_nz();
        #pragma omp parallel for
        for (int l = 0; l < _confi._output; ++l) {
            result._kernel[0][0][l] = _bias[l];
            for (int i = 0; i < tmpz; ++i) {
                for (int j = 0; j < tmpy; ++j) {
                    for (int k = 0; k < tmpx; ++k) {
                        result._kernel[0][0][l] += input._kernel[i][j][k] * _weights._kernel[0][l][k + tmpx * j + tmpy * tmpx * i];
                    }
                }
            }
        }
        return result;
    } 
    else{
        #pragma omp parallel for
        for (int i = 0; i < _confi._output; ++i) {
            result._kernel[0][0][i] = _bias[i];
            for (int j = 0; j < input.get_nx(); ++j) {
                result._kernel[0][0][i] += input._kernel[0][0][j] * _weights._kernel[0][i][j];
            }
        }
        return result;
    }
}

Tensor Relu::calculate(Tensor &input) {
    #pragma omp parallel for
    for (int i = 0; i < input.get_nz(); ++i) {
        for (int j = 0; j < input.get_ny(); ++j) {
            for (int k = 0; k < input.get_nx(); ++k) {
                input._kernel[i][j][k] = max(0.0, input._kernel[i][j][k]);
            }
        }
    }
    return input;
}

Tensor Sigmoid::calculate(Tensor &input) {
    #pragma omp parallel for
    for (int i = 0; i < input.get_nz(); ++i) {
        for (int j = 0; j < input.get_ny(); ++j) {
            for (int k = 0; k < input.get_nx(); ++k) {
                input._kernel[i][j][k] = 1 / (1 + exp(-input._kernel[i][j][k]));
            }
        }
    }
    return input;
}

Tensor Tanh::calculate(Tensor &input) {
    #pragma omp parallel for
    for (int i = 0; i < input.get_nz(); ++i) {
        for (int j = 0; j < input.get_ny(); ++j) {
            for (int k = 0; k < input.get_nx(); ++k) {
                input._kernel[i][j][k] = (exp(input._kernel[i][j][k]) - exp(-input._kernel[i][j][k]))
                                        /(exp(input._kernel[i][j][k]) + exp(-input._kernel[i][j][k]));
            }
        }
    }
    return input;
}

Tensor Softmax::calculate(Tensor &input) {
    //1 dimensional
    double sum = 0;
    #pragma omp parallel for
    for (int i = 0; i < input.get_nx(); ++i) {
        sum += exp(input._kernel[0][0][i]);
    }
    #pragma omp parallel for
    for (int j = 0; j < input.get_nx(); ++j) {
        input._kernel[0][0][j] = exp(input._kernel[0][0][j]) / sum;
    }
    return input;
}

void Conv::bprop(Layer *prev) {
    //delta

}

void MaxPool2d::bprop(Layer *prev) { //max be max, others be 0

    #pragma omp parallel for
    for (int i = 0; i < prev->result.get_nz(); ++i) {
        for (int j = 0; j < prev->result.get_ny(); ++j) {
            for (int k = 0; k < prev->result.get_nx(); ++k) {
                if (prev->result._kernel[i][j][k]==result._kernel[i][j/2][k/2]){
                    prev->error._kernel[i][j][k]=error._kernel[i][j/2][k/2];
                }else{
                    prev->error._kernel[i][j][k]=0;
                }
            }
        }
    }
}

void Linear::bprop(Layer *prev) {
    if (prev->result.get_nx()==1 && prev->result.get_ny()==1){ //linear
        int output_dim=prev->result.get_nx();
        for (int i = 0; i <output_dim ; ++i) {
            prev->error._kernel[0][0][i]=0;
            for (int j = 0; j <_confi._output ; ++j) {
                prev->error._kernel[0][0][i]+=error._kernel[0][0][j]*_weights._kernel[0][i][j];
            }
        }
        //update delta w
        for (int i = 0; i <output_dim ; ++i) {
            for (int j = 0; j <_confi._output ; ++j) {
                _dweights._kernel[0][i][j]+=error._kernel[0][0][j]*prev->result._kernel[0][0][i];

            }
        }
        //update delta bias
        for (int k = 0; k <_bias.size() ; ++k) {
            _dbias[k]+=error._kernel[0][0][k];
        }
    }

}

void Relu::bprop(Layer *prev) {
#pragma omp parallel for
    for (int i = 0; i < error.get_nz(); ++i) {
        for (int j = 0; j < error.get_ny(); ++j) {
            for (int k = 0; k < error.get_nx(); ++k) {
                if (result._kernel[i][j][k]==0){
                    prev->error._kernel[i][j][k]=0;
                }else{
                    prev->error._kernel[i][j][k]=result._kernel[i][j][k];
                }
            }
        }
    }
}

