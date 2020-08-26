//
// Created by dungpb on 26/08/2020.
//

#include "libMountFile/mountManager.h"
#include "libFTPUpload/FTPUpload.h"
#include "debug_macro.h"
#include "json.hpp"

#include <vector>
#include <string>
#include <chrono>

void testFTP(){
    std::string pathConfig = "../config.json";
    std::ifstream info(pathConfig);
    nlohmann::json json = nlohmann::json::parse(info);

    std::vector<std::string> listImg = json["IMG"];
    FTPUpload::upload("/home/dungpb/intel", json);
}

void run(const std::vector<std::string> &path, int &index, const nlohmann::json &config){
    int next = 0;
    if(index < path.size() - 1) next = index + 1;

    mountManager::ejectUSB();
    mountManager::connectUSB(path[next]);
    mountManager::mount(path[index]);
    FTPUpload::upload("/mnt/usb", config);
    mountManager::unmount();
}

int main(){
//    testFTP();
    std::string pathConfig = "/home/dungpb/Work/piZeroW/autoUploadData/config.json";
    std::ifstream info(pathConfig);
    nlohmann::json json = nlohmann::json::parse(info);

    std::vector<std::string> listImg = json["IMG"];
    int timeset = json["TIME"].get<int>();

    log_info("time set: ", timeset, "\n");


    bool flag = true;
    int index = 0;

    while (1) {

        if(index < listImg.size() - 1) index++;
        else index = 0;

        run(listImg, index, json);

        auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::tm bt = *std::localtime(&timenow);
        std::ostringstream oss;
        std::stringstream ss;

        ss << std::put_time(&bt, "%H");

        if (std::atoi(ss.str().c_str()) == timeset) {
            if(flag) {
                run(listImg, index, json);
                flag = false;
            }
        }
        if (std::atoi(ss.str().c_str()) != timeset) {
            if(!flag){
                flag = true;
            }
        }
    }
}