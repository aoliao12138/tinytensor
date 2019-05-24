#ifndef TINYTENSOR_LAYER_HPP
#define TINYTENSOR_LAYER_HPP

#include "tensor.hpp"
#include <string>

#define CONV 0
#define LINEAR 1
#define POOL 2
#define RELU 3
#define SIGMOD 4
#define TANH 5
#define SOFTMAX 6


using namespace std;

class Configure{
};

class ConvConfigure: Configure{
    int _input;
    int _output;
    int _kernel_size;
    int _stride;
    int _padding;
    double _bias;

public:
    ConvConfigure(int input_channels, int output_channels,int kernel_size, double bias
            , int stride=1, int padding=0);
};

class PoolConfigure: Configure{
    int _kernel_size;
    int _stride;
    int _padding;
public:
    PoolConfigure(int kernel_size,int stride=0,int padding=0);
};

class LinearConfigure: Configure{
    int _input;
    int _output;
    double _bias;
public:
    LinearConfigure(int input_features, int output_features, double bias);
};

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

    Layer * creator(int mode, Configure *c );

    Layer * creator(int mode, Configure &c, Tensor &t);
};

class Conv: Layer{
    ConvConfigure _confi;

    Tensor kernel;
public:
    Conv(ConvConfigure *confi);
};

class MaxPool2d: Layer{
    PoolConfigure _confi;

public:
    MaxPool2d(PoolConfigure *confi);
};

class Linear: Layer{
    LinearConfigure _confi;

    Tensor weights;
public:
    Linear(LinearConfigure &confi);
};
class Relu: Layer{
public:
    Relu();
};
 //optional
class Sigmoid: Layer{
public:
    Sigmoid();
};
//optional
class Tanh: Layer{
public:
    Tanh();
};

class Softmax: Layer{
public:
    Softmax();
};

//need to comfirm
class LogSoftmax: Layer{
public:
    LogSoftmax();
};


#endif //TINYTENSOR_LAYER_HPP
