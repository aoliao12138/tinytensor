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
public:
    virtual ~Configure()= default;
};

class ConvConfigure: public Configure{
public:
    int _input;
    int _output;
    int _kernel_size;
    int _stride;
    int _padding;
    vector<double> _bias;

    ConvConfigure(int input_channels, int output_channels,int kernel_size, vector<double> bias
            , int stride=1, int padding=0);
};

class PoolConfigure: public Configure{
public:
    int _kernel_size;
    int _stride;
    int _padding;
    PoolConfigure(int kernel_size,int stride=2,int padding=0);
};

class LinearConfigure: public Configure{
public:
    int _input;
    int _output;
    vector<double> _bias;
    LinearConfigure(int input_features, int output_features, vector<double> bias);
};

//Factory Method

class Layer{
private:
    string name; //layer name for debug


public:
    string getName() {
        return name;
      }

    void setName(string name) {
        this->name = name;
      }

    static Layer * creator(int mode, Configure *c );

    virtual Tensor calculate(Tensor & input)=0;
};

class Conv: public Layer{
    ConvConfigure _confi;

    vector<Tensor> kernel;

    Tensor pad(Tensor& x,int _padding);

public:
    Conv(ConvConfigure *confi);

    Tensor calculate(Tensor & input);

    void setkernel( vector<Tensor> & x);
};

class MaxPool2d: public Layer{
    PoolConfigure _confi;

public:
    MaxPool2d(PoolConfigure *confi);

    Tensor calculate(Tensor & input);
};

class Linear: public Layer{
    LinearConfigure _confi;

    Tensor weights;
public:
    Linear(LinearConfigure *confi);

    Tensor calculate(Tensor & input);

    void setkernel(vector<vector<vector<double> > > & x);
};
class Relu: public Layer{
public:
    Relu();

    Tensor calculate(Tensor & input);
};
 //optional
class Sigmoid: public Layer{
public:
    Sigmoid();

    Tensor calculate(Tensor & input);
};
//optional
class Tanh: public Layer{
public:
    Tanh();

    Tensor calculate(Tensor & input);
};

class Softmax: public Layer{
public:
    Softmax();

    Tensor calculate(Tensor & input);
};

//need to comfirm
class LogSoftmax: public Layer{
public:
    LogSoftmax();

    Tensor calculate(Tensor & input);
};


#endif //TINYTENSOR_LAYER_HPP
