//
// Created by dungpb on 22/08/2020.
//

#ifndef AUTOUPLOADDATA_CHECKFILEUPDATE_H
#define AUTOUPLOADDATA_CHECKFILEUPDATE_H

#include <fstream>
#include <string>

#include "blockingQueue.h"
#include "debug_macro.h"
#include "FileInfo.h"
#include "FTPUpload.h"

namespace checkFileUpdate {
    void process(const std::string& path, BlockingQueue<std::string>& listFileUpload, std::vector<FileInfo> &filesInfo);

    int getSize(const std::string& path);
};


#endif //AUTOUPLOADDATA_CHECKFILEUPDATE_H
