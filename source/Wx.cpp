#include "Wx.h"

Wx::Wx(std::vector<std::string>& in_wx_data)
{   Function::load_map_dictionary("../dictionary/AMOFSG_Dictionary.txt", map_AMOFSG_Dictionary);
    wx_string_ = in_wx_data.at(0);
    not_decoded_ = in_wx_data.at(1);
}

void Wx::wx_transform()
{    Function::replace_wx_string_(wx_string_);
}

void Wx::wx_display()
{   if (wx_string_ != "") { std::cout << "\nявлени€: " << wx_string_; }
   // if (not_decoded_ != "") { std::cout << "\nне декодировано:" << not_decoded_; }
}
