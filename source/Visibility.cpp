#include "Visibility.h"

Visibility::Visibility(std::vector<std::string> &in_visibility_data)
{	
	visibility_statute_mi_= in_visibility_data.at(0);
	altim_in_hg_ = in_visibility_data.at(1);
	vert_vis_ft_ = in_visibility_data.at(2);

}

void Visibility::visibility_transform()
{	Function::mi_to_m(visibility_statute_mi_);
	Function::inch_to_m(altim_in_hg_);
	Function::ft_to_m(vert_vis_ft_);
}

void Visibility::visibility_display()
{	if (visibility_statute_mi_ != "") {
		std::cout << "\nVisibility:" << " " << visibility_statute_mi_ << "m.";
	}
	if (altim_in_hg_ != "") {
		std::cout << "\nAltimeter: " << " " << altim_in_hg_ << "mm Hg";
	}
	if (vert_vis_ft_ != "") {
		std::cout << "\nVertical visibility: " << " " << vert_vis_ft_ << "m.";
	}
	
}
