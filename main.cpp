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

#define clr_screen() std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"; //clear screen
#define no_read() do { clr_screen(); std::cout << "FILES HAVEN'T BEEN SUCCESSFULLY READ YET\n";} while (0); //displays a message to the user that states that the files haven't been read successfully yet
#define brk() do { std::cout << "Press the 'enter' key to continue.." << '\n'; getchar(); clr_screen();} while (0); //break function used for waiting for the user


std::string str_trim(const std::string& str){
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

std::map<std::string, size_t> *map_ref;

#include "include/date.h"
#include "include/address.h"
#include "include/travelpack.h"

// these functions are used by clients.h so they must be here 
template <class Temp>
int find_in_vector(std::vector<Temp> const &vec, Temp const &t);
    /* Returns the index of element t in the vector. Returns -1 if t isn't found in vec.*/
int find_in_vector(std::vector<TravelPack> const &vec, const int &id);
    /* Returns the position of the travel pack which has the same identificator as id. Returns -1 if no travel packet with id is found.*/

#include "include/client.h"

int find_in_vector(std::vector<Client> const &vec, const std::string &name);
    /* Returns the position of the client which has the same name as name. Returns -1 if no client with the given name is found.*/

#include "include/agency.h"


int select_client(const std::vector<Client> &client_list)
{
    /*Forces the user to enter a valid client name. Returns the index of the client with the name given by the user.
    @param client_list: Vector used to see if the given name exists.
    @param result: The index of the client with the name given by the user. Returns -1 if the user opted-out*/

    std::string name;
    int index = -1;

    while(name != "-1")
    {
        std::cout << "Insert the client name.\n";
        std::cout << "\nTo cancel type -1\n";
        getline(std::cin, name);
        index = find_in_vector(client_list, name);

        if(index != -1)
            return(index);
         else 
            {
            if(name != "-1")
                std::cout << "No such client with that name. Please try again\n";
        }
    }

    return index;
}


int select_id(const std::vector<TravelPack> &packet_list)
{
    /*Forces the user to enter a valid packet ID. Returns the index of the package with the ID given by the user.
    @param packet_list: Vector used to see if the given id exists.
    @param result: The index of the package with the ID given by the user. Returns -1 if the user opted-out*/
    bool sucess=false;
    int index_of_packet;
    int id_in_vector=-1;

    while((!sucess)&(index_of_packet != 0))
    {
        std::cout << "Insert the Id of the travel pack.\nType 0 to go back\n";
        std::cin >> index_of_packet;
        if(std::cin.fail())
        {
            std::cout << "Please insert a valid integer\n";
            std::cin.clear(); std::cin.ignore(1000, '\n');
            continue; // re-iterates loop
        }

        index_of_packet = abs(index_of_packet);
        id_in_vector = find_in_vector(packet_list, index_of_packet);

        if(id_in_vector != -1) // if found, sucess!
            sucess = true;
        else{
            index_of_packet *= -1;
            id_in_vector = find_in_vector(packet_list, index_of_packet);

            if(id_in_vector != -1) // if found, sucess!
                sucess = true;
            else{
                // sucess = false; not needed because sucess if by default set to false
                std::cout << "There isn't any packet that has the given id. Please try again.\n";
            } 
        }
    }

    return(id_in_vector);
    
}


void clients_manager(Agency &agency)
{
    int op;
    int id; //option selected by user from the menu
    clr_screen();
    do{
        std::cout   << "1 - Create new client\n"
                    << "2 - Change existing client\n"
                    << "3 - Delete existing client\n" //TODO: refund packs or not??
                    << "4 - Make a purchase by an existing client\n"
                    << "\nQ - Go back" << std::endl; //menu options
        std::cin >> op; std::cin.ignore(1000, '\n');
        clr_screen();

        try{
            switch (op){
            case '1':
            {
                new_client(agency.client_list);
                brk();
                break;
            }
            case '2':
            {
                int index = select_client(agency.client_list);
                if(index != -1) // if user hasn't opted out from selecting a client name
                    modify_client(agency.client_list, index);
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
                std::cout << "THERE IS NO SUCH OPTION\n";
                brk();
                break;
            }
        }
        catch(const std::exception& e){
            std::cerr << e.what() << '\n';
        }
    }while (op != 'q' && op != 'Q');
}


void travelpack_manager(std::vector<TravelPack> &packet_list){
    char op; 
    int id; //option selected by user from the menu
    clr_screen();
    do{
        std::cout   << "1 - Create new travel pack\n"
                    << "2 - Edit travel pack\n"
                    << "3 - Make travel pack unavailable\n"
                    << "\nQ - Go back" << std::endl; //menu options
        std::cin >> op; std::cin.ignore(1000, '\n');
        //std::cout << std::endl;

        try{
            switch (op){
            case '1':
            {
                TravelPack temp_travelpack(std::cin);
                id = find_in_vector(packet_list, temp_travelpack.get_id());
                if (id != -1)
                    throw std::runtime_error("CAN'T HAVE TRAVEL PACKS WITH DUPLICATED IDS");
                id = find_in_vector(packet_list, temp_travelpack.get_id() * -1);
                if (id != -1)
                    throw std::runtime_error("CAN'T HAVE TRAVEL PACKS WITH DUPLICATED IDS");

                packet_list.push_back(temp_travelpack);
                brk();
                break;
            }
            case '2':
                id = select_id(packet_list);
                if (id == -1){
                    brk();
                    break;
                }

                packet_list.at(id) = TravelPack(std::cin);
                brk();
                break;
            case '3':
                id = select_id(packet_list);
                if (id == -1){
                    brk();
                    break;
                }

                packet_list.at(id).make_unavailable();
                brk();
                break;
            case 'q':
            case 'Q':
                break;
            default:
                std::cout << "THERE IS NO SUCH OPTION\n";
                brk();
                break;
            }
        }
        catch(const std::exception& e){
            std::cerr << e.what() << '\n';
            brk();
        }
        
    }while (op != 'q' && op != 'Q');
}


void read_info(bool &files_read, Agency &ragency){
    Agency agency;  //information is read into a temporary agency struct so if the reading process fails, the information
                    //read before-hand, is not changed

    try{
        clr_screen();
        std::cout << "What's the name/path of the agency's static information file (0 to go back)?" << std::endl;
        std::string agencyfile_path; //agency file path
        getline(std::cin, agencyfile_path);

        if (agencyfile_path == "0") //go back
            return;

        if (!file_exists(agencyfile_path)) //check for file existance
            throw std::invalid_argument("THE SPECIFIED AGENCY FILE DOES NOT EXIST");
        
        std::ifstream file_input(agencyfile_path);
        std::string clientsfile_path, packsfile_path, url, name, aux_string;
        unsigned int nif;

        getline(file_input, name);
        file_input >> nif; if(file_input.fail()) throw std::runtime_error("INCORRECT FISCAL NUMBER\n"); file_input.ignore();
        getline(file_input, url);
        Address address(file_input);
        getline(file_input, clientsfile_path);
        getline(file_input, packsfile_path);
        file_input.close();

        if (!file_exists(clientsfile_path))
            throw std::invalid_argument("THE SPECIFIED CLIENTS FILE DOES NOT EXIST");

        if (!file_exists(packsfile_path))
            throw std::invalid_argument("THE SPECIFIED PACKS FILE DOES NOT EXIST");

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
            
            i = find_in_vector(agency.packet_list, temp_travelpack.get_id());
            if (i != -1)
                throw std::runtime_error("CAN'T HAVE TRAVEL PACKS WITH DUPLICATED IDS");
            i = find_in_vector(agency.packet_list, temp_travelpack.get_id() * -1);
            if (i != -1)
                throw std::runtime_error("CAN'T HAVE TRAVEL PACKS WITH DUPLICATED IDS");
            
            
            agency.packet_list.push_back(temp_travelpack);
        }
        file_input.close();

        ragency = agency; //Reading operation was successful so the information is saved
        map_ref = &ragency.map_visits; //need to update pointer because the other object will be destroyed
        files_read = true;

        clr_screen();
        std::cout << "INFORMATION HAS BEEN READ SUCCESSFULLY\n";
        brk();
    }
    catch(const std::exception& e){
        map_ref = &ragency.map_visits; //update the refence to go back to the hold map in case of failure
        std::cerr << e.what() << '\n';
        std::cout << "INFORMATION HAS NOT BEEN SAVED/CHANGED\n";
        brk();
    }
    
    clr_screen();
}


void write_info(const Agency &agency,const std::string &agencyfile_path,const std::string &clientsfile_path, const std::string &packsfile_path)
{
    std::ofstream file_output;
    
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


void clients_print(std::vector<Client> const &client_list)
{
    char op; //option selected by user from the menu
    bool files_read = false;

    clr_screen();

    do{
        //TODO: Overload print functions so we have less options and vars
        std::cout   << "1 - Print information about a specific client\n"
                    << "2 - Print information about all clients\n"
                    << "\nQ - Exit" << std::endl; //menu options

        std::cin >> op; std::cin.ignore(1000, '\n');
        switch (op){
        case '1':
        {
            int index = select_client(client_list);
            clr_screen();
            if(index != -1) // if user hasn't opted out
                client_list[index].print(std::cout);
            brk();
            break;
        }
        case '2':
        {
            clr_screen();
            print_clients(client_list, std::cout);
            brk();
            break;
        }
        case 'q':
        case 'Q':
            break;
        default:
            std::cout << "THERE IS NO SUCH OPTION\n";
            brk();
            break;
        }

    }while (op != 'q' && op != 'Q');
}


void travelpacks_print(std::vector<TravelPack> const &packet_list){
    char op; //option selected by user from the menu
    bool files_read = false;

    clr_screen();

    do{
        //TODO: Overload print functions so we have less options and vars
        std::cout   << "1 - Print information about all travel packs\n"
                    << "2 - Print information about a specific destination\n"
                    << "3 - Print information about a specific timespan\n"
                    << "4 - Print information about a specific destination and timespan\n"
                    << "\nQ - Exit" << std::endl; //menu options

        std::cin >> op; std::cin.ignore(1000, '\n');
        try{
            switch (op){
            case '1':
            {
                clr_screen();
                print_travelpacks(packet_list, std::cout);
                brk();
                break;
            }
            case '2':
            {   
                std::string dest;
                std::cout << "Insert the specific destination: "; std::cin >> dest; std::cin.ignore();

                print_travelpacks(packet_list, std::cout, dest);
                brk();
                break;
            }
            case '3':
            {
                std::cout << "Start date (yyyy/mm/dd)? "; Date startdate(std::cin);
                std::cout << "End date (yyyy/mm/dd)? "; Date enddate(std::cin);

                print_travelpacks(packet_list, std::cout, startdate, enddate);
                brk();
                break;
            }
            case '4':
            {
                std::string dest;
                std::cout << "Insert the specific destination: "; std::cin >> dest; std::cin.ignore();
                std::cout << "Start date (yyyy/mm/dd)? "; Date startdate(std::cin);
                std::cout << "End date (yyyy/mm/dd)? "; Date enddate(std::cin);

                print_travelpacks(packet_list, std::cout, startdate, enddate, dest);
                brk();
                break;
            }
            case 'q':
            case 'Q':
                break;
            default:
                std::cout << "THERE IS NO SUCH OPTION\n";
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


void profit_made(std::vector<TravelPack> const &packet_list){
    float profit = 0;
    unsigned long long int packs = 0;

    for(size_t i = 0; i < packet_list.size(); i++){
        packs += packet_list.at(i).get_taken_seats();
        profit += (packet_list.at(i).get_price() * packet_list.at(i).get_taken_seats());
    }

    std::cout << "The agency sold " << packs << " travel packs and profited " << std::fixed << std::setprecision(2) << profit << std::endl;
}


void top_print(){
    size_t max_packs;
    std::cout << "What's the maximum of travel packs that should be shown? (0 to go back) ";
    while(true){
        std::cin >> max_packs;
        if(std::cin.fail()){
            std::cout << "Please insert a valid integer\n";
            std::cin.clear(); std::cin.ignore(1000, '\n');
            continue; // re-iterates loop
        }else
            break;
    }

    std::map<std::string, size_t>::iterator it; 
    for (it = map_ref->begin(); it != map_ref->end(); it++) 
        std::cout << (*it).first << '\t' << (*it).second << std::endl; 
    brk();
    //std::multiset<dests_visits, cmp_visits> set_visits;
    //std::multiset<dests_visits, cmp_visits>::iterator it2;
}


int main(){
    char op; //option selected by user from the menu
    bool files_read = false;

    Agency agency;
    clr_screen();
    std::cout << "Developed by:\tJoao de Jesus Costa - up201806560 (FEUP)\n\t\tJoao Lucas Silva Martins - up2018XXXXX (FEUP)\n" << std::endl;

    do{
        std::cout   << "1 - Read information files\n"
                    << "2 - Manage clients\n"
                    << "3 - Manage travel packs\n"
                    << "4 - Print client's information\n"
                    << "5 - Print travel packs' information\n"
                    << "6 - View sold travel packs\n"
                    << "7 - Number of sold travel packs and profit made\n"
                    << "8 - Print most visited locals\n"
                    << "9 - Suggested travel packs for each client\n"
                    << "S - Save read agency information to files\n"
                    << "\nQ - Exit\n" << std::endl; //menu options

        std::cin >> op; std::cin.ignore(1000, '\n');
        switch (op){
        case '1':
            read_info(files_read, agency);
            break;
        case '2':
            if (files_read){
                clients_manager(agency);
            }else
                no_read();
            brk();
            break;
        case '3':
            if (files_read){
                travelpack_manager(agency.packet_list);
            }else
                no_read();
            brk();
            break;
        case '4':
            if (files_read){
                clients_print(agency.client_list);
            }else
                no_read();
            brk();
            break;
        case '5':
            if (files_read){
                travelpacks_print(agency.packet_list);
            }else
                no_read();
            brk();
            break;
        case '6':
        {
            for(int i=0;i<agency.client_list.size();i++)
            {
                std::cout << agency.client_list.at(i).getName() << ":\n";
                for(int j=0;j<agency.client_list.at(i).getPackets().size();j++)
                {
                    int index = find_in_vector(agency.packet_list, agency.client_list.at(i).getPackets().at(j));
                    if(index == -1)
                        std::cout << "Packet with ID " << agency.client_list.at(i).getPackets().at(j) << " not recognized!\n";
                    else
                        agency.packet_list[index].print(std::cout);
                    std::cout << "::::::::::" << std::endl;
                }
            }
            brk();
            break;
        }
        case '7':
            if (files_read){
                profit_made(agency.packet_list);
            }else
                no_read();
            brk();
            break;
        case '8':
            if (files_read){
                top_print();
            }else
                no_read();
            brk();
            break;
        case '9':
            //TODO: sugested dests (dict)
            break;
        case 's':
        case 'S':
        {
            std::string agencyfile_path, clientsfile_path, packsfile_path;
            std::cout << "Insert 'Q' at anytime to go back\n";
            std::cout << "Agency's information file name? "; std::cin >> agencyfile_path;
            if(agencyfile_path == "q" || agencyfile_path == "Q") break;

            std::cout << "Clients' information file name? "; std::cin >> clientsfile_path;
            if(clientsfile_path == "0") break;
            if(agencyfile_path == clientsfile_path)
                throw std::invalid_argument("THE FILES FOR THE AGENCY'S AND THE CLIENTS' INFORMATION CAN'T HAVE THE SAME NAME");

            std::cout << "Travel packs' information file name? "; std::cin >> packsfile_path;
            if(packsfile_path == "0") break;
            if(packsfile_path == agencyfile_path)
                throw std::invalid_argument("THE FILES FOR THE AGENCY'S AND THE TRAVEL PACKS' INFORMATION CAN'T HAVE THE SAME NAME");
            if(packsfile_path == clientsfile_path)
                throw std::invalid_argument("THE FILES FOR THE CLIENTS' AND THE TRAVEL PACKS' INFORMATION CAN'T HAVE THE SAME NAME");

            write_info(agency, agencyfile_path, clientsfile_path, packsfile_path);
            break;
        }
        case 'q':
        case 'Q':
            break;
        default:
            std::cout << "THERE IS NO SUCH OPTION\n";
            brk();
            break;
        }

    }while (op != 'q' && op != 'Q');

    clr_screen();
    return 0;
}
/*
    TODO
    -Ler e guardar a informação da agência, dos clientes e dos pacotes turísticos armazenada em ficheiros.

    ---Gerir os clientes e pacotes turísticos: criar, alterar e remover um cliente; criar, alterar ou colocar como
    indisponível um pacote turístico (nota: os pacotes turísticos nunca são efetivamente removidos.

    ---Gerar e visualizar de modo formatado a informação de um cliente especificado.

    ---Gerar e visualizar de modo formatado a informação de todos os clientes da agência.

    ---Gerar e visualizar de modo formatado os pacotes turísticos disponíveis (todos, todos relativos a um destino
    específico, todos entre duas datas, todos os relativos a um destino específico e entre duas datas).

    ---Gerar e visualizar de modo formatado os pacotes turísticos vendidos (a um cliente específico, a todos os clientes).

    ---Efetuar a compra de uma pacote turístico por um cliente.

    ---Calcular e visualizar o número e o valor total de pacotes vendidos.

    -Obter o nome dos N locais mais visitados (um pacote pode incluir visitas a vários locais), ordenados por ordem
    decrescente do número de visitas ( = número de pacotes vendidos que passam por esse local).

    -Gerar uma listagem de todos os clientes na qual se indica, para cada cliente, um dos pacotes em que seja
    visitado um dos N locais mais visitados (ver ponto 9) que ele ainda não visitou.
*/
