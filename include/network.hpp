#ifndef TINYTENSOR_NETWORK_HPP
#define TINYTENSOR_NETWORK_HPP

#include "layer.hpp"
#include <vector>

using namespace std;

class Network{
    Network();

    Network(vector<layer*> & ls);

    void add_layer(layer & l){
      layers.push_back(&l);
    }

    Tensor run(Tensor & input); //run the network, iteratively use calculate function in the layer

private:
    vector<layer*> layers;
};




#endif //TINYTENSOR_NETWORK_HPP
