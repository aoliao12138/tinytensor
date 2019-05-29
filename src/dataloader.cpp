#include "dataloader.hpp"
#include "para.hpp"

unsigned int& endianSwap(unsigned int &x) {
    x = (x>>24)|((x<<8)&0x00FF0000)|((x>>8)&0x0000FF00)|(x<<24);
    return x;
}

MNISTData::MNISTData(FILE* images, FILE* labels) {
    unsigned int magic_number = 0;
    unsigned int num_images = 0;
    unsigned int num_labels = 0;
    unsigned int rows = 0;
    unsigned int columns = 0;
    unsigned char pixel_value;
    unsigned char label;

    fread(&magic_number, sizeof(int), 1, images);
    endianSwap(magic_number);
    fread(&num_images, sizeof(int), 1, images);
    endianSwap(num_images);
    cout << "Number of images: " << num_images << endl;
    fread(&rows, sizeof(int), 1, images);
    fread(&columns, sizeof(int), 1, images);
    fread(&magic_number, sizeof(int), 1, labels);
    endianSwap(magic_number);
    fread(&num_labels, sizeof(int), 1, labels);
    endianSwap(num_labels);
    if (num_labels == num_images) {
        _pixels_in_row = endianSwap(rows);
        _pixels_in_col = endianSwap(columns);
        _size = num_images;
        _images = std::vector<std::vector<int> >(_size);
        _labels = std::vector<int>(_size);
        std::vector<int> image;
        for (int i = 0; i < _size; i++) {
            for (int j = 0; j < (rows * columns); j++) {
                fread(&pixel_value, sizeof(char), 1, images);
                _images[i].push_back((int)pixel_value);
            }
            fread(&label, sizeof(char), 1, labels);
            _labels[i] = (int)label;
        }
    } else {
        cout << "number of labels does not match with number of images" << endl;
        exit(0);
    }
}

MNISTData::~MNISTData() {}

void MNISTData::show(int index) {
    int pixel_count = 0;
    for (auto pixel : _images[index]) {
        if (pixel_count % 28 == 0) cout << endl;
            if (pixel >= 1) {
                cout << "* ";
            } else {
                cout << "0 ";
            }
        pixel_count ++;
    }
    cout << endl;
    cout << "the label is: " << _labels[index] << endl;
}

Tensor MNISTData::operator[] (int index) {
    Tensor result = Tensor(28, 28, 1);
    std::vector<std::vector<std::vector<double> > > kernel_vec;
    std::vector<std::vector<double> > image;
    std::vector<double> row;
    int pixel_count = 0;
    for (auto pixel : _images[index]) {
        if (pixel_count % 28 == 0 && row.size() == 28) {
            image.push_back(row);
            row.clear();
        }
        row.push_back(pixel);
        pixel_count ++;
    }
    image.push_back(row);
    kernel_vec.push_back(image);
    result.set_kernel(kernel_vec);
    return result;
}




int MNISTData::label(int index) {
    return _labels[index];
}

int MNISTData::getSize() {
    return _images.size();
}


MNISTData load_training_data(string & training_directory) {
    string image_location_str = training_directory + "/train-images.idx3-ubyte";
    string label_location_str = training_directory + "/train-labels.idx1-ubyte";
    const char * image_location = image_location_str.c_str();
    const char * label_location = label_location_str.c_str();
    FILE * training_images = fopen(image_location, "r");
    FILE * training_labels = fopen(label_location, "r");
    MNISTData training = MNISTData(training_images, training_labels);
    return training;
}

MNISTData load_test_data(string & test_directory) {
    string image_location_str = test_directory + "/t10k-images.idx3-ubyte";
    string label_location_str = test_directory + "/t10k-labels.idx1-ubyte";
    const char * image_location = image_location_str.c_str();
    const char * label_location = label_location_str.c_str();
    FILE * test_images = fopen(image_location, "r");
    FILE * test_labels = fopen(label_location, "r");
    MNISTData test = MNISTData(test_images, test_labels);
    return test;
}

vector<Tensor> load_MNIST(string & datapath, vector<int> & labels) {
    std::vector<Tensor> result;
    MNISTData test = load_test_data(datapath);
    cout << test.getSize() << endl;
    for (int i = 0; i < test.getSize(); ++i) {
        result.push_back(test[i]);
        labels.push_back(test.label(i));
    }
    cout << "result size: " << result.size() << endl;
    cout << "label size: " << labels.size() << endl;
    return result;

}

// Create a Network, load all weight into it and return.
Network load_Lenet_weights() {
    Network net;

    ConvConfigure c1(1,6,5,parameters_2,1,2);
    Layer * L1 = Layer::creator(CONV, &c1);
    Conv * conv1=dynamic_cast<Conv *>(L1);
    vector<Tensor> k1;
    for (int i = 0; i <parameters_1.size() ; ++i) {
        Tensor tmp=Tensor(5,5,1);
        tmp.set_kernel(parameters_1[i]);
        k1.push_back(tmp);
    }
    conv1->setkernel(k1);
    net.add_layer(L1);

    Layer * L2 = Layer::creator(RELU, nullptr);
    net.add_layer(L2);

    PoolConfigure p1(2,2);

    Layer * L3 = Layer::creator(POOL, &p1);
    net.add_layer(L3);

    ConvConfigure c2(6,16,5,parameters_4);
    Layer * L4 = Layer::creator(CONV, &c2);

    Conv* conv2=dynamic_cast<Conv* >(L4);
    vector<Tensor> k4;
    for (int i = 0; i <parameters_3.size() ; ++i) {
        Tensor tmp=Tensor(5,5,6);
        tmp.set_kernel(parameters_3[i]);
        k4.push_back(tmp);
    }
    conv2->setkernel(k4);

    net.add_layer(L4);

    Layer * L5 = Layer::creator(RELU, nullptr);
    net.add_layer(L5);

    PoolConfigure p2(2,2);

    Layer * L6 = Layer::creator(POOL, &p2);
    net.add_layer(L6);

    LinearConfigure l1(16*5*5,120,parameters_6);

    Layer * L7 = Layer::creator(LINEAR, &l1);

    Linear* line1= dynamic_cast<Linear*>(L7);
    line1->setkernel(parameters_5);

    net.add_layer(L7);

    Layer * L8 = Layer::creator(RELU, nullptr);
    net.add_layer(L8);

    LinearConfigure l2(120,84,parameters_8);

    Layer * L9 = Layer::creator(LINEAR, &l2);

    Linear* line2= dynamic_cast<Linear*>(L9);
    line2->setkernel(parameters_7);

    net.add_layer(L9);

    Layer * L10 = Layer::creator(RELU, nullptr);
    net.add_layer(L10);

    LinearConfigure l3(84,10,parameters_10);

    Layer * L11 = Layer::creator(LINEAR, &l3);

    Linear* line3= dynamic_cast<Linear*>(L11);
    line3->setkernel(parameters_9);

    net.add_layer(L11);

    return net;
}

