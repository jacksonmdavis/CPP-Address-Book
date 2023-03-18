#include "DateType.hpp"
#include <iostream>
#include <sstream>

using namespace std;

static int daysInMonth[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

DateType::DateType()
{
    initialized = false;
    month = 0;
    day = 0;
    year = 0;
}

void DateType::Initialize(int newMonth, int newDay, int newYear)
{
    if (newYear < 1583 || newYear > 9999)
        throw InvalidDateException();
    else if (newMonth < 1 || newMonth > 12)
        throw InvalidDateException();
    else if (newDay < 1 || newDay > daysInMonth[newMonth] || 
            (newMonth == 2 && newDay == 29 && (newYear % 4 != 0 || 
            (newYear % 100 == 0 && newYear % 400 != 0))))
        throw InvalidDateException();
    else
    {
        initialized = true;
        month = newMonth;
        day = newDay;
        year = newYear;
    }
}

bool DateType::IsInitialized()
{
    return initialized;
}

int DateType::GetMonth() const
{
    return month;
}

int DateType::GetDay() const
{
    return day;
}

int DateType::GetYear() const
{
    return year;
}

void DateType::SetMonth(int newMonth)
{
    if (initialized = false)
        throw UnInitializedException();
    else
        try
        {
            DateType::Initialize(newMonth, day, year);
        }
        catch(const InvalidDateException)
        {
            throw;
        }
}


void DateType::SetDay(int newDay)
{
    if (initialized = false)
        throw UnInitializedException();
    else
        try
        {
            DateType::Initialize(month, newDay, year);
        }
        catch(InvalidDateException)
        {
            throw;
        }
        
        
}

void DateType::SetYear(int newYear)
{
    if (initialized = false)
        throw UnInitializedException();
    else
        try
        {
            DateType::Initialize(month, day, newYear);
        }
        catch(InvalidDateException)
        {
            throw;
        }
}

bool DateType::operator==(DateType otherDate)
{
    if (initialized == false || otherDate.initialized == false)
        return false;
    else
    {
        if (year == otherDate.year && month == otherDate.month && day == otherDate.day)
            return true;
        else
            return false;
    }
}

bool DateType::operator<(DateType otherDate)
{
    if (initialized == false || otherDate.initialized == false)
        return false;
    else 
    {
        if (year < otherDate.year)
            return true;
        else if (year == otherDate.year && month < otherDate.month)
            return true;
        else if (year == otherDate.year && month == otherDate.month && day == otherDate.day)
            return true;
        else
            return false;
    }
}

string DateType::DateString()
{
    if (initialized == false)
    {
        return "Unspecified";
    }
    else
    {
        ostringstream outputStream;
        outputStream << month << "/" << day << "/" << year;
        string outputString = outputStream.str();
        return outputString;
    }
}