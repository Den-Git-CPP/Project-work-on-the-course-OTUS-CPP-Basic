#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Function.h"

class Wind : private Function {
public:
	Wind();
	Wind(std::vector<std::string>& in_wind_data);
	~Wind() {};

	void wind_transform();
	void wind_display();
private:
	std::string wind_dir_degrees_{};
	std::string wind_speed_kt_{};
	std::string wind_gust_kt_{};
};
