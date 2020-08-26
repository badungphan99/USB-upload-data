//
// Created by dungpb on 26/08/2020.
//

#include "json.hpp"
#include <iostream>
#include <fstream>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;

    auto pipe = popen(cmd, "r"); // get rid of shared_ptr

    if (!pipe) throw std::runtime_error("popen() failed!");

    while (!feof(pipe)) {
        if (fgets(buffer.data(), 128, pipe) != nullptr)
            result += buffer.data();
    }

    auto rc = pclose(pipe);

    if (rc == EXIT_SUCCESS) { // == 0

    } else if (rc == EXIT_FAILURE) {  // EXIT_FAILURE is not used by all programs, maybe needs some adaptation.

    }
    return result;
}

int main(){
    std::string pathConfig = "/home/dungpb/Work/piZeroW/autoUploadData/config.json";

    std::cout << exec("sudo mkdir /mnt/usb") << "\n";
    std::cout << exec("sudo chmod -R 777 /mnt/usb") << "\n";

    std::ifstream info(pathConfig);
    nlohmann::json json = nlohmann::json::parse(info);
    for (auto & i:json["IMG"]){
        std::string mkfile = "sudo dd bs=1M if=/dev/zero of=" + i.get<std::string>() + " count=" + json["SIZE"].get<std::string>();
        std::cout << exec(mkfile.c_str()) << "\n";

        std::string formatfile = "sudo mkdosfs " + i.get<std::string>() + " -F 32 -I";
        std::cout << exec(formatfile.c_str()) << "\n";
    }
}