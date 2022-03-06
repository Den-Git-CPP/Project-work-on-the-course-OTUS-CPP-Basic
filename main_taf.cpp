#include <iostream>
#include <cstdlib>
#include <vector>
#include "download_weather_curl.h"
#include "Main_Inform_TAF.h"

std::vector<std::string>& split(const std::string& data_for_split, char delim, std::vector<std::string>& elems) {
	std::stringstream ss(data_for_split);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> read_weather_file_vRaw(const std::string& path)
{
	std::vector<std::string> m_vRawStruct, vRaw_Element;
	std::fstream fin;
	fin.open("../dictionary/Struct_Taf_Forecast.txt");
	if (!fin.is_open()) {
		std::cout << "File Struct_Taf_Forecast not found " << std::endl;
		std::cout << "Need Struct_Taf_Forecast.txt" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::string Struct_Taf_Forecast_etalon;
	std::getline(fin, Struct_Taf_Forecast_etalon);
	fin.close();

	std::string str = "";
	fin.open(path);
	while (!fin.eof())
	{
		getline(fin, str);
		if (str != "") m_vRawStruct.push_back(str);
	}
	fin.close();

	if (m_vRawStruct[0] == "No errors" && m_vRawStruct[1] == "No warnings" && m_vRawStruct[5] == Struct_Taf_Forecast_etalon)
	{ 
			split(m_vRawStruct[6],',',vRaw_Element);
	}
	else
	{
		std::cout << "Errors!!! Open File on path: " << path << "\n\n";
		if (m_vRawStruct[0] != "No errors") { std::cout << "Errors:\n" << m_vRawStruct[0] << "\n\n"; };
		if (m_vRawStruct[1] != "No warnings") { std::cout << "Warnings:\n" << m_vRawStruct[1] << "\n\n"; };
		if (m_vRawStruct[5] != Struct_Taf_Forecast_etalon) { std::cout << "The decoding structure is not correct. \nNeed:\n" << Struct_Taf_Forecast_etalon << "\n\n"; };
		exit(EXIT_FAILURE);
	}
	return vRaw_Element;
}
 
int main() {
	std::setlocale(LC_ALL, "Russian_Russia.1251");
    std::cout<<"Введит четерехбуквенный код аэропорта\t";
    std::string ICAO_airport_name; std::cin>>ICAO_airport_name;
    DownloadFile(ICAO_airport_name); 
	std::vector<std::string> raw_data = read_weather_file_vRaw(ICAO_airport_name + "_TAF.txt");
	Main_Inform_TAF TAF(raw_data);	 
	TAF.transform();				 
	TAF.display();					 
	
	std::cout << "\n";
	system("pause");
}