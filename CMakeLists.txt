cmake_minimum_required(VERSION 3.17)
project(autoUploadData)

set(CMAKE_CXX_STANDARD 14)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

include_directories(libFTP)

add_executable(autoUploadData main.cpp FileInfo.cpp FileInfo.h blockingQueue.h FTPUpload.cpp FTPUpload.h)
add_executable(testftp mainftp2.cpp libFTP/CurlHandle.cpp libFTP/CurlHandle.h libFTP/FTPClient.cpp libFTP/FTPClient.h FTPUpload.cpp FTPUpload.h)

target_link_libraries(testftp ${CURL_LIBRARIES} )