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


int main(){
    TravelPack a;
    std::string b;
    std::cout << a.get_sold_seats() << "\n";
    ++a;
    std::cout << a.get_sold_seats() << "\n";
    /*
    std::vector<std::string> land_marks;
    std::string temp_str, destination;
    std::istringstream input_string, cino;
    cino.str("Douro Vinhateiro - Porto, Regua, Pinhao, Vila Real");
    getline(cino, destination, '-'); destination = str_trim(destination);
    getline(cino, temp_str); input_string.str(temp_str.append(" ,"));
    while(!input_string.fail()){ //not sure if it works
        getline(input_string, temp_str, ','); temp_str = str_trim(temp_str);
        land_marks.push_back(temp_str);
    }
    std::cout << destination << '\n' << land_marks[0] << '\n' << land_marks[1] << '\n' << land_marks[2] << '\n' << land_marks[3] << '\n';
    */
    /*
    Date date1, date2;
    std::cout << (date1 < date2);
    */
    return 0;
}
