#ifndef __CLIENT_H_
#define __CLIENT_H_

#include <iostream>
#include <string>
#include <vector>

#include "address.h"
#include "date.h"
#include "travelpack.h"

class Client{
    private:
        std::string name;
        unsigned int nif;
        unsigned int short familySize;
        Address address;
        std::vector<int> packets;
        // std::vector<Packet> packets;  FIXME: fazer com int's ou com packets, como nos templates??
        unsigned int budget;

    public:
        Client(std::istream &input_stream);
        // GET methods
        std::string getName() const;
        unsigned int getNif() const;
        unsigned int short getFamilySize() const;
        Address getAddress() const;
        std::vector<int> getPackets() const;
        unsigned int getBudget() const;
        void buyPacket(std::vector<TravelPack> &packet_list, const int &id);
        /* Changes information about an existing client*/
        
        // SET methods
        // no need for set methods, just use the constructor instead
        // other methods
        void print(std::ostream &output_stream) const;

  // friend ostream& operator<<(ostream& out, const Client & client); FIXME: What dis do??
};

Client::Client(std::istream &input_stream)
{
    std::cout << "Name?\n"; getline(input_stream, name);
    std::cout << "NIF?\n"; input_stream >> nif; input_stream.ignore(1000, '\n');     // TODO: Check if Nif for duplicates
    std::cout << "Family size?\n"; input_stream >> familySize; input_stream.ignore(1000, '\n');
    address = Address(input_stream);

    std::cout << "Travel packs bought?(n1 ; n2 ; n3 ...)\n";
    std::istringstream temp_stream; std::string temp_str;
    getline(input_stream, temp_str); temp_stream.str(temp_str.append(" ;-;")); //read line to format into temporary string and sends it for formatting
    // read the client's travel packs bought information
    do
    {
        getline(temp_stream, temp_str, ';');
        if(temp_str == "" || temp_str == " ")
            break;

        int id;
        try
        {
            id = stoi(temp_str);
        }
        catch(const std::exception)
        {
            throw(std::string("THE ID OF A CLIENT'S PACKETS MUST BE AN INTEGER!\n"));
        }

        packets.push_back(id);
    } while(temp_stream.peek() != '-');

    std::cout << "Total money spent?\n"; input_stream >> budget; input_stream.ignore(1000, '\n');
}
void Client::print(std::ostream &output_stream) const
{
    output_stream << name << '\n' << nif << '\n' << familySize << '\n';
    address.print(output_stream);
    int n(packets.size());
    for(int i=0;i<n-1;i++) output_stream << packets[i] << " ; ";
    output_stream << packets[n - 1] << '\n';
    output_stream << budget << std::endl;
}

std::string Client::getName() const
{
    return name;
}
unsigned int Client::getNif() const
{
    return nif;
}
unsigned int short Client::getFamilySize() const
{
    return familySize;
}
Address Client::getAddress() const
{
    return address;
}
std::vector<int> Client::getPackets() const
{
    return packets;
}
unsigned int Client::getBudget() const
{
    return budget;
}
void Client::buyPacket(std::vector<TravelPack> &packet_list, const int &index)
{
    if(find_in_vector(packets, packet_list[index].get_id()) != -1)
        throw(std::string("That packet was already bought by") + name);
    packets.push_back(index);
    packet_list[index]++;
}

//TODO: Add cout to constructors of address and date so that when calling those constructors with cin user knows what to type
/*Changelog:
v1
    - Added const to print function in classes address and date
    - Added constructor for class client
v2  
    - Added default constructors for address and date
    - Made changes to address constructor to resolve problems when reading with cin
    - Added getter methods to clients
    - Added agency.h, the agency struct (Kinda temporary??) and some methods related to clients
    - Some changes were made to travelpack.h:
            - Some minor errors that prevented compilation
            - Make getters from dates return the class date and not a string
            - ++ operator function was fixed (removed const from params) because i rly wanted to compile
    - Added function to modify client and to check for client duplicates in agency.h
    TODO: Discuss criteria for a duplicate client. Does the name have to be the same, the nif, or both??
    
    v3
    - Added create and delete client functions to agency.h
    - Solved a few bugs by changing the modify client function in agency.h
    - Modified print from class clients to take into account output formating when writing to a file
    - Added a print client function, which works with both cout and file streams
    - Didn't change the packets vector in the client class from <int> to <TravelPack> because i don't think i'll use any of the TravelPack's
methods inside the client class. This might change though.
    - Added method for a client to buy a packet
    // TODO: Change packet vector in client class to a set mb??
    // NOT TODO: There's no need for a destructor since we won't allocate dynamic memory. Could be wrong about this though.
    */
#endif