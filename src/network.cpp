#include "network.hpp"

Tensor Network::eval(Tensor &input) {
    for (int i = 0; i < layers.size(); ++i) {
        input=layers[i]->calculate(input);
    }
    return input;
}

Network::~Network() {
    for (int i = 0; i < layers.size(); ++i) {
        delete(layers[i]);
    }
}