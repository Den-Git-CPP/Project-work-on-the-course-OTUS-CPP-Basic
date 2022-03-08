#pragma once

#include <fstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include "colored_cout.h"
#include "Function.h"
#include "Wind.h"
#include "Station_Sensors.h"
#include "Sky_Cover.h"


class Main_Inform_METAR :private Function
{
public:
	Main_Inform_METAR();
	Main_Inform_METAR(std::vector<std::string>& in_data);
	~Main_Inform_METAR();
	void transform();
	void display();

private:
	std::string raw_text_{};
	std::string station_id_{};
	std::string observation_time_{};
	std::string latitude_{};
	std::string longitude_{};
	std::string temp_c_{};
	std::string dwepoint_c_{};
	Wind* wind = nullptr; std::vector<std::string> in_wind_data;//ветер
	std::string visibility_statute_mi_{};
	std::string altim_in_hg_{};
	std::string sea_level_pressure_mb_{};
	Station_Sensors* station_sensors = nullptr; std::vector<std::string> in_station_sensors_data;
	std::string wx_string_{};
	Sky_Cover* sky_cover = nullptr; std::vector<std::string> in_sky_cover_data;//формат облачности
	std::string flight_category_{};
	std::string three_hr_pressure_tendency_mb_{};
	std::string maxT_c_{};
	std::string minT_c_{};
	std::string maxT24hr_c_{};
	std::string minT24hr_c_{};
	std::string precip_in_{};
	std::string pcp3hr_in_{};
	std::string pcp6hr_in_{};
	std::string pcp24hr_in_{};
	std::string snow_in_{};
	std::string vert_vis_ft_{};
	std::string metar_type_{};
	std::string elevation_m_{};
};