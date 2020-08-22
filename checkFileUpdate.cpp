//
// Created by dungpb on 22/08/2020.
//

#include "checkFileUpdate.h"

std::string checkFileUpdate::execute(const std::string &command) {
    system((command + " > temp.txt").c_str());

    std::ifstream ifs("temp.txt");
    std::string ret{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
    ifs.close(); // must close the inout stream so the file can be cleaned up
    if (std::remove("temp.txt") != 0) {
        perror("Error deleting temporary file");
    }
    return ret;
}

std::vector<std::string> checkFileUpdate::split(const std::string &s, const std::string &delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

void checkFileUpdate::process(const std::string &path, BlockingQueue<std::string>& listFileUpload, std::vector<FileInfo>& filesInfo) {
//    std::vector<FileInfo> filesInfo;
    std::string delimiter = "\t";
    std::string command = "du -sh " + path + "/*";
    std::string info = execute(command);
    std::istringstream ss(info);
    for (std::string line; std::getline(ss, line);) {
        std::vector<std::string> splited = split(line, delimiter);
        if(!listFileUpload.isExist(splited[1])) {
            if (filesInfo.empty()) {
                filesInfo.emplace_back(splited[1], splited[0]);
            } else {
                for (auto it = filesInfo.begin(); it != filesInfo.end(); ++it) {
                    if (it->checkPath(splited[1]) == 0) {
                        if (it->updateInfo(splited[0]) == 0) {
                            std::cout << "add file to queue :" << splited[1] << "\n";
                            listFileUpload.push(it->getPath());
                            filesInfo.erase(it);
                            break;
                        }
                    }
                }
                filesInfo.emplace_back(splited[1], splited[0]);
            }
        }
    }
}
