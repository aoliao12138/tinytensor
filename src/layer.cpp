#include "layer.hpp"
#include <vector>

using namespace std;

ConvConfigure::ConvConfigure(int input_channels, int output_channels, int kernel_size, vector<double> bias, int stride,
                             int padding): _input(input_channels), _output(output_channels),
                             _kernel_size(kernel_size),_stride(stride),_padding(padding),_bias(bias){
}

PoolConfigure::PoolConfigure(int kernel_size, int stride, int padding): _kernel_size(kernel_size),
                            _stride(stride),_padding(padding){
}

LinearConfigure::LinearConfigure(int input_features, int output_features, vector<double> bias):
                            _input(input_features),_output(output_features),_bias(bias){
}

Layer* Layer::creator(int mode, Configure *c) {
    if (mode == 0){
        ConvConfigure *confi=dynamic_cast<ConvConfigure *>(c);
        return new Conv(confi);
    }else if (mode == 1){
        LinearConfigure *confi= dynamic_cast<LinearConfigure *>(c);
        return new Linear(confi);
    }else if (mode == 2){
        PoolConfigure *confi= dynamic_cast<PoolConfigure*>(c);
        return new MaxPool2d(confi);
    }else if (mode == 3){
        return new Relu();
    }
}


Conv::Conv(ConvConfigure *confi): _confi(*confi) {
    setName("Conv");
    for (int i = 0; i < _confi._output ; ++i) {
        kernel.push_back(Tensor(_confi._kernel_size,_confi._kernel_size,_confi._input));
    }
}

MaxPool2d::MaxPool2d(PoolConfigure *confi): _confi(*confi) {
    setName("MaxPool2d");
}

Linear::Linear(LinearConfigure *confi): _confi(*confi) {
    setName("Linear");
    Tensor tmp (1,_confi._output,_confi._input);
    weights=tmp;
}

Relu::Relu() {
    setName("Relu");
}


Tensor Conv::calculate(Tensor &input) {
    int result_nx = (input.get_nx() + 2 * _confi._padding - _confi._kernel_size) / _confi._stride + 1;
    int result_ny = (input.get_ny() + 2 * _confi._padding - _confi._kernel_size) / _confi._stride + 1;
    Tensor result(result_nx,result_ny,_confi._output);
    if (_confi._padding==0) {
        for (int i = 0; i < _confi._output; ++i) {
            for (int j = 0; j < result_ny; ++j) {
                for (int k = 0; k < result_nx; ++k) {
                    double tmp = _confi._bias[i];
                    for (int n = 0; n < kernel[i].get_nz(); ++n) {
                        for (int l = 0; l < kernel[i].get_ny(); ++l) {
                            for (int m = 0; m < kernel[i].get_nx(); ++m) {
                                tmp += kernel[i]._kernel[n][l][m] *
                                       input._kernel[n][l + j * _confi._stride][m + k * _confi._stride];
                            }
                        }
                    }
                    result._kernel[i][j][k] = tmp;
                }
            }
        }
    }
    return result;
}
Tensor MaxPool2d::calculate(Tensor &input) {
    int result_nx = input.get_nx() / 2;
    int result_ny = input.get_ny() / 2;
    Tensor result(result_nx,result_ny,input.get_nz());

    for (int i = 0; i <input.get_nz() ; ++i) {
        for (int j = 0; j <result_ny ; ++j) {
            for (int k = 0; k <result_nx ; ++k) {
                double tmp = max(input._kernel[i][2*j][2*k], input._kernel[i][2*j+1][2*k]);
                tmp = max(tmp,input._kernel[i][2*j][2*k+1]);
                tmp = max(tmp,input._kernel[i][2*j+1][2*k+1]);
                result._kernel[i][j][k] = tmp;
            }
        }
    }
    return result;
}

Tensor Linear::calculate(Tensor &input) {
    Tensor result(weights.get_nx(),1,1);
    if (input.get_nz()!=1) {
        int tmpx = input.get_nx();
        int tmpy = input.get_ny();
        int tmpz = input.get_nz();
        for (int l = 0; l < weights.get_ny(); ++l) {
            result._kernel[0][0][l]=_confi._bias[l];
            for (int i = 0; i < tmpz; ++i) {
                for (int j = 0; j < tmpy; ++j) {
                    for (int k = 0; k < tmpx; ++k) {
                        result._kernel[0][0][l] += input._kernel[i][j][k] * weights._kernel[0][l][k+tmpx*j+tmpy*i];
                    }
                }
            }
        }
        return result;
    } else{
        //tmpy=1;
        for (int i = 0; i < weights.get_ny(); ++i) {
            result._kernel[0][0][i]=_confi._bias[i];
            for (int j = 0; j < input.get_nx(); ++j) {
                result._kernel[0][0][i] += input._kernel[0][0][j] * weights._kernel[0][i][j];
            }
        }
        return result;
    }
}

Tensor Relu::calculate(Tensor &input) {
    Tensor result(input.get_nx(),input.get_ny(),input.get_nz());
    for (int i = 0; i <result.get_nz() ; ++i) {
        for (int j = 0; j <result.get_ny() ; ++j) {
            for (int k = 0; k <result.get_nx() ; ++k) {
                result._kernel[i][j][k] = max(0.0, input._kernel[i][j][k]);
            }
        }
    }
    return result;
}
