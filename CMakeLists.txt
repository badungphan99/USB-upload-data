cmake_minimum_required(VERSION 3.10)
project(autoUploadData)

set(CMAKE_CXX_STANDARD 14)

find_package(CURL REQUIRED)
find_package(Threads REQUIRED)
find_library(WIRINGPI_LIBRARIES NAMES wiringPi)

include_directories(${CURL_INCLUDE_DIRS})

include_directories(libFTP libCNU)

add_executable(autoUploadData mainCNU.cpp libCNU/FileInfo.cpp libCNU/FileInfo.h libCNU/blockingQueue.h libCNU/checkFileUpdate.cpp libCNU/checkFileUpdate.h debug_macro.h libFTP/CurlHandle.cpp libFTP/CurlHandle.h libFTP/FTPClient.cpp libFTP/FTPClient.h libCNU/FTPUpload.cpp libCNU/FTPUpload.h)
add_executable(mountfile mainMountFile.cpp libMountFile/mountManager.h libMountFile/mountManager.cpp debug_macro.h)
add_executable(testGPIO libGPIO/main.cpp)

target_link_libraries(autoUploadData ${CURL_LIBRARIES} stdc++fs ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(testGPIO ${WIRINGPI_LIBRARIES})