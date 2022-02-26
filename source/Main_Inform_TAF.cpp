#include "Main_Inform_TAF.h"

Main_Inform_TAF::Main_Inform_TAF(std::vector<std::string>& in_data) 	
{   
	raw_text_ = in_data.at(0);
	station_id_ = in_data.at(1);
	issue_time_ = in_data.at(2);
	bulletin_time_ = in_data.at(3);
	valid_time_from_ = in_data.at(4);
	valid_time_to_ = in_data.at(5);
	remarks_=in_data.at(6);
	
	latitude_=std::stof(in_data.at(7));
	longitude_=std::stof(in_data.at(8));
	elevation_m_=std::stof(in_data.at(9));
}

void Main_Inform_TAF::transform(){ 	
//raw_text_ = 
// 	station_id_ = 
// 	issue_time_ = 
// 	bulletin_time_ = 
// 	valid_time_from_ = 
// 	valid_time_to_ = 
}

void Main_Inform_TAF::display(){
//
}

std::string Main_Inform_TAF::replace_raw_taf(const std::string& raw_str_taf)
{	std::istringstream ss(raw_str_taf);
	std::ostringstream os;

	std::for_each(
		std::istream_iterator<std::string>(ss),
		std::istream_iterator<std::string>(),
		[&](const std::string& s) 
		{
			if ((s == "TEMPO") ||
				(s == "BECMG") ||
				(s == "FM")
				)
			{
				os << "\n\t" << s << "\t";
			}
			else
			{
				os << " " << s;
			};
		}
			);
	return os.str();
}




