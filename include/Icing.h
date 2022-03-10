#pragma once
#include<iostream>
#include <string>
#include <vector>
#include "Function.h"

class Icing :public Function {
public:
	Icing();
	Icing(std::vector<std::string>& in_icing_data);
	~Icing() {};

	void icing_transform();
	void icing_display();
private:
	std::string icing_intensity_{};
	std::string icing_min_alt_ft_agl_{};
	std::string icing_max_alt_ft_agl_{};
};