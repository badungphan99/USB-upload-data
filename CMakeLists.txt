cmake_minimum_required(VERSION 3.17)
project(autoUploadData)

set(CMAKE_CXX_STANDARD 14)

add_executable(autoUploadData main.cpp FileInfo.cpp FileInfo.h blockingQueue.h)