#ifndef TINYTENSOR_LAYER_HPP
#define TINYTENSOR_LAYER_HPP

#include "tensor.hpp"
#include <string>

#define CONV 0
#define LINEAR 1
#define POOL 2
#define RELU 3
#define SIGMOID 4
#define TANH 5
#define SOFTMAX 6


using namespace std;

/**
 * @brief base type for layer configures
 */
class Configure {
public:
    virtual ~Configure() = default;
};

/**
 * @brief Configures for a convolution layer
 */
class ConvConfigure: public Configure {
public:
    int _input;
    int _output;
    int _kernel_size;
    int _stride;
    int _padding;

    /**
     * @brief Constructor.
     * @param input_channels input channels of convolution layer
     * @param output_channels output channels of convolution layer
     * @param kernel_size kernel size of the convolution
     * @param stride  controls the stride for the cross-correlation
     * @param padding controls the amount of zero-paddings of the image
     */
    ConvConfigure(int input_channels, int output_channels, int kernel_size
            , int stride=1, int padding=0);
};

/**
 * @brief Configures for a pool layer
 */
class PoolConfigure: public Configure {
public:
    int _kernel_size;
    int _stride;
    int _padding;
    /**
     * @brief Constructor.
     * @param kernel_size kernel size for max pooling
     * @param stride the stride of the window
     * @param padding controls the amount of zero-paddings of the image
     */
    PoolConfigure(int kernel_size, int stride=2, int padding=0);
};

/**
 * @brief Configures for a fully connected layer
 */
class LinearConfigure: public Configure {
public:
    int _input;
    int _output;
    /**
     * @brief Constructor.
     * @param input_features input features of a fully connected layer
     * @param output_features output features of a fully connected layer
     */
    LinearConfigure(int input_features, int output_features);
};


/**
 * @brief base class of different layers.
 */
class Layer {
private:
    /**
     * name of the layer (like conv, linear, relu)
     */
    string _name;

public:
    /**
     * @brief get the name of layer
     * @return the name of layer
     */
    string getName() {
        return _name;
      }
    /**
     * @brief set the name of layer
     * @param name the name you want to call this layer
     */
    void setName(string name) {
        this->_name = name;
      }

    /**
     * @brief Factory method to let the subclass to generate the concerte layer
     * @param mode decide which kind of layer to create
     * @param c configure needed for the layer
     * @return base type pointer of layer
     */
    static Layer *creator(int mode, Configure *c);

    /**
     * @brief calculate the result of the layer
     * @param input output of the last layer
     * @return the input of next layer
     */
    virtual Tensor calculate(Tensor &input)=0;
};

/**
 *@brief convolution layer
 */
class Conv: public Layer {
    /**
     * store some parameters for convolution
     */
    ConvConfigure _confi;

    Tensor error;
    Tensor result;

    vector<double> _bias;
    vector<double> _dbias;

    /**
     * convolution kernel
     */
    vector<Tensor> _kernel;
    vector<Tensor> _dkernel;

    /**
     * @brief padding function for convolution
     * @param x the input that need to pad
     * @param _padding the amount of 0 for one side
     * @return the tensor that has been padded
     */
    Tensor pad(Tensor &x, int _padding);

public:
    /**
     * @brief constructor
     * @param confi parameters for convolution
     */
    Conv(ConvConfigure *confi);

    /**
     * @brief calculate the result of the layer
     * @param input output of the last layer
     * @return the input of next layer
     */
    Tensor calculate(Tensor &input);
    Tensor bprop(Layer * prev);

    void setbias(vector<double> bias);
    /**
     * @brief set the kernel of convolution directly
     * @param x convolution kernel
     */
    void setkernel(vector<Tensor> &x);
};

/**
 * @brief maxpool layer
 */
class MaxPool2d: public Layer {
    /**
     * parameters for pool
     */
    PoolConfigure _confi;

public:
    /**
     * @brief constructor
     * @param confi pooling parameters
     */
    MaxPool2d(PoolConfigure *confi);

    /**
     * @brief calculate the result of the layer
     * @param input output of the last layer
     * @return the input of next layer
     */
    Tensor calculate(Tensor &input);
    Tensor bprop(Layer * prev);
};

/**
 * @brief fully connected layer
 */
class Linear: public Layer {
    /**
     * parameters for fully connected layer
     */
    LinearConfigure _confi;

    vector<double> _bias;
    /**
     * weights for fully connected layer
     */
    Tensor _weights;
public:
    /**
     * @brief constructor
     * @param confi parameters for fully connected layer
     */
    Linear(LinearConfigure *confi);

    /**
    * @brief calculate the result of the layer
    * @param input output of the last layer
    * @return the input of next layer
    */
    Tensor calculate(Tensor &input);

    void setbias(vector<double> bias);
    /**
     * @brief set the kernel of fully connnected layer directly
     * @param x weight for fully connnected layer
     */
    void setkernel(vector<vector<vector<double> > > &x);
};

/**
 * @brief layer for relu calculation
 */
class Relu: public Layer {
public:
    /**
     * @brief constructor.
     */
    Relu();

    /**
    * @brief calculate the result of the layer
    * @param input output of the last layer
    * @return the input of next layer
    */
    Tensor calculate(Tensor &input);
};

/**
 * @brief layer for sigmod calculation
 */
class Sigmoid: public Layer {
public:
    /**
     * constructor
     */
    Sigmoid();

    /**
   * @brief calculate the result of the layer
   * @param input output of the last layer
   * @return the input of next layer
   */
    Tensor calculate(Tensor &input);
};

/**
 * @brief layer for tanh calculation
 */
class Tanh: public Layer {
public:
    /**
     * @brief constructor
     */
    Tanh();

    /**
   * @brief calculate the result of the layer
   * @param input output of the last layer
   * @return the input of next layer
   */
    Tensor calculate(Tensor &input);
};

/**
 * @brief layer for softmax calculation
 */
class Softmax: public Layer {
public:
    /**
     * @brief constructor
     */
    Softmax();

    /**
   * @brief calculate the result of the layer
   * @param input output of the last layer
   * @return the input of next layer
   */
    Tensor calculate(Tensor &input);
};


#endif //TINYTENSOR_LAYER_HPP
