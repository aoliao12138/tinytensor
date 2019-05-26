#include "dataloader.hpp"

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
    Tensor result = Tensor(1, 28, 28);
    std::vector<std::vector<std::vector<double> > > kernel_vec;
    std::vector<double> row;
    std::vector<std::vector<double> > image;
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

// Author: huzy
// Create a Network, load all weight into it and return.
// Notice that layer names are: 1, 2, 3..., 10, should be changed later.
Network MNISTData::load_weights() {
    Network net;

    Layer * L1 = Layer::creater(mode, c1, parameters_1);  // TODO:
    net.add_layer(L1);

    Layer * L2 = Layer::creater(mode, c2, parameters_2);  // TODO:
    net.add_layer(L2);

    Layer * L3 = Layer::creater(mode, c3, parameters_3);  // TODO:
    net.add_layer(L3);

    Layer * L4 = Layer::creater(mode, c4, parameters_4);  // TODO:
    net.add_layer(L4);

    Layer * L5 = Layer::creater(mode, c5, parameters_5);  // TODO:
    net.add_layer(L5);

    Layer * L6 = Layer::creater(mode, c6, parameters_6);  // TODO:
    net.add_layer(L6);

    Layer * L7 = Layer::creater(mode, c7, parameters_7);  // TODO:
    net.add_layer(L7);

    Layer * L8 = Layer::creater(mode, c8, parameters_8);  // TODO:
    net.add_layer(L8);

    Layer * L9 = Layer::creater(mode, c9, parameters_9);  // TODO:
    net.add_layer(L9);

    Layer * L10 = Layer::creater(mode, c10, parameters_10);  // TODO:
    net.add_layer(L10);

    return net;
}

