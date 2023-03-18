#include "ContactType.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

ContactType::ContactType()
{
    
}

ContactType::ContactType(string newFirstName, string newLastName, DateType newBirthday, DateType newAnniversary)
{
    firstName = newFirstName;
    lastName = newLastName;
    birthday = newBirthday;
    anniversary = newAnniversary;
}

string ContactType::GetFirstName()
{
    return firstName;
}

string ContactType::GetLastName()
{
    return lastName;
}
DateType ContactType::GetBirthday()
{
    return birthday;
}
DateType ContactType::GetAnniversary()
{
    return anniversary;
}
string ContactType::GetBirthdayString()
{
    return birthday.DateString();
}
string ContactType::GetAnniversaryString()
{
    return anniversary.DateString();
}
void ContactType::SetFirstName(string newFirstName)
{
    firstName = newFirstName;
}
void ContactType::SetLastName(string newLastName)
{
    lastName = newLastName;
}
void ContactType::SetBirthday(DateType newBirthday)
{
    birthday = newBirthday;
}
void ContactType::SetAnniversary(DateType newAnniversary)
{
    anniversary = newAnniversary;
}

bool ContactType::operator<(ContactType otherContact)
{
    string selfLastName = lastName;
    string selfFirstName = firstName;
    string otherLastName = otherContact.GetLastName();
    string otherFirstName = otherContact.GetFirstName();
    transform(selfLastName.begin(), selfLastName.end(), selfLastName.begin(), ::toupper);
    transform(selfFirstName.begin(), selfFirstName.end(), selfFirstName.begin(), ::toupper);
    transform(otherLastName.begin(), otherLastName.end(), otherLastName.begin(), ::toupper);
    transform(otherFirstName.begin(), otherFirstName.end(), otherFirstName.begin(), ::toupper);
    if (selfLastName > otherLastName)
        return false;
    else if (selfLastName == otherLastName)
        return (selfFirstName < otherFirstName);
    else
        return true;


}
bool ContactType::operator==(ContactType otherContact)
{
    string selfLastName = lastName;
    string selfFirstName = firstName;
    string otherLastName = otherContact.GetLastName();
    string otherFirstName = otherContact.GetFirstName();
    transform(selfLastName.begin(), selfLastName.end(), selfLastName.begin(), ::toupper);
    transform(selfFirstName.begin(), selfFirstName.end(), selfFirstName.begin(), ::toupper);
    transform(otherLastName.begin(), otherLastName.end(), otherLastName.begin(), ::toupper);
    transform(otherFirstName.begin(), otherFirstName.end(), otherFirstName.begin(), ::toupper);
    if (selfLastName == otherLastName && selfFirstName == otherFirstName)
        return true;
    else
        return false;
}

void ContactType::PrintContactString(ostream& outputLocation)
{
    outputLocation<<"Name: " << lastName << ", " << firstName<< endl;
    outputLocation<<"Birthday: "<< birthday.DateString() << endl;
    outputLocation<<"Anniversary: " << anniversary.DateString() << endl;
}