cmake_minimum_required(VERSION 2.4)

project("algorithm_and_practice-pknu-2016/15" C CXX)

# We need C++ 11
if(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 3.1)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED on)
else(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 3.1)
    set(CMAKE_CXX_FLAGS "-std=c++11")
endif(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 3.1)

include_directories(./include)

add_executable(pagerank main.cpp)
