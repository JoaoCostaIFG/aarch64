#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <sys/stat.h>

#define clr_screen() std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"; //clear screen
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

    while((!sucess)&(index_of_packet != -2000))
    {
        std::cout << "Insert the Id packet.\nType -2000 to exit\n";
        std::cin >> index_of_packet;
        if(std::cin.fail())
        {
            std::cout << "Please insert a valid integer\n";
            std::cin.clear(); std::cin.ignore(1000, '\n');
            continue; // re-iterates loop
        }

        id_in_vector = find_in_vector(packet_list, index_of_packet);

        if(id_in_vector != -1) // if found, sucess!
            sucess = true;
        else
        {
            // sucess = false; not needed because sucess if by default set to false
             std::cout << "There isn't any packet that has the given id. Please try again.\n";
        } 
    }

    return(id_in_vector);
    
}

void clients_manager(Agency &agency)
{
    int op, id; //option selected by user from the menu
    clr_screen();
    do{
        std::cout   << "1 - Create new client\n"
                    << "2 - Change existing client\n"
                    << "3 - Delete existing client\n"
                    << "4 - Make a purchase by an existing client\n"
                    << "0 - Go back" << std::endl; //menu options
        std::cout << "\n\nPlease Select an option? ";
        std::cin >> op; std::cin.ignore(1000, '\n');
        clr_screen();


        switch (op){
        // TODO: INSERT TRY CATCH HERE
        case 1:
        {
            new_client(agency.client_list);
            brk();
            break;
        }
        case 2:
        {
            int index = select_client(agency.client_list);
            if(index != -1) // if user hasn't opted out from selecting a client name
                modify_client(agency.client_list, index);
            brk();
            break;
        }
        case 3:
        {
            int index = select_client(agency.client_list);
            if(index != -1) // if user hasn't opted out from selecting a client name
                agency.client_list.erase(agency.client_list.begin() + index);
            brk();
            break;
        }
        case 4:
        {
            int client_index = select_client(agency.client_list);
            if(client_index != -1) // if user hasn't opted out from selecting a client name
            {
                int packet_index = select_id(agency.packet_list);
                if(packet_index != -1)
                    agency.client_list[client_index].buyPacket(agency.packet_list, packet_index);
            }
            brk();
            break;
        }
        case 0:
            break;
        default:
            std::cout << "THERE IS NO SUCH OPTION\n";
            brk();
            break;
        }
    }while (op != 0);
}


void travelpack_manager(){
    int op, id; //option selected by user from the menu
    clr_screen();
    std::cout   << "1 - Create new travel pack\n"
                << "2 - Change travel pack\n"
                << "3 - Make travel pack unavailable\n"
                << "0 - Go back" << std::endl; //menu options

    do{
        std::cin >> op; std::cin.ignore(1000, '\n');
        std::cout << "Travel pack id? ";
        std::cin >> id; std::cin.ignore(1000, '\n');
        //std::cout << std::endl;

        //WE NEED TO REFERENCE THE TRAVELPACK THROUGH AN ARRAY
        switch (op){
        case 1:
            //TODO: Create travel pack here (constructor e append)
            break;
        case 2:
            //TODO: Change travel pack info (constructor??)
            break;
        case 3:
            //TODO: Make travel pack unavailable ("travelpack".make_unavailable())
            break;
        case 0:
            break;
        default:
            std::cout << "THERE IS NO SUCH OPTION\n";
            brk();
            break;
        }
    }while (op != 0);
    brk();
}


void read_info(bool &files_read, Agency &agency){
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
        file_input >> nif; if(file_input.fail()) throw("INCORRECT FISCAL NUMBER\n"); file_input.ignore();
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
            agency.client_list.push_back((Client(file_input)));
            file_input.ignore('\n'); file_input.ignore();
        }
        file_input.close();
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        brk();
    }

    files_read = true;
}

void clients_print(std::vector<Client> const &client_list)
{
    int op; //option selected by user from the menu
    bool files_read = false;

    Agency agency;
    clr_screen();
    std::cout << "Developed by:\tJoao de Jesus Costa - up201806560 (FEUP)\n\t\tJoao Lucas Silva Martins - up2018XXXXX (FEUP)\n" << std::endl;

    do{
        //TODO: Overload print functions so we have less options and vars
        std::cout   << "1 - Print information about a specific client\n"
                    << "2 - Print information about all clients\n"
                    << "0 - Exit" << std::endl; //menu options

        std::cin >> op; std::cin.ignore(1000, '\n');
        switch (op){
        case 1:
        {
            int index = select_client(client_list);
            clr_screen();
            if(index != -1) // if user hasn't opted out
                client_list[index].print(std::cout);
            brk();
            break;
        }
        case 2:
        {
            clr_screen();
            print_clients(client_list, std::cout);
            brk();
            break;
        }
        case 0:
            break;
        default:
            std::cout << "THERE IS NO SUCH OPTION\n";
            brk();
            break;
        }

    }while (op != 0);
}


int main(){
    int op; //option selected by user from the menu
    bool files_read = false;

    Agency agency;
    clr_screen();
    std::cout << "Developed by:\tJoao de Jesus Costa - up201806560 (FEUP)\n\t\tJoao Lucas Silva Martins - up2018XXXXX (FEUP)\n" << std::endl;

    do{
        //TODO: Overload print functions so we have less options and vars
        std::cout   << "1 - Read information files\n"
                    << "2 - Manage clients\n"
                    << "3 - Manage travel packs\n"
                    << "4 - Print client's information\n"
                    << "5 - Print travel packs' information\n"
                    << "6 - Buy a travel pack\n"
                    << "7 - Number of solve travel packs and profit made\n"
                    << "8 - Print most visited locals\n"
                    << "9 - Suggested travel packs for each client\n"
                    << "0 - Exit" << std::endl; //menu options

        std::cin >> op; std::cin.ignore(1000, '\n');
        switch (op){
        case 1:
            read_info(files_read, agency);
            break;
        case 2:
            if (files_read){
                clients_manager(agency);
            }else
                std::cout << "FILES HAVEN'T BEEN SUCCESSFULLY READ YET\n";
            brk();
            break;
        case 3:
            if (files_read){
                travelpack_manager();
            }else
                std::cout << "FILES HAVEN'T BEEN SUCCESSFULLY READ YET\n";
            brk();
            break;
        case 4:
            if (files_read){
                clients_print(agency.client_list);
            }else
                std::cout << "FILES HAVEN'T BEEN SUCCESSFULLY READ YET\n";
            brk();
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 0:
            break;
        default:
            std::cout << "THERE IS NO SUCH OPTION\n";
            brk();
            break;
        }

    }while (op != 0);

    return 0;
}
/*
    TODO
    -Ler e guardar a informação da agência, dos clientes e dos pacotes turísticos armazenada em ficheiros.

    -Gerir os clientes e pacotes turísticos: criar, alterar e remover um cliente; criar, alterar ou colocar como
    indisponível um pacote turístico (nota: os pacotes turísticos nunca são efetivamente removidos.

    -Gerar e visualizar de modo formatado a informação de um cliente especificado.

    -Gerar e visualizar de modo formatado a informação de todos os clientes da agência.

    -Gerar e visualizar de modo formatado os pacotes turísticos disponíveis (todos, todos relativos a um destino
    específico, todos entre duas datas, todos os relativos a um destino específico e entre duas datas).

    -Gerar e visualizar de modo formatado os pacotes turísticos vendidos (a um cliente específico, a todos os clientes).

    -Efetuar a compra de uma pacote turístico por um cliente.

    -Calcular e visualizar o número e o valor total de pacotes vendidos.

    -Obter o nome dos N locais mais visitados (um pacote pode incluir visitas a vários locais), ordenados por ordem
    decrescente do número de visitas ( = número de pacotes vendidos que passam por esse local).

    -Gerar uma listagem de todos os clientes na qual se indica, para cada cliente, um dos pacotes em que seja
    visitado um dos N locais mais visitados (ver ponto 9) que ele ainda não visitou.
*/
