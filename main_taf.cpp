#define CURL_STATICLIB
#include "curl/curl.h"
#include <cstdio>
#include <iostream>

using namespace std;

static size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream) {
    size_t written = fwrite(ptr, size, nmemb, static_cast<FILE*>(stream));
    return written;
} /* write_data */

void DownloadFile(string &ICAO_airport_name) {

    string http_link_airport_weather ="https://www.aviationweather.gov/adds/dataserver_current/httpparam?dataSource=tafs&requestType=retrieve&format=csv&stationString="+ICAO_airport_name+"%20&hoursBeforeNow=1";
    string local_pth_airport_weather = ICAO_airport_name+".txt";

    // Download the file using curl library into DownloadCURL folder
    if(CURL* curl = curl_easy_init()) 
    {
        FILE* fp = fopen(local_pth_airport_weather.c_str(), "wb");
            curl_easy_setopt(curl, CURLOPT_URL, http_link_airport_weather.c_str());
            curl_easy_setopt (curl, CURLOPT_SSL_VERIFYHOST, 0);
            curl_easy_setopt (curl, CURLOPT_SSL_VERIFYPEER, 0); 
            curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // follow redirects
            curl_easy_perform(curl);

        fclose(fp);
        curl_easy_cleanup(curl);
    } 

 curl_global_cleanup();



} /* Download */

int main() {
    cout<<"ICAO_airport_name\t";
    string ICAO_airport_name;
    cin>>ICAO_airport_name;
    DownloadFile(ICAO_airport_name);
}

