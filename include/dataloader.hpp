#ifndef TINYTENSOR_DATALOADER_HPP
#define TINYTENSOR_DATALOADER_HPP

#include <string>
#include "tensor.hpp"
#include "network.hpp"

using namespace std;

vector<Tensor> dataloader(string & datapath);

vector<Tensor> load_MNIST(string & datapath, vector<int> & labels);

Network load_weights(string & datapath);

#endif //TINYTENSOR_DATALOADER_HPP
