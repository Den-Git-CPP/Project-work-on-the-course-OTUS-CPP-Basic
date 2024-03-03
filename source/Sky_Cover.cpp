#include "Sky_Cover.h"

Sky_Cover::Sky_Cover(std::vector<std::string>& in_sky_cover_data) {
	arguments = static_cast<int>(in_sky_cover_data.size());
	switch (arguments) {
	case 8:
		sky_cover_ = in_sky_cover_data.at(0);
		cloud_base_ft_agl_ = in_sky_cover_data.at(1);

		sky_cover1_ = in_sky_cover_data.at(2);
		cloud_base_ft_agl1_ = in_sky_cover_data.at(3);

		sky_cover2_ = in_sky_cover_data.at(4);
		cloud_base_ft_agl2_ = in_sky_cover_data.at(5);

		sky_cover3_ = in_sky_cover_data.at(6);
		cloud_base_ft_agl3_ = in_sky_cover_data.at(7);
		break;
	case 9:
		sky_cover_ = in_sky_cover_data.at(0);
		cloud_base_ft_agl_ = in_sky_cover_data.at(1);
		cloud_type_ = in_sky_cover_data.at(2);

		sky_cover1_ = in_sky_cover_data.at(3);
		cloud_base_ft_agl1_ = in_sky_cover_data.at(4);
		cloud_type1_ = in_sky_cover_data.at(5);

		sky_cover2_ = in_sky_cover_data.at(6);
		cloud_base_ft_agl2_ = in_sky_cover_data.at(7);
		cloud_type2_ = in_sky_cover_data.at(8);
		break;
	default:
		std::cout << "incorrect class Sky_Cover initialization";
	}
}

void Sky_Cover::sky_cover_transform() {
	switch (arguments) {
	case 8:

		if (!sky_cover_.empty()) {
			Function::replace_sky_cover_(sky_cover_);
			Function::ft_to_m(cloud_base_ft_agl_);
		}
		if (!sky_cover1_.empty()) {
			Function::replace_sky_cover_(sky_cover1_);
			Function::ft_to_m(cloud_base_ft_agl1_);
		}
		if (!sky_cover2_.empty()) {
			Function::replace_sky_cover_(sky_cover2_);
			Function::ft_to_m(cloud_base_ft_agl2_);
		}
		if (!sky_cover3_.empty()) {
			Function::replace_sky_cover_(sky_cover3_);
			Function::ft_to_m(cloud_base_ft_agl3_);
		}
		break;
	case 9:
	{if (!sky_cover_.empty()) {
		Function::replace_sky_cover_(sky_cover_);
		Function::ft_to_m(cloud_base_ft_agl_);
		Function::replace_cloud_type_(cloud_type_);
	}
	if (!sky_cover1_.empty()) {
		Function::replace_sky_cover_(sky_cover1_);
		Function::ft_to_m(cloud_base_ft_agl1_);
		Function::replace_cloud_type_(cloud_type1_);
	}
	if (!sky_cover2_.empty()) {
		Function::replace_sky_cover_(sky_cover2_);
		Function::ft_to_m(cloud_base_ft_agl2_);
		Function::replace_cloud_type_(cloud_type2_);
	}
	}
	break;
	default:
		std::cout << "incorrect class Sky_Cover transform";
	}

}

void Sky_Cover::sky_cover_display() {
	switch (arguments) {
	case 8:
	{if (!sky_cover_.empty()) {
		std::cout << "\n" << sky_cover_;
		if (!cloud_base_ft_agl_.empty()) {
			std::cout << " на " << cloud_base_ft_agl_ << " м.";
		}
	}
	if (!sky_cover1_.empty()) {
		std::cout << "\n" << sky_cover1_
			<< " на " << cloud_base_ft_agl1_ << " м.";
	}
	if (!sky_cover2_.empty()) {
		std::cout << "\n" << sky_cover2_
			<< " на " << cloud_base_ft_agl2_ << " м.";
	}
	if (!sky_cover2_.empty()) {
		std::cout << "\n" << sky_cover3_
			<< " на " << cloud_base_ft_agl3_ << " м.";
	}
	}
	break;
	case 9:
	{if (!sky_cover_.empty()) {
		std::cout << "\n" << sky_cover_
			<< " на " << cloud_base_ft_agl_ << " м."
			<< cloud_type_;
	}
	if (!sky_cover1_.empty()) {
		std::cout << "\n" << sky_cover1_
			<< " на " << cloud_base_ft_agl1_ << " м."
			<< cloud_type1_;
	}
	if (!sky_cover2_.empty()) {
		std::cout << "\n" << sky_cover2_
			<< " на " << cloud_base_ft_agl2_ << " м."
			<< cloud_type2_;
	}
	}
	break;
	default:
		std::cout << "incorrect class Sky_Cover display";
	}

}
