#include "Main_Inform_METAR.h"

Main_Inform_METAR::Main_Inform_METAR(std::vector<std::string>& in_data) {
	raw_text_ = in_data.at(0);
	station_id_ = in_data.at(1);
	observation_time_ = in_data.at(2);
	latitude_ = in_data.at(3);
	longitude_ = in_data.at(4);
	temp_c_ = in_data.at(5);
	dwepoint_c_ = in_data.at(6);
	in_wind_data.assign(in_data.begin() + 7, in_data.begin() + 10);
	wind = new Wind(in_wind_data);
	visibility_statute_mi_ = in_data.at(10);
	altim_in_hg_ = in_data.at(11);
	sea_level_pressure_mb_ = in_data.at(12);
	in_station_sensors_data.assign(in_data.begin() + 13, in_data.begin() + 21);
	station_sensors = new Station_Sensors(in_station_sensors_data);
	wx_string_ = in_data.at(21);
	in_sky_cover_data.assign(in_data.begin() + 22, in_data.begin() + 30);
	sky_cover = new Sky_Cover(in_sky_cover_data);
	flight_category_ = in_data.at(30);
	three_hr_pressure_tendency_mb_ = in_data.at(31);
	maxT_c_ = in_data.at(32);
	minT_c_ = in_data.at(33);
	maxT24hr_c_ = in_data.at(34);
	minT24hr_c_ = in_data.at(35);
	precip_in_ = in_data.at(36);
	pcp3hr_in_ = in_data.at(37);
	pcp6hr_in_ = in_data.at(38);
	pcp24hr_in_ = in_data.at(39);
	snow_in_ = in_data.at(40);
	vert_vis_ft_ = in_data.at(41);
	metar_type_ = in_data.at(42);
	elevation_m_ = in_data.at(43);
}

Main_Inform_METAR::~Main_Inform_METAR() {
	delete wind;
	delete sky_cover;
	delete station_sensors;
}

void Main_Inform_METAR::transform() {
	Function::load_map_dictionary("../dictionary/NameAirport.txt", map_airport_Dictionary);
	Function::load_map_dictionary("../dictionary/AMOFSG_Dictionary.txt", map_AMOFSG_Dictionary);

	raw_text_ = Function::replace_raw_text(raw_text_);
	station_id_ = Function::replace_station_id_(station_id_);
	observation_time_ = Function::replace_format_time(observation_time_);
	wind->wind_transform();
	Function::mi_to_m(visibility_statute_mi_);
	Function::inch_to_bar(altim_in_hg_);
	station_sensors->station_sensors_transform();
	Function::replace_wx_string_(wx_string_);
	sky_cover->sky_cover_transform();
	Function::replace_flight_category_(flight_category_);
	Function::inch_to_mm(precip_in_);
	Function::inch_to_mm(pcp3hr_in_);
	Function::inch_to_mm(pcp6hr_in_);
	Function::inch_to_mm(pcp24hr_in_);
	Function::inch_to_mm(snow_in_);
}

void Main_Inform_METAR::display() {
	std::cout << clr::yellow << "\nФАКТИЧЕСКАЯ ПОГОДА:" << clr::white
		<< "\nДата и время наблюдения:\t" << observation_time_
		<< clr::cyan
		<< "\nАэропорт:" << station_id_
		<< clr::white
		<< "\tШирота:" << latitude_
		<< "\tДолгота:" << longitude_
		<< "\tПревышение:" << elevation_m_
		<< "\nСводка:" << raw_text_;
	wind->wind_display();
	sky_cover->sky_cover_display();
	if (!wx_string_.empty()) {
		std::cout << wx_string_;
	}
	if (!temp_c_.empty()) {
		std::cout << "\nTемпература воздуха:     " << temp_c_ << " °C";
	}
	if (!dwepoint_c_.empty()) {
		std::cout << "\nTемпература точки росы:  " << dwepoint_c_ << " °C";
	}
	if (!sea_level_pressure_mb_.empty()) {
		std::cout << "\nДавление аэропорта по уровню моря:" << " " << sea_level_pressure_mb_ << " мб.";
	}
	if (!altim_in_hg_.empty()) {
		std::cout << "\nДавление аэропорта:\t " << altim_in_hg_ << " мб.";
	}
	if (!flight_category_.empty()) {
		std::cout << flight_category_;
	}
	if (!three_hr_pressure_tendency_mb_.empty()) {
		std::cout << "\nИзменение давления за последние 3 часа" << three_hr_pressure_tendency_mb_ << "мб.";
	}
	if (!maxT_c_.empty()) {
		std::cout << "\nМаксимальная температура воздуха за последние 6 часов" << maxT_c_ << " °C.";
	}
	if (!minT_c_.empty()) {
		std::cout << "\nМинимальная температура воздуха за последние 6 часов" << minT_c_ << " °C.";
	}
	if (!maxT24hr_c_.empty()) {
		std::cout << "\nМаксимальная температура воздуха за последние 24 часа: " << maxT24hr_c_ << " °C.";
	}
	if (!minT24hr_c_.empty()) {
		std::cout << "\nМинимальная температура воздуха за последние 24 часа: " << minT24hr_c_ << " °C.";
	}
	if (!precip_in_.empty()) {
		std::cout << "\nКоличество осадков с момента выпуска крайней сводки METAR: " << precip_in_ << " мм.";
	}
	if (!pcp3hr_in_.empty()) {
		std::cout << "\nКоличество осадков за последние 3 часа: " << pcp3hr_in_ << " мм.";
	}
	if (!pcp6hr_in_.empty()) {
		std::cout << "\nКоличество осадков за последние 6 часов: " << pcp6hr_in_ << " мм.";
	}
	if (!pcp24hr_in_.empty()) {
		std::cout << "\nКоличество осадков за последние 24 часа: " << pcp24hr_in_ << " мм.";
	}
	if (!snow_in_.empty()) {
		std::cout << "\nГлубина снежного покрова" << snow_in_ << " мм.";
	}
	//Инофрмация от датчиков станции НЕ НУЖНА
	/*
	station_sensors->station_sensors_display();
	*/
}
