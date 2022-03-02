#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Function.h"

class Wx:private Function
{
public:
	Wx();
	Wx(std::vector<std::string>& in_wx_data);
	~Wx() {};

	void wx_transform();
	void wx_display();
private:
	std::string wx_string_{};
	std::string not_decoded_{};
};

