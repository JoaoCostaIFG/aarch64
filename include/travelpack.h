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
        void make_unavailable();
        void buy_seat();
        //Getters
        bool is_available();
        int get_id() const;
        std::string get_destination() const;
        Date get_start_date() const;
        Date get_end_date() const;
        float get_price() const;
        unsigned int get_total_seats() const;
        unsigned int get_sold_seats() const;
    private:
        void rect_availability();
        int id;
        std::string destination;
        Date start_date;
        Date end_date;
        float price;
        unsigned int total_seats;
        unsigned int sold_seats;
};
TravelPack::TravelPack(){
    id = 0x00000000;
    destination = "";
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
    getline(input_stream, destination, '-'); destination = str_trim(destination);

    getline(input_stream, temp_str); input_string.str(temp_str.append(" /"));
    start_date = Date(input_string);

    getline(input_stream, temp_str); input_string.str(temp_str.append(" /"));
    end_date = Date(input_string);

    if(start_date > end_date){
        throw(std::string("INSERT A VALID START AND END DATES FOR THE TRAVEL PACKS\n"));
    }

    input_stream >> price; input_stream.ignore(1000, '\n');
    input_stream >> total_seats; input_stream.ignore(1000, '\n');
    input_stream >> sold_seats; input_stream.ignore(1000, '\n');

    rect_availability();
}


void TravelPack::rect_availability(){
    if (total_seats <= sold_seats && id > 0){
        id *= -1;
    }
}


void TravelPack::make_unavailable(){
    if (!is_available()){
        throw(std::string("TRAVEL PACK IS ALREADY UNAVAILABLE\n"));
    }
    id *= -1;
}


void TravelPack::buy_seat(){
    if (!is_available()){
        throw(std::string("CAN'T BUY SEAT BECAUSE THE TRAVEL PACK IS UNAVAILABLE/OVERBOOKED\n"));
    }
    sold_seats++;
    rect_availability();
}


//Getters
bool TravelPack::is_available(){
    //rect_availability(); //not needed if we always rectify stuff correctly everywhere (here for redundancy)
    if (id > 0){
        return true;
    }
    return false;
}
int TravelPack::get_id() const{
    return id;
}
std::string TravelPack::get_destination() const{
    return destination;
}
Date TravelPack::get_start_date() const{
    return (start_date);
}
Date TravelPack::get_end_date() const{
    return end_date;
}
float TravelPack::get_price() const{
    return price;
}
unsigned int TravelPack::get_total_seats() const{
    return total_seats;
}
unsigned int TravelPack::get_sold_seats() const{
    return sold_seats;
}


//Operator overload
bool operator++(TravelPack &travelpack){
    if (!travelpack.is_available()){
        throw(std::string("CAN'T BUY PACK BECAUSE IT IS UNAVAILABLE/OVERBOOKED\n"));
    }
    travelpack.buy_seat();
    //UPDATE DICT HERE
}

#endif