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
        bool has_landmarks();
        std::vector<std::string> get_landmarks() const;
        std::string get_start_date() const;
        std::string get_end_date() const;
        float get_price() const;
        unsigned int get_seats() const;
    private:
        void rect_availability();
        int id;
        std::string destination;
        std::vector<std::string> landmarks;
        Date start_date;
        Date end_date;
        float price;
        unsigned int seats;
};


TravelPack::TravelPack(){
    id = 0x00000000;
    //id = 10;
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

    getline(input_stream, temp_str);
    if (temp_str.find("-") != std::string::npos){ //verify if the land mark list is present
        input_string.str(temp_str);
        getline(input_string, destination, '-'); destination = str_trim(destination);
        getline(input_string, temp_str); input_string.str(temp_str.append(" ,"));

        while(!input_string.fail()){
            getline(input_stream, temp_str, ','); temp_str = str_trim(temp_str);
            if (temp_str.length() != 0)
                landmarks.push_back(temp_str);
        }

    }else{
        destination = str_trim(temp_str);
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
bool TravelPack::has_landmarks(){
    if (landmarks.size() == 0)
        return false;
    return true;
}
std::vector<std::string> TravelPack::get_landmarks() const{
    return landmarks;
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
unsigned int TravelPack::get_seats() const{
    return seats;
}


//Operator overload
void operator++(TravelPack &travelpack){ //++travelpack
    travelpack.buy_seat();
}
void operator++(TravelPack &travelpack, int){ //travelpack++
    travelpack.buy_seat();
}

#endif
