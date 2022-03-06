#pragma once

#define CURL_STATICLIB
#include "curl/curl.h"
#include <cstdio>
#include <iostream>
#include <fstream>

#include <ratio>
#include <chrono>

static size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream) {
    size_t written = fwrite(ptr, size, nmemb, static_cast<FILE*>(stream));
    return written;
} /* write_data */

void DownloadFile(std::string &ICAO_airport_name) {
   std::chrono::duration<int, std::ratio<14400> > delta(1);
    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point start = end - delta;
     
    std::string http_link_airport_weather ="https://www.aviationweather.gov/adds/dataserver_current/httpparam?dataSource=tafs&requestType=retrieve&format=csv&startTime="
    +std::to_string(std::chrono::system_clock::to_time_t(start))
    +"&endTime="
    + std::to_string(std::chrono::system_clock::to_time_t(end))
    +"&timeType=issue&stationString="+ ICAO_airport_name;

    std::string local_pth_airport_weather = ICAO_airport_name+".txt";
    // Download the file using curl library into DownloadCURL folder
         
    if(CURL* curl = curl_easy_init()) 
    {   CURLcode res;
        FILE* fp = fopen(local_pth_airport_weather.c_str(), "wb");
            curl_easy_setopt(curl, CURLOPT_URL, http_link_airport_weather.c_str());
            curl_easy_setopt (curl, CURLOPT_SSL_VERIFYHOST, 0);
            curl_easy_setopt (curl, CURLOPT_SSL_VERIFYPEER, 0); 
            curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // follow redirects
            res = curl_easy_perform(curl);

        fclose(fp);
           if (res != CURLE_OK) {
        const char* str = curl_easy_strerror(res);
        std::ofstream out_file{ local_pth_airport_weather, std::ios_base::app };
        if (!out_file.is_open())
        {
            std::cout << "Failed to open file for write" << std::endl;
            exit(1);
        }
        std::cout << "Libcurl said:" <<str<<"\n";
        out_file  << "Libcurl said:" <<str<< "\n";
        exit(1);
        }


        curl_easy_cleanup(curl);
    } 

 curl_global_cleanup();
} /* Download */



