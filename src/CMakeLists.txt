cmake_minimum_required( VERSION 2.8 )
project( projector )

#SET(CMAKE_CUDA_COMPILER /usr/local/cuda-11.1/bin/nvcc)
#SET(CUDA_TOOLKIT_ROOT_DIR /usr/local/cuda-11.1)

find_package(OpenCV REQUIRED)
message(STATUS "Find OpenCV include at ${OpenCV_INCLUDE_DIRS}")
message(STATUS "Find OpenCV libraries: ${OpenCV_LIBRARIES}")


include_directories( "/usr/include/eigen3" )

#include_directories( "/usr/local/include/opencv4" )
#set(OpenCV_DIR "/usr/local/include/opencv4/opencv2/core")
add_executable( projector projector.cpp )
target_link_libraries(projector ${OpenCV_LIBRARIES})

