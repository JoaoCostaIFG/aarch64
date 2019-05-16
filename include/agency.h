#ifndef __AGENCY_H_
#define __AGENCY_H_

/*
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
*/

typedef pair<size_t, string> dests_visits;

struct cmp_visits{ //Struct as cmp function because operator() is fast and we don't run nto more toubles with lambdas and/or pointers than necessary
    bool operator() (const dests_visits &a, const dests_visits &b) const
    {return a.first > b.first;}
};

typedef struct
{
    string name;
    unsigned int nif;
    Address address;
    string url;
    vector<TravelPack> packet_list;
    vector<Client> client_list;
    map<string, map_vistis_id> map_visits;
} Agency;


bool client_exists(vector<Client> const client_list, string const name);
    /* Returns false if there is already a client in client_list whose name is the same as name. Returns true otherwise*/
bool client_exists(vector<Client> const client_list, string const name, unsigned int const nif);
    /* Returns false if there is already a client in client_list whose name is the same as name and whose nif is the same as nif
    . Returns true otherwise*/
void new_client(vector<Client> &client_list);
    /* Adds a new client to client_list. Checks for any bad info or duplicate clients.*/
void modify_client(vector<Client> const  &client_list, int index);
    /* Changes client from client_list[index]. Checks for any bad info and for duplicate clients.*/
void print_clients(vector<Client> const &client_list, ostream &output_stream);
    /* Exports each client from client_list into output_stream.*/


//Vector searching functions
template <class Temp>
int find_in_vector(vector<Temp> const &vec, Temp const &t)
{
    for(int i=0;i<vec.size();i++)
        if(t == vec[i])
            return i;
    return -1;
}
int find_in_vector(vector<TravelPack> const &vec, const int &id)
{
    for(int i=0;i<vec.size();i++)
        if(abs(vec[i].get_id()) == abs(id))
            return i;
    return -1;
}
int find_in_vector(vector<Client> const &vec, const string &name)
{
    for(int i=0;i<vec.size();i++)
        if(vec[i].getName() == name)
            return i;
    return -1;
}


//Client vector search functions
bool client_exists(vector<Client> const client_list, unsigned int const nif, unsigned const int agency_nif, const int index=-1)
/* Returns 1 if any client in client list has a nif equal to @param: nif. Returns 0 otherwise.
If an index is given the client with that corresponding index in the client's vector will be ignored in the comparison.*/
{
    if(agency_nif == nif)
        return 0;
    for(int i=0;i<client_list.size();i++)
        if((nif == client_list[i].getNif()) && (i != index))  // Check if nif already is taken by a client in a list except the client susceptible to change
            return 1;
    return 0;
}


void modify_client(vector<Client> &client_list, int index, unsigned const int agency_nif)
{
    Client new_client(cin);  // any kind of bad input exception will be thrown here
    if(client_exists(client_list, new_client.getNif(), agency_nif, index))
        throw runtime_error("Client already exists in the agency!!\n");
    client_list[index] = new_client;  // replaces client
}


void new_client(vector<Client> &client_list, unsigned const int agency_nif)
{
    Client new_client(cin);  // any kind of bad input exception will be thrown here
    if(client_exists(client_list, new_client.getNif(), agency_nif))
        throw runtime_error("Client already exists in the agency!!\n");
    client_list.push_back(new_client);
}


void print_clients(vector<Client> const &client_list, ostream &output_stream)
{
    int n = client_list.size();
    for(int i=0;i<n-1;i++)
    {
        client_list[i].print(output_stream);
        output_stream << "::::::::::\n";
    }
    client_list[n-1].print(output_stream);
}


//Travel pack overloaded printing functions
void print_travelpacks(vector<TravelPack> const &packet_list, ostream &output_stream, bool flag){
    //print all the travel packs info
    bool found = false;
    unsigned long int  i;
    for(i = 0; i < packet_list.size(); i++){
        if (flag || packet_list.at(i).is_available()){
            found = true;
            packet_list.at(i).print(output_stream);
            break;
        }
    }
    
    for(i++; i < packet_list.size(); i++){
        if (flag || packet_list.at(i).is_available()){
            output_stream << "::::::::::\n";
            packet_list.at(i).print(output_stream);
        }
    }

    if (!found)
        throw runtime_error("THE AGENCY DOESN'T HAVE ANY REGISTERED TRAVEL PACKS\n"); //redundancy
}
void print_travelpacks(vector<TravelPack> const &packet_list, ostream &output_stream, string &dest, bool flag){
    //print all the travel packs that list this specific destination
    bool found = false;
    unsigned long int i;

    for(i = 0; i < packet_list.size(); i++){
        if (flag || (packet_list.at(i).is_available() && packet_list.at(i).get_destination() == dest)){
            found = true;
            packet_list.at(i).print(output_stream);
            break;
        }
    }

    for(i++; i < packet_list.size(); i++){
        if (flag || (packet_list.at(i).is_available() && packet_list.at(i).get_destination() == dest)){
            output_stream << "::::::::::\n";
            packet_list.at(i).print(output_stream);
        }
    }

    if (!found)
        throw runtime_error("THERE IS NO TRAVEL PACK WITH THAT LISTED DESTINATION\n");
}
void print_travelpacks(vector<TravelPack> const &packet_list, ostream &output_stream, Date &startdate, Date &enddate, bool flag){
    //print all the travel packs that are within this time span
    bool found = false;
    unsigned long int i;

    for(i = 0; i < packet_list.size(); i++){
        if (flag || (packet_list.at(i).is_available() && packet_list.at(i).get_start_date() >= startdate && packet_list.at(i).get_end_date() <= enddate)){
            found = true;
            packet_list.at(i).print(output_stream);
            break;
        }
    }

    for(i++; i < packet_list.size(); i++){
        if (flag || (packet_list.at(i).is_available() && packet_list.at(i).get_start_date() >= startdate && packet_list.at(i).get_end_date() <= enddate)){
            output_stream << "::::::::::\n";
            packet_list.at(i).print(output_stream);
        }
    }

    if (!found)
        throw runtime_error("THERE IS NO TRAVEL PACK WITHIN THAT TIMESPAN\n");
}
void print_travelpacks(vector<TravelPack> const &packet_list, ostream &output_stream, Date &startdate, Date &enddate, string &dest, bool flag){
    //print all the travel packs that are within this time span and have the specified destination listed
    bool found = false;
    unsigned long int i;

    for(i = 0; i < packet_list.size(); i++){
        if (flag || (packet_list.at(i).is_available() && packet_list.at(i).get_start_date() >= startdate && packet_list.at(i).get_end_date() <= enddate && packet_list.at(i).get_destination() == dest)){
            found = true;
            packet_list.at(i).print(output_stream);
            break;
        }
    }

    for(i++; i < packet_list.size(); i++){
        if (flag || (packet_list.at(i).is_available() && packet_list.at(i).get_start_date() >= startdate && packet_list.at(i).get_end_date() <= enddate && packet_list.at(i).get_destination() == dest)){
            output_stream << "::::::::::\n";
            packet_list.at(i).print(output_stream);
        }
    }

    if (!found)
        throw runtime_error("THERE IS NO TRAVEL PACK WITHIN THAT TIMESPAN AND WITH THAT LISTED DESTINATION\n");
}
#endif