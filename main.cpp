#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <sys/stat.h>
#include <set>
#include <map>
#include <utility>

//In memory of Terry Davis (December 15, 1969 - August 11, 2018)
using namespace std;

#define clr_screen() cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"; //clear screen
#define no_read() do { clr_screen(); cout << "FILES HAVEN'T BEEN SUCCESSFULLY READ YET\n";} while (0); //displays a message to the user that states that the files haven't been read successfully yet
#define brk() do { cout << "Press the 'enter' key to continue.." << '\n'; getchar(); clr_screen();} while (0); //break function used for waiting for the user

typedef pair<size_t, set<size_t>> map_vistis_id;

string str_trim(const string& str){
    /*
        Trims a string of whitespaces in the beggining and end;
        Takes a string to trim as an argument;
        Returns the trimmed string;
    */
    if(str == ""){
        return "";
    }
    return (str.substr(str.find_first_not_of(" "), str.find_last_not_of(" ") - str.find_first_not_of(" ") + 1));
}

bool file_exists(const string& name){
    /*
        Checks if a given file exists;
        Takes a string specifing the path to the file to check as an argument;
        Returns true in case the file exists and false in case the files doesn't exist;
        Source: https://stackoverflow.com/a/12774387
    */
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

map<string, map_vistis_id> *map_ref;

#include "include/date.h"
#include "include/address.h"
#include "include/travelpack.h"

// these functions are used by clients.h so they must be here 
template <class Temp>
int find_in_vector(vector<Temp> const &vec, Temp const &t);
    /* Returns the index of element t in the vector. Returns -1 if t isn't found in vec.*/
int find_in_vector(vector<TravelPack> const &vec, const int &id);
    /* Returns the position of the travel pack which has the same identificator as id. Returns -1 if no travel packet with id is found.*/

#include "include/client.h"

int find_in_vector(vector<Client> const &vec, const string &name);
    /* Returns the position of the client which has the same name as name. Returns -1 if no client with the given name is found.*/

#include "include/agency.h"

int select_client(const vector<Client> &client_list)
{
    /*Forces the user to enter a valid client name. Returns the index of the client with the name given by the user.
    @param client_list: Vector used to see if the given name exists.
    @param result: The index of the client with the name given by the user. Returns -1 if the user opted-out*/

    string name;
    int index = -1;

    while(name != "-1")
    {
        cout << "Insert the client name.\n";
        cout << "\nTo cancel type -1\n";
        getline(cin, name);
        index = find_in_vector(client_list, name);

        if(index != -1)
            return(index);
         else 
            {
            if(name != "-1")
                cout << "No such client with that name. Please try again\n";
        }
    }

    return index;
}


int select_id(const vector<TravelPack> &packet_list)
{
    /*Forces the user to enter a valid packet ID. Returns the index of the package with the ID given by the user.
    @param packet_list: Vector used to see if the given id exists.
    @param result: The index of the package with the ID given by the user. Returns -1 if the user opted-out*/
    bool sucess=false;
    int index_of_packet;
    int id_in_vector=-1;

    while((!sucess)&(index_of_packet != 0))
    {
        cout << "Insert the Id of the travel pack.\nType 0 to go back\n";
        cin >> index_of_packet;
        if(cin.fail())
        {
            cout << "Please insert a valid integer\n";
            cin.clear(); cin.ignore(1000, '\n');
            continue; // re-iterates loop
        }

        //index_of_packet = abs(index_of_packet);
        id_in_vector = find_in_vector(packet_list, index_of_packet);

        if(id_in_vector != -1) // if found, sucess!
            sucess = true;
        else{
            index_of_packet *= -1; //we check for both the positive and the negative "version" of the id
            id_in_vector = find_in_vector(packet_list, index_of_packet);

            if(id_in_vector != -1) // if found, sucess!
                sucess = true;
            else{
                // sucess = false; not needed because sucess if by default set to false
                cout << "There isn't any packet that has the given id. Please try again.\n";
            } 
        }
    }

    return(id_in_vector);
}


void clients_manager(Agency &agency)
{
    char op;
    int id; //option selected by user from the menu
    clr_screen();
    do{
        cout    << "1 - Create new client\n"
                << "2 - Change existing client\n"
                << "3 - Delete existing client\n"
                << "4 - Make a purchase by an existing client\n"
                << "\nQ - Go back" << endl; //menu options
        cin >> op; cin.ignore(1000, '\n');
        clr_screen();

        try{
            switch (op){
            case '1':
            {
                new_client(agency.client_list, agency.nif);
                brk();
                break;
            }
            case '2':
            {
                int index = select_client(agency.client_list);
                if(index != -1) // if user hasn't opted out from selecting a client name
                    modify_client(agency.client_list, index, agency.nif);
                brk();
                break;
            }
            case '3':
            {
                int index = select_client(agency.client_list);
                if(index != -1) // if user hasn't opted out from selecting a client name
                    agency.client_list.erase(agency.client_list.begin() + index);
                brk();
                break;
            }
            case '4':
            {
                int client_index = select_client(agency.client_list);
                if(client_index != -1) // if user hasn't opted out from selecting a client name
                {
                    int packet_index = select_id(agency.packet_list);
                    if(packet_index != -1){
                        agency.packet_list.at(packet_index)++; //Do first because it throws an exception if the travel pack is not available anymore
                        agency.client_list[client_index].buyPacket(agency.packet_list, packet_index);
                    }
                }
                
                brk();
                break;
            }
            case 'q':
            case 'Q':
                break;
            default:
                cout << "THERE IS NO SUCH OPTION\n";
                cout << op;
                brk();
                break;
            }
        }
        catch(const exception& e){
            cerr << e.what() << '\n';
        }
    }while (op != 'q' && op != 'Q');
}


void travelpack_manager(vector<TravelPack> &packet_list){
    char op;
    int id; //option selected by user from the menu
    clr_screen();
    do{
        cout    << "1 - Create new travel pack\n"
                << "2 - Edit travel pack (ID can't be changed)\n"
                << "3 - Make travel pack unavailable\n"
                << "\nQ - Go back" << endl; //menu options
        cin >> op; cin.ignore(1000, '\n');
        //cout << endl;

        try{
            switch (op){
            case '1':
            {
                TravelPack temp_travelpack(cin);
              	//Check for duplicates for both the positive and the negative versions of the id 
                id = find_in_vector(packet_list, temp_travelpack.get_id());
                if (id != -1)
                    throw runtime_error("CAN'T HAVE TRAVEL PACKS WITH DUPLICATED IDS");
                id = find_in_vector(packet_list, temp_travelpack.get_id() * -1);
                if (id != -1)
                    throw runtime_error("CAN'T HAVE TRAVEL PACKS WITH DUPLICATED IDS");

                packet_list.push_back(temp_travelpack);
                brk();
                break;
            }
            case '2':{
                id = select_id(packet_list);
                if (id == -1){
                    brk();
                    break;
                }
                
                packet_list.at(id) = TravelPack(cin, packet_list.at(id)); //Call a different constructer for this travel pack because we're editing it. This constructor cleans the destination map of "trash information" and prevents ID changes
				
                brk();
                break;
            }
            case '3':
                clr_screen();
                id = select_id(packet_list);
                if (id == -1){
                    brk();
                    break;
                }

                packet_list.at(id).make_unavailable(); //Makes the ID negative. Throws an exception in case the id is already negative. Also cleans the destination amp of "trash information"
                brk();
                break;
            case 'q':
            case 'Q':
                break;
            default:
                cout << "THERE IS NO SUCH OPTION\n";
                brk();
                break;
            }
        }
        catch(const exception& e){
            cerr << e.what() << '\n';
            brk();
        }
        
    }while (op != 'q' && op != 'Q');
}


void read_info(bool &files_read, Agency &ragency){
    Agency agency;  //information is read into a temporary agency struct so if the reading process fails, the information read before-hand, is not changed

    try{
        clr_screen();
        cout << "What's the name/path of the agency's static information file (0 to go back)?" << endl;
        string agencyfile_path; //agency file path
        getline(cin, agencyfile_path);

        if (agencyfile_path == "0") //go back
            return;

        if (!file_exists(agencyfile_path)) //check for file existance
            throw invalid_argument("THE SPECIFIED AGENCY FILE DOES NOT EXIST");
        
        //Read agency info
        ifstream file_input(agencyfile_path);
        string clientsfile_path, packsfile_path, url, name, aux_string;
        unsigned int nif;

        getline(file_input, name);
        file_input >> nif; if(file_input.fail()) throw runtime_error("INCORRECT FISCAL NUMBER\n"); file_input.ignore();
        getline(file_input, url);
        Address address(file_input);
        getline(file_input, clientsfile_path);
        getline(file_input, packsfile_path);
        file_input.close();

        //Check clients' information file existence
        if (!file_exists(clientsfile_path))
            throw invalid_argument("THE SPECIFIED CLIENTS FILE DOES NOT EXIST");

        //Check travel packs' information file existence
        if (!file_exists(packsfile_path))
            throw invalid_argument("THE SPECIFIED PACKS FILE DOES NOT EXIST");

        agency.name = name; agency.nif = nif; agency.address = address; agency.url = url;

        // clients file
        file_input.open(clientsfile_path);
        while(!file_input.eof())
        {
            agency.client_list.push_back(Client(file_input));
            file_input.ignore('\n'); file_input.ignore();
        }
        file_input.close();

        // travel pack's file
        int i;
        file_input.open(packsfile_path); file_input.ignore(1000, '\n');

        map_ref = &agency.map_visits; //update the refence to work on the new map
        while(!file_input.eof())
        {
            TravelPack temp_travelpack(file_input);
            file_input.ignore('\n'); file_input.ignore();
            
          	//check for id duplication before adding it to the vector
            i = find_in_vector(agency.packet_list, temp_travelpack.get_id());
            if (i != -1)
                throw runtime_error("CAN'T HAVE TRAVEL PACKS WITH DUPLICATED IDS");
            i = find_in_vector(agency.packet_list, temp_travelpack.get_id() * -1);
            if (i != -1)
                throw runtime_error("CAN'T HAVE TRAVEL PACKS WITH DUPLICATED IDS");
            
            //only register travelpack if the info has been read correctly and the id is not dulicated
            agency.packet_list.push_back(temp_travelpack);
        }
        file_input.close();

        ragency = agency; //Reading operation was successful so the information is saved
        map_ref = &ragency.map_visits; //need to update pointer because the other object will be destroyed
        files_read = true;

        clr_screen();
        cout << "INFORMATION HAS BEEN READ SUCCESSFULLY\n";
        brk();
    }
    catch(const exception& e){
        map_ref = &ragency.map_visits; //update the refence to go back to the hold map in case of failure
        cerr << e.what() << '\n';
        cout << "INFORMATION HAS NOT BEEN SAVED/CHANGED\n";
        brk();
    }
    
    clr_screen();
}


void write_info(const Agency &agency,const string &agencyfile_path,const string &clientsfile_path, const string &packsfile_path)
{
    //use all the print methods in all the classes with the write files' handlers as ostreams
    ofstream file_output;
    
    file_output.open (agencyfile_path);
    file_output << agency.name << '\n' << agency.nif << '\n' << agency.url << '\n';
    agency.address.print(file_output);
    file_output << clientsfile_path << '\n';
    file_output << packsfile_path;
    file_output.close();

    file_output.open (clientsfile_path);
    int n = agency.client_list.size();
    for(int i=0;i<n-1;i++)
    {
        agency.client_list.at(i).print(file_output);
        file_output << "::::::::::\n";
    }
    agency.client_list[n-1].print(file_output);
    file_output.close();

    file_output.open (packsfile_path);
    n = agency.packet_list.size();

    file_output << agency.packet_list.at(n - 1).get_id() << '\n';  // add last package id to the top of the file
    for(int i=0;i<n-1;i++)
    {
        agency.packet_list[i].print(file_output);
        file_output << "::::::::::\n";
    }
    agency.packet_list[n-1].print(file_output);

    file_output.close();
}


void clients_print(vector<Client> const &client_list)
{
    char op; //option selected by user from the menu

    clr_screen();

    do{
        cout    << "1 - Print information about a specific client\n"
                << "2 - Print information about all clients\n"
                << "\nQ - Exit" << endl; //menu options

        cin >> op; cin.ignore(1000, '\n');
        try{
            if (client_list.size() == 0)
                throw logic_error("The agency doesn't have any registered travel packs");

            switch (op){
            case '1':
            {
                int index = select_client(client_list);
                clr_screen();
                if(index != -1) // if user hasn't opted out
                    client_list[index].print(cout);
                brk();
                break;
            }
            case '2':
            {
                clr_screen();
                print_clients(client_list, cout);
                brk();
                break;
            }
            case 'q':
            case 'Q':
                break;
            default:
                cout << "THERE IS NO SUCH OPTION\n";
                brk();
                break;
            }
        }
        catch(const std::exception& e){
            brk();
            std::cerr << e.what() << '\n';
        }
        

    }while (op != 'q' && op != 'Q');
}


void travelpacks_print(vector<TravelPack> const &packet_list){
    char op, op2; //option selected by user from the menu
    bool flag;

    clr_screen();

    do{
        cout    << "1 - Print information about all travel packs\n"
                << "2 - Print information about a specific destination\n"
                << "3 - Print information about a specific timespan\n"
                << "4 - Print information about a specific destination and timespan\n"
                << "\nQ - Exit" << endl; //menu options

        //overloaded print functions for travel packs
        cin >> op; cin.ignore(1000, '\n');

        flag = false;
        if(op == 'q' || op == 'Q')
            return;
        cout << "Should unavailable travel packs' information be printed too (y for yes)? ";
        cin >> op2; cin.ignore(1000, '\n');
        if (op2 == 'y' || op2 == 'Y')
            flag = true;

        try{
            if (packet_list.size() == 0)
                throw runtime_error("THE AGENCY DOESN'T HAVE ANY REGISTERED TRAVEL PACKS");

            switch (op){
            case '1':
            {
                clr_screen();
                print_travelpacks(packet_list, cout, flag);
                brk();
                break;
            }
            case '2':
            {   
                string dest;
                cout << "Insert the specific destination: "; cin >> dest; cin.ignore();

                print_travelpacks(packet_list, cout, dest, flag);
                brk();
                break;
            }
            case '3':
            {
                cout << "Start date (yyyy/mm/dd)? "; Date startdate(cin);
                cout << "End date (yyyy/mm/dd)? "; Date enddate(cin);

                print_travelpacks(packet_list, cout, startdate, enddate, flag);
                brk();
                break;
            }
            case '4':
            {
                string dest;
                cout << "Insert the specific destination: "; cin >> dest; cin.ignore();
                cout << "Start date (yyyy/mm/dd)? "; Date startdate(cin);
                cout << "End date (yyyy/mm/dd)? "; Date enddate(cin);

                print_travelpacks(packet_list, cout, startdate, enddate, dest, flag);
                brk();
                break;
            }
            /*case 'q':  // exit check is done above
            case 'Q':
                break;*/
            default:
                cout << "THERE IS NO SUCH OPTION\n";
                brk();
                break;
            }    
        }
        catch(const exception& e){
            brk();
            cerr << e.what() << '\n';
        }
        
    }while (op != 'q' && op != 'Q');
}


void profit_made(vector<TravelPack> const &packet_list){
    float profit = 0;
    unsigned long long int packs = 0;

    //Calculate and print the total number of travel packs registered in the agency and how they're worth in total
    for(size_t i = 0; i < packet_list.size(); i++){
        packs += packet_list.at(i).get_taken_seats();
        profit += (packet_list.at(i).get_price() * packet_list.at(i).get_taken_seats());
    }

    cout << "The agency sold " << packs << " travel packs and profited " << fixed << setprecision(2) << profit << endl;
}


void bought_travelpacks_print(vector<TravelPack> const &packet_list, vector<Client> const &client_list){
    char op; //option selected by user from the menu

    clr_screen();

    do{
        cout    << "1 - Print information about all clients' travel packs\n"
                << "2 - Print information about a specific client's  travel packs\n"
                << "\nQ - Exit" << endl; //menu options

        cin >> op; cin.ignore(1000, '\n');
        try{
            switch (op){
            case '1':
            {
                clr_screen();
                //Iterates through all clients
                for(int i=0;i<client_list.size();i++)
                {
                    cout << client_list.at(i).getName() << ":\n";
                    for(int j=0; j<client_list.at(i).getPackets().size(); j++)
                    {
                        //For each travel pack check if their info has been registred in the agency yet
                        int index = find_in_vector(packet_list, client_list.at(i).getPackets().at(j));
                        if(index == -1)
                            cout << "Packet with ID " << client_list.at(i).getPackets().at(j) << " not recognized!\n";
                        else
                            packet_list[index].print(cout); //Say that we don't have the info for each travel pack we haven't found

                        cout << "::::::::::" << endl;
                    }
                    cout << "\n\n\n";
                }
                brk();
                break;
            }
            case '2':
            {   
                int client_index = select_client(client_list);
                clr_screen();
                if(client_index != -1)
                {
                    cout << client_list.at(client_index).getName() << ":\n";
                    for(int i=0; i<client_list.at(client_index).getPackets().size(); i++)
                    {
                        int packet_index = find_in_vector(packet_list, client_list.at(client_index).getPackets().at(i));
                        if(packet_index == -1)
                            cout << "Packet with ID " << client_list.at(client_index).getPackets().at(i) << " not recognized!\n";
                        else
                            packet_list[packet_index].print(cout);
                        cout << "::::::::::" << endl;
                    }
                }
                brk();
                break;
            }
            case 'q':
            case 'Q':
                break;
            default:
                cout << "THERE IS NO SUCH OPTION\n";
                brk();
                break;
            }    
        }
        catch(const exception& e){
            brk();
            cerr << e.what() << '\n';
        }

    }while (op != 'q' && op != 'Q');
}


multiset<dests_visits, cmp_visits> make_set_from_map(){
    /*Creates and returns a multiset made from the cisited locals map.
    The multiset contains pairs of <size_t, string> and sorts itself by the size_t in descending order*/
    map<string, map_vistis_id>::iterator it;
    multiset<dests_visits, cmp_visits> set_visits;
    for (it = map_ref->begin(); it != map_ref->end(); it++)
        set_visits.insert(make_pair((*it).second.first, (*it).first));

    return set_visits;
}


void top_print(){
    size_t max_packs;
    clr_screen();

    //Reading a valid unsigned long int
    cout << "What's the maximum of travel packs that should be shown? (0 to go back) ";
    while(true){
        cin >> max_packs;
        if(cin.fail()){
            cout << "Please insert a valid integer\n";
            cin.clear(); cin.ignore(1000, '\n');
            continue; // re-iterates loop
        }else{
            cin.ignore(1000, '\n');
            break;
        }
    }

    if(max_packs == 0)
        return;

    multiset<dests_visits, cmp_visits> set_visits = make_set_from_map();
    multiset<dests_visits, cmp_visits>::iterator it;

    cout << "Destinations are ordered from most popular to least popular (When popularity is the same, the travel packs are ordered by name)\n" << endl;
    for (it = set_visits.begin(); it != set_visits.end() && max_packs > 0; it++){
        max_packs--;
        cout << (*it).second << ' ' << '(' << (*it).first << " bought seats)\n"; //print all the elements in the set set_visits in order
    }

    cout << endl;
}


void ai(vector<TravelPack> const &packet_list, vector<Client> const &client_list){
    multiset<dests_visits, cmp_visits> set_visits = make_set_from_map();
    multiset<dests_visits, cmp_visits>::iterator it;
    clr_screen();

    for(size_t i = 0; i < client_list.size(); i++){ //iterates through all clients
        //The set clientvisits will contain all the locations visited by this client's bough travel packs
        set<string> clientvisits;
        for(size_t j = 0; j < client_list.at(i).getPackets().size(); j++){ //iterates through all the travel packs bought by the current client
            int index = find_in_vector(packet_list, client_list.at(i).getPackets().at(j));
          	
          	//If the travelpacks being checked are currently available, the locations visited by them are added to the clientvisits set
            if (index != -1){
                clientvisits.insert(packet_list.at(index).get_destination());
                if (packet_list.at(index).has_landmarks()){
                    for (size_t k = 0; k < packet_list.at(index).get_landmarks().size(); k++){
                        clientvisits.insert(packet_list.at(index).get_landmarks().at(k));
                    }
                }
            }
        }

        //looks at travel packs that list locations not visited by the current client's bought travel packs
        bool not_found = true;
        for (it = set_visits.begin(); it != set_visits.end(); it++){
            if ((*map_ref)[(*it).second].second.size() != 0 && clientvisits.find((*it).second) == clientvisits.end()){ //it only selects available travel packs for suggestion
                not_found = false;
                cout    << "The client '" << client_list.at(i).getName()
                        << "' should buy the travel pack with the id " << (*(*map_ref)[(*it).second].second.begin())
                        << " because '" << (*it).second << "' is the most popular location that he hasn't visited\n";
                break;
            }
        }
        if (not_found) //in case there were no suggestions to be made
            cout    << "The client '" << client_list.at(i).getName() 
                    << "' has visited/will visit all the locations offered by the agency's AVAILABLE travel packs already."
                    << " No suggestions to be made.\n";
        cout << endl;
    } 
}


int main(){
    char op; //option selected by user from the menu
    bool files_read = false;

    Agency agency;
    clr_screen();
    cout << "Developed by:\tJoao de Jesus Costa - up201806560 (FEUP)\n\t\tJoao Lucas Silva Martins - up201806436 (FEUP)\n" << endl;

    do{
        cout    << "1 - Read information files\n"
                << "2 - Manage clients\n"
                << "3 - Manage travel packs\n"
                << "4 - Print client's information\n"
                << "5 - Print travel packs' information\n"
                << "6 - View sold travel packs\n"
                << "7 - Number of sold travel packs and profit made\n"
                << "8 - Print most visited locals\n"
                << "9 - Suggested travel packs for each client\n"
                << "S - Save read agency information to files\n"
                << "\nQ - Exit\n" << endl; //menu options

        cin >> op; cin.ignore(1000, '\n');
        switch (op){
        case '1':
            read_info(files_read, agency);
            break;
        case '2':
            if (files_read)
                clients_manager(agency);
            else
                no_read();
            brk();
            break;
        case '3':
            if (files_read)
                travelpack_manager(agency.packet_list);
            else
                no_read();
            brk();
            break;
        case '4':
            if (files_read)
                clients_print(agency.client_list);
            else
                no_read();
            brk();
            break;
        case '5':
            if (files_read)
                travelpacks_print(agency.packet_list);
            else
                no_read();
            brk();
            break;
        case '6':
        {
            if (files_read)
                bought_travelpacks_print(agency.packet_list, agency.client_list);
            else
                no_read();
            brk();
            break;
        }
        case '7':
            if (files_read)
                profit_made(agency.packet_list);
            else
                no_read();
            brk();
            break;
        case '8':
            if (files_read)
                top_print();
            else
                no_read();
            brk();
            break;
        case '9':
            if (files_read)
                ai(agency.packet_list, agency.client_list);
            else
                no_read();
            brk();
            break;
        case 's':
        case 'S':
        {
            if (files_read){
                try{
                    //Read the file names to save to ad verify if they are not duplicates
                    string agencyfile_path, clientsfile_path, packsfile_path;
                    cout << "Insert 'Q' at anytime to go back\n";
                    cout << "Agency's information file name? "; cin >> agencyfile_path;
                    if(agencyfile_path == "q" || agencyfile_path == "Q") break;

                    cout << "Clients' information file name? "; cin >> clientsfile_path;
                    if(clientsfile_path == "0") break;
                    if(agencyfile_path == clientsfile_path)
                        throw invalid_argument("THE FILES FOR THE AGENCY'S AND THE CLIENTS' INFORMATION CAN'T HAVE THE SAME NAME");

                    cout << "Travel packs' information file name? "; cin >> packsfile_path;
                    if(packsfile_path == "0") break;
                    if(packsfile_path == agencyfile_path)
                        throw invalid_argument("THE FILES FOR THE AGENCY'S AND THE TRAVEL PACKS' INFORMATION CAN'T HAVE THE SAME NAME");
                    if(packsfile_path == clientsfile_path)
                        throw invalid_argument("THE FILES FOR THE CLIENTS' AND THE TRAVEL PACKS' INFORMATION CAN'T HAVE THE SAME NAME");

                    write_info(agency, agencyfile_path, clientsfile_path, packsfile_path);
                }
                catch(const exception& e){
                    cerr << e.what() << '\n';
                }
            }
            else
                no_read();

            brk();
            break;
        }
        case 'q':
        case 'Q':
            break;
        default:
            cout << "THERE IS NO SUCH OPTION\n";
            brk();
            break;
        }

    }while (op != 'q' && op != 'Q');

    clr_screen();
    return 0;
}
/*
    TODO
    ---Ler e guardar a informação da agência, dos clientes e dos pacotes turísticos armazenada em ficheiros.

    ---Gerir os clientes e pacotes turísticos: criar, alterar e remover um cliente; criar, alterar ou colocar como
    indisponível um pacote turístico (nota: os pacotes turísticos nunca são efetivamente removidos.

    ---Gerar e visualizar de modo formatado a informação de um cliente especificado.

    ---Gerar e visualizar de modo formatado a informação de todos os clientes da agência.

    ---Gerar e visualizar de modo formatado os pacotes turísticos disponíveis (todos, todos relativos a um destino
    específico, todos entre duas datas, todos os relativos a um destino específico e entre duas datas).

    ---Gerar e visualizar de modo formatado os pacotes turísticos vendidos (a um cliente específico, a todos os clientes).

    ---Efetuar a compra de uma pacote turístico por um cliente.

    ---Calcular e visualizar o número e o valor total de pacotes vendidos.

    ---Obter o nome dos N locais mais visitados (um pacote pode incluir visitas a vários locais), ordenados por ordem
    decrescente do número de visitas ( = número de pacotes vendidos que passam por esse local).

    ---Gerar uma listagem de todos os clientes na qual se indica, para cada cliente, um dos pacotes em que seja
    visitado um dos N locais mais visitados (ver ponto 9) que ele ainda não visitou.
*/
