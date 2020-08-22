//
// Created by dungpb on 22/08/2020.
//

#include "checkFileUpdate.h"
void checkFileUpdate::process(const std::string &path, BlockingQueue<std::string>& listFileUpload, std::vector<FileInfo>& filesInfo) {
    for (auto &entry : std::experimental::filesystem::directory_iterator(path)) {
        int ec = FTPUpload::checkPath(entry.path());
        if (ec == 1 || ec == 0) {
            if (!listFileUpload.isExist(entry.path())) {
                if (filesInfo.empty()) {
                    filesInfo.emplace_back(entry.path(), getSize(entry.path()));
                } else {
                    bool flag = true;
                    for (auto it = filesInfo.begin(); it != filesInfo.end(); ++it) {
                        if (it->checkPath(entry.path()) == 0) {
                            flag = false;
                            if (it->updateInfo(getSize(entry.path())) == 0) {
                                log_info("add file to queue: ", entry.path(), "\n");
                                listFileUpload.push(it->getPath());
                                filesInfo.erase(it);
                                break;
                            }
                        }
                    }
                    if(flag) {
                        filesInfo.emplace_back(entry.path(), getSize(entry.path()));
                    }
                    flag = true;
                }
            }
        }
        if (ec == 2) {
            log_err("Unknow file: ", entry.path(), "\n");
            return;
        }
    }
}

int checkFileUpdate::getSize(const std::string &path) {
    if(FTPUpload::checkPath(path)){
        return std::experimental::filesystem::file_size(path);
    } else {
        std::vector<std::string> listDir;
        std::vector<std::string> listFile;

        FTPUpload::directoryAndFileRegression(path, listDir, listFile);

        int size = 0;
        for(auto &file : listFile){
            size += std::experimental::filesystem::file_size(file);
        }
        return size;
    }
}
