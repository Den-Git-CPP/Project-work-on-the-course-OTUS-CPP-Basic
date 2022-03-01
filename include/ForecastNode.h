#pragma once
#include <vector>
#include "Function.h"
#include "Wind.h"
#include "Wind_Shear.h"
#include "Visibility.h"

using std::cout;

class Forecast:private Function
{
public:
	Forecast();
	Forecast(std::vector<std::string> &in_forecast_data);
	~Forecast();
	void forecast_transform();
	void display();
private:
	std::string fcst_time_from_{};
	std::string fcst_time_to_{};
	std::string change_indicator_{};
	std::string time_becoming_{};
	std::string probability_{};
	Wind* wind=nullptr;						std::vector<std::string> in_wind_data;//ветер
	Wind_Shear* wind_shear = nullptr;		std::vector<std::string> in_wind_shear_data;//сдвиг ветрва
	Visibility* visibility = nullptr;		std::vector<std::string> in_visibility_data;//видимость
};


