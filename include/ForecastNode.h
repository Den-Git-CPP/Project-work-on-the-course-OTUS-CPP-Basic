#pragma once
#include <vector>
#include "colored_cout.h"
#include "Function.h"
#include "Wind.h"
#include "Wind_Shear.h"
#include "Sky_Cover.h"
#include "Turbulence.h"
#include "Icing.h"
#include "Surface_Temperature.h"

using std::cout;

class Forecast :private Function {
public:
	Forecast();
	Forecast(std::vector<std::string>& in_forecast_data);
	~Forecast();
	void forecast_transform();
	void display();
private:
	std::string fcst_time_from_{};
	std::string fcst_time_to_{};
	std::string change_indicator_{};
	std::string time_becoming_{};
	std::string probability_{};
	std::string wx_string_{};
	std::string not_decoded_{};
	Wind* wind = nullptr;						std::vector<std::string> in_wind_data;//�����
	Wind_Shear* wind_shear = nullptr;		std::vector<std::string> in_wind_shear_data;//����� ������
	std::string visibility_statute_mi_{};
	std::string altim_in_hg_{};
	std::string vert_vis_ft_{};
	Sky_Cover* sky_cover = nullptr;			std::vector<std::string> in_sky_cover_data;//������ ����������
	Turbulence* turbulence = nullptr;		std::vector<std::string> in_turbulence_data; // ��������������
	Icing* icing = nullptr;					std::vector<std::string> in_icing_data;// �����������
	Surface_Temperature* surface_temperature = nullptr; std::vector<std::string> in_surface_temperature_data;//����������� �����������	
};


