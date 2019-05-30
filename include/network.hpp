#ifndef TINYTENSOR_NETWORK_HPP
#define TINYTENSOR_NETWORK_HPP

#include "layer.hpp"
#include <vector>
#include <functional>


using namespace std;
/**
 * @brief The network class is to store the structure of the neural network. Also, it can calculate the
 * result of the network.
 */
class Network {
public:
    /**
     * @brief destructor
     */
    ~Network();
    /**
     * @brief Add a layer for the neural network
     * @param l A concrete layer pointer inherit from Layer class
     */
    void add_layer(Layer *l) {
      _layers.push_back(l);
    }

    /**
     * @brief Response function: calculate the result of the neural network
     * @param input A tensor store one picture with many channels or some pictures.
     * @return the output vector(layer)
     */
    Tensor eval(Tensor &input); //run the network, iteratively use calculate function in the layer
    void train(vector<Tensor> images, double learing_rate,int batch_size);
    void fprop();
    void bprop(vector<int> label,std::function<double(double,double) > loss=[](double y, double t){return (y - t) * (y - t) / 2;}); //maybe classification
    void reset_weights();
    void update_weights(double learning_rate);

    /**
     * A layer pointer vector to store different types of layers and dynamic change layers of the network.
     */
    vector<Layer *> _layers;
};




#endif //TINYTENSOR_NETWORK_HPP
