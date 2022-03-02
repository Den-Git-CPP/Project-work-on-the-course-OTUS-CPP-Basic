#include "Surface_Temperature.h"

Surface_Temperature::Surface_Temperature(std::vector<std::string> &in_surface_temperature_data)
{
	valid_time_= in_surface_temperature_data.at(0);
	sfc_temp_c_ = in_surface_temperature_data.at(1);
	max_or_min_temp_c_ = in_surface_temperature_data.at(2);

	valid_time1_ = in_surface_temperature_data.at(3);
	sfc_temp_c1_ = in_surface_temperature_data.at(4);
	max_or_min_temp_c1_ = in_surface_temperature_data.at(5);
}

void Surface_Temperature::surface_temperature_transform()
{
	if (!valid_time_.empty()) {
		Function::replace_format_time(valid_time_);
	}
	if (!valid_time1_.empty()) {
		Function::replace_format_time(valid_time1_);
	}
}

void Surface_Temperature::surface_temperature_display()
{
	if (!valid_time_.empty()) {
		std::cout << valid_time_
			<< "\nПриземная температура "
			<< sfc_temp_c_
			<< max_or_min_temp_c_ << "\n";
	}
	if (!valid_time1_.empty()) {
		std::cout << valid_time1_
			<< "\nПриземная температура "
			<< sfc_temp_c1_
			<< max_or_min_temp_c1_ << "\n";
	}
}
