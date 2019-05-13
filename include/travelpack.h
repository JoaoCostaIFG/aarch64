#ifndef __TRAVELPACK_H_
#define __TRAVELPACK_H_


class TravelPack{
    public:
        TravelPack();
        TravelPack(std::istream &input_stream);
        void print(std::ostream &output_stream) const;
        void buy_seat();
        void make_unavailable();
        //Getters
        bool is_available() const;
        int get_id() const;
        std::string get_destination() const;
        bool has_landmarks() const;
        std::vector<std::string> get_landmarks() const;
        Date get_start_date() const;
        Date get_end_date() const;
        float get_price() const;
        unsigned int get_available_seats() const;
        unsigned int get_taken_seats() const;
    private:
        bool id_validity();
        void rect_availability();
        int id;
        std::string destination;
        std::vector<std::string> landmarks;
        Date start_date;
        Date end_date;
        float price;
        unsigned int available_seats;
        unsigned int taken_seats;
};
TravelPack::TravelPack(){
    id = 0x00000000;
    //id = 10;
    destination = "";
    //start_date = Date();
    //end_date = Date();
    price = 0;
    available_seats = 0;
    taken_seats = 0;
}
TravelPack::TravelPack(std::istream &input_stream){
    std::string temp_str;
    std::istringstream input_string;

    // TODO: Verify duplicated ids
    std::cout << "ID (negative IDs make the travel pack unavailable)? ";
    input_stream >> id; input_stream.ignore(1000, '\n');

    std::cout << "Destination and land marks? ";
    getline(input_stream, temp_str);
    if (temp_str.find("-") != std::string::npos){ //verify if the landmark list is present
        input_string.str(temp_str.append("\n"));
        getline(input_string, destination, '-'); destination = str_trim(destination);
        getline(input_string, temp_str); input_string.str(temp_str.append(" ,\n"));
        while(input_string.peek() != '\n'){
            getline(input_string, temp_str, ','); temp_str = str_trim(temp_str);
            if (temp_str.length() != 0)
                landmarks.push_back(temp_str);
        }

    }else{
        destination = str_trim(temp_str);
    }

    std::cout << "Start date (yyyy/mm/dd)? ";
    getline(input_stream, temp_str); input_string.str(temp_str.append("\n"));
    start_date = Date(input_string);

    std::cout << "End date (yyyy/mm/dd)? ";
    getline(input_stream, temp_str); input_string.str(temp_str.append("\n"));
    end_date = Date(input_string);
    std::cout << std::endl;

    if(start_date > end_date){
        throw std::logic_error("END DATE CAN'T BE LOWER THAN START DATE\n");
    }

    std::cout << "Price? ";
    input_stream >> price; input_stream.ignore(1000, '\n');
    std::cout << "Available seats? ";
    input_stream >> available_seats; input_stream.ignore(1000, '\n');
    std::cout << "Taken seats? ";
    input_stream >> taken_seats; input_stream.ignore(1000, '\n');
    std::cout << std::endl;

    rect_availability();
}


void TravelPack::print(std::ostream &output_stream) const{
    output_stream << id << std::endl;
    output_stream << destination;
    if (has_landmarks()){
        output_stream << " - " << landmarks.at(0);
        for(int i=1; i<landmarks.size(); i++)
            output_stream << ", " << landmarks.at(i);
        
    }
    output_stream << std::endl;
    start_date.print(output_stream);
    end_date.print(output_stream);
    output_stream << price << std::endl;
    output_stream << available_seats << std::endl;
    output_stream << taken_seats << std::endl;
}


void TravelPack::rect_availability(){
    if (taken_seats >= available_seats && id > 0){
        id *= -1;
    }
}


void TravelPack::make_unavailable(){
    if (!is_available()){
        throw std::logic_error("TRAVEL PACK IS ALREADY UNAVAILABLE\n");
    }
    id *= -1;
}


void TravelPack::buy_seat(){
    if (!is_available()){
        throw std::logic_error("CAN'T BUY SEAT BECAUSE THE TRAVEL PACK IS UNAVAILABLE/OVERBOOKED\n");
    }
    taken_seats++;
    rect_availability();
}


//Getters
bool TravelPack::is_available() const{
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
bool TravelPack::has_landmarks() const{
    if (landmarks.size() == 0)
        return false;
    return true;
}
std::vector<std::string> TravelPack::get_landmarks() const{
    return landmarks;
}
Date TravelPack::get_start_date() const{
    return start_date;
}
Date TravelPack::get_end_date() const{
    return end_date;
}
float TravelPack::get_price() const{
    return price;
}
unsigned int TravelPack::get_available_seats() const{
    return available_seats;
}
unsigned int TravelPack::get_taken_seats() const{
    return taken_seats;
}


//Operator overload
void operator++(TravelPack &travelpack){ //++travelpack
    travelpack.buy_seat();
}
void operator++(TravelPack &travelpack, int){ //travelpack++
    travelpack.buy_seat();
}

#endif
