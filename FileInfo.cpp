//
// Created by dungpb on 21/08/2020.
//

#include <iostream>
#include "FileInfo.h"

FileInfo::FileInfo(const std::string &path, const std::string &size){
    this->path = path;
    this->size = size;
    this->count = 0;
}

int FileInfo::updateInfo(const std::string &size) {
    if(size.compare(this->size) == 0){
        this->count++;
    } else {
        this->size = size;
        this->count = 0;
    }

    if(this->count == NUM_CHECK){
        this->count++;
        return 0;
    }

    return 1;
}

int FileInfo::checkPath(const std::string &path) {
    if(path.compare(this->path) != 0 ){
        return 1;
    } else{
        return 0;
    }
}

const std::string &FileInfo::getPath() const {
    return path;
}
