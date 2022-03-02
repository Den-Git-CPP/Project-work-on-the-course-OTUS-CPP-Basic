#include "Icing.h"

Icing::Icing(std::vector<std::string>& in_icing_data)
{
	icing_intensity_= in_icing_data.at(0);
	icing_min_alt_ft_agl_ = in_icing_data.at(1);
	icing_max_alt_ft_agl_ = in_icing_data.at(2);
}

void Icing::icing_transform()
{	Function::ft_to_m(icing_min_alt_ft_agl_);
	Function::ft_to_m(icing_max_alt_ft_agl_);
}

void Icing::icing_display()
{	if (!icing_intensity_.empty())
	{std::cout << "\nОбледенение" << icing_intensity_
	     		<< " от высоты " << icing_min_alt_ft_agl_ << " м."
				<< " до высоты " << icing_min_alt_ft_agl_ << " м.";
	}
}
