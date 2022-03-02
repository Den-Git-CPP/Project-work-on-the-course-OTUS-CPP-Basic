#include "Wind_Shear.h"

Wind_Shear::Wind_Shear(std::vector<std::string> &in_wind_shear_data)
{	wind_shear_hgt_ft_agl_= in_wind_shear_data.at(0);
	wind_shear_dir_degrees_ = in_wind_shear_data.at(1);
	wind_shear_speed_kt_ = in_wind_shear_data.at(2);
}

void Wind_Shear::wind_shear_transform()
{	Function::ft_to_m(wind_shear_hgt_ft_agl_);
	Function::kt_to_ms(wind_shear_speed_kt_);
}

void Wind_Shear::wind_shear_display()
{	if (wind_shear_hgt_ft_agl_ != "") {
		std::cout << "\n—двиг ветра на высоте"
			<< wind_shear_hgt_ft_agl_
			<< " " << wind_shear_dir_degrees_ << "∞"
			<< " " << wind_shear_speed_kt_ << " м/с";
	}	
}
