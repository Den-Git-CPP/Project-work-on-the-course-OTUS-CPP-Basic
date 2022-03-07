#include "Station_Sensors.h"

Station_Sensors::Station_Sensors(std::vector<std::string>& in_station_sensors_data)
{
	corrected_ = in_station_sensors_data.at(0);
	auto_wx_=in_station_sensors_data.at(1);
	auto_station_=in_station_sensors_data.at(2);
	maintenance_indicator_on_=in_station_sensors_data.at(3);
	no_signal_=in_station_sensors_data.at(4);
	lightning_sensor_off_=in_station_sensors_data.at(5);
	freezing_rain_sensor_off_=in_station_sensors_data.at(6);
	present_weather_sensor_off_=in_station_sensors_data.at(7);
}

void Station_Sensors::station_sensors_transform()
{	if (!auto_station_.empty()) { auto_station_ = "\n��� ������������������ �������: "+ auto_station_; };
}

void Station_Sensors::station_sensors_display()
{
	std::cout <<"\n\n���������� � �������� ������� METAR.";
	if (!corrected_.empty()) { std::cout << "\n�����������->"<< corrected_; };
	if (!auto_wx_.empty()) { std::cout << "\n������ �������������->"<< auto_wx_; };
	if (!auto_station_.empty()) { std::cout << auto_station_; };
	if (!maintenance_indicator_on_.empty()) { std::cout << "\n��������� ����������� ������������->"; }; \
	if (!no_signal_.empty()) { std::cout <<"�������������� ����� �������->"<<no_signal_; };
	if (!lightning_sensor_off_.empty()) { std::cout << "\n������ ����������� ������->"<< lightning_sensor_off_; };
	if (!freezing_rain_sensor_off_.empty()) { std::cout << "\n������ �������� �����->"<< freezing_rain_sensor_off_; };
	if (!present_weather_sensor_off_.empty()) { std::cout << "\n������ ������� ������->"<< present_weather_sensor_off_; };
}
