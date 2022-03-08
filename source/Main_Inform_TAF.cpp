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
	latitude_=in_data.at(7);
	longitude_=in_data.at(8);
	elevation_m_=in_data.at(9);
	all_forecast_node.reserve(10);
	auto it = in_data.begin() + 10;
	Function::load_map_dictionary("../dictionary/NameAirport.txt",map_airport_Dictionary);
	
	while ((it != in_data.end()) and (*it != ""))
	{	v_init_forecast.assign(it, it + 37);
		Forecast* frc = new Forecast(v_init_forecast);
		all_forecast_node.push_back(*frc);
		std::advance(it, 37);
	}
}

Main_Inform_TAF::~Main_Inform_TAF()
{
	delete [] forecast;
}

void Main_Inform_TAF::transform()
{  //отформатирован чистый текст raw_text_taf
	raw_text_ = Function::replace_raw_text(raw_text_);
	//переведено название аэропорта
	station_id_ = Function::replace_station_id_(station_id_);
	//отформатировано время из ISO8601 UTC  в необходимый формат UTC
	issue_time_ = Function::replace_format_time(issue_time_);
	bulletin_time_ = Function::replace_format_time(bulletin_time_);
	valid_time_from_ = Function::replace_format_time(valid_time_from_);
	valid_time_to_ = Function::replace_format_time(valid_time_to_);
	//перевели каждый подпрогноз в векторе прогнозов all_forecast_node
	for (auto it = all_forecast_node.begin(); it != all_forecast_node.end(); it++)
	{
		it->forecast_transform();
	}
}

void Main_Inform_TAF::display()
{	cout<<clr::yellow<<"\n\nПРОГНОЗ:"<<clr::white
		<<"\nДата и время подготовки прогноза: " << issue_time_ << "\n"
		<< "Время выпуска бюллетеня прогноза: "<< bulletin_time_ << "\n"
		<< "Действует  с:                     "<< valid_time_from_ << "\n"
		<< "Действует по:                     "<< valid_time_to_ << "\n"
		<< "Дополнительная информация:        " << remarks_ << "\n"
		<<clr::cyan
		<< "Аэропорт:" << station_id_ 
		<<clr::white<< "\t"
		<< "Широта:" << latitude_ << "\t"
		<< "Долгота:" << longitude_ << "\t"
		<< "Превышение:" << elevation_m_ << "\n"
		<< "Сводка:" << raw_text_;
//отобразили каждый подпрогноз в векторе прогнозов all_forecast_node
 for (auto it = all_forecast_node.begin(); it != all_forecast_node.end(); it++)
		{it->display();
		}
}

