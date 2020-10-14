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
#include <unistd.h>

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
    std::string pathConfig = "../config.json";
    std::ifstream info(pathConfig);
    nlohmann::json json = nlohmann::json::parse(info);

    std::vector<std::string> listImg = json["IMG"];
    int timeset = json["TIME"].get<int>();

    if (timeset < 0 || timeset > 2400){
        log_err("check time config\n");
        return 1;
    }

    log_info("time set: ", timeset, "\n");


    bool flag = true;
    bool once = true;
    int index = 0;

    while (1) {
        if(once) {
            run(listImg, index, json);
            once = false;
        }
        auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::tm bt = *std::localtime(&timenow);
        std::ostringstream oss;
        std::stringstream ss;

        ss << std::put_time(&bt, "%H%M");
//        usleep(1800000000); // 30 minutes
        if (std::atoi(ss.str().c_str()) == timeset) {
            if(flag) {
                if(index < listImg.size() - 1) index++;
                else index = 0;
                run(listImg, index, json);
                flag = false;
            }
        }
        if (std::atoi(ss.str().c_str()) != timeset && flag == false){
                flag = true;
        }
    }
}
