#ifndef __DATE_H_
#define __DATE_H_


class Date{
    public:
        Date();
        Date(istream &input_stream);
        void print(ostream &output_stream) const;
        //Getters
        short int get_year() const;
        short int get_month() const;
        short int get_day() const;
    private:
        bool is_leap();
        unsigned short int year;
        unsigned short int month;
        unsigned short int day;
};
Date::Date(){
    year = 0;
    month = 0;
    day = 0;
}
Date::Date(istream &input_stream)
{
    input_stream >> year; input_stream.ignore(1000, '/');
    input_stream >> month; input_stream.ignore(1000, '/');
    input_stream >> day; input_stream.ignore(1000, '\n');

    if(input_stream.fail()){
        input_stream.clear();
        throw invalid_argument("DATE IS NOT FORMATED CORRECTLY\n");
    }

    if((month < 1) || (month > 12)) //check if the inserted month exists
        throw domain_error("INSERT A MONTH BETWEEN 1 AND 12\n");
    
    if((day < 1) || (day > 31)) //check if the inserted day can exist
        throw domain_error("INSERT A DAY BETWEEN 1 AND 31\n");

    if(month == 2)
    {
        if (is_leap() && (day > 29)) //In case of leap year february, check if the day number is possible
            throw domain_error("INSERT A VALID DAY FOR THAT MONTH (LEAP YEAR)\n");
        else if (day > 28) //In case of non-leap year february, check if the day number is possible
            throw domain_error("INSERT A VALID DAY FOR THAT MONTH (LEAP YEAR)\n");   
    }
    else if(!(month == 1 ||month == 3 ||month == 5 ||month == 7 ||month == 8 ||month == 10 ||month == 12) && (day > 30)){ //In case of 31 day month, check if the day number is possible
        Date data(cin);
        throw domain_error("INSERT A VALID DAY FOR THAT MONTH\n");
    }
}


void Date::print(ostream &output_stream) const
{
    //output the inserted date to an ostream in the corrected string format
    output_stream   << year << '/'
                    << month << '/'
                    << day << endl;
}


bool Date::is_leap()
{
    //Check if the inserted year is a leap year
    if(((year % 4) == 0) && ((year % 100) != 0))
        return true;
    else
        if((year % 400) == 0) 
            return true;

    return false;
}


//Getters
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


//Operator overload
bool operator<(const Date &date1, const Date &date2)
{
    //compare dates to see which came first. The "greater" date comes after the other date
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
    //See if two dates are occur at the same time
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
bool operator>=(const Date &date1, const Date &date2)
{
    return !(date1 < date2);
}
bool operator<=(const Date &date1, const Date &date2)
{
    return !(date1 > date2);
}

#endif
