#include "Wind.h"

Wind::Wind(std::vector<std::string>& in_wind_data) {
	wind_dir_degrees_ = in_wind_data.at(0);
	wind_speed_kt_ = in_wind_data.at(1);
	wind_gust_kt_ = in_wind_data.at(2);
}

void Wind::wind_transform() {
	Function::kt_to_ms(wind_speed_kt_);
	Function::kt_to_ms(wind_gust_kt_);
}

void Wind::wind_display() {
	if (wind_dir_degrees_ != "") {
		std::cout << "\n�����: " << wind_dir_degrees_ << "�" << " " << wind_speed_kt_ << " �/�.";
	}
	if (wind_gust_kt_ != "") {
		std::cout << " ������ " << wind_gust_kt_ << "�/�.";;
	}
}
