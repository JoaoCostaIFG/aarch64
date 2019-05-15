#ifndef __FUNCTIONS_H_
#define __FUNCTIONS_H_

/*
#include <iostream>
#include <string>
#include <vector>
*/

string str_trim(const string& str){
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

#include "travelpack.h"

template <class Temp>
int find_in_vector(vector<Temp> const &vec, Temp const &t);
    /* Returns the index of element t in the vector. Returns -1 if t isn't found in vec.*/
int find_in_vector(vector<TravelPack> const &vec, const int &id);
    /* Returns the position of the travel pack which has the same identificator as id. Returns -1 if no travel packe with id is found.*/

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
        if(vec[i].get_id() == id)
            return i;
    return -1;
}

#endif