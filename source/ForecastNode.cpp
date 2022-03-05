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

	in_wx_data.assign(in_forecast_data.begin() + 14, in_forecast_data.begin() + 16);//���������
	wx_string = new Wx(in_wx_data);

	in_sky_cover_data.assign(in_forecast_data.begin() + 16, in_forecast_data.begin() + 25);//������ ����������
	sky_cover = new Sky_Cover(in_sky_cover_data);
	
	in_turbulence_data.assign(in_forecast_data.begin() + 25, in_forecast_data.begin() + 28); // ��������������
	turbulence = new Turbulence(in_turbulence_data);
	
	in_icing_data.assign(in_forecast_data.begin() + 28, in_forecast_data.begin() + 31);// �����������
	icing = new Icing(in_icing_data);

	in_surface_temperature_data.assign(in_forecast_data.begin() + 31, in_forecast_data.begin() + 37);//����������� �����������	
	surface_temperature = new Surface_Temperature(in_surface_temperature_data);
}

Forecast::~Forecast()
{	delete wind;
	delete wind_shear;
	delete visibility;
	delete wx_string;
	delete sky_cover;
	delete turbulence;
	delete icing;
	delete surface_temperature;
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
 wx_string->wx_transform();
 sky_cover->sky_cover_transform();
 turbulence->turbulence_transform();
 icing->icing_transform();
 surface_temperature->surface_temperature_transform();
}

void Forecast::display()
{	std::cout <<clr::green<< "\n\n� ������ � " << fcst_time_from_ << " �� " << fcst_time_to_<<clr::white;
if (change_indicator_ != "") { std::cout <<"\n"<< change_indicator_; };
if (time_becoming_ != "") { std::cout <<"������� c " << time_becoming_; };
if (probability_ != "") { std::cout << "c ������������ " << probability_ << "%"; };

// ���������� ����������� ���������
wind->wind_display();
wind_shear->wind_shear_display();
visibility->visibility_display();
wx_string->wx_display();
sky_cover->sky_cover_display();
turbulence->turbulence_display();
icing->icing_display();
surface_temperature->surface_temperature_display();
}
