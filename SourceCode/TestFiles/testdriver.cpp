//This is a test driver for the SortedList class (a circular, doubly linked list),
//the ContactType class, and the DateType class.

#include <fstream>
#include <iostream>

#include "../SortedList.hpp"
#include "../DateType.hpp"
#include "../ContactType.hpp"

using namespace std;

const string SORTED_TEST_INFILE = "TestFiles\\sortedtestinput.txt";
const string SORTED_TEST_OUTFILE = "TestFiles\\sortedtestoutput.txt";

void SortedUnitTest(istream& inFile, ostream& outFile);
void ContactTypeTest(istream& inFile, ostream& outFile);
void DateTypeTest(istream& inFile, ostream& outFile);

//The printList functions are at the top because I was having trouble
//forward-declaring a function template.  Sorry I know it's not very
//readable.

template<class T>
void printList(SortedListType<T>& list, ostream& outFile)
{
    
    int listLength = list.GetLength();
    T currentItem = list.GetFirstItem();
    int currentIndex = list.GetCurrentIndex();
    //cout << "Start printing" << endl;
    outFile << "[" << currentIndex << "]:" << currentItem << " ";
    for (int i = 0; i < listLength - 1; i++)
    {
        currentItem = list.GetNextItem();
        currentIndex = list.GetCurrentIndex();
        outFile << "[" << currentIndex << "]:" << currentItem << " ";
    }
    outFile << endl;
    return;
}

template<class T>
void printListReversed(SortedListType<T>& list, ostream& outFile)
{
    int listLength = list.GetLength();
    T currentItem = list.GetFirstItem();
    int currentIndex = list.GetCurrentIndex();
    //cout << "Start printing" << endl;
    for (int i = 0; i < listLength; i++)
    {
        currentItem = list.GetPreviousItem();
        currentIndex = list.GetCurrentIndex();
        outFile << "[" << currentIndex << "]:" << currentItem << " ";
    }
    outFile << endl;
    return;
}

/*
--------------------------------------
MAIN TESTS START HERE
--------------------------------------
*/

int main()
{
    ifstream inFile;
    ofstream outFile;
    inFile.open(SORTED_TEST_INFILE);
    outFile.open(SORTED_TEST_OUTFILE);
    if (!inFile)
        cout << "INPUT FILE ERROR" << endl;
    if (!outFile)
        cout << "OUTPUT FILE ERROR";
    cout << "Test driver called correctly." << endl;

    //Tests SortedList using input and output file
    SortedUnitTest(inFile, outFile);
    cout << "Sorted List unit test complete." << endl;

    //Tests DateType, does not use input file
    DateTypeTest(inFile, outFile);
    cout << "DateType unit test complete." << endl;

    //Tests ContactType
    ContactTypeTest(inFile, outFile);
    cout << "ContactType unit test complete." << endl;

    inFile.close();
    outFile.close();

    cout << "Exiting" << endl;

    return 0;
}

void SortedUnitTest(istream& inFile, ostream& outFile)
{

    SortedListType<float> myTestList;

    //PutItem Test
    float newItem;
    for (int i = 0; i<10 ; i++)
    {
        inFile >> newItem;
        myTestList.PutItem(newItem);
    }
    //printList tests GetFirstItem(), GetNextItem(), GetLength(), and GetCurrentIndex(),
    //and verifies PutItem(). printListReversed tests GetPreviousItem.
    printList(myTestList, outFile);
    printListReversed(myTestList, outFile);

    //SearchList Test
    float searchItem = 3.0;
    float result = myTestList.SearchList(searchItem);
    outFile << result << endl;
    try
    {
        myTestList.SearchList(11.0);
    }
    catch(ItemNotFoundException)
    {
        outFile << "Item not found exception, correct" << endl;
    }
    

    //DeleteItem Test
    myTestList.DeleteItem(3.0);
    myTestList.DeleteItem(5.3);
    printList(myTestList, outFile);
    myTestList.DeleteItem(1.0);
    myTestList.DeleteItem(10.0);
    printList(myTestList, outFile);
    try
    {
        myTestList.DeleteItem(3.0);
    }
    catch(ItemNotFoundException)
    {
        outFile << "Item not found exception, correct" << endl;
    }
    //cout << "List printed to outfile" << endl;

}

void DateTypeTest(istream& inFile, ostream& outFile)
{
    DateType firstDate, secondDate;
    //test uninitialized date
    outFile << firstDate.DateString() << endl; //"Unspecified"
    
    //Test Initialize and DateString
    firstDate.Initialize(1,1,2001);
    secondDate.Initialize(2,24,1985);
    outFile << firstDate.DateString() << "\n" << secondDate.DateString()<< endl;\

    //Test Set methods and exceptions
    firstDate.SetDay(29);
    outFile << firstDate.DateString() << endl;
    firstDate.SetYear(1900);
    outFile << firstDate.DateString() << endl;
    try
    {
        firstDate.SetMonth(2);
        outFile << firstDate.DateString() << endl;
    }
    catch(InvalidDateException)
    {
        outFile << "Error caught" << endl;
    }
    firstDate.SetYear(2000);
    firstDate.SetMonth(2);
    outFile << firstDate.DateString() << endl;

//Operator tests, expected "0 , 1 , 0 , 1"
    outFile << (firstDate < secondDate) << "\n" << (secondDate < firstDate) << endl;
    outFile << (firstDate == secondDate) << endl;
    firstDate.Initialize(2,24,1985);
    outFile << (firstDate == secondDate) << endl;    
}

void ContactTypeTest(istream& inFile, ostream& outFile)
{
    //Input details from file
    string newFirstName, newLastName;
    int newBirthdayMonth, newBirthdayDay, newBirthdayYear;
    int newAnniversaryMonth, newAnniversaryDay, newAnniversaryYear;
    inFile >> newFirstName >> newLastName >> newBirthdayMonth>> newBirthdayDay >> newBirthdayYear;
    inFile >> newAnniversaryMonth >> newAnniversaryDay >> newAnniversaryYear;
    
    //Initialize datetypes
    DateType newBirthday, newAnniversary;
    newBirthday.Initialize(newBirthdayMonth,newBirthdayDay,newBirthdayYear);
    newAnniversary.Initialize(newAnniversaryMonth,newAnniversaryDay,newAnniversaryYear);
    
    //Create contact with all details
    ContactType firstContact(newFirstName, newLastName, newBirthday, newAnniversary);

    //print contact to file
    firstContact.PrintContactString(outFile);

    //Input second contact name
    inFile >> newFirstName >> newLastName;
    
    //Empty dates
    DateType secondBirthday, secondAnniversary;

    //Create contact with all details
    ContactType secondContact(newFirstName, newLastName, secondBirthday, secondAnniversary);
    
    //Print contact to file
    secondContact.PrintContactString(outFile);

    //expected: 1
    outFile << (firstContact < secondContact) << endl;
    //expected: 0 0
    outFile << (firstContact == secondContact) << " " << (secondContact < firstContact) << endl;
    //expected: 1 0
    inFile >> newFirstName;
    secondContact.SetFirstName(newFirstName);
    outFile << (firstContact == secondContact) << " " << (firstContact < secondContact) << endl;
    
    secondContact.SetBirthday(newBirthday);
    secondContact.SetAnniversary(newAnniversary);
    secondContact.PrintContactString(outFile);
}

