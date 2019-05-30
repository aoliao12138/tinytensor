#include "network.hpp"

Tensor Network::eval(Tensor &input) {
    for (int i = 0; i < _layers.size(); ++i) {
        input = _layers[i]->calculate(input);
    }
    return input;
}

Network::~Network() {
    for (int i = 0; i < _layers.size(); ++i) {
        delete(_layers[i]);
    }
}