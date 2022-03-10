#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Function.h"

class Surface_Temperature : private Function {
public:
	Surface_Temperature();
	Surface_Temperature(std::vector<std::string>& in_surface_temperature_data);
	~Surface_Temperature() {};

	void surface_temperature_transform();
	void surface_temperature_display();
private:
	std::string valid_time_{};
	std::string sfc_temp_c_{};
	std::string max_or_min_temp_c_{};

	std::string valid_time1_{};
	std::string sfc_temp_c1_{};
	std::string max_or_min_temp_c1_{};
};

