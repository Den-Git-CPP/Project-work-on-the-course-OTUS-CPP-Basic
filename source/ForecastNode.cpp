#include "ForecastNode.h"
Forecast::Forecast(std::vector<std::string>& in_forecast_data)
{
	fcst_time_from_ =in_forecast_data.at(0);
	fcst_time_to_ =  in_forecast_data.at(1);
	change_indicator_=in_forecast_data.at(2);
	time_becoming_ = in_forecast_data.at(3);
	probability_=in_forecast_data.at(4);

	//������������� ���������� ������� � ������� Forecast
	in_wind_data.assign(in_forecast_data.begin() + 5, in_forecast_data.begin() + 8);//�����
	wind= new Wind(in_wind_data);
	
	in_wind_shear_data.assign(in_forecast_data.begin() + 8, in_forecast_data.begin() + 11);//����� �����
	wind_shear = new Wind_Shear(in_wind_shear_data);
	
	in_visibility_data.assign(in_forecast_data.begin() + 11, in_forecast_data.begin() + 14);//���������
	visibility = new Visibility(in_visibility_data);
}

Forecast::~Forecast()
{	delete wind;
	delete wind_shear;
	delete visibility;
}

void Forecast::forecast_transform()
{fcst_time_from_ = Function::replace_format_time(fcst_time_from_);
 fcst_time_to_ = Function::replace_format_time(fcst_time_to_);
 Function::replace_change_indicator(change_indicator_);
 time_becoming_ = Function::replace_format_time(time_becoming_);
 // ���������������� ����������� ���������
 wind->wind_transform();
 wind_shear->wind_shear_transform();
 visibility->visibility_transform();
}

void Forecast::display()
{	std::cout << "\n� ������ � " << fcst_time_from_ << " �� " << fcst_time_to_ << "\n";
if (change_indicator_ != "") { std::cout << change_indicator_; };
if (time_becoming_ != "") { std::cout <<"������� c " << time_becoming_; };
if (probability_ != "") { std::cout << "c ������������ " << probability_ << "%"; };

// ���������� ����������� ���������
wind->wind_display();
wind_shear->wind_shear_display();
visibility->visibility_display();
}
