#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Function.h"

class Turbulence :private Function {
public:
	Turbulence();
	Turbulence(std::vector<std::string>& in_turbulence_data);
	~Turbulence() {};
	void turbulence_transform();
	void turbulence_display();

private:
	std::string turbulence_intensity_{};
	std::string turbulence_min_alt_ft_agl_{};
	std::string turbulence_max_alt_ft_agl_{};
};

