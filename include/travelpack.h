#ifndef __TRAVELPACK_H_
#define __TRAVELPACK_H_


class TravelPack{
    public:
        TravelPack();
        TravelPack(std::istream &input_stream);
        void print(std::ostream &output_stream);
        void buy_seat();
        void make_unavailable();
        //Getters
        bool is_available();
        int get_id() const;
        std::string get_destination() const;
        std::vector<std::string> get_land_marks() const;
        std::string get_start_date() const;
        std::string get_end_date() const;
        float get_price() const;
        unsigned int get_total_seats() const;
        unsigned int get_sold_seats() const;
    private:
        void rect_availability();
        int id;
        std::string destination;
        std::vector<std::string> land_marks;
        Date start_date;
        Date end_date;
        float price;
        unsigned int seats;
};
TravelPack::TravelPack(){
    id = 0x00000000;
    destination = "";
    //start_date = Date();
    //end_date = Date();
    price = 0;
    seats = 0;
}
TravelPack::TravelPack(std::istream &input_stream){
    std::string temp_str;
    std::istringstream input_string;

    input_stream >> id; input_stream.ignore(1000, '\n');
    getline(input_stream, destination, '-'); destination = str_trim(destination);
    getline(input_stream, temp_str); input_string.str(temp_str.append(" ,"));
    while(!input_string.fail()){ //not sure if it works
        getline(input_stream, temp_str, ','); temp_str = str_trim(temp_str);
        land_marks.push_back(temp_str);
    }

    getline(input_stream, temp_str); input_string.str(temp_str.append(" /"));
    start_date = Date(input_string);

    getline(input_stream, temp_str); input_string.str(temp_str.append(" /"));
    end_date = Date(input_string);

    if(start_date > end_date){
        throw(std::string("INSERT A VALID START AND END DATES FOR THE TRAVEL PACKS\n"));
    }

    input_stream >> price; input_stream.ignore(1000, '\n');
    input_stream >> seats; input_stream.ignore(1000, '\n');

    rect_availability();
}


void TravelPack::print(std::ostream &output_stream){

}


void TravelPack::rect_availability(){
    if (seats == 0 && id > 0){
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
    seats--;
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
std::vector<std::string> TravelPack::get_land_marks() const{
    return land_marks;
}
std::string TravelPack::get_start_date() const{
    return std::to_string(start_date.get_day()) + "/" + std::to_string(start_date.get_month()) + "/" + std::to_string(start_date.get_year());
}
std::string TravelPack::get_end_date() const{
    return std::to_string(end_date.get_day()) + "/" + std::to_string(end_date.get_month()) + "/" + std::to_string(end_date.get_year());
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
void operator++(TravelPack &travelpack){
    travelpack.buy_seat();
}

#endif
