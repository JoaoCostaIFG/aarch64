#ifndef __AGENCY_H_
#define __AGENCY_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <sys/stat.h>

#define brk() do { std::cout << "Press the 'enter' key to continue.." << '\n'; getchar(); } while (0); //break function used for waiting for the user
#define clr_screen() std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"; //clear screen

std::string str_trim(const std::string& str){
    /*
        Trims a string of whitespaces in the beggining and end;
        Takes a string to trim as an argument;
        Returns the trimmed string;
    */
    return (str.substr(str.find_first_not_of(" "), str.find_last_not_of(" ") - str.find_first_not_of(" ") + 1));
}

#include "date.h"
#include "address.h"
#include "travelpack.h"
#include "client.h"

typedef struct
{
    std::string name;
    unsigned int nif;
    Address address;
    std::string url;
    std::vector<TravelPack> packet_list;
    std::vector<Client> client_list;
} Agency;

bool client_exists(std::vector<Client> const client_list, std::string const name);
    /* Returns false if there is already a client in client_list whose name is the same as name. Returns true otherwise*/
bool client_exists(std::vector<Client> const client_list, std::string const name, unsigned int const nif);
    /* Returns false if there is already a client in client_list whose name is the same as name and whose nif is the same as nif
    . Returns true otherwise*/
void modify_client(std::vector<Client> client_list, Client client);
    /* Changes client from client_list. Checks for any bad info and for duplicate clients.*/

bool client_exists(std::vector<Client> const client_list, std::string const name)
{
    for(int i=0;i<client_list.size();i++)
        if(name == client_list[i].getName())
            return 1;
    return 0;
}
bool client_exists(std::vector<Client> const client_list, std::string const name, unsigned int const nif)
{
    for(int i=0;i<client_list.size();i++)
        if(name == client_list[i].getName() && nif == client_list[i].getNif())
            return 1;
    return 0;
}


void modify_client(std::vector<Client> client_list, Client client)
{
    Client new_client(std::cin);  // any kind of bad input exception will be thrown here
    if(client_exists(client_list, new_client.getName(), new_client.getNif())) //TODO: Check criteria!!
        throw("Client already exists in the agency!!\n");
    client = new_client;
}
#endif