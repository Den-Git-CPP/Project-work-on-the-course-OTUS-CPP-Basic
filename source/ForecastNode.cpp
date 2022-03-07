#include "ForecastNode.h"
Forecast::Forecast(std::vector<std::string>& in_forecast_data)
{ Function::load_map_dictionary("../dictionary/AMOFSG_Dictionary.txt", map_AMOFSG_Dictionary);
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

	altim_in_hg_= in_forecast_data.at(12);
	vert_vis_ft_= in_forecast_data.at(13);
	wx_string_= in_forecast_data.at(14);
	not_decoded_ =in_forecast_data.at(15);

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
 Function::mi_to_m(visibility_statute_mi_);
 Function::inch_to_m(altim_in_hg_);
 Function::ft_to_m(vert_vis_ft_);
 Function::replace_wx_string_(wx_string_);
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
wind->wind_display();
wind_shear->wind_shear_display();
if (visibility_statute_mi_ != "") {std::cout << "\n���������:" << " " << visibility_statute_mi_ << " �.";}
if (altim_in_hg_ != "") {std::cout << "\n�������� ���������:" << " " << altim_in_hg_ << " �� ��.��.";}
if (vert_vis_ft_ != "") {std::cout << "\n������������ ���������: " << " " << vert_vis_ft_ << " �.";}
if (wx_string_ != "") { std::cout << "\n�������: " << wx_string_ << "\n"; }
if (not_decoded_ != "") { std::cout << "\n�� ������������:" << not_decoded_ << "\n"; }
sky_cover->sky_cover_display();
turbulence->turbulence_display();
icing->icing_display();
surface_temperature->surface_temperature_display();
}
