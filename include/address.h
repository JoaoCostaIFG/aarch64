#ifndef __ADDRESS_H_
#define __ADDRESS_H_

/*
#include <iostream>
#include <string>
#include <sstream>
*/

class Address{
    public:
        Address(istream &input_stream);
        Address() = default;
        void print(ostream &output_stream) const;
        string get_street_name() const;
        unsigned int get_door_num() const;
        string get_floor_num() const; //can be '-' if not applicable
        string get_postal_code() const;
        string get_locale() const;
    private:
        string street_name;
        unsigned int door_num;
        string floor_num; //can be '-' if not applicable
        string postal_code;
        string locale;
};


Address::Address(istream &input_stream)
{
    string temp_str;
    istringstream input_string;
    
    cout << "Address?(Street name / Door number / Floor number / Postal code / Location)\n"; getline(input_stream, temp_str);
    input_string.str(temp_str.append(" /")); //read line to format into temporary string and sends it for formatting
    
    // read the address struct information. Lines are trimmed of white spaces in both ends
    getline(input_string, temp_str, '/'); street_name = str_trim(temp_str);
    input_string >> door_num; input_string.ignore(1000, '/');
    getline(input_string, temp_str, '/'); floor_num = str_trim(temp_str);
    getline(input_string, temp_str, '/'); postal_code = str_trim(temp_str);
    getline(input_string, temp_str, '/'); locale = str_trim(temp_str);
    getline(input_string, temp_str, '/');

    if(temp_str != "" || input_stream.fail()){
        input_stream.clear();
        throw invalid_argument("ADDRESS INFO WRITTEN INCORRECTLY\n");
    } 
}


void Address::print(ostream &output_stream) const
{
    output_stream << street_name << " / " << door_num << " / " << floor_num << " / " << postal_code << " / " << locale << endl;
    /*
    output_stream << "Street name: " << street_name;
    output_stream << "\nDoor number: " << door_num;
    output_stream << "\nFloor number: " << floor_num;
    output_stream << "\nPostal Code: " << postal_code;
    output_stream << "\nLocale: " << locale << endl;*/
}


//getters
string Address::get_street_name() const{
    return street_name;
}
unsigned int Address::get_door_num() const{
    return door_num;
}
string Address::get_floor_num() const{
    return floor_num;
}
string Address::get_postal_code() const{
    return postal_code;
} 
string Address::get_locale() const{
    return locale;
}

#endif
