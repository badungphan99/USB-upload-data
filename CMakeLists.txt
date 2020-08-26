cmake_minimum_required(VERSION 3.10)
project(autoUploadData)

set(CMAKE_CXX_STANDARD 14)

find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIRS})

include_directories(libFTP libCNU)

add_executable(usb main.cpp json.hpp debug_macro.h libMountFile/mountManager.h libMountFile/mountManager.cpp libFTP/CurlHandle.cpp libFTP/CurlHandle.h libFTP/FTPClient.cpp libFTP/FTPClient.h libFTPUpload/FTPUpload.cpp libFTPUpload/FTPUpload.h)
add_executable(init init.cpp)

target_link_libraries(usb ${CURL_LIBRARIES} stdc++fs ${CMAKE_THREAD_LIBS_INIT})