#include <vector>
#include <tensor.hpp>
#include <iostream>
#include "lap_timer.hpp"
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

    int num = 1000;

    swissknife::profiling::LapTimer timer;
    swissknife::profiling::LapHandle lap1 = timer.addLap(std::string("MNIST"));
    timer.start(lap1);

    for (int i = 0; i < num; ++i) {
        Tensor result = Lenet5.eval(images[i]);
        int predict_number = result.max_tensor_index();
        if (predict_number == labels[i]) {
            correct++;
        }
    }

    timer.stop();

    // report
    timer.printSummary(num);

    //cout << "per image: "  << double(endTime - startTime) / CLOCKS_PER_SEC /num << "s" << endl;

    cout << "Accuracy: " << correct / num << endl;
    return 0;
}

