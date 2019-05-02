#ifndef __ADDRESS_H_
#define __ADDRESS_H_

#include <iostream>
#include <string>
#include <sstream>

class Address{
    public:
        Address(std::istream &input_stream);
        void print(std::ostream &output_stream);
    private:
        std::string street_name;
        unsigned int door_num;
        std::string floor_num; //can be '-' if not applicable
        std::string postal_code;
        std::string locale;
};


Address::Address(std::istream &input_stream)
{
    std::string temp_str;
    std::istringstream input_string;
    getline(input_stream, temp_str); input_string.str(temp_str.append(" /")); //read line to format into temporary string and sends it for formatting
    // read the address struct information. Lines are trimmed of white spaces in both ends
    getline(input_string, temp_str, '/'); street_name = str_trim(temp_str);
    input_string >> door_num; input_string.ignore(1000, '/');
    getline(input_string, temp_str, '/'); floor_num = str_trim(temp_str);
    getline(input_string, temp_str, '/'); postal_code = str_trim(temp_str);
    getline(input_string, temp_str, '/'); locale = str_trim(temp_str);
    getline(input_string, temp_str, '/');

    if(temp_str != "" || input_stream.fail())
        throw(std::string("ADDRESS INFO WRITTEN INCORRECTLY\n"));
}

void Address::print(std::ostream &output_stream)
{
    output_stream << "Street name: " << street_name;
    output_stream << "\nDoor number: " << door_num;
    output_stream << "\nFloor number: " << floor_num;
    output_stream << "\nPostal Code: " << postal_code;
    output_stream << "\nLocale: " << locale << std::endl;
}

#endif
