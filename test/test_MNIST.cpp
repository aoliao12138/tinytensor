#include <vector>
#include <tensor.hpp>
#include <iostream>
#include "dataloader.hpp"
#include "network.hpp"

using namespace std;

int main(){

    string datapath="/media/yurisa/本地磁盘/Junior/C++/Project/MNIST";
    string weightpath="../../weights";

    vector<int> labels;
    vector<Tensor> images=load_MNIST(datapath, labels);
    Network Lenet5=load_weights();

    double correct=0;

    int num=10000;

    for (int i = 0; i <num ; ++i) {
        Tensor result=Lenet5.eval(images[i]);
        int predict_number=result.max_tensor_index();
        if (predict_number==labels[i]){
          correct++;
        }
    }

    cout<<"Accuracy:"<<correct/num<<endl;

}