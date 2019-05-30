#include <vector>
#include <tensor.hpp>
#include <iostream>
#include <ctime>
#include "dataloader.hpp"
#include "network.hpp"
#include "omp.h"

using namespace std;

int main() {
    string datapath = "../MNIST";

    vector<int> labels;
    vector<Tensor> images = load_MNIST(datapath, labels);
    Network Lenet5 = load_Lenet_weights();

    double correct = 0;

    int num = 10000;

    clock_t startTime = clock();
    #pragma omp parallel for
    for (int i = 0; i < num; ++i) {
        Tensor result = Lenet5.eval(images[i]);
        int predict_number = result.max_tensor_index();
        if (predict_number == labels[i]) {
            correct ++;
        }
    }
    clock_t endTime = clock();
    cout << "per image: "  << double(endTime - startTime) / CLOCKS_PER_SEC /num << "s" << endl;

    cout << "Accuracy: " << correct / num << endl;
    return 0;
}

