#ifndef __DATE_H_
#define __DATE_H_

#include <iostream>
#include <string>
#include <sstream>

class Date{
    public:
        Date(std::istream &input_stream);
        void print(std::ostream &output_stream);
        short int compare(Date date);
    private:
        bool is_leap();
        unsigned short int year;
        unsigned short int month;
        unsigned short int day;
};


Date::Date(std::istream &input_stream)
{
    std::string temp_str;
    std::istringstream input_string;
    std::cout << "Start date (yyyy/mm/dd)? "; getline(input_stream, temp_str);
    input_string.str(temp_str);
    input_string >> year; input_string.ignore(1000, '/');
    input_string >> month; input_string.ignore(1000, '/');
    input_string >> day; input_string.ignore(1000, '\n');

    if(input_stream.fail())
        throw(std::string("DATE INFO WRITTEN INCORRECTLY\n"));

    if((month < 1) || (month > 12))
        throw(std::string("INSERT A MONTH BETWEEN 1 AND 12\n"));
    
    if((day < 1) || (day > 31))
        throw(std::string("INSERT A DAY BETWEEN 1 AND 31\n"));

    if(month == 2)
    {
        if (is_leap() && (day > 29))
            throw(std::string("INSERT A VALID DAY FOR THAT MONTH (LEAP YEAR)\n"));
        else if (day > 28)
            throw(std::string("INSERT A VALID DAY FOR THAT MONTH (LEAP YEAR)\n"));   
    }
    else if(!(month == 1 ||month == 3 ||month == 5 ||month == 7 ||month == 8 ||month == 10 ||month == 12) && (day > 30))
    {Date data(std::cin);
        throw(std::string("INSERT A VALID DAY FOR THAT MONTH (LESS THAT 30)\n"));
    }
}


void Date::print(std::ostream &output_stream)
{
    output_stream << "Year: " << year;
    output_stream << "\nMonth: " << month;
    output_stream << "\nDay: " << day << std::endl;
}


bool Date::is_leap()
{
    if(((year % 4) == 0) && ((year % 100) != 0))
        return true;
    else
        if((year % 400) == 0) 
            return true;

    return false;
}


short int Date::compare(Date date)
{
    if(year == date.year && month == date.month && day == date.day)
        return 0;

    if(year < date.year)
        return -1;
    else
    {
        if(year == date.year)
        {
            if(month < date.month)
                return -1;
            else
            {
                if((month == date.month) && (day < date.day))
                    return -1;
            }
        }
    }

    return 1;

}

/*
int main()
{
    try
    {
        Date data1(std::cin), data2(std::cin);
        std::cout << data1.compare(data2);
    }
    catch(std::string e)
    {
        std::cout << e << '\n';
    }

    return 0;
}
*/

#endif
