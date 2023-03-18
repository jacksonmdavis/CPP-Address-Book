/*
This is a class for storing dates.  Most dates are interacted with in Month/Date/Year order (Because 'merica).
*/

#include <iostream>
#pragma once

using namespace std;

class InvalidDateException
{};

class UnInitializedException
{};

class DateType
{
public:
    DateType();
    void Initialize(int newMonth, int newDay, int newYear);
    int GetMonth() const;
    int GetDay() const;
    int GetYear() const;
    bool IsInitialized(); //Project required the possibility of an empty DateType.
    void SetMonth(int newMonth);
    void SetDay(int newDay);
    void SetYear(int newYear);
    bool operator==(DateType otherDate);
    bool operator<(DateType otherDate);
    string DateString(); //Prints in MM/DD/YYYY format, even though that is silly.

private:    
    int month;
    int day;
    int year;
    bool initialized;
};