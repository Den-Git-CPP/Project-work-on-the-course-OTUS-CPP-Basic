#include "Function.h"
void Function::load_map_dictionary(const std::string& dictionary_path, std::map<std::string, std::string>& Dictionary_)
{
	std::ifstream infile;
	infile.open(dictionary_path);
	if (!infile) {
		std::cout << "Can't open file Dictionary: " << dictionary_path << "\n";
		exit(EXIT_FAILURE);
	}
	std::string item1, item2;
	while (infile) {
		std::getline(infile, item1, '/'), getline(infile, item2);
		if (item1 != "") { Dictionary_[item1] = item2; }
	}
	infile.close();
}

std::string Function::replace_format_time(const std::string& str_time)
{	std::tm t = {};
	std::istringstream ss(str_time);
	std::ostringstream os;
	ss >> std::get_time(&t, "%Y-%m-%dT%H:%M:%SZ");
	if (str_time != "") {		//проверка на пустоту
		if (ss.fail()) {		//проверка на формат
		std::cout << "Parse DATE_TIME failed\n";
		}
		else {					//все норм
		os << std::put_time(&t, "%H:%M:%S %d-%m-%Y  UTC");
		}
	}
	else{
	os << "";
	};
return os.str();
}

std::string Function::replace_station_id_(std::string& station_id_)
{
	if (!station_id_.empty()) {
		station_id_ = map_airport_Dictionary.at(station_id_);
	}
	return station_id_;
}

std::string Function::replace_wx_string_(std::string& wx_string_)
{
	if (!wx_string_.empty()) {
		wx_string_ = map_AMOFSG_Dictionary.at(wx_string_);
	}
	return wx_string_;
}

void Function::replace_change_indicator(std::string& change_indicator_)
{	if (!change_indicator_.empty()) {
		if (change_indicator_ == "") change_indicator_ = "ПРОГНОЗ: ";
		if (change_indicator_ == "TEMPO") change_indicator_ = "ВРЕМЕНАМИ: ";
		if (change_indicator_ == "BECMG") change_indicator_ = "УСТОЙЧИВО: ";
		if (change_indicator_ == "FM")	change_indicator_ = "ИЗМЕНЕНИЯ: ";
	}
}

void Function::replace_sky_cover_(std::string& sky_cover_)
{
	if (!sky_cover_.empty()) {
		if (sky_cover_ == "NSC")	sky_cover_ = "Без существенной облачность ";
		if (sky_cover_ == "SKC")	sky_cover_ = "Небо чистое ";
		if (sky_cover_ == "CLR")	sky_cover_ = "Нет облачности ниже 3700м";
		if (sky_cover_ == "BKN")	sky_cover_ = "Значительная облачность   ";
		if (sky_cover_ == "FEW")	sky_cover_ = "Незначительная облачность ";
		if (sky_cover_ == "OVC")	sky_cover_ = "Сплошная облачность       ";
		if (sky_cover_ == "SCT")	sky_cover_ = "Рассеянная облачность     ";
		if (sky_cover_ == "SKT")	sky_cover_ = "SKT";
		if (sky_cover_ == "OVCX")	sky_cover_ = "OVCX";
	}
}

void Function::replace_cloud_type_(std::string& cloud_type_)
{
	if (!cloud_type_.empty()) {
		if (cloud_type_ == "CB") cloud_type_ = " (кучеводождевая)";
		if (cloud_type_ == "TCU") cloud_type_ = " (мощно-кучеводождевая)";
		if (cloud_type_ == "CU") cloud_type_ = " CU";
	}
}

void Function::kt_to_ms(std::string& kt)
{	if (!kt.empty()) {
		kt = std::to_string(static_cast<int>(stoi(kt) * 0.514444));
	}	
}

void Function::ft_to_m(std::string& ft)
{if (!ft.empty()) {
	 ft = std::to_string(static_cast<int>(stoi(ft) * 0.3048));
	}
}

void Function::mi_to_m(std::string& mi)
{
	if (!mi.empty()){ 
		mi = std::to_string(static_cast<int>(stof(mi) * 1609.1));
	}
}

void Function::inch_to_m(std::string& inch)
{//1 inches of mercury = 267.11892350861 meters 
	if (!inch.empty()) {
		inch = std::to_string(static_cast<int>(stof(inch) * 267.11892350861));
	}
}
 
