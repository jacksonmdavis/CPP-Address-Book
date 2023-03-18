/*
Class file for the ContactType class, which is an object that stores information about a contact in an "address book".  Project requirements were
to store names, birthdays, and "anniversaries" for each contact, but no actual address.
*/

#include <iostream>
#include "DateType.hpp"
#pragma once

using namespace std;

class ContactType
{
public:
    ContactType();
    ContactType(string newFirstName, string newLastName, DateType newBirthday, DateType newAnniversary);
    string GetFirstName();
    string GetLastName();
    DateType GetBirthday();
    DateType GetAnniversary();
    string GetBirthdayString();
    string GetAnniversaryString();
    void SetFirstName(string newFirstName);
    void SetLastName(string newLastName);
    void SetBirthday(DateType newBirthday);
    void SetAnniversary(DateType newAnniversary);
    bool operator<(ContactType otherContact);
    bool operator==(ContactType otherContact);
    void PrintContactString(ostream& outputLocation);

private:
    string firstName;
    string lastName;
    DateType birthday;
    DateType anniversary;

};