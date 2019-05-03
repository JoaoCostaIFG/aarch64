#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <sys/stat.h>

#define brk() do { std::cout << "Press the 'enter' key to continue.." << '\n'; getchar(); } while (0); //break function used for waiting for the user
#define clr_screen() std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"; //clear screen

//typedef structs
typedef struct{ //date type
    unsigned short int year;
    unsigned short int month;
    unsigned short int day;
}Date;

typedef struct{ //address type
    std::string street_name;
    unsigned int door_num;
    std::string floor_num; //can be '-' if not applicable
    std::string postal_code;
    std::string locale;
}Address;

typedef struct{ //travel pack type
    int id;
    std::string destinations;
    Date start_date;
    Date end_date;
    float price;
    unsigned int total_seats;
    unsigned int sold_seats;
}TravelPack;

typedef struct{ //client type
    std::string name;
    size_t nif;
    unsigned short int number_family_members;
    Address address;
    std::vector<int> travelpacks_bought;
    unsigned short int pack_number;
}Client;

typedef struct{ //agency type
    std::string name;
    size_t nif;
    std::string url;
    Address address;
    std::vector<Client> clients;
    std::vector<TravelPack> travelpacks_sell;
}Agency;

Agency agency; //creating a global agency struct instance that will serve as a base for the info
Agency new_agency; //Replaces agency if the ifnormation is read successfully

//functions
bool file_exists(const std::string& name){
    /*
        Checks if a given file exists;
        Takes a string specifing the path to the file to check as an argument;
        Returns true in case the file exists and false in case the files doesn't exist;
        Source: https://stackoverflow.com/a/12774387
    */
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}


void pack_rect(int pack_sync){
    //syncs availability info of a pack with all the clients that bought it
    for(size_t i = 0; i < agency.clients.size(); i++){
        for(size_t j = 0; j < agency.clients.at(i).travelpacks_bought.size(); j++){
            if(agency.clients.at(i).travelpacks_bought.at(j) == -pack_sync){
                agency.clients.at(i).travelpacks_bought.at(j) *= -1;
            }
        }
    }
}


std::string str_trim(const std::string& str){
    /*
        Trims a string of whitespaces in the beggining and end;
        Takes a string to trim as an argument;
        Returns the trimmed string;
    */
    return (str.substr(str.find_first_not_of(" "), str.find_last_not_of(" ") - str.find_first_not_of(" ") + 1));
}


int clients_reader(std::string clientsfile_path){
    /*
        0 - Operation successful
        Error Codes:
        2 - missing/incorrect info in clients file
    */
    std::string temp_str; //holds lines from files temporarly when formatting over that line is necessary
    std::istringstream temp_stream; //holds formated lines to attribute to structs/sub-structs
    bool flag = true; //swtiches to false when we've read all the clients' info present in the file

    std::ifstream clients_handler(clientsfile_path); //clients file handler

    //read the file
    try{
        while(flag){
            Client temp_client;
            getline(clients_handler, temp_client.name);
            clients_handler >> temp_client.nif; clients_handler.ignore(1000, '\n'); //getting int
            //check if NIF is already registred
            for(size_t i = 0; i < new_agency.clients.size(); i++){
                if(new_agency.clients.at(i).nif == temp_client.nif || temp_client.nif == new_agency.nif){
                    std::cout << "A least one client has a duplicate NIF information in the clients's information file." << std::endl;
                    return 2;
                }
            }

            clients_handler >> temp_client.number_family_members; clients_handler.ignore(1000, '\n'); //getting int

            temp_stream.clear();
            getline(clients_handler, temp_str); temp_stream.str(temp_str.append(" /")); //read line to format into temporary string and sends it for formatting
            // read the address struct information. Lines are trimmed of white spaces in both ends
            getline(temp_stream, temp_str, '/'); temp_client.address.street_name = str_trim(temp_str);
            temp_stream >> temp_client.address.door_num; temp_stream.ignore(1000, '/');
            getline(temp_stream, temp_str, '/'); temp_client.address.floor_num = str_trim(temp_str);
            getline(temp_stream, temp_str, '/'); temp_client.address.postal_code = str_trim(temp_str);
            getline(temp_stream, temp_str, '/'); temp_client.address.locale = str_trim(temp_str);
            getline(temp_stream, temp_str, '/');
            if (temp_str != ""){
                std::cout << "A least one of the client's address information in the clients's information file is incomplete/written in an incorrect form." << std::endl;
                return 2;
            }
            
            temp_stream.clear();
            getline(clients_handler, temp_str); temp_stream.str(temp_str.append(" ;-;")); //read line to format into temporary string and sends it for formatting
            
            // read the client's travel packs bought information
            temp_client.pack_number = 0;
            do{
                getline(temp_stream, temp_str, ';');
                if(temp_str == "" || temp_str == " ")
                    break;
                temp_client.pack_number += 1;
                temp_client.travelpacks_bought.push_back(stoi(temp_str));
            }while(temp_stream.peek() != 45);

            new_agency.clients.push_back(temp_client); //saving the info to the agency main struct

            getline(clients_handler,temp_str);
            if(temp_str != "::::::::::")
                flag = false; //checks if there are more clients to read
        }
    }
    catch(const std::exception& e){
        std::cout << e.what() << " Information in the clients's information file is incomplete/written in an incorrect form." << std::endl;
        return 2;
    }

    clients_handler.close();
    return 0;
}


int packs_reader(std::string packsfile_path){
    /*
        0 - Operation successful
        Error Codes:
        2 - missing/incorrect info in packs file
    */
    std::string temp_str; //holds lines from files temporarly when formatting over that line is necessary
    std::istringstream temp_stream; //holds formated lines to attribute to structs/sub-structs
    bool flag = true; //swtiches to false when we've read all the clients' info present in the file
    int last_id, comp_id;

    std::ifstream packs_handler(packsfile_path); //clients file handler

    //read the file
    packs_handler >> last_id; packs_handler.ignore(1000, '\n');
    try{
        do{
            TravelPack temp_pack;
            packs_handler >> temp_pack.id; packs_handler.ignore(1000, '\n'); //getting int
            comp_id = temp_pack.id;
            for(size_t i = 0; i < new_agency.travelpacks_sell.size(); i++){
                if(abs(new_agency.travelpacks_sell.at(i).id) == abs(temp_pack.id)){
                    std::cout << "A least one travel pack has a duplicate ID information in the travel pack's information file." << std::endl;
                    return 2;
                    break;
                }
            }

            getline(packs_handler, temp_pack.destinations);
            //read dates
            //start date
            packs_handler >> temp_pack.start_date.year; packs_handler.ignore(1000, '/');
            packs_handler >> temp_pack.start_date.month; packs_handler.ignore(1000, '/');
            packs_handler >> temp_pack.start_date.day; packs_handler.ignore(1000, '\n');
            //end date
            packs_handler >> temp_pack.end_date.year; packs_handler.ignore(1000, '/');
            packs_handler >> temp_pack.end_date.month; packs_handler.ignore(1000, '/');
            packs_handler >> temp_pack.end_date.day; packs_handler.ignore(1000, '\n');
            
            packs_handler >> temp_pack.price; packs_handler.ignore(1000, '\n');
            packs_handler >> temp_pack.total_seats; packs_handler.ignore(1000, '\n');
            packs_handler >> temp_pack.sold_seats; packs_handler.ignore(1000, '\n');

            if (temp_pack.total_seats <= temp_pack.sold_seats && temp_pack.id > 0){
                temp_pack.id *= -1;
            }

            new_agency.travelpacks_sell.push_back(temp_pack); //saving the info to the agency main struct

            packs_handler.ignore(1000, '\n'); //clear the "::::::::::" line
        }while(last_id != comp_id);
    }
    catch(const std::exception& e){
        std::cout << e.what() << " Information in the agency's information file is incomplete/written in an incorrect form." << std::endl;
        return 2;
    }

    packs_handler.close();
    return 0;
}


int agency_reader(){
    /*
        4 - Operation canceled by user
        0 - Operation successful
        Error Codes:
        1 - missing at least 1 file
        2 - missing/incorrect info in agency file
        3 - missing/incorrect info in clients and/or packs file (received from error code 2 from either clients_reader or packs_reader)
    */

    clr_screen();
    
    std::cout << "What's the name of the agency's static information file (0 to go back)?" << std::endl;
    std::string agencyfile_path; //agency file path
    getline(std::cin, agencyfile_path);

    if(agencyfile_path == "0"){
        return 4;
    }

    if (!file_exists(agencyfile_path)){
        std::cout << "The specified file doesn't exist." << std::endl;
        return 1;
    }

    std::string temp_str; //holds lines from files temporarly when formatting over that line is necessary
    std::istringstream temp_stream; //holds formated lines to attribute to structs/sub-structs
    std::string clientsfile_path, packsfile_path; //path to the other two info files

    std::ifstream agency_handler(agencyfile_path); //agency file handler

    Agency clr_agency;
    new_agency = clr_agency;

    //read the file
    try{
        getline(agency_handler, new_agency.name);
        agency_handler >> new_agency.nif; agency_handler.ignore(1000, '\n'); //getting int
        getline(agency_handler, new_agency.url);
        
        getline(agency_handler, temp_str); temp_stream.str(temp_str.append("/")); //read line to format into temporary string and sends it for formatting
        // read the address struct information. Lines are trimmed of white spaces in both ends
        getline(temp_stream, temp_str, '/'); new_agency.address.street_name = str_trim(temp_str);
        temp_stream >> new_agency.address.door_num; temp_stream.ignore(1000, '/');
        getline(temp_stream, temp_str, '/'); new_agency.address.floor_num = str_trim(temp_str);
        getline(temp_stream, temp_str, '/'); new_agency.address.postal_code = str_trim(temp_str);
        getline(temp_stream, temp_str, '/'); new_agency.address.locale = str_trim(temp_str);
        getline(temp_stream, temp_str, '/');
        if (temp_str != ""){
            std::cout << "Address information in the agency's information file is incomplete/written in an incorrect form." << std::endl;
            return 2;
        }

        agency_handler >> clientsfile_path;
        agency_handler >> packsfile_path;
    }
    catch(const std::exception& e){
        std::cout << e.what() << " Information in the agency's information file is incomplete/written in an incorrect form." << std::endl;
        return 2;
    }

    agency_handler.close(); //close the file after all the info is read

    //branch into the other 2 given files
    if (!file_exists(clientsfile_path) || !file_exists(packsfile_path)){
        std::cout << "At least one of the auxiliary files referenced by the specified file doesn't exist." << std::endl;
        return 1;
    }
    else if(clients_reader(clientsfile_path) != 0 || packs_reader(packsfile_path) != 0){
        return 3;
    }
        
    agency = new_agency;
    return 0;
}


void clients_manager(){
    int op;
    do{
        std::cout   << "1 - Create new client" << std::endl
                    << "2 - Change Client Info" << std::endl
                    << "3 - Delete Client Info" << std::endl
                    << "0 - Go back" << std::endl;

        std::cin >> op; std::cin.ignore(1000, '\n');
        Client new_client;
        bool flag = false;
        size_t i = 0;
        std::string temp_str;
        std::istringstream temp_stream;
        clr_screen();
        switch(op){
            case 0:
                break;

            case 1:
                std::cout << "Enter new client's info:" << std::endl;
                std::cout << "NIF? "; std::cin >> new_client.nif; std::cin.ignore(1000, '\n');

                //check if NIF is already registred
                for(i = 0; i < agency.clients.size(); i++){
                    if(agency.clients.at(i).nif == new_client.nif || new_client.nif == agency.nif){
                        std::cout << "New client creation failed. That NIF was already registred" << std::endl;
                        brk();
                        clr_screen();
                        break;
                    }
                }

                std::cout << "Name? "; getline(std::cin, new_client.name);
                std::cout << "Number of family members? "; std::cin >> new_client.number_family_members; std::cin.ignore(1000, '\n');

                std::cout << "Address:" << std::endl; 
                std::cout << " Street name? "; getline(std::cin, new_client.address.street_name);
                std::cout << " Door num? "; std::cin >> new_client.address.door_num; std::cin.ignore(1000, '\n');
                std::cout << " Floor ('-' char if not applicable)? "; getline(std::cin, new_client.address.floor_num);
                std::cout << " Postal code? "; getline(std::cin, new_client.address.postal_code);
                std::cout << " Locale? "; getline(std::cin, new_client.address.locale);

                std::cout << "Travel packs bought id's (separated by the char ';')? ";
                new_client.pack_number = 0;
                getline(std::cin, temp_str); temp_stream.str(temp_str.append(";-;"));
                do{
                    getline(temp_stream, temp_str, ';');
                    if(temp_str == "" || temp_str == " ")
                        break;
                    new_client.pack_number += 1;
                    new_client.travelpacks_bought.push_back(stoi(temp_str));
                }while(temp_stream.peek() != 45);
                
                agency.clients.push_back(new_client);
                std::cout << "Client added with success" << std::endl;
                brk();
                clr_screen();
                break;

            case 2:
                std::cout << "Enter target client's NIF and new information:" << std::endl;
                std::cout << "NIF? "; std::cin >> new_client.nif; std::cin.ignore(1000, '\n');

                //check if NIF is already registred
                for(i = 0; i < agency.clients.size(); i++){
                    if(agency.clients.at(i).nif == new_client.nif){
                        flag = true;
                    }
                }

                if(!flag){
                    std::cout << "Client info editing failed. That NIF hasn't been registred yet" << std::endl;
                    brk();
                    clr_screen();
                    break;
                }

                std::cout << "Name? "; getline(std::cin, new_client.name);
                std::cout << "Number of family members? "; std::cin >> new_client.number_family_members; std::cin.ignore(1000, '\n');

                std::cout << "Address:" << std::endl; 
                std::cout << " Street name? "; getline(std::cin, new_client.address.street_name);
                std::cout << " Door num? "; std::cin >> new_client.address.door_num; std::cin.ignore(1000, '\n');
                std::cout << " Floor ('-' char if not applicable)? "; getline(std::cin, new_client.address.floor_num);
                std::cout << " Postal code? "; getline(std::cin, new_client.address.postal_code);
                std::cout << " Locale? "; getline(std::cin, new_client.address.locale);

                std::cout << "Travel packs bought id's (separated by the char ';')? ";
                new_client.pack_number = 0;
                getline(std::cin, temp_str); temp_stream.str(temp_str.append(";-;"));
                do{
                    getline(temp_stream, temp_str, ';');
                    if(temp_str == "" || temp_str == " ")
                        break;
                    new_client.pack_number += 1;
                    new_client.travelpacks_bought.push_back(stoi(temp_str));
                }while(temp_stream.peek() != 45);

                agency.clients.at(i) = new_client;
                std::cout << "Client info changed with success" << std::endl;
                brk();
                clr_screen();
                break;

            case 3:
                std::cout << "Enter target client's NIF:" << std::endl;
                std::cout << "NIF? "; std::cin >> new_client.nif; std::cin.ignore(1000, '\n');

                //check if NIF is already registred
                for(i = 0; i < agency.clients.size(); i++){
                    if(agency.clients.at(i).nif == new_client.nif){
                        flag = true;
                    }
                }

                if(!flag){
                    std::cout << "Client info deletion failed. That NIF hasn't been registred yet" << std::endl;
                    brk();
                    clr_screen();
                    break;
                }

                agency.clients.erase(agency.clients.begin() + i);
                std::cout << "Client info deleted with success" << std::endl;
                brk();
                clr_screen();
                break;

            default:
                op = -1;
                break;
        }

        clr_screen();
    }while(op != 0);

}


void pack_manager(){
    int op;
    do{
        std::cout   << "1 - Create new Travel Pack" << std::endl
                    << "2 - Change Travel Pack Info" << std::endl
                    << "3 - Make TravelPack Unavailable" << std::endl
                    << "0 - Go back" << std::endl;

        std::cin >> op; std::cin.ignore(1000, '\n');
        TravelPack new_travelpack;
        bool flag = false;
        size_t i = 0;
        std::string temp_str;
        std::istringstream temp_stream;
        clr_screen();

        switch(op){
            case 0:
                break;

            case 1:
                std::cout << "Enter new Travel Pack's info:" << std::endl;
                std::cout << "ID? "; std::cin >> new_travelpack.id; std::cin.ignore(1000, '\n');

                //check if ID is already registred
                for(i = 0; i < agency.travelpacks_sell.size(); i++){
                    if(abs(agency.travelpacks_sell.at(i).id) == abs(new_travelpack.id)){
                        flag = true;
                        break;
                    }
                }
                if(flag){
                    std::cout << "New Travel Pack creation failed. That ID was already registred." << std::endl;
                    brk();
                    clr_screen();
                    break;
                }

                std::cout << "Destinations? "; getline(std::cin, new_travelpack.destinations);
                //Read dates
                std::cout << "Start date (yyyy/mm/dd)? "; getline(std::cin, temp_str);
                temp_stream.str(temp_str);
                temp_stream >> new_travelpack.end_date.year; temp_stream.ignore(1000, '/');
                temp_stream >> new_travelpack.end_date.month; temp_stream.ignore(1000, '/');
                temp_stream >> new_travelpack.end_date.day; temp_stream.ignore(1000, '\n');

                std::cout << "End date (yyyy/mm/dd)? "; getline(std::cin, temp_str);
                temp_stream.str(temp_str);
                temp_stream >> new_travelpack.end_date.year; temp_stream.ignore(1000, '/');
                temp_stream >> new_travelpack.end_date.month; temp_stream.ignore(1000, '/');
                temp_stream >> new_travelpack.end_date.day; temp_stream.ignore(1000, '\n');
                
                std::cout << "Price? "; std::cin >> new_travelpack.price; std::cin.ignore(1000, '\n');
                std::cout << "Total number of seats? "; std::cin >> new_travelpack.total_seats; std::cin.ignore(1000, '\n');
                std::cout << "Number of seats sold? "; std::cin >> new_travelpack.sold_seats; std::cin.ignore(1000, '\n');

                //checks if it's available and changes the id singla accordingly
                if (new_travelpack.total_seats <= new_travelpack.sold_seats && new_travelpack.id > 0){
                    new_travelpack.id *= -1;
                }

                agency.travelpacks_sell.push_back(new_travelpack);
    
                pack_rect(new_travelpack.id);
                
                std::cout << "Travel Pack added with success" << std::endl;
                brk();
                clr_screen();
                break;

            case 2:
                std::cout << "Enter target Travel Pack's ID and new information:" << std::endl;
                std::cout << "ID? "; std::cin >> new_travelpack.id; std::cin.ignore(1000, '\n');

                //check if ID is already registred
                for(i = 0; i < agency.travelpacks_sell.size(); i++){
                    if(abs(agency.travelpacks_sell.at(i).id) == abs(new_travelpack.id)){
                        flag = true;
                        break;
                    }
                }
                
                if (!flag){
                    std::cout << "Travel Pack info editing failed. That ID hasn't been registred yet" << std::endl;
                    brk();
                    clr_screen();
                    break;
                }
                std::cout << "Destinations? "; getline(std::cin, new_travelpack.destinations);
                //Read dates
                std::cout << "Start date (yyyy/mm/dd)? "; getline(std::cin, temp_str);
                temp_stream.str(temp_str);
                temp_stream >> new_travelpack.end_date.year; temp_stream.ignore(1000, '/');
                temp_stream >> new_travelpack.end_date.month; temp_stream.ignore(1000, '/');
                temp_stream >> new_travelpack.end_date.day; temp_stream.ignore(1000, '\n');

                std::cout << "End date (yyyy/mm/dd)? "; getline(std::cin, temp_str);
                temp_stream.str(temp_str);
                temp_stream >> new_travelpack.end_date.year; temp_stream.ignore(1000, '/');
                temp_stream >> new_travelpack.end_date.month; temp_stream.ignore(1000, '/');
                temp_stream >> new_travelpack.end_date.day; temp_stream.ignore(1000, '\n');
                
                std::cout << "Price? "; std::cin >> new_travelpack.price; std::cin.ignore(1000, '\n');
                std::cout << "Total number of seats? "; std::cin >> new_travelpack.total_seats; std::cin.ignore(1000, '\n');
                std::cout << "Number of seats sold? "; std::cin >> new_travelpack.sold_seats; std::cin.ignore(1000, '\n');

                //checks if it's available and changes the id singla accordingly
                if (new_travelpack.total_seats <= new_travelpack.sold_seats && new_travelpack.id > 0){
                    new_travelpack.id *= -1;
                }

                std::cout << agency.travelpacks_sell.at(i).id;
                agency.travelpacks_sell.at(i) = new_travelpack;
                
                pack_rect(new_travelpack.id);

                std::cout << "Travel Pack info changed with success" << std::endl;
                brk();
                clr_screen();
                break;


            case 3:
                std::cout << "Enter target Travel Pack's ID:" << std::endl;
                std::cout << "ID? "; std::cin >> new_travelpack.id; std::cin.ignore(1000, '\n');

                //check if it is possible to make id unavailable
                if (new_travelpack.id < 0){
                    std::cout << "Travel Pack has to be available to be made unavailable." << std::endl;
                    brk();
                    clr_screen();
                    break;
                }
                
                //check if NIF is already registred
                for(i = 0; i < agency.travelpacks_sell.size(); i++){
                    if(agency.travelpacks_sell.at(i).id == new_travelpack.id){
                        flag = true;
                        break;
                    }
                }
                
                if (!flag){
                    std::cout << "Operation Failed. That ID hasn't been registred yet" << std::endl;
                    brk();
                    clr_screen();
                    break;
                }

                //agency.travelpacks_sell.erase(agency.travelpacks_sell.begin() + i);
                
                agency.travelpacks_sell.at(i).id *= -1;

                pack_rect(agency.travelpacks_sell.at(i).id);

                std::cout << "Travel Pack was made unavailable with success." << std::endl;
                brk();
                clr_screen();
                break;

            default:
                op = -1;
                break;
        }

        clr_screen();
    }while(op != 0);

}


void clients_print(size_t search_nif){
    if (search_nif == 0){
        for(size_t i = 0; i < agency.clients.size(); i++){
            std::cout   << agency.clients.at(i).name << std::endl
                        << agency.clients.at(i).nif  << std::endl
                        << agency.clients.at(i).address.street_name << " / "
                        << agency.clients.at(i).address.door_num << " / "
                        << agency.clients.at(i).address.floor_num << " / "
                        << agency.clients.at(i).address.postal_code << " / "
                        << agency.clients.at(i).address.locale << " / " << std::endl
                        << agency.clients.at(i).number_family_members << std::endl
                        << agency.clients.at(i).pack_number << std::endl;
            for(size_t j = 0; j < agency.clients.at(i).pack_number; j++){
                std::cout << agency.clients.at(i).travelpacks_bought.at(j) << "; ";
            }
            std::cout << std::endl << ":::::::::::" << std::endl;
        }
    }
    else{
        bool flag = false;
        for(size_t i = 0; i < agency.clients.size(); i++){
            if(agency.clients.at(i).nif == search_nif){
                flag = true;
                std::cout   << agency.clients.at(i).name << std::endl
                            << agency.clients.at(i).nif  << std::endl
                            << agency.clients.at(i).address.street_name << " / "
                            << agency.clients.at(i).address.door_num << " / "
                            << agency.clients.at(i).address.floor_num << " / "
                            << agency.clients.at(i).address.postal_code << " / "
                            << agency.clients.at(i).address.locale << " / " << std::endl
                            << agency.clients.at(i).number_family_members << std::endl
                            << agency.clients.at(i).pack_number << std::endl;
                for(size_t j = 0; j < agency.clients.at(i).pack_number; j++){
                    std::cout << agency.clients.at(i).travelpacks_bought.at(j) << "; ";
                }
                std::cout << std::endl;
                break;
            }
        }
        if (!flag){
            std::cout << "Listing operation failed. That NIF wasn't found" << std::endl;
        }
    }
}


void packs_print(){
    for(size_t i = 0; i < agency.travelpacks_sell.size(); i++){
        std::cout   << agency.travelpacks_sell.at(i).id << std::endl
                    << agency.travelpacks_sell.at(i).destinations  << std::endl
                    << agency.travelpacks_sell.at(i).start_date.year << " / "
                    << agency.travelpacks_sell.at(i).start_date.month << " / "
                    << agency.travelpacks_sell.at(i).start_date.day << " / " << std::endl
                    << agency.travelpacks_sell.at(i).end_date.year << " / "
                    << agency.travelpacks_sell.at(i).end_date.month << " / "
                    << agency.travelpacks_sell.at(i).end_date.day << " / " << std::endl
                    << agency.travelpacks_sell.at(i).total_seats << std::endl
                    << agency.travelpacks_sell.at(i).sold_seats  << std::endl
                    << agency.travelpacks_sell.at(i).price  << std::endl
                    << ":::::::::::" << std::endl;
    }
}


void agency_print(){
    // agency info
    std::cout   << "Agency: " << std::endl
                << " Name: " << agency.name << std::endl
                << " NIF: " << agency.nif << std::endl
                << " URL: " << agency.url << std::endl
                << " Address: " << agency.address.street_name << " / "
                << agency.address.door_num << " / "
                << agency.address.floor_num << " / "
                << agency.address.postal_code << " / "
                << agency.address.locale << std::endl;
}


void pack_buy(){
    bool flag = false;
    size_t client_nif, i, j; //target client's NIF
    int travelpack_id; //id of travel pack to sell

    std::cout << "Enter target client's nif (0 to go back): "; std::cin >> client_nif; std::cin.ignore(1000, '\n');
    if(client_nif == 0){
        std::cout << "Operation has been canceled successfully" << std::endl;
        return;
    }
    for(i = 0; i < agency.clients.size(); i++){
        if(agency.clients.at(i).nif == client_nif){
            flag = true;
        }
    }
    if (!flag){
        std::cout << "Operation Failed. That client doesn't exist." << std::endl;
        return;
    }

    std::cout << "Enter target travel pack's id: "; std::cin >> travelpack_id; std::cin.ignore(1000, '\n');
    if(abs(travelpack_id) != travelpack_id){
        std::cout << "Operation failed. The travel pack has to be available to be sold." << std::endl;
        return;
    }
    //travelpack_id = abs(travelpack_id);
    for(j = 0; j < agency.travelpacks_sell.size(); j++){
        if(agency.travelpacks_sell.at(j).id == travelpack_id){
            flag = true;
        }
    }
    if (!flag){
        std::cout << "Operation failed. There is no available travel pack witht that id." << std::endl;
        return;
    }

    //selling operation:
    agency.clients.at(i).travelpacks_bought.push_back(travelpack_id);
    agency.clients.at(i).pack_number++;
    agency.travelpacks_sell.at(j).sold_seats++;
    if (agency.travelpacks_sell.at(j).sold_seats >= agency.travelpacks_sell.at(j).total_seats){
        agency.travelpacks_sell.at(j).id *= -1;
    }

    pack_rect(agency.travelpacks_sell.at(j).id); //sync travel pack info across clients

    std::cout << "Operation successful. The travel pack was bought." << std::endl;
}


void grofit(){
    int packs_sold = 0;
    float profit = 0;

    for(size_t i = 0; i < agency.travelpacks_sell.size(); i++){
        packs_sold += agency.travelpacks_sell.at(i).sold_seats;
        profit += packs_sold * agency.travelpacks_sell.at(i).price;
    }

    std::cout   << "Number of Travel Packs sold: " << packs_sold << std::endl
                << "Profit made from selling travel Packs: " << profit << std::endl;
}


// My girlfriend just hur dur'ed me. What do?
int main(){
    int op = -1;
    size_t argtpass = 0;
    bool files_read = false; //tells if the files have been read successfuly
    clr_screen();
    std::cout << "Developed by Joao de Jesus Costa - up201806560 (FEUP)" << std::endl;
    
    do{
        std::cout   << "1 - Read information files (overrides current info)" << std::endl
                    << "2 - Manage Clients" << std::endl
                    << "3 - Manage Travel Packs" << std::endl
                    << "4 - List all/target clients" << std::endl
                    << "5 - List all travel packs" << std::endl
                    << "6 - Show stored agency info" << std::endl
                    << "7 - Sell a Travel Pack to a client" << std::endl
                    << "8 - Number and Value of sold Travel packs" << std::endl
                    << "0 - Close Application" << std::endl;

        std::cin >> op; std::cin.ignore(1000, '\n');
        clr_screen();
        switch (op){
            case 0:
                break;

            case 1:
                argtpass = agency_reader();
                if (argtpass == 4){
                    std::cout << "Reading operation canceled successfully. No changes have been made to the stored info." << std::endl;
                }
                else if (argtpass == 0){
                    files_read = true;
                    std::cout << "Reading operation successful." << std::endl;
                }
                else{
                    std::cout << "Reading operation failed. Stored info has not been changed." << std::endl;
                }

                brk();
                break;

            case 2:
                if (files_read)
                    clients_manager();
                else{
                    std::cout << "Can't manage information because files haven't been read yet" << std::endl;
                    brk();
                }
                break;

            case 3:
                if (files_read)
                    pack_manager();
                else{
                    std::cout << "Can't manage information because files haven't been read yet" << std::endl;
                    brk();
                }
                break;

            case 4:
                if (files_read){
                    std::cout << "Target client's NIF (0 to list all clients)? ";
                    std::cin >> argtpass; std::cin.ignore(1000, '\n');
                    clients_print(argtpass);
                }
                else
                    std::cout << "Can't print information because files haven't been read yet" << std::endl;
                brk();
                break;

            case 5:
                if (files_read){
                    /*
                        std::cout << "Target travel pack's ID (0 to list all travel packs)? ";
                        std::cin >> argtpass; std::cin.ignore(1000, '\n');
                        */
                    packs_print();
                }
                else
                    std::cout << "Can't print information because files haven't been read yet" << std::endl;
                brk();
                break;

            case 6:
                if (files_read)
                    agency_print();
                else
                    std::cout << "Can't print information because files haven't been read yet" << std::endl;

                brk();
                break;

            case 7:
                if (files_read)
                    pack_buy();
                else
                    std::cout << "Clients can't buy travel packs because no information has been read yet" << std::endl;
                brk();
                break;

            case 8:
                if (files_read)
                    grofit();
                else
                    std::cout << "Clients can't buy travel packs because no information has been read yet" << std::endl;
                brk();
                break;

            default:
                op = -1;
                break;
        }
        
        clr_screen();
    }while(op != 0);

    return 0;
}


/*
TODO:
5. Gerar e visualizar de modo formatado os pacotes turísticos disponíveis (todos, todos relativos a
um destino específico, todos entre duas datas, todos os relativos a um destino específico e entre
duas datas).
6. Gerar e visualizar de modo formatado os pacotes turísticos vendidos (a um cliente específico, a
todos os clientes).
*/
