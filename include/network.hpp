#ifndef TINYTENSOR_NETWORK_HPP
#define TINYTENSOR_NETWORK_HPP

#include "layer.hpp"
#include <vector>

using namespace std;

class Network{
public:

    void add_layer(Layer * l){
      layers.push_back(l);
    }

    Tensor eval(Tensor & input); //run the network, iteratively use calculate function in the layer

private:
    vector<Layer*> layers;
};




#endif //TINYTENSOR_NETWORK_HPP
