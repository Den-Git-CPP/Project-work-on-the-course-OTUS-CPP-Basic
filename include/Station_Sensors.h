#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Function.h"

class Station_Sensors :public Function {
public:
	Station_Sensors();
	Station_Sensors(std::vector<std::string>& in_station_sensors_data);
	~Station_Sensors() {};

	void station_sensors_transform();
	void station_sensors_display();
private:
	std::string corrected_{};
	std::string auto_wx_{};
	std::string auto_station_{};
	std::string maintenance_indicator_on_{};
	std::string no_signal_{};
	std::string lightning_sensor_off_{};
	std::string freezing_rain_sensor_off_{};
	std::string present_weather_sensor_off_{};
};
