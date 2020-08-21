#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "FileInfo.h"
#include "blockingQueue.h"

std::string execute(const std::string& command) {
    system((command + " > temp.txt").c_str());

    std::ifstream ifs("temp.txt");
    std::string ret{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
    ifs.close(); // must close the inout stream so the file can be cleaned up
    if (std::remove("temp.txt") != 0) {
        perror("Error deleting temporary file");
    }
    return ret;
}

std::vector<std::string> split (const std::string& s, const std::string& delimiter) {
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

int main() {
    std::vector<FileInfo> filesInfo;
//    BlockingQueue<std::string> queue;
//    std::vector<std::string> listFileUpload;
    std::string delimiter = "\t";
    for(int asdasdasd=0; asdasdasd < 10; asdasdasd++) {
        std::cout <<"b: " << asdasdasd << "\n";
        std::string info = execute("du -sh /home/dungpb/Work/piZeroW/autoUploadData/testdir/*");
        std::istringstream ss(info);
        for (std::string line; std::getline(ss, line);) {
            std::vector<std::string> splited = split(line, delimiter);
            if (filesInfo.empty()) {
                filesInfo.push_back(FileInfo(splited[1], splited[0]));
            } else {
                bool flag = true;
                for (auto it = filesInfo.begin(); it != filesInfo.end(); ++it) {
                    if (it->checkPath(splited[1]) == 0) {
                        if (it->updateInfo(splited[0]) == 0) {
                            std::cout << "file nay co the upload: " << splited[1] << "\n";
//                                listFileUpload.push_back(it->getPath());
//                                filesInfo.erase(it);
                            break;
                        }
                        flag = false;
                    }
                }
                if(flag) {
                    filesInfo.push_back(FileInfo(splited[1], splited[0]));
                }
            }

        }
    }
}
