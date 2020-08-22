//
// Created by dungpb on 21/08/2020.
//

#include <sys/stat.h>
#include <curl/curl.h>
#include <stdio.h>
#include <fcntl.h>

int main(){
    CURL *curl;
    CURLcode res;
    struct stat file_info;
    curl_off_t speed_upload, total_time;
    FILE *fd;

    fd = fopen("/home/dungpb/gentoo_root.img", "rb");

    if(!fd)
        return 1;

    if(fstat(fileno(fd), &file_info) != 0)
        return 1;

    curl = curl_easy_init();

    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL,
                         "ftp://ftp.dlptest.com/curl-7.72.0.zip");

        curl_easy_setopt( curl, CURLOPT_USERPWD, "dlpuser@dlptest.com:eUj8GeW55SvYaswqUyDSm5v6N" );

        /* tell it to "upload" to the URL */
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        /* set where to read from (on Windows you need to use READFUNCTION too) */
        curl_easy_setopt(curl, CURLOPT_READDATA, fd);

        /* and give the size of the upload (optional) */
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,
                         (curl_off_t)file_info.st_size);

        /* enable verbose for easier tracing */
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        } else {
        /* now extract transfer info */
        curl_easy_getinfo(curl, CURLINFO_SPEED_UPLOAD_T, &speed_upload);
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &total_time);

        fprintf(stderr, "Speed: %" CURL_FORMAT_CURL_OFF_T " bytes/sec during %"
                        CURL_FORMAT_CURL_OFF_T ".%06ld seconds\n",
                speed_upload,
                (total_time / 1000000), (long)(total_time % 1000000));

        }
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    fclose(fd);
    return 0;
}