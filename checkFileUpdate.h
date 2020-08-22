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

namespace checkFileUpdate {
    std::string execute(const std::string& command);

    std::vector<std::string> split (const std::string& s, const std::string& delimiter);

    void process(const std::string& path, BlockingQueue<std::string>& listFileUpload, std::vector<FileInfo> &filesInfo);
};


#endif //AUTOUPLOADDATA_CHECKFILEUPDATE_H
