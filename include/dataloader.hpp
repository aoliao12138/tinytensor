#ifndef TINYTENSOR_DATALOADER_HPP
#define TINYTENSOR_DATALOADER_HPP

#include <string>
#include <cstdio>
#include <iostream>
#include "tensor.hpp"
#include "network.hpp"
#include "parameter.hpp"
#include "layer.hpp"

using namespace std;

// the implementation of this class refers to https://github.com/pauldpong/mnist-dataloader
class MNISTData {
public:
	MNISTData(FILE* images, FILE* labels);
	~MNISTData();
	void show(int index);
	Tensor operator[] (int index);
	int label(int index);
	int getSize();
private:
	std::vector<std::vector<int> > _images;
	std::vector<int> _labels;
	int _size;
	int _pixels_in_row;
	int _pixels_in_col;
};

unsigned int& endianSwap(unsigned int &x);

MNISTData load_training_data(string & training_directory);

MNISTData load_test_data(string & test_directory);

// vector<Tensor> dataloader(string & datapath);

vector<Tensor> load_MNIST(string & datapath, vector<int> & labels);

Network load_weights();

#endif //TINYTENSOR_DATALOADER_HPP
