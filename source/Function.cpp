#include "Function.h"
void Function::load_map_dictionary(const std::string& dictionary_path, std::map<std::string, std::string>& Dictionary_) {
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

std::string Function::replace_raw_text(std::string& raw_str) {
	std::istringstream ss(raw_str);
	std::ostringstream os;

	std::for_each(
		std::istream_iterator<std::string>(ss),
		std::istream_iterator<std::string>(),
		[&](const std::string& s) {
			if ((s == "TEMPO") ||
				(s == "BECMG") ||
				(s == "FM")
				) {
				os << "\n\t" << s << "\t";
			}
			else {
				os << " " << s;
			};
		}
	);
	return os.str();;
}

std::string Function::replace_format_time(const std::string& str_time) {
	std::tm t = {};
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
	else {
		os << "";
	};
	return os.str();
}

std::string Function::replace_station_id_(std::string& station_id_) {
	if (!station_id_.empty()) {
		try {
			station_id_ = map_airport_Dictionary.at(station_id_);
		}
		catch (const std::exception& e) {  //  std::cerr << e.what() << "\n Function::replace_wx_string_";
			station_id_ = "КОД ИКАО " + station_id_ + " НЕ РАСШИФРОВАН";

		}
	}
	return station_id_;
}

std::string Function::replace_wx_string_(std::string& wx_string_) {
	if (!wx_string_.empty()) {

		try {
			wx_string_ = map_AMOFSG_Dictionary.at(wx_string_);
		}
		catch (const std::exception& e) {
			//	std::cerr << e.what() << "\n Function::replace_wx_string_";
			wx_string_ = "  КОД ЯВЛЕНИЯ ПОГОДЫ " + wx_string_ + " НЕ РАСШИФРОВАН";
		}


	}
	return wx_string_;
}

void Function::replace_change_indicator(std::string& change_indicator_) {
	if (!change_indicator_.empty()) {
		if (change_indicator_ == "") change_indicator_ = "ПРОГНОЗ: ";
		if (change_indicator_ == "TEMPO") change_indicator_ = "ВРЕМЕНАМИ: ";
		if (change_indicator_ == "BECMG") change_indicator_ = "УСТОЙЧИВО: ";
		if (change_indicator_ == "FM")	change_indicator_ = "ИЗМЕНЕНИЯ: ";
	}
}

void Function::replace_sky_cover_(std::string& sky_cover_) {
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
		if (sky_cover_ == "CAVOK")	sky_cover_ = "Видимость более 10 км, нет облаков ниже 1500 м, нет явлений погоды и облачности ";
	}
}

void Function::replace_cloud_type_(std::string& cloud_type_) {
	if (!cloud_type_.empty()) {
		if (cloud_type_ == "CB") cloud_type_ = " (кучеводождевая)";
		if (cloud_type_ == "TCU") cloud_type_ = " (мощно-кучеводождевая)";
		if (cloud_type_ == "CU") cloud_type_ = " CU";
	}
}

void Function::replace_flight_category_(std::string& flight_category_) {
	if (!flight_category_.empty()) {
		if (flight_category_ == "VFR") flight_category_ = "\nУсловия для полетов согласно правилам визуальных полетов \nПОТОЛОК:\tболее 900 м. над уровнем земли.\nВИДИМОСТЬ:\tболее 9 км.";
		if (flight_category_ == "MVFR") flight_category_ = "\nПредельные условия для полетов согласно правилам визуальных полетов. \nПОТОЛОК:\tот 300 до 900 м. от уровня земли \nВИДИМОСТЬ:\tот 5.5 до 9 км.";
		if (flight_category_ == "IFR") flight_category_ = "\nУсловия для полетов согласно правилам полетов по приборам. \nПОТОЛОК:\tот 150 до 300 м. от уровня земли \nВИДИМОСТЬ:\tот 1.8 км до 5.5 км.";
		if (flight_category_ == "LIFR") flight_category_ = "\nПредельные условия для полетов согласно правила полетов на малой высоте по приборам. \nПОТОЛОК:\t   ниже 150 м. над уровнем земли \nВИДИМОСТЬ:\tменее 1.8 км.";
	}
}

void Function::kt_to_ms(std::string& kt) {
	if (!kt.empty()) {
		kt = std::to_string(static_cast<int>(stoi(kt) * 0.514444));
	}
}

void Function::ft_to_m(std::string& ft) {
	if (!ft.empty()) {
		ft = std::to_string(static_cast<int>(stoi(ft) * 0.3048));
	}
}

void Function::mi_to_m(std::string& mi) {
	if (!mi.empty()) {
		mi = std::to_string(static_cast<int>(stof(mi) * 1609.1));
	}
}

void Function::inch_to_m(std::string& inch) {//1 inches of mercury = 267.11892350861 meters 
	if (!inch.empty()) {
		inch = std::to_string(static_cast<int>(stof(inch) * 267.11892350861));
	}
}

void Function::inch_to_mm(std::string& inch) {
	if (!inch.empty()) {
		inch = std::to_string(static_cast<int>(stof(inch) * 25.04));
	}
}

void Function::inch_to_bar(std::string& inch) {// 1 inches of mercury = 0.033863886666667 bars 
	if (!inch.empty()) {
		inch = std::to_string(static_cast<int>(stof(inch) * 34));
	}
}

