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
	//Долгота и широта аропорта
	latitude_=std::stof(in_data.at(7));
	longitude_=std::stof(in_data.at(8));
	// превышение аэропорта
	elevation_m_=std::stof(in_data.at(9));
	//создаем вектор сводок прогноза по временам 
	all_forecast_node.reserve(10);
	auto it = in_data.begin() + 10;
	while ((it != in_data.end()) and (*it != "")){	
		v_init_forecast.assign(it, it + 37);
		Forecast* frc = new Forecast(v_init_forecast);
		all_forecast_node.push_back(*frc);
		std::advance(it, 37);
	};
}
Main_Inform_TAF::~Main_Inform_TAF()
{
	
}
void Main_Inform_TAF::transform(){ 	
//TODO продумать класс функций для перевода мер
	
}

void Main_Inform_TAF::display(){
	cout<< "Дата и время подготовки прогноза: " << issue_time_ << "\n"
		<< "Время выпуска бюллетеня прогноза: "<< bulletin_time_ << "\n"
		<< "Действует  с:                     "<< valid_time_from_ << "\n"
		<< "Действует по:                     "<< valid_time_to_ << "\n"
		<< "Дополнительная информация:        " << remarks_ << "\n"
		<< "Аэропорт:" << station_id_ << "\t"
		<< "Широта:" << latitude_ << "\t"
		<< "Долгота:" << longitude_ << "\t"
		<< "Превышение:" << elevation_m_ << "\n"
		<< "Сводка:" << raw_text_ << "\n";
//отобразили каждый подпрогноз в векторе прогнозов all_forecast_node
 	for (auto it = all_forecast_node.begin(); it != all_forecast_node.end(); it++){
	it->display();
		}
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




