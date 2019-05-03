#ifndef __TRAVELPACK_H_
#define __TRAVELPACK_H_

#include <sstream>
#include <string>

#include "date.h"

class TravelPack{
    public:
        TravelPack();
        TravelPack(std::istream &input_stream);
        void print(std::ostream &output_stream);
    private:
        int id;
        std::string destinations;
        Date start_date;
        Date end_date;
        float price;
        unsigned int total_seats;
        unsigned int sold_seats;
};
TravelPack::TravelPack(){
    id = 0x00000000;
    destinations = "";
    /*
    start_date = Date();
    end_date = Date();
    */
    price = 0;
    total_seats = 0;
    sold_seats = 0;
}
TravelPack::TravelPack(std::istream &input_stream){
    std::string temp_str;
    std::istringstream input_string;

    input_stream >> id; input_stream.ignore(1000, '\n');
    getline(input_stream, destinations);

    getline(input_stream, temp_str); input_string.str(temp_str.append(" /"));
    start_date = Date(input_string);

    getline(input_stream, temp_str); input_string.str(temp_str.append(" /"));
    end_date = Date(input_string);

    input_stream >> price; input_stream.ignore(1000, '\n');
    input_stream >> total_seats; input_stream.ignore(1000, '\n');
    input_stream >> sold_seats; input_stream.ignore(1000, '\n');

    if (total_seats <= sold_seats && id > 0){
        id *= -1;
    }
}

#endif
