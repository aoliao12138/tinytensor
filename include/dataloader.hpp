#ifndef TINYTENSOR_DATALOADER_HPP
#define TINYTENSOR_DATALOADER_HPP

#include <string>
#include <cstdio>
#include <iostream>
#include "tensor.hpp"
#include "network.hpp"
#include "layer.hpp"

using namespace std;

// the implementation of this class refers to https://github.com/pauldpong/mnist-dataloader
/**
 * @brief the encapsulation of MNIST Data
 */
class MNISTData {
public:
	/**
	 * @brief the constructor of MNISTData
	 * @param images the compressed images
	 * @param labels the compressed labels
	 */
	MNISTData(FILE* images, FILE* labels);
	/**
	 * @brief deconstructor
	 */
	~MNISTData();
	/**
	 * @brief print the selected image on screeen
	 * @param index the index of the wanted image
	 */
	void show(int index);
	/**
	 * @brief selected the wanted image
	 * @param index the index of the wanted image
	 * @return a tensor contained the wanted image
	 */
	Tensor operator[] (int index);
	/**
	 * @brief get the label of certained image
	 * @param index the index of the wanted image
	 * @return the label of the wanted image
	 */
	int label(int index);
	/**
	 * @brief get the size of the MNISTData
	 * @return number of images in the MNISTData instance
	 */
	int getSize();
private:
	/**
	 * vector of all the images
	 */
	std::vector<std::vector<int> > _images;
	/**
	 * vector of all the labels
	 */
	std::vector<int> _labels;
	/**
	 * indicate how many images in all
	 */
	int _size;
	/**
	 * indicate how many pixels in a row in the images
	 */
	int _pixels_in_row;
	/**
	 * indicate how many pixels in a column in the images
	 */
	int _pixels_in_col;
};

/**
 * @brief transfer from little endian to big endian and vice versa
 * @param x the integar we want to change
 * @return the changed endian number
 */
unsigned int& endianSwap(unsigned int &x);

/**
 * @brief load the training data from MNIST
 * @param training_directory the path to the MNIST directory
 * @return a MNISTData class contained all the images and labels of the training set
 */
MNISTData load_training_data(string & training_directory);

/**
 * @brief load the test data from MNIST
 * @param test_directory the path to the MNIST directory
 * @return a MNISTData class contained all the images and labels of the test set
 */
MNISTData load_test_data(string & test_directory);

/**
 * @brief load MNIST images and labels
 * @param datapath the file path for mnist dataset
 * @param labels the labels for each picture
 * @return picture vector, each picture is a tensor
 */
vector<Tensor> load_MNIST(string & datapath, vector<int> & labels);

/**
 * @brief load Lenet5 pretrain model
 * @return lenet5 network structure
 */
Network load_Lenet_weights();

#endif //TINYTENSOR_DATALOADER_HPP
