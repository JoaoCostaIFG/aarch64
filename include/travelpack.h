#ifndef __TRAVELPACK_H_
#define __TRAVELPACK_H_


class TravelPack{
    public:
        TravelPack();
        TravelPack(istream &input_stream);
        TravelPack(istream &input_stream, TravelPack const &old_tp);
        void print(ostream &output_stream) const;
        void buy_seat();
        void make_unavailable();
        //Getters
        bool is_available() const;
        int get_id() const;
        string get_destination() const;
        bool has_landmarks() const;
        vector<string> get_landmarks() const;
        Date get_start_date() const;
        Date get_end_date() const;
        float get_price() const;
        unsigned int get_available_seats() const;
        unsigned int get_taken_seats() const;
    private:
        bool id_validity();
        void rect_availability();
        void cleanup_oldmap(TravelPack const &old_tp);
        int id;
        string destination;
        vector<string> landmarks;
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
TravelPack::TravelPack(istream &input_stream){
    string temp_str;
    istringstream input_string;

    cout << "ID (negative IDs make the travel pack unavailable)? ";
    input_stream >> id; input_stream.ignore(1000, '\n');

    cout << "Destination and land marks? ";
    getline(input_stream, temp_str);
    if (temp_str.find("-") != string::npos){ //verify if the landmark list is present
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

    cout << "Start date (yyyy/mm/dd)? ";
    getline(input_stream, temp_str); input_string.str(temp_str.append("\n"));
    start_date = Date(input_string);

    cout << "End date (yyyy/mm/dd)? ";
    getline(input_stream, temp_str); input_string.str(temp_str.append("\n"));
    end_date = Date(input_string);
    cout << endl;

    if(start_date > end_date){
        throw logic_error("END DATE CAN'T BE LOWER THAN START DATE\n");
    }

    cout << "Price? ";
    input_stream >> price; input_stream.ignore(1000, '\n');
    cout << "Available seats? ";
    input_stream >> available_seats; input_stream.ignore(1000, '\n');
    cout << "Taken seats? ";
    input_stream >> taken_seats; input_stream.ignore(1000, '\n');
    cout << endl;

    if(input_stream.fail()){
        input_stream.clear();
        throw invalid_argument("TRAVEL PACK IS NOT FORMATED CORRECTLY\n");
    }

    rect_availability();

    if (map_ref->find(destination) == map_ref->end()){
        (*map_ref)[destination].first = 0;
        if (is_available())
            (*map_ref)[destination].second.insert(id);
    }
    (*map_ref)[destination].first += taken_seats;


    if (has_landmarks()){
        for(int i = 0; i < landmarks.size(); i++){
            if (map_ref->find(landmarks.at(i)) == map_ref->end()){
                (*map_ref)[landmarks.at(i)].first = 0;
                if (is_available())
                    (*map_ref)[landmarks.at(i)].second.insert(id);
            }
            (*map_ref)[landmarks.at(i)].first += taken_seats;
        }
    }
}
TravelPack::TravelPack(istream &input_stream, TravelPack const &old_tp){
    string temp_str;
    istringstream input_string;

    id = old_tp.get_id();

    cout << "Destination and land marks? ";
    getline(input_stream, temp_str);
    if (temp_str.find("-") != string::npos){ //verify if the landmark list is present
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

    cout << "Start date (yyyy/mm/dd)? ";
    getline(input_stream, temp_str); input_string.str(temp_str.append("\n"));
    start_date = Date(input_string);

    cout << "End date (yyyy/mm/dd)? ";
    getline(input_stream, temp_str); input_string.str(temp_str.append("\n"));
    end_date = Date(input_string);
    cout << endl;

    if(start_date > end_date){
        throw logic_error("END DATE CAN'T BE LOWER THAN START DATE\n");
    }

    cout << "Price? ";
    input_stream >> price; input_stream.ignore(1000, '\n');
    cout << "Available seats? ";
    input_stream >> available_seats; input_stream.ignore(1000, '\n');
    cout << "Taken seats? ";
    input_stream >> taken_seats; input_stream.ignore(1000, '\n');
    cout << endl;

    if(input_stream.fail()){
        input_stream.clear();
        throw invalid_argument("TRAVEL PACK IS NOT FORMATED CORRECTLY\n");
    }

    rect_availability();

    // CLean-up "trash" left from the old version of this travel pack in the map
    cleanup_oldmap(old_tp);

    //update map with edited travel pack info
    if (map_ref->find(destination) == map_ref->end()){
        (*map_ref)[destination].first = 0;
        if (is_available())
            (*map_ref)[destination].second.insert(id);
    }
    (*map_ref)[destination].first += taken_seats;


    if (has_landmarks()){
        for(int i = 0; i < landmarks.size(); i++){
            if (map_ref->find(landmarks.at(i)) == map_ref->end()){
                (*map_ref)[landmarks.at(i)].first = 0;
                if (is_available())
                    (*map_ref)[landmarks.at(i)].second.insert(id);
            }
            (*map_ref)[landmarks.at(i)].first += taken_seats;
        }
    }
}


void TravelPack::print(ostream &output_stream) const{
    output_stream << id << endl;
    output_stream << destination;
    if (has_landmarks()){
        output_stream << " - " << landmarks.at(0);
        for(int i=1; i<landmarks.size(); i++)
            output_stream << ", " << landmarks.at(i);
        
    }
    output_stream << endl;
    start_date.print(output_stream);
    end_date.print(output_stream);
    output_stream << price << endl;
    output_stream << available_seats << endl;
    output_stream << taken_seats << endl;
}


void TravelPack::cleanup_oldmap(TravelPack const &old_tp){
    // CLean-up "trash" left from the old version of this travel pack in the map
    (*map_ref)[old_tp.get_destination()].first -= old_tp.get_taken_seats();
    
    if ((*map_ref)[old_tp.get_destination()].first <= 0)
        (*map_ref).erase(map_ref->find(old_tp.get_destination()));
    else
        (*map_ref)[old_tp.get_destination()].second.erase((*map_ref)[old_tp.get_destination()].second.find(old_tp.get_id()));

    if (old_tp.has_landmarks()){
        for(int i = 0; i < old_tp.get_landmarks().size(); i++){
            (*map_ref)[old_tp.get_landmarks().at(i)].first -= old_tp.get_taken_seats();
            if((*map_ref)[old_tp.get_landmarks().at(i)].first <= 0)
                (*map_ref).erase(map_ref->find(old_tp.get_landmarks().at(i)));
            else
                (*map_ref)[old_tp.get_landmarks().at(i)].second.erase((*map_ref)[old_tp.get_landmarks().at(i)].second.find(old_tp.get_id()));
        }
    }
}


void TravelPack::rect_availability(){
    if (taken_seats >= available_seats && id > 0){
        make_unavailable();
    }
}


void TravelPack::make_unavailable(){
    if (!is_available()){
        throw logic_error("TRAVEL PACK IS ALREADY UNAVAILABLE\n");
    }

    (*map_ref)[get_destination()].second.erase((*map_ref)[get_destination()].second.find(get_id()));
    if (has_landmarks()){
        for(int i = 0; i < get_landmarks().size(); i++){
            (*map_ref)[get_landmarks().at(i)].second.erase((*map_ref)[get_landmarks().at(i)].second.find(get_id()));
        }
    }

    id *= -1;
}


void TravelPack::buy_seat(){
    if (!is_available()){
        throw logic_error("CAN'T BUY SEAT BECAUSE THE TRAVEL PACK IS UNAVAILABLE/OVERBOOKED\n");
    }

    (*map_ref)[destination].first += 1;
    if (has_landmarks()){
        for(int i = 0; i < landmarks.size(); i++){
            (*map_ref)[landmarks.at(i)].first += 1;
        }
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
string TravelPack::get_destination() const{
    return destination;
}
bool TravelPack::has_landmarks() const{
    if (landmarks.size() == 0)
        return false;
    return true;
}
vector<string> TravelPack::get_landmarks() const{
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
