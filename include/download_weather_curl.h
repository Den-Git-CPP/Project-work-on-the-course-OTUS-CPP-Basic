#pragma once

#define CURL_STATICLIB
#include "curl/curl.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <ratio>
#include <chrono>
#include <iomanip>
#include <sstream>

using time_point = std::chrono::system_clock::time_point;

static size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream) {
	size_t written = fwrite(ptr, size, nmemb, static_cast<FILE*>(stream));
	return written;
} /* write_data */

std::string TimeGMTFormatToString(const time_point& in_time, const std::string& format) {
	std::time_t in_tt = std::chrono::system_clock::to_time_t(in_time);
	std::tm out_tm = *std::gmtime(&in_tt);
	std::stringstream ss;
	ss << std::put_time(&out_tm, format.c_str());
	return ss.str();
}

void CurlDownload(const std::string& local_pth_airport_weather, const std::string& http_link_airport_weather) {
	// Download the file using curl library into DownloadCURL folder
	if (CURL* curl = curl_easy_init()) {
		CURLcode res;
		FILE* fp = fopen(local_pth_airport_weather.c_str(), "wb");
		curl_easy_setopt(curl, CURLOPT_URL, http_link_airport_weather.c_str());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // follow redirects
		res = curl_easy_perform(curl);

		fclose(fp);
		if (res != CURLE_OK) {
			const char* str = curl_easy_strerror(res);
			std::ofstream out_file{ local_pth_airport_weather, std::ios_base::app };
			if (!out_file.is_open()) {
				std::cout << "Failed to open file for write" << std::endl;
				exit(1);
			}
			std::cout << "Libcurl said:" << str << "\n";
			out_file << "Libcurl said:" << str << "\n";
			exit(1);
		}
		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();
}/* Download */
void DownloadFile(std::string& ICAO_airport_name) {
	std::chrono::duration<int, std::ratio<14400> > delta_TAF(1);// 3 hours
	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point start = end - delta_TAF;

	std::string local_pth_airport_weather{};
	std::string http_link_airport_weather{};
	http_link_airport_weather = "https://www.aviationweather.gov/adds/dataserver_current/httpparam?dataSource=tafs&requestType=retrieve&format=csv&startTime="
		+ TimeGMTFormatToString(start, "%Y-%m-%dT%H:%M:%SZ")
		+ "&endTime="
		+ TimeGMTFormatToString(end, "%Y-%m-%dT%H:%M:%SZ")
		+ "&timeType=issue&stationString=" + ICAO_airport_name;
	local_pth_airport_weather = ICAO_airport_name + "_TAF.txt";
	CurlDownload(local_pth_airport_weather, http_link_airport_weather);

	std::chrono::duration<int, std::ratio<3600> > delta_METAR(1);// 30min
	start = end - delta_METAR;

	http_link_airport_weather = "https://www.aviationweather.gov/adds/dataserver_current/httpparam?dataSource=metars&requestType=retrieve&format=csv&startTime="
		+ TimeGMTFormatToString(start, "%Y-%m-%dT%H:%M:%SZ")
		+ "&endTime="
		+ TimeGMTFormatToString(end, "%Y-%m-%dT%H:%M:%SZ")
		+ "&stationString=" + ICAO_airport_name;

	local_pth_airport_weather = ICAO_airport_name + "_METAR.txt";
	CurlDownload(local_pth_airport_weather, http_link_airport_weather);
}



