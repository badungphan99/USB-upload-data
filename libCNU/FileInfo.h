//
// Created by dungpb on 21/08/2020.
//

#ifndef AUTOUPLOADDATA_FILEINFO_H
#define AUTOUPLOADDATA_FILEINFO_H

#define NUM_CHECK 10


#include <string>

class FileInfo {
private:
    std::string path;
    int size;
    int count;
public:
    FileInfo(const std::string &path, const int &size);
    int updateInfo(const int &size);
    int checkPath(const std::string &path);
    const std::string &getPath() const;
};


#endif //AUTOUPLOADDATA_FILEINFO_H
