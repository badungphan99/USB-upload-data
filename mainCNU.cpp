
#define TIME 1000000000 // 1s

#include "libFTPUpload//FTPUpload.h"
#include <thread>


int main() {

    std::string path =  "/mnt/usb";

    while (true) {
        FTPUpload::upload(path);
    }
}