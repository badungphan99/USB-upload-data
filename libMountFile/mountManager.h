//
// Created by dungpb on 25/08/2020.
//

#ifndef AUTOUPLOADDATA_MOUNTMANAGER_H
#define AUTOUPLOADDATA_MOUNTMANAGER_H

#include <sys/mount.h>
#include <string>

#include "../debug_macro.h"

namespace mountManager {
    std::string exec(const char* cmd);

    int mount(const std::string &path);

    int unmount();

    int connectUSB(const std::string &path);

    int ejectUSB();

};


#endif //AUTOUPLOADDATA_MOUNTMANAGER_H
