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
void Network::fprop(Tensor &input) {
    for (int i = 0; i < _layers.size(); ++i) {
        input = _layers[i]->calculate(input);
        _layers[i]->result=input;
    }
}

void Network::bprop(vector<int> label, function<double(double, double)> loss, function<double(double, double)> dloss) {
    auto output_layer=_layers[_layers.size()-1];
    for (int i = 0; i <label.size() ; ++i) {
        output_layer->error._kernel[0][0][i]=dloss(output_layer->result._kernel[0][0][i],label[i]);
    }
    Layer * prev_layer= nullptr;
    for (int i = label.size()-1; i >=0 ; --i) {
        _layers[i]->bprop(prev_layer);
        prev_layer=_layers[i];
    }
}

void Network::reset_weights() {
    for (int i = 0; i < _layers.size(); ++i) {
        _layers[i]->reset_dweights();
    }
}

void Network::update_weights(double learning_rate) {
    for (int i = 0; i < _layers.size(); ++i) {
        _layers[i]->update_dweights(learning_rate);
    }
}