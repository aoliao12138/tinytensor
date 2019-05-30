#include <vector>
#include <tensor.hpp>
#include <iostream>
#include "dataloader.hpp"
#include "network.hpp"

using namespace std;

int main(){

    string datapath = "../MNIST";

    vector<int> labels;
    vector<Tensor> images = load_MNIST(datapath, labels);
    Network Lenet5 = load_Lenet_weights();

    double correct = 0;

    int num = 100;

    for (int i = 0; i < num; ++i) {
        Tensor result = Lenet5.eval(images[i]);
        int predict_number = result.max_tensor_index();
        if (predict_number == labels[i]) {
            correct ++;
        }
    }

    cout << "Accuracy: " << correct / num << endl;
    return 0;
}