#include "checkFileUpdate.h"
#include "FTPUpload.h"
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
        std::string path =  "/home/dungpb/Work/piZeroW/autoUploadData/testdir";

        while (true) {
            std::thread t1(checkUpdate, std::ref(path), std::ref(listFileUpload), std::ref(filesInfo));
            std::thread t2(uploadFTPServer, std::ref(listFileUpload));
            t1.join();
            t2.join();
        }
}