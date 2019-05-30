CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

PROJECT(tinytensor)
SET(CMAKE_CXX_STANDARD 14)

#set build type
set(CMAKE_BUILD_TYPE Debug)

# Major project
INCLUDE_DIRECTORIES(include)

FIND_PACKAGE( OpenMP REQUIRED)
if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()


SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O3 -msse2  -funroll-loops")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -msse2  -funroll-loops")

set( TINYTENSOR_SRC src/tensor.cpp src/network.cpp src/layer.cpp src/dataloader.cpp src/lap_timer.cpp)

add_library( tinytensor_lib ${TINYTENSOR_SRC} )

ADD_EXECUTABLE( test_mnist test/test_MNIST.cpp )
ADD_EXECUTABLE( live_demo test/live_demo.cpp )
ADD_EXECUTABLE( test_time test/test_time.cpp )

TARGET_LINK_LIBRARIES( test_mnist tinytensor_lib )
TARGET_LINK_LIBRARIES( live_demo tinytensor_lib )
TARGET_LINK_LIBRARIES( test_time tinytensor_lib )
