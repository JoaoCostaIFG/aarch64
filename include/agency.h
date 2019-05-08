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
    if(str == ""){
        return "";
    }
    return (str.substr(str.find_first_not_of(" "), str.find_last_not_of(" ") - str.find_first_not_of(" ") + 1));
}

#include "date.h"
#include "address.h"
#include "travelpack.h"

template <class Temp>
int find_in_vector(std::vector<Temp> const &vec, Temp const &t);
    /* Returns the index of element t in the vector. Returns -1 if t isn't found in vec.*/
int find_in_vector(std::vector<TravelPack> const &vec, const int &id);
    /* Returns the position of the travel pack which has the same identificator as id. Returns -1 if no travel packe with id is found.*/

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
void new_client(std::vector<Client> &client_list);
    /* Adds a new client to client_list. Checks for any bad info or duplicate clients.*/
void modify_client(std::vector<Client> const  &client_list, int index);
    /* Changes client from client_list[index]. Checks for any bad info and for duplicate clients.*/
void create_client(std::vector<Client>);
    /* Adds a new client to a client vector. Checks for bad input or for duplicate clients.*/
void print_clients(std::vector<Client> const &client_list, std::ostream &output_stream);
    /* Exports each client from client_list into output_stream.*/


template <class Temp>
int find_in_vector(std::vector<Temp> const &vec, Temp const &t)
{
    for(int i=0;i<vec.size();i++)
        if(t == vec[i])
            return i;
    return -1;
}
int find_in_vector(std::vector<TravelPack> const &vec, const int &id)
{
    for(int i=0;i<vec.size();i++)
        if(vec[i].get_id() == id)
            return i;
    return -1;
}
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


void modify_client(std::vector<Client> &client_list, int index)
{
    Client new_client(std::cin);  // any kind of bad input exception will be thrown here
    if(client_exists(client_list, new_client.getName(), new_client.getNif())) //TODO: Check criteria!!
        throw("Client already exists in the agency!!\n");
    client_list[index] = new_client;
}



void new_client(std::vector<Client> &client_list)
{
    Client new_client(std::cin);
    if(client_exists(client_list, new_client.getName(), new_client.getNif())) //TODO: Check criteria!!
        throw("Client already exists in the agency!!\n");
    client_list.push_back(new_client);
}

void print_clients(std::vector<Client> const &client_list, std::ostream &output_stream)
{
    int n = client_list.size();
    for(int i=0;i<n-1;i++)
    {
        client_list[i].print(output_stream);
        output_stream << "::::::::::\n";
    }
    client_list[n-1].print(output_stream);
}

#endif