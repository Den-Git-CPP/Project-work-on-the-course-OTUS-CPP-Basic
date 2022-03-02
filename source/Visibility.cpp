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
		std::cout << "\n���������:" << " " << visibility_statute_mi_ << " �.";
	}
	if (altim_in_hg_ != "") {
		std::cout << "\n�������� ���������:" << " " << altim_in_hg_ << " �� ��.��.";
	}
	if (vert_vis_ft_ != "") {
		std::cout << "\n������������ ���������: " << " " << vert_vis_ft_ << " �.";
	}
	
}
