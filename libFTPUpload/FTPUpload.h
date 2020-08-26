//
// Created by dungpb on 22/08/2020.
//

#ifndef AUTOUPLOADDATA_FTPUPLOAD_H
#define AUTOUPLOADDATA_FTPUPLOAD_H

#include <chrono>
#include <experimental/filesystem>

#include "FTPClient.h"
#include "../json.hpp"
#include "../debug_macro.h"

namespace FTPUpload {
    /**
     * @brief this function for upload file to server
     * @param path_local: The path can be a directory or a file
     * @return
     */
    int upload(const std::string& path_local, const nlohmann::json &config);

    /**
     * @brief check path is a directory of a file
     * @param path
     * @return 0 : directory | 1 : file
     */
    int checkPath(const std::string& path_check);

    /**
     * @brief get environment variables
     * @return
     */
    int getEnvVar(std::string& FTP_SERVER_ADD, int& FTP_SERVER_PORT, std::string& FTP_USERNAME, std::string& FTP_PASSWORD, const nlohmann::json &config);

    /**
     * @brief upload file to ftp server
     * @param path_local
     * @return
     */
    int uploadFile(const std::string& FTP_SERVER_ADD, int& FTP_SERVER_PORT, const std::string& FTP_USERNAME,
                   const std::string& FTP_PASSWORD,const std::string& path_local);

    /**
     * @brief rename file with time stamp
     * @param path
     * @param filename
     * @return
     */
    int renameTimeStamp(const std::string &path, std::string& filename);

    bool renameFileRemote(const std::string& str, const std::string& from, const std::string& to, std::string &res);

    int directoryAndFileRegression(const std::string& path, std::vector<std::string> &listDir, std::vector<std::string> &listFile);

    int uploadDir(const std::string& FTP_SERVER_ADD, int& FTP_SERVER_PORT, const std::string& FTP_USERNAME,
                  const std::string& FTP_PASSWORD,const std::string& path_local);

};


#endif //AUTOUPLOADDATA_FTPUPLOAD_H
