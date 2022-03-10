#pragma once

#include<iostream>
#include<string>
#include<vector>
#include"Function.h"

class Sky_Cover :private Function {
public:
	Sky_Cover();
	Sky_Cover(std::vector<std::string>& in_sky_cover_data);
	~Sky_Cover() {};
	void sky_cover_transform();
	void sky_cover_display();

private:
	int arguments{};
	std::string sky_cover_{};
	std::string cloud_base_ft_agl_{};
	std::string cloud_type_{};

	std::string sky_cover1_{};
	std::string cloud_base_ft_agl1_{};
	std::string cloud_type1_{};

	std::string sky_cover2_{};
	std::string cloud_base_ft_agl2_{};
	std::string cloud_type2_{};

	std::string sky_cover3_{};
	std::string cloud_base_ft_agl3_{};
};

