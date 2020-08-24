cmake_minimum_required(VERSION 3.17)
project(autoUploadData)

set(CMAKE_CXX_STANDARD 14)

find_package(CURL REQUIRED)
find_package(Threads REQUIRED)

include_directories(${CURL_INCLUDE_DIRS})

include_directories(libFTP libCNU)

add_executable(autoUploadData mainCNU.cpp libCNU/FileInfo.cpp libCNU/FileInfo.h libCNU/blockingQueue.h libCNU/checkFileUpdate.cpp libCNU/checkFileUpdate.h debug_macro.h libFTP/CurlHandle.cpp libFTP/CurlHandle.h libFTP/FTPClient.cpp libFTP/FTPClient.h libCNU/FTPUpload.cpp libCNU/FTPUpload.h)

target_link_libraries(autoUploadData ${CURL_LIBRARIES} stdc++fs ${CMAKE_THREAD_LIBS_INIT})