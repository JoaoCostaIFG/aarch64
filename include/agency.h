#ifndef __AGENCY_H_
#define __AGENCY_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <sys/stat.h>

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
void new_client(std::vector<Client> &client_list);
    /* Adds a new client to client_list. Checks for any bad info or duplicate clients.*/
void modify_client(std::vector<Client> const  &client_list, int index);
    /* Changes client from client_list[index]. Checks for any bad info and for duplicate clients.*/
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
int find_in_vector(std::vector<Client> const &vec, const std::string &name)
{
    for(int i=0;i<vec.size();i++)
        if(vec[i].getName() == name)
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
        throw std::runtime_error("Client already exists in the agency!!\n");
    client_list[index] = new_client;
}


void new_client(std::vector<Client> &client_list)
{
    Client new_client(std::cin);
    if(client_exists(client_list, new_client.getName(), new_client.getNif())) //TODO: Check criteria!!
        throw std::runtime_error("Client already exists in the agency!!\n");
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


void print_travelpacks(std::vector<TravelPack> const &packet_list, std::ostream &output_stream){
    //print all the travel packs info
    packet_list.at(0).print(output_stream);
    for(int i = 1; i < packet_list.size(); i++){
        output_stream << "::::::::::\n";
        packet_list.at(i).print(output_stream);
    }
}
void print_travelpacks(std::vector<TravelPack> const &packet_list, std::ostream &output_stream, std::string &dest){
    //print all the travel packs that list this specific destination
    bool found = false;
    unsigned long int i;
    for(i = 0; i < packet_list.size(); i++){
        if (packet_list.at(i).get_destination() == dest){
            found = true;
            packet_list.at(i).print(output_stream);
        }
    }

    for(; i < packet_list.size(); i++){
        if (packet_list.at(i).get_destination() == dest){
            output_stream << "::::::::::\n";
            packet_list.at(i).print(output_stream);
        }
    }

    if (!found)
        throw std::runtime_error("There is no travel pack with that listed destination\n");
}
void print_travelpacks(std::vector<TravelPack> const &packet_list, std::ostream &output_stream, Date &startdate, Date &enddate){
    //print all the travel packs that are within this time span
    bool found = false;
    unsigned long int i;
    for(i = 0; i < packet_list.size(); i++){
        if (packet_list.at(i).get_start_date() >= startdate && packet_list.at(i).get_end_date() <= enddate){
            found = true;
            packet_list.at(i).print(output_stream);
        }
    }

    for(; i < packet_list.size(); i++){
        if (packet_list.at(i).get_start_date() >= startdate && packet_list.at(i).get_end_date() <= enddate){
            output_stream << "::::::::::\n";
            packet_list.at(i).print(output_stream);
        }
    }

    if (!found)
        throw std::runtime_error("There is no travel pack within that timespan\n");
}
void print_travelpacks(std::vector<TravelPack> const &packet_list, std::ostream &output_stream, Date &startdate, Date &enddate, std::string &dest){
    //print all the travel packs that are within this time span and have the specified destination listed
    bool found = false;
    unsigned long int i;
    for(i = 0; i < packet_list.size(); i++){
        if (packet_list.at(i).get_start_date() >= startdate && packet_list.at(i).get_end_date() <= enddate && packet_list.at(i).get_destination() == dest){
            found = true;
            packet_list.at(i).print(output_stream);
        }
    }

    for(; i < packet_list.size(); i++){
        if (packet_list.at(i).get_start_date() >= startdate && packet_list.at(i).get_end_date() <= enddate && packet_list.at(i).get_destination() == dest){
            output_stream << "::::::::::\n";
            packet_list.at(i).print(output_stream);
        }
    }

    if (!found)
        throw std::runtime_error("There is no travel pack within that timespan\n");
}
#endif