#include <vector>
#include <tensor.hpp>
#include <iostream>
#include "dataloader.hpp"
#include "network.hpp"

using namespace std;

int main(){

  string datapath="../../MNIST";
  string weightpath="../../weights";

  vector<int> labels;
  vector<Tensor> images=load_MNIST(datapath, labels);
  Network Lenet5=load_weights(weightpath);

  double correct=0;

  for (int i = 0; i <images.size() ; ++i) {
    Tensor result=Lenet5.eval(images[i]);
    int predict_number=result.max_tensor_index();
    if (predict_number==labels[i]){
      correct++;
    }
  }

  cout<<"Accuracy:"<<correct/images.size()<<endl;

}