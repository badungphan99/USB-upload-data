
#define TIME 1000000000 // 1s

#include "libCNU/checkFileUpdate.h"
#include "libCNU/FTPUpload.h"
#include <thread>

void checkUpdate(const std::string& path, BlockingQueue<std::string> &listFileUpload, std::vector<FileInfo> &filesInfo){
    checkFileUpdate::process(path, listFileUpload, filesInfo);
}
void uploadFTPServer(BlockingQueue<std::string>& listFileUpload){
    while (!listFileUpload.empty()) {
        FTPUpload::upload(listFileUpload.front());
        std::experimental::filesystem::remove_all(listFileUpload.front());
        listFileUpload.pop();
    }
}

int main() {

    BlockingQueue<std::string> listFileUpload;
    std::vector<FileInfo> filesInfo;
    std::string path =  "/mnt/usb";

    auto timeStart = std::chrono::high_resolution_clock::now();

    while (true) {
        auto time = (std::chrono::high_resolution_clock::now() - timeStart).count();
        std::thread t1;
        if (time > TIME) {
            t1 = std::thread(checkUpdate, std::ref(path), std::ref(listFileUpload), std::ref(filesInfo));
            timeStart = std::chrono::high_resolution_clock::now();
        }

        std::thread t2(uploadFTPServer, std::ref(listFileUpload));
        if(t1.joinable()){t1.join();}
        if(t2.joinable()){t2.join();}
    }
}