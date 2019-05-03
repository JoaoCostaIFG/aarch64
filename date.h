#include <iostream>
#include <sstream>
class Date{
    public:
        Date(std::istream &input_stream);
        void print(std::ostream &output_stream);
        short int get_year() const;
        short int get_month() const;
        short int get_day() const;
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
        throw(std::string("INSERT AN INTEGER\n"));

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
short int Date::get_year() const
{
    return year;
}
short int Date::get_month() const
{
    return month;
}
short int Date::get_day() const
{
    return day;
}
bool operator<(const Date &date1, const Date &date2)
{
    const int year1 = date1.get_year(), year2 = date2.get_year();
    const int month1 = date1.get_month(), month2 = date2.get_month();
    const int day1 = date1.get_day(), day2 = date2.get_day();
    if(year1 < year2)
        return 1;
    else
    {
        if(year1 == year2)
        {
            if(month1 < month2)
                return 1;
            else
            {
                if((month1 == month2) && (day1 < day2))
                    return 1;
            }
        }
    }
    
    return 0;
}
bool operator==(const Date &date1, const Date &date2)
{
    if((date1.get_year() == date2.get_year()) && (date1.get_month() == date2.get_month()) && (date1.get_day() == date2.get_day()))
        return 1;
    return 0;
}
bool operator>(const Date &date1, const Date &date2)
{
    if(date1 == date2)
        return 0;
    return (!(date1 < date2));
}