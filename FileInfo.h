//
// Created by dungpb on 21/08/2020.
//

#ifndef AUTOUPLOADDATA_FILEINFO_H
#define AUTOUPLOADDATA_FILEINFO_H

#define NUM_CHECK 2


#include <string>

class FileInfo {
private:
    std::string path;
    std::string size;
    int count;
public:
    FileInfo(const std::string &path, const std::string &size);
    int updateInfo(const std::string &size);
    int checkPath(const std::string &path);
    const std::string &getPath() const;
};


#endif //AUTOUPLOADDATA_FILEINFO_H
