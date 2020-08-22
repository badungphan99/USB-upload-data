//
// Created by dungpb on 22/08/2020.
//

#include "FTPUpload.h"

#define PRINT_LOG [](const std::string& strLogMsg) { std::cout << strLogMsg << std::endl; }

int FTPUpload::upload(const std::string &path_local) {
    std::string FTP_SERVER_ADD;
    int FTP_SERVER_PORT;
    std::string FTP_USERNAME;
    std::string FTP_PASSWORD;

    if(getEnvVar(FTP_SERVER_ADD, FTP_SERVER_PORT, FTP_USERNAME, FTP_PASSWORD)){
        log_err("missing info FTP SERVER\n");
        return 1;
    }

    if(checkPath(path_local)){
        log_info("Upload file\n");
        if(!uploadFile(FTP_SERVER_ADD, FTP_SERVER_PORT, FTP_USERNAME, FTP_PASSWORD, path_local)){
            log_info("File uploaded successfully\n");
        } else{
            log_err("Error when upload file\n");
            return 1;
        }
    }

    return 0;
}

int FTPUpload::checkPath(const std::string &path) {
    return 1;
}

int FTPUpload::getEnvVar(std::string &FTP_SERVER_ADD, int& FTP_SERVER_PORT, std::string &FTP_USERNAME,
                         std::string &FTP_PASSWORD) {
    FTP_SERVER_ADD = "ftp.dlptest.com";
    FTP_SERVER_PORT = 21;
    FTP_USERNAME = "dlpuser@dlptest.com";
    FTP_PASSWORD = "eUj8GeW55SvYaswqUyDSm5v6N";
    return 0;
}

int FTPUpload::uploadFile(const std::string &FTP_SERVER_ADD, int &FTP_SERVER_PORT,
                          const std::string &FTP_USERNAME, const std::string &FTP_PASSWORD, const std::string &path_local) {
    std::string fileNameRemote;
    if(renameFile(path_local, fileNameRemote)){
        log_err("Can't get file name\n");
        return 1;
    }

    std::cout << fileNameRemote << "\n";

    auto *cftpClient = new ftp::CFTPClient(PRINT_LOG);
    cftpClient->InitSession(FTP_SERVER_ADD, FTP_SERVER_PORT, FTP_USERNAME, FTP_PASSWORD);
    cftpClient->UploadFile(path_local, fileNameRemote);
    cftpClient->CleanupSession();

    return 0;
}

int FTPUpload::renameFile(const std::string &path, std::string &filename) {
    char delimiter = '/';
    size_t i = path.rfind(delimiter, path.length());
    if (i != std::string::npos){
        filename = path.substr(i+1, path.length() - i);
    } else {
        log_err("Can't get file name\n");
        return 1;
    }
    int timestamp = std::chrono::microseconds (std::chrono::microseconds (std::time(NULL))).count();
    filename =  std::to_string(timestamp)+filename;
    return 0;
}
