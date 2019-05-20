#ifndef TINYTENSOR_LAYER_HPP
#define TINYTENSOR_LAYER_HPP

#include "tensor.hpp"
//Factory Method

class Layer{
private:
    String name; //layer name for debug

    virtual Tensor calculate(Tensor & input)=0;

public:
    String getName() {
        return name;
      }

    void setName(String name) {
        this.name = name;
      }
};

class Conv::Layer{
    int _input;
    int _output;
    int _kernel_size;
    int _stride;
    int _padding;
    double _bias;

    Tensor Kernel;

    Conv(int input_channels, int output_channels,int kernel_size, int stride=1,
            int padding=0, double bias);
};

class MaxPool2d:Layer{
    int _kernel_size;
    int _stride;
    int _padding;

    void MaxPool2d(int kernel_size,int stride=0,int padding=0);
};

class Linear::Layer{
    int _inputl;
    int _output;
    double _bias;

    Tensor weights;

    Linear(int input_features, int output_features, double bias);
};
class Relu::layer{
    Relu();
};
 //optional
class Sigmoid::layer{
    Sigmoid();
};
//optional
class Tanh::layer{
    Tanh();
};

class Softmax::layer{
    Softmax();
};

//need to comfirm
class LogSoftmax::layer{
    LogSoftmax();
};


#endif //TINYTENSOR_LAYER_HPP
