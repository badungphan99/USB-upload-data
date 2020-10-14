//
// Created by dungpb on 22/08/2020.
//

#include "FTPUpload.h"

#define PRINT_LOG [](const std::string& strLogMsg) { log_debug(strLogMsg, "\n"); }

int FTPUpload::upload(const std::string &path_ftp_dir, const nlohmann::json &config) {
    std::string FTP_SERVER_ADD;
    int FTP_SERVER_PORT;
    std::string FTP_USERNAME;
    std::string FTP_PASSWORD;

    if(getEnvVar(FTP_SERVER_ADD, FTP_SERVER_PORT, FTP_USERNAME, FTP_PASSWORD, config)){
        log_err("missing info FTP SERVER\n");
        return 1;
    }
    for (auto &entry : std::experimental::filesystem::directory_iterator(path_ftp_dir)) {

        int ec = checkPath(entry.path());

        if (ec == 1) {
            log_info("Upload file\n");
            if (!uploadFile(FTP_SERVER_ADD, FTP_SERVER_PORT, FTP_USERNAME, FTP_PASSWORD, entry.path())) {
                log_info("File uploaded successfully", entry.path(), "\n");
                std::experimental::filesystem::remove_all(entry.path());
            } else {
                log_err("Error when upload file", entry.path(), "\n");
                return 1;
            }
        }
        if (ec == 0) {
            log_info("Upload dir\n");
            if (!uploadDir(FTP_SERVER_ADD, FTP_SERVER_PORT, FTP_USERNAME, FTP_PASSWORD, entry.path())) {
                log_info("Dir uploaded successfully", entry.path(), "\n");
                std::experimental::filesystem::remove_all(entry.path());
            } else {
                log_err("Error when upload dir", entry.path(), "\n");
                return 1;
            }
        }
        if (ec == 2) {
            log_err("Unknow path: ", entry.path());
            return 1;
        }
    }
    return 0;
}

int FTPUpload::checkPath(const std::string &path_check) {
    std::experimental::filesystem::path path(path_check);
    std::error_code ec;
    if (std::experimental::filesystem::is_directory(path, ec)){
        return 0;
    }
    if (ec){
        log_err("Error in is_directory: ", ec.message(), "\n");
    }
    if (std::experimental::filesystem::is_regular_file(path, ec)){
        return 1;
    }
    if (ec){
        log_err("Error in is_regular_file: ", ec.message(), "\n");
    }
    return 2;
}

int FTPUpload::getEnvVar(std::string &FTP_SERVER_ADD, int& FTP_SERVER_PORT, std::string &FTP_USERNAME,
                         std::string &FTP_PASSWORD, const nlohmann::json &config) {
    FTP_SERVER_ADD = config["FTP_SERVER_ADD"].get<std::string>();
    FTP_SERVER_PORT = config["FTP_SERVER_PORT"].get<int>();
    FTP_USERNAME = config["FTP_USERNAME"].get<std::string>();
    FTP_PASSWORD = config["FTP_PASSWORD"].get<std::string>();
    return 0;
}

int FTPUpload::uploadDir(const std::string &FTP_SERVER_ADD, int &FTP_SERVER_PORT, const std::string &FTP_USERNAME,
                         const std::string &FTP_PASSWORD, const std::string &path_local) {
    std::vector<std::string> listFileLocal;
    std::vector<std::string> listDir;

    listFileLocal.clear();
    listDir.clear();

    std::string dirTimeStamp;

    if (renameTimeStamp(path_local, dirTimeStamp)) {
        log_err("Can't get file name\n");
        return 1;
    }

    directoryAndFileRegression(path_local, listDir, listFileLocal);

    auto *cftpClient = new ftp::CFTPClient(PRINT_LOG);
    cftpClient->InitSession(FTP_SERVER_ADD, FTP_SERVER_PORT, FTP_USERNAME, FTP_PASSWORD);

    if(cftpClient->CreateDir(dirTimeStamp)){
        log_info("Create dir successfully ", dirTimeStamp, "\n");
    } else {
        log_err("Cannot create dir or dir existed", dirTimeStamp, "\n");
    }

    for(auto &i : listDir) {
        std::string dirNameRemote;
        renameFileRemote(i, path_local, dirTimeStamp, dirNameRemote);
        if(cftpClient->CreateDir(dirNameRemote)){
            log_info("Create dir successfully ", dirNameRemote, "\n");
        } else {
            log_err("Cannot create dir or dir existed", dirNameRemote, "\n");
        }
    }

    for(auto &i: listFileLocal){
        std::string fileNameRemote;
        renameFileRemote(i, path_local, dirTimeStamp, fileNameRemote);
        if(cftpClient->UploadFile(i, fileNameRemote)){
            log_info("File uploaded successfully ", fileNameRemote, "\n");
        } else {
            log_err("error when upload file ", fileNameRemote, "\n");
        }
    }
    cftpClient->CleanupSession();

    return 0;
}

int FTPUpload::uploadFile(const std::string &FTP_SERVER_ADD, int &FTP_SERVER_PORT,
                          const std::string &FTP_USERNAME, const std::string &FTP_PASSWORD, const std::string &path_local) {
    std::string fileNameRemote;
    if(renameTimeStamp(path_local, fileNameRemote)){
        log_err("Can't get file name\n");
        return 1;
    }

    auto *cftpClient = new ftp::CFTPClient(PRINT_LOG);
    cftpClient->InitSession(FTP_SERVER_ADD, FTP_SERVER_PORT, FTP_USERNAME, FTP_PASSWORD);
    cftpClient->UploadFile(path_local, fileNameRemote);
    cftpClient->CleanupSession();

    return 0;
}

int FTPUpload::renameTimeStamp(const std::string &path, std::string &filename) {
    char delimiter = '/';
    size_t i = path.rfind(delimiter, path.length());
    if (i != std::string::npos){
        filename = path.substr(i+1, path.length() - i);
    } else {
        log_err("Can't get file name\n");
        return 1;
    }
    int timestamp = std::chrono::microseconds (std::chrono::microseconds (std::time(nullptr))).count();
    filename =  std::to_string(timestamp)+filename;
    return 0;
}

std::string base_name(std::string const & path)
{
    return path.substr(path.find_last_of("/\\") + 1);
}

int FTPUpload::directoryAndFileRegression(const std::string &path, std::vector<std::string> &listDir,
                                          std::vector<std::string> &listFile) {
    for (auto &entry : std::experimental::filesystem::directory_iterator(path)) {

        int ec = checkPath(entry.path());

        if(ec == 2){
            log_err("Unknow file: ", entry.path(), "\n");
            return 1;
        }

        if(ec){
            if (base_name(entry.path())[0] != '.') {
                listFile.push_back(entry.path());
            }
        } else {
            if (base_name(entry.path())[0] != '.') {
                listDir.push_back(entry.path());
                directoryAndFileRegression(entry.path(), listDir, listFile);
            }
        }
    }
    return 0;
}

bool FTPUpload::renameFileRemote(const std::string& str, const std::string& from, const std::string& to, std::string &res) {
    res = str;
    size_t start_pos = res.find(from);
    if(start_pos == std::string::npos)
        return false;
    res.replace(start_pos, from.length(), to);
    return true;
}
