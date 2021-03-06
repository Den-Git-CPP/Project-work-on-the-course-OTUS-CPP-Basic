#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include <string>
#include <map>

class Function {
public:
	Function() {};
	~Function() {};
	std::map<std::string, std::string> map_airport_Dictionary;
	std::map<std::string, std::string> map_AMOFSG_Dictionary;
protected:
	void load_map_dictionary(const std::filesystem::path& dictionary_path, std::map<std::string, std::string>& Dictionary_);
	std::string replace_raw_text(std::string& raw_str);
	std::string replace_format_time(const std::string& str_time);
	std::string replace_station_id_(std::string& station_id_);
	std::string replace_wx_string_(std::string& wx_string_);
	void replace_change_indicator(std::string& in_change_indicator);
	void replace_sky_cover_(std::string& cloud_base_ft_agl_);
	void replace_cloud_type_(std::string& cloud_type_);
	void replace_flight_category_(std::string& flight_category_);
	void kt_to_ms(std::string& kt);
	void ft_to_m(std::string& ft);
	void mi_to_m(std::string& mi);
	void inch_to_m(std::string& inch);
	void inch_to_mm(std::string& inch);
	void inch_to_bar(std::string& inch);
};

