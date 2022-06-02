cmake_minimum_required( VERSION 2.8 )
project( projector )

find_package(OpenCV REQUIRED)
message(STATUS "Find OpenCV include at ${OpenCV_INCLUDE_DIRS}")
message(STATUS "Find OpenCV libraries: ${OpenCV_LIBRARIES}")

include_directories( "/usr/include/eigen3" )

add_executable( projector projector.cpp )
target_link_libraries(projector ${OpenCV_LIBRARIES})

