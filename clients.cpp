#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "includes/address.h"
#include "includes/date.h"

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
        unsigned int getVATnumber() const;
        unsigned int short getFamilySize() const;
        Address getAddress() const;
        //std::vector<Packet> getPacketList() const;
        unsigned int getTotalPurchased() const;
        
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

    std::istringstream temp_stream;
    std::string temp_str;

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

    input_stream >> budget; input_stream.ignore(1000, '\n');
}
void Client::print(std::ostream &output_stream) const
{
    output_stream << "Name: " << name << "\nNIF: "  << nif << "\nNumber of family members: " << familySize;
    address.print(output_stream);
    output_stream << "Bought travel packs: ";
    int n(packets.size());
    for(int i=0;i<n-1;i++) output_stream << packets[i] << " ; ";
    output_stream << packets[n - 1] << std::endl;
}


int main()
{

    return 0;
}


//TODO: Add cout to constructors of address and date so that when calling those constructors with cin user knows what to type
/*Changelog:
    - Added const to print function in classes address and date
    - Added constructor for class client*/