//
// Created by dungpb on 25/08/2020.
//

#include "mountManager.h"

std::string mountManager::exec(const char* cmd) {
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

int mountManager::mount(const std::string &path) {
    std::string command = "sudo mount -t vfat " + path + " /mnt/usb";
    std::string res = exec(command.c_str());
    std::cout << res << "\n";

    command = "sudo chmod -R 777 " + path;
    res = exec(command.c_str());
    std::cout << res << "\n";
    return 0;
}

int mountManager::unmount() {
    std::string command = "sudo umount /mnt/usb";
    std::string res = exec(command.c_str());
    std::cout << res << "\n";
    return 0;
}

int mountManager::connectUSB(const std::string &path) {
    std::string command = "sudo modprobe g_mass_storage file=" + path + " removeable=y";
    std::string res = exec(command.c_str());
    std::cout << res << "\n";
    return 0;
}

int mountManager::ejectUSB() {
    std::string command = "sudo modprobe -r g_mass_storage";
    std::string res = exec(command.c_str());
    std::cout << res << "\n";
    return 0;
}
