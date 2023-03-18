/*
This project implements an editable and searchable sorted "address book" of contacts. Project requirements included 
storing a birthday and "anniversary" for each contact, as well as the ability to print birthay/anniversary "cards" 
for all appropriate contacts on a particular date.  Despite the name, actual addresses are not included.  

Implementation was done via circular doubly-linked list, allowing for the option to browse the full list of contacts 
and edit individual contacts without prior knowledge of what names to search for.
*/

#include <iostream>
#include <fstream>
#include <limits>
#include <ctime>

#include "SortedList.hpp"
#include "DateType.hpp"
#include "ContactType.hpp"

using namespace std;

const string TEST_INFILE = "finaltestinput.txt";
const string TEST_OUTFILE = "finaltestoutput.txt";
const string ADDRESS_BOOK_FILE = "addressbook.txt";

const int ERROR = 0, ADD_CONTACT = 1, DELETE_CONTACT = 2, SEARCH_CONTACT = 3, 
    BROWSE_LIST = 4, GENERATE_BIRTHDAYS = 5, GENERATE_ANNIVERSARIES = 6, QUIT = 7;

//In retrospect, I should have included most of these functions in a separate file,
//or even better in an AddressBook class.
void runProgram(istream& input, ostream& output);
void loadContactList(SortedListType<ContactType>& contactList);
void saveContactList(SortedListType<ContactType>& contactList);
int getMenuSelection(istream& input);
int addContact(istream& input, SortedListType<ContactType>& contactList);
void deleteContact(istream& input, SortedListType<ContactType>& contactList);
void searchContact(istream& input, SortedListType<ContactType>& contactList);
void browseContactList(istream& input, SortedListType<ContactType>& contactList);
void generateTodayBirthdays(istream& input, SortedListType<ContactType>& contactList);
void generateTodayAnniversaries(istream& input, SortedListType<ContactType>& contactList);
void printBirthdayCard(ContactType& contact);
void printAnniversaryCard(ContactType& contact);



int main()
{
    bool programTest = false;
    cout << "Enter '1' for program test, '0' for manual control." << endl;
    cin >> programTest;

    if (programTest == true)
    {
        ifstream inFile;
        ofstream outFile;
        inFile.open(TEST_INFILE);
        outFile.open(TEST_OUTFILE);
        if (!inFile)
        {
            cerr << "ERROR, test file '" << TEST_INFILE << "' not found. Exiting test." << endl;
            return 1;
        }
        streambuf *coutbuf = cout.rdbuf();
        cout.rdbuf(outFile.rdbuf());
        runProgram(inFile,cout);
        inFile.close();
        outFile.close();
        cout.rdbuf(coutbuf);
        cout << "Program test complete, all output saved to: " << TEST_OUTFILE << endl;
        cout << "addressbook.txt should now have 3 contacts." << endl;
    }
    else
        runProgram(cin, cout);
    cout << "Exiting program.  Thanks for coming!" << endl;
    return 0; 
}

void runProgram(istream& input, ostream& output)
{
    
    SortedListType<ContactType> contactList;
    loadContactList(contactList);

    int menuSelection = 0;
    while (menuSelection != QUIT)
        {
            menuSelection = getMenuSelection(input);
            switch (menuSelection)
            {
            case ADD_CONTACT:
                addContact(input, contactList);
                break;
            case DELETE_CONTACT:
                deleteContact(input, contactList);
                break;
            case SEARCH_CONTACT:
                searchContact(input, contactList);
                break;
            case BROWSE_LIST:
                browseContactList(input, contactList);
                break;
            case GENERATE_BIRTHDAYS:
                generateTodayBirthdays(input, contactList);
                break;
            case GENERATE_ANNIVERSARIES:
                generateTodayAnniversaries(input, contactList);
                break;
            }
        }
    
    
    saveContactList(contactList);

}

int getMenuSelection(istream& input)
{
    int menuSelection = 0;
    while (menuSelection < 1 || menuSelection > 7)
    {

        cout << "\n*****************************************" << endl;
        cout << "*               MAIN MENU               *" << endl;
        cout << "*****************************************" << endl;
        cout << "Please choose from the following options:" << endl;
        cout << "1. Add a new contact" << endl;
        cout << "2. Delete contact (by name)" << endl;
        cout << "3. Search and edit contact (by name)" << endl;
        cout << "4. Browse contact list" << endl;
        cout << "5. Generate today's birthday cards" << endl;
        cout << "6. Generate today's anniversary cards" << endl;
        cout << "7. Save and exit program" << endl;
        cout << "*****************************************" << endl;
        cout << "Enter your selection (1-7):";

        input >> menuSelection;

        if (menuSelection < 1 || menuSelection > 7)
        {
            cout << "Error, please enter integer between 1-7" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            menuSelection = 0;
        }
    }
        cout << "*****************************************" << endl;
    return menuSelection;
}

int addContact(istream& input, SortedListType<ContactType>& contactList)
{
    string newFirstName, newLastName;
    DateType newBirthday, newAnniversary;
    char hasBirthday, hasAnniversary;
    cout << "\nNote: This program does not support middle names!" << endl;
    cout << "Enter contact's first name: ";
    input >> newFirstName;
    cout << "Enter contact's last name: ";
    input >> newLastName;
    cout << "Would you like to enter a birthday (y/n)? ";
    input >> hasBirthday;
    if (hasBirthday == 'y' || hasBirthday == 'Y')
    {
        int newMonth, newDay, newYear;
        cout << "Enter birthday month (MM): ";
        input >> newMonth;
        cout << "Enter birthday day (DD): ";
        input >> newDay;
        cout << "Enter birthday year (YYYY): ";
        input >> newYear;
        try
        {
            newBirthday.Initialize(newMonth, newDay, newYear);
        }
        catch(...)
        {
            cout << "Error, date not valid.  Birthday left blank." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            newBirthday = DateType();
        }
    }
    cout << "Would you like to enter an anniversary (y/n)? ";
    input >> hasAnniversary;
    if (hasAnniversary == 'y' || hasAnniversary == 'Y')
    {
        int newMonth, newDay, newYear;
        cout << "Enter anniversary month (MM): ";
        input >> newMonth;
        cout << "Enter anniversary day (DD): ";
        input >> newDay;
        cout << "Enter anniversary year (YYYY): ";
        input >> newYear;
        try
        {
            newAnniversary.Initialize(newMonth, newDay, newYear);
        }
        catch(...)
        {
            cout << "\nError, date not valid.  Anniversary left blank." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            newAnniversary = DateType(); 
        }
        
    }
    ContactType newContact(newFirstName, newLastName, newBirthday, newAnniversary);
    try
    {
        contactList.PutItem(newContact);
        cout << "\nContact saved:" << endl;
        newContact.PrintContactString(cout);
    }
    catch(DuplicateItemException)
    {
        cout << "Error, contact with that name already exists.  Contact not saved." << endl;
        return 1;
    }
    
    return 0;    
}

void deleteContact(istream& input, SortedListType<ContactType>& contactList)
{
    string newFirstName, newLastName;
    cout << "Enter first name of contact to delete: ";
    input >> newFirstName;
    cout << "Enter last name of contact to delete: ";
    input >> newLastName;
    DateType newBirthday, newAnniversary;
    ContactType newContact(newFirstName, newLastName, newBirthday, newAnniversary);
    try
    {
        contactList.DeleteItem(newContact);
        cout << "\nContact deleted successfully." << endl;
    }
    catch(...)
    {
        cout << "Error, contact not found.  No Changes Made." << endl;
    }

}

void searchContact(istream& input, SortedListType<ContactType>& contactList)
{
    string newFirstName, newLastName;
    cout << "Enter first name of contact: ";
    input >> newFirstName;
    cout << "Enter last name of contact: ";
    input >> newLastName;
    DateType newBirthday, newAnniversary;
    ContactType newContact(newFirstName, newLastName, newBirthday, newAnniversary);

    try
    {
        newContact = contactList.SearchList(newContact);
    }
    catch(...)
    {
        cout << "Error, contact not found.  No Changes Made." << endl;
        return;
    }

    cout << "Contact found:" << endl;
    newContact.PrintContactString(cout);

    char willEdit;
    cout << "Edit contact (y/n)? ";
    input >> willEdit;
    if (willEdit == 'y' || willEdit == 'Y')
    {        
        contactList.DeleteItem(newContact);
        int editSuccess = addContact(input, contactList);
        if (editSuccess == 0)
        {
            cout << "Edit successful." << endl;
            return;
        }
        else
        {
            cout << "Edit unsuccessful, no changes made." << endl;
            contactList.PutItem(newContact);
            return;
        }
    }

}

void browseContactList(istream& input, SortedListType<ContactType>& contactList)
{
    int listLength = contactList.GetLength();
    int editSuccess = 1;
    if (listLength == 0)
    {
        cout << "List is currently empty.  Try adding some contacts first!" << endl;
        return;
    }

    int menuChoice = 1;
    ContactType currentContact = contactList.GetFirstItem();

    //This really should have been split into smaller functions.
    while(menuChoice == 1 || menuChoice == 2)
    {
        cout << "------------------------------------------" << endl;
        cout << "Browsing contacts, current item #:" << contactList.GetCurrentIndex() << "/" << listLength << endl;
        currentContact.PrintContactString(cout);
        cout << "------------------------------------------" << endl;
        cout << "1:Next contact" << endl;
        cout << "2:Previous contact" << endl;
        cout << "3:Delete contact" << endl;
        cout << "4:Edit contact" << endl;
        cout << "5:Generate birthday card" << endl;
        cout << "6:Generate anniversary card" << endl;
        cout << "7:Return to main menu" << endl;
        cout << "------------------------------------------" << endl;
        cout << "Enter selection (1-7): ";
        input >> menuChoice;


        switch (menuChoice)
        {
        case 1:
            currentContact = contactList.GetNextItem();
            break;
        case 2:
            currentContact = contactList.GetPreviousItem();
            break;
        case 3:
            contactList.DeleteItem(currentContact);
            cout << "Contact deleted.  Returning to main menu.";
            return;
        case 4: //edit
            contactList.DeleteItem(currentContact);
            editSuccess = addContact(input, contactList);
            if (editSuccess == 0)
            {
                cout << "Edit successful." << endl;
                return;
            }
            else
            {
                cout << "Edit unsuccessful, no changes made." << endl;
                contactList.PutItem(currentContact);
                return;
            }
            return;
        case 5: //birthday card
            printBirthdayCard(currentContact);
            return;
        case 6: //anniversary card
            printAnniversaryCard(currentContact);
            return;
        case 7:
            return;
        default:
            cout << "Error, input not understood.  Returning to main menu." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }
    }
}

void generateTodayBirthdays(istream& input, SortedListType<ContactType>& contactList)
{
    time_t now = time(0);
    tm *local_Time = localtime(&now);
    int currentMonth = (1 + local_Time ->tm_mon);
    int currentDay = local_Time ->tm_mday;
    char useToday;
    cout<< "Use today's date (MM/YY = " << currentMonth << "/" << currentDay << ") to generate (y/n)?";
    input >> useToday;
    if (useToday == 'n' || useToday == 'N')
    {
        cout << "Enter new month (MM): ";
        input >> currentMonth;
        cout << "Enter new day (DD): ";
        input >> currentDay;
    }

    cout << "Generating birthday cards..." << endl;
    ContactType currentContact = contactList.GetFirstItem();
    int listLength = contactList.GetLength();
    int generatedCount = 0;

    for (int i = 0; i < listLength; i++)
    {
        if (currentMonth == currentContact.GetBirthday().GetMonth() && 
            currentDay == currentContact.GetBirthday().GetDay())
            {
                printBirthdayCard(currentContact);
                generatedCount++;
            }
        currentContact = contactList.GetNextItem();
    }

    if (generatedCount == 0)
    {
        cout << "Looks like there are no birthdays today!" << endl;
    }
    cout << "Generating complete, returning to main menu." << endl;
}

void generateTodayAnniversaries(istream& input, SortedListType<ContactType>& contactList)
{
    time_t now = time(0);
    tm *local_Time = localtime(&now);
    int currentMonth = (1 + local_Time ->tm_mon);
    int currentDay = local_Time ->tm_mday;
    char useToday;
    cout << "Use today's date (MM/YY = " << currentMonth << "/" << currentDay << ") to generate (y/n)?";
    input >> useToday;
    if (useToday == 'n' || useToday == 'N')
    {
        cout << "Enter new month (MM): ";
        input >> currentMonth;
        cout << "Enter new day (DD): ";
        input >> currentDay;
    }

    cout << "Generating anniversary cards..." << endl;
    ContactType currentContact = contactList.GetFirstItem();
    int listLength = contactList.GetLength();
    int generatedCount = 0;

    for (int i = 0; i < listLength; i++)
    {
        if (currentMonth == currentContact.GetAnniversary().GetMonth() && 
            currentDay == currentContact.GetAnniversary().GetDay())
            {
                printAnniversaryCard(currentContact);
                generatedCount++;
            }
        currentContact = contactList.GetNextItem();
    }

    if (generatedCount == 0)
    {
        cout << "Looks like there are no anniversaries today!" << endl;
    }
    cout << "Generating complete, returning to main menu." << endl;
}

void printBirthdayCard(ContactType& contact)
{
    cout << "\nBirthday card for " << contact.GetFirstName() << " " << contact.GetLastName() << endl;
    cout << "Birthday date: " << contact.GetBirthdayString() << "\n" << endl;

    cout << "**************************************************" << endl;
    cout << "*              HAPPY BIRTHDAY!!!!!!              *" << endl;
    cout << "**************************************************" << endl << endl;
    cout << "Dear " << contact.GetFirstName() << " " << contact.GetLastName() << "-" << endl << endl;
    cout << "\tHappy birthday!!  I really hope you have" << endl;
    cout << "a great day, and a fantastic upcoming year!" << endl << endl;
    cout << "**************************************************\n" << endl;
}

void printAnniversaryCard(ContactType& contact)
{
    cout << "Anniversary card for " << contact.GetFirstName() << " " << contact.GetLastName() << endl;
    cout << "Anniversary date: " << contact.GetAnniversaryString() << "\n" << endl;

    cout << "\n**************************************************" << endl;
    cout << "*              HAPPY ANNIVERSARY!!!              *" << endl;
    cout << "**************************************************" << endl << endl;
    cout << "Dear " << contact.GetFirstName() << " " << contact.GetLastName() << "-" << endl << endl;
    cout << "\tHappy anniversary!!  I don't know what" << endl;
    cout << "it's the anniversary of, but I hope it's great!" << endl << endl;
    cout << "**************************************************\n" << endl;
}

void loadContactList(SortedListType<ContactType>& contactList)
{
    ifstream addressBook;
    addressBook.open(ADDRESS_BOOK_FILE);
        if (!addressBook)
            cout << "NOTE: '" << ADDRESS_BOOK_FILE <<"' NOT FOUND.  Program will create a new file on exit." << endl;
        else
        {
            cout << "Address Book found, loading to memory...";
            try
            {
                int fileLength;
                addressBook >> fileLength;

                for(int i = 0; i < fileLength; i++)
                    {
                        int newMonth, newDay, newYear;
                        string newFirstName, newLastName;
                        bool hasDate;
                        DateType newBirthday, newAnniversary;
                        addressBook >> newFirstName >> newLastName >> hasDate;
                        if (hasDate)
                        {
                            addressBook >> newMonth >> newDay >> newYear;
                            newBirthday.Initialize(newMonth,newDay,newYear);
                        }
                        addressBook >>hasDate;
                        if (hasDate)
                        {
                            addressBook >> newMonth >> newDay >> newYear;
                            newAnniversary.Initialize(newMonth,newDay,newYear);
                        }
                        ContactType newContact(newFirstName, newLastName, newBirthday, newAnniversary);
                        contactList.PutItem(newContact);

                    }
                cout << "done!" << endl;
            }
            catch(...)
            {
                std::cerr << "\n ERROR: '" << ADDRESS_BOOK_FILE << "' corrupted, new file will be created on exit." << endl;
                contactList = SortedListType<ContactType>();
            }        
        }
    addressBook.close();
}

void saveContactList(SortedListType<ContactType>& contactList)
{
    cout << "Saving to '" << ADDRESS_BOOK_FILE << "'...";
    ofstream addressBook;
    addressBook.open(ADDRESS_BOOK_FILE);
    int listLength = contactList.GetLength();
    addressBook << listLength << endl;
    if (listLength == 0)
    {
        addressBook.close();
        return;
    }

    ContactType newContact = contactList.GetFirstItem();

    for (int i = 0; i < listLength; i++)
    {
        string contactFirstName = newContact.GetFirstName();
        string contactLastName = newContact.GetLastName();
        DateType contactBirthday = newContact.GetBirthday();
        DateType contactAnniversary = newContact.GetAnniversary();
        addressBook << contactFirstName << " " << contactLastName << endl;
        bool hasDate = contactBirthday.IsInitialized();

        addressBook << hasDate << endl;
        if (hasDate)
            addressBook << contactBirthday.GetMonth() << " " << contactBirthday.GetDay() 
            << " " << contactBirthday.GetYear() << endl;

        hasDate = contactAnniversary.IsInitialized();

        addressBook << hasDate << endl;
        if (hasDate)
            addressBook << contactAnniversary.GetMonth() << " " << contactAnniversary.GetDay() 
            << " " << contactAnniversary.GetYear() << endl;        

        newContact = contactList.GetNextItem();
    }

    addressBook.close();
    cout << "done!" << endl;
    
}

