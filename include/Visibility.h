#pragma once
#include <iostream>
#include <vector>
#include"Function.h"

class Visibility:private Function
{
public:
	Visibility() {};
	Visibility(std::vector<std::string> &in_visibility_data);
	~Visibility() {};
	void visibility_transform();
	void visibility_display();
private:
	std::string visibility_statute_mi_{};
	std::string altim_in_hg_{};
	std::string vert_vis_ft_{};
};
