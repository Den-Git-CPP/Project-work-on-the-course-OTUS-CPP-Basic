#include "Turbulence.h"

Turbulence::Turbulence(std::vector<std::string>& in_turbulence_data) {
	turbulence_intensity_ = in_turbulence_data.at(0);
	turbulence_min_alt_ft_agl_ = in_turbulence_data.at(1);
	turbulence_max_alt_ft_agl_ = in_turbulence_data.at(2);
}

void Turbulence::turbulence_transform() {
	Function::ft_to_m(turbulence_min_alt_ft_agl_);
	Function::ft_to_m(turbulence_max_alt_ft_agl_);
}

void Turbulence::turbulence_display() {
	if (!turbulence_intensity_.empty()) {
		std::cout << "\n���������������" << turbulence_intensity_
			<< " �� ������ " << turbulence_min_alt_ft_agl_ << " �."
			<< " �� ������ " << turbulence_max_alt_ft_agl_ << " �.";
	}
}
