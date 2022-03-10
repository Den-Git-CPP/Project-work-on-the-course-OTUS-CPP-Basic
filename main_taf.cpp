#include <iostream>
#include <cstdlib>
#include <vector>
#include "download_weather_curl.h"
#include "Main_Inform_METAR.h"
#include "Main_Inform_TAF.h"

std::vector<std::string>& split(const std::string& data_for_split, char delim, std::vector<std::string>& elems) {
	std::stringstream ss(data_for_split);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> read_weather_file_vRaw(const std::string& path, const std::string& type_forecast) {
	std::vector<std::string> m_vRawStruct, vRaw_Element;
	std::fstream fin;
	fin.open("../dictionary/STRUCT_" + type_forecast + ".txt");
	if (!fin.is_open()) {
		std::cout << clr::red << "Файл для проверки структуры скаченого файа с прогнозом " << type_forecast << " не найден." << clr::white << std::endl;
		std::cout << clr::red << "Для работы необходим эталонный файл STRUCT_" << type_forecast << ".txt" << clr::white << std::endl;
		exit(EXIT_FAILURE);
	}
	std::string Struct_Taf_Forecast_etalon;
	std::getline(fin, Struct_Taf_Forecast_etalon);
	fin.close();

	std::string str = "";
	fin.open(path);
	while (!fin.eof()) {
		getline(fin, str);
		if (str != "") m_vRawStruct.push_back(str);
	}
	fin.close();

	if (m_vRawStruct[0] == "No errors" && m_vRawStruct[1] == "No warnings" && m_vRawStruct[5] == Struct_Taf_Forecast_etalon) {
		split(m_vRawStruct[6], ',', vRaw_Element);
	}
	else {
		std::cout << "Errors!!! Open File on path: " << path << "\n\n";
		if (m_vRawStruct[0] != "No errors") { std::cout << "Errors:\n" << m_vRawStruct[0] << "\n\n"; };
		if (m_vRawStruct[1] != "No warnings") { std::cout << "Warnings:\n" << m_vRawStruct[1] << "\n\n"; };
		if (m_vRawStruct[5] != Struct_Taf_Forecast_etalon) { std::cout << clr::red << "The decoding structure is not correct. \nNeed:\n" << Struct_Taf_Forecast_etalon << clr::white << "\n\n"; };
		exit(EXIT_FAILURE);
	}
	return vRaw_Element;
}

int main(int argc, char** argv) {
	std::setlocale(LC_ALL, "Russian_Russia.1251");
	std::string type_forecast{};
	std::vector<std::string>  raw_data;
	std::string ICAO_airport_name;

	if (argc <= 1) {
		std::cout << clr::yellow << "Введите четырехбуквенный кодов ICAO аэропорта\t" << clr::white;
		std::cin >> ICAO_airport_name; 
		DownloadFile(ICAO_airport_name);
	
		type_forecast = "METAR";
		raw_data = read_weather_file_vRaw(ICAO_airport_name + "_" + type_forecast + ".txt", type_forecast);
		Main_Inform_METAR METAR(raw_data);
		METAR.transform();
		METAR.display();

		type_forecast = "TAF";
		raw_data = read_weather_file_vRaw(ICAO_airport_name + "_" + type_forecast + ".txt", type_forecast);
		Main_Inform_TAF TAF(raw_data);
		TAF.transform();
		TAF.display();
	}

	if (argc >= 2) {
		std::string arg1_value{ argv[1] };
		if (arg1_value == "-metar") {
			std::cout << clr::yellow << "Введите четырехбуквенный кодов ICAO аэропорта\t" << clr::white;
			std::cin >> ICAO_airport_name;
			DownloadFile(ICAO_airport_name);

			type_forecast = "METAR";
			raw_data = read_weather_file_vRaw(ICAO_airport_name + "_" + type_forecast + ".txt", type_forecast);
			Main_Inform_METAR METAR(raw_data);
			METAR.transform();
			METAR.display();

		}
		
		if (arg1_value == "-taf") {
			std::cout << clr::yellow << "Введите четырехбуквенный кодов ICAO аэропорта\t" << clr::white;
			std::cin >> ICAO_airport_name;
			DownloadFile(ICAO_airport_name);

			type_forecast = "TAF";
			raw_data = read_weather_file_vRaw(ICAO_airport_name + "_" + type_forecast + ".txt", type_forecast);
			Main_Inform_TAF TAF(raw_data);
			TAF.transform();
			TAF.display();
		}
	}
	
	std::cout << "\n";
	std::system("pause");
	std::setlocale(LC_ALL, "English");
}