#pragma once
#include <fstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include "colored_cout.h"
#include "Function.h"
#include "ForecastNode.h"


class Main_Inform_TAF :private Function {
public:
	Main_Inform_TAF();
	Main_Inform_TAF(std::vector<std::string>& in_data);
	~Main_Inform_TAF();
	void transform();
	void display();

private:
	std::string raw_text_{};
	std::string station_id_{};
	std::string issue_time_{};
	std::string bulletin_time_{};
	std::string valid_time_from_{};
	std::string valid_time_to_{};
	std::string remarks_{};
	std::string latitude_{};
	std::string longitude_{};
	std::string elevation_m_{};
	std::vector<Forecast> all_forecast_node;
	Forecast* forecast = nullptr; std::vector<std::string>v_init_forecast;

	std::string replace_raw_taf(const std::string& raw_str_taf);
};

