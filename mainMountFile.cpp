//
// Created by dungpb on 25/08/2020.
//

#include "libMountFile/mountManager.h"

int main(){
    std::string path = "/piusb.img";
    mountManager::ejectUSB();
    mountManager::mount(path);
}