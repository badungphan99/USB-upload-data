cmake_minimum_required(VERSION 3.10)
project(autoUploadData)

set(CMAKE_CXX_STANDARD 14)

find_package(CURL REQUIRED)
find_package(Threads REQUIRED)

include_directories(${CURL_INCLUDE_DIRS})

include_directories(libFTP libCNU)

add_executable(autoUploadData mainCNU.cpp debug_macro.h libFTP/CurlHandle.cpp libFTP/CurlHandle.h libFTP/FTPClient.cpp libFTP/FTPClient.h libCNU/FTPUpload.cpp libCNU/FTPUpload.h)
add_executable(mountfile mainMountFile.cpp libMountFile/mountManager.h libMountFile/mountManager.cpp debug_macro.h)

target_link_libraries(autoUploadData ${CURL_LIBRARIES} stdc++fs ${CMAKE_THREAD_LIBS_INIT})