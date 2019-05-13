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
//#include "include/client.h"
//#include "include/agency.h"


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


void read_info(bool &files_read){
    try{
        clr_screen();
        std::cout << "What's the name/path of the agency's static information file (0 to go back)?" << std::endl;
        std::string agencyfile_path; //agency file path
        getline(std::cin, agencyfile_path);

        if (agencyfile_path == "0") //go back
            return;

        if (!file_exists(agencyfile_path)) //check for file existance
            throw std::invalid_argument("THE SPECIFIED FILE DOES NOT EXIST");
        
        //TODO: integrate agency.h here
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }

    files_read = true;
}


int main(){
    int op; //option selected by user from the menu
    bool files_read = false;

    //Agency agency;
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
            read_info(files_read);
            break;
        case 2:
            break;
        case 3:
            if (files_read){
                travelpack_manager();
            }else
                std::cout << "FILES HAVEN'T BEEN SUCCESSFULLY READ YET\n";
            brk();
            break;
        case 4:
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
