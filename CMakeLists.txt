CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(tinytensor)
SET(CMAKE_CXX_STANDARD 14)

#set build type
set(CMAKE_BUILD_TYPE Debug)

# Major project
INCLUDE_DIRECTORIES(include)

set( TINYTENSOR_SRC src/tensor.cpp src/network.cpp src/layer.cpp src/dataloader.cpp)

add_library( tinytensor_lib ${TINYTENSOR_SRC} )

ADD_EXECUTABLE( test_mnist test/test_MNIST.cpp )
TARGET_LINK_LIBRARIES( test_mnist tinytensor_lib )
