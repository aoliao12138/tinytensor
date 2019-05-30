#include "dataloader.hpp"
#include "network.hpp"

#include <tensor.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <istream>
#include <sstream>
#include <cmath>

using namespace std;

std::vector<std::vector<int> > load_hand_written_data();

Tensor generate_test_tensor(std::vector<std::vector<int> > image);

int main() {
    string datapath = "../MNIST";

    vector<int> labels;
    vector<Tensor> images = load_MNIST(datapath, labels);
    Network Lenet5 = load_Lenet_weights();

    std::vector<std::vector<int> > image = load_hand_written_data();
	Tensor image_tensor = generate_test_tensor(image);

    Tensor result = Lenet5.eval(image_tensor);
    int predict_number = result.max_tensor_index();

    cout << "your input image: " << endl;
    for (auto x : image) {
        for (auto y : x) {
            if (y > 0) cout << "0 ";
            else cout << "* ";
        }
        cout << endl;
    }

    cout << "predict_number: " << predict_number << endl;
	return 0;
}


std::vector<std::vector<int> > load_hand_written_data() {
    std::vector<std::vector<int> > image;
    for (int i = 0; i < 28; ++i) {
        std::vector<int> row(28);
        image.push_back(row);
    }
    ifstream fin("../data.txt");
    string input;
    bool tiktok = true;
    bool first = true;
    int x;
    int y;
    while(fin >> input) {
        if (tiktok) {
            x = std::atoi(input.c_str());

            tiktok = false;
        } else {
            stringstream ss(input);
            ss >> y;
            tiktok = true;
            if (first) {
                first = false;
                continue;
            }
            image[y][x] = 255;
        }
    }
    return image;
}

Tensor generate_test_tensor(std::vector<std::vector<int> > image) {
    Tensor image_tensor = Tensor(28, 28, 1);
    std::vector<std::vector<std::vector<double> > > kernel_vec;
    std::vector<std::vector<double> > my_image;
    std::vector<double> row;
    int pixel_count = 0;
    for (auto x : image) {
        if (pixel_count % 28 == 0 && row.size() == 28) {
            my_image.push_back(row);
            row.clear();
        }
        for (auto y : x) {
            row.push_back(y);
            pixel_count ++;
        }
    }
    my_image.push_back(row);
    kernel_vec.push_back(my_image);
    image_tensor.set_kernel(kernel_vec);
    return image_tensor;
}