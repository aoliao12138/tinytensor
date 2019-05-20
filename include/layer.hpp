#ifndef TINYTENSOR_LAYER_HPP
#define TINYTENSOR_LAYER_HPP

#include "tensor.hpp"
#include <string>

using namespace std;

//Factory Method

class Layer{
private:
    string name; //layer name for debug

    virtual Tensor calculate(Tensor & input)=0;

public:
    string getName() {
        return name;
      }

    void setName(string name) {
        this->name = name;
      }
};

class Conv:Layer{
    int _input;
    int _output;
    int _kernel_size;
    int _stride;
    int _padding;
    double _bias;

    Tensor Kernel;

    Conv(int input_channels, int output_channels,int kernel_size, double bias
            , int stride=1, int padding=0);
};

class MaxPool2d:Layer{
    int _kernel_size;
    int _stride;
    int _padding;

    MaxPool2d(int kernel_size,int stride=0,int padding=0);
};

class Linear:Layer{
    int _inputl;
    int _output;
    double _bias;

    Tensor weights;

    Linear(int input_features, int output_features, double bias);
};
class Relu:Layer{
    Relu();
};
 //optional
class Sigmoid:Layer{
    Sigmoid();
};
//optional
class Tanh:Layer{
    Tanh();
};

class Softmax:Layer{
    Softmax();
};

//need to comfirm
class LogSoftmax:Layer{
    LogSoftmax();
};


#endif //TINYTENSOR_LAYER_HPP
