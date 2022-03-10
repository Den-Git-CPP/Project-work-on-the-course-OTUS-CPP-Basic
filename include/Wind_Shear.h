#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Function.h"

class Wind_Shear :private Function {
public:
	Wind_Shear();
	Wind_Shear(std::vector<std::string>& in_wind_shear_data);
	~Wind_Shear() {};
	void wind_shear_transform();
	void wind_shear_display();
private:
	std::string wind_shear_hgt_ft_agl_{};
	std::string wind_shear_dir_degrees_{};
	std::string wind_shear_speed_kt_{};
};

