/*
This is a circular doubly-linked list implementation of a sorted list ADT.
*/

#include <iostream>
#pragma once

using namespace std;


//The NodeType used in the implementation of the linked list.
template<class T>
struct NodeType
{
    T info;
    NodeType<T>* next;
    NodeType<T>* back;
};

// Error thrown if a duplicated item is added to the list
class DuplicateItemException
{};

// Error thrown if item is searched for in the list but not found
class ItemNotFoundException
{};

// Error thrown if actions are attempted on an empty list
class EmptyListException
{};


template<class T>
class SortedListType
{
public:
    SortedListType();
    ~SortedListType();
    T SearchList(T item); //Precondition: item in list.  Will throw ItemNotFoundException otherwise.
    void PutItem(T item); //Precondition: item not already in list.  Will throw DuplicateItemException otherwise.
    void DeleteItem(T item); //Precondition: item in list.  Will throw ItemNotFoundException otherwise.
    int GetLength() const;
    T GetFirstItem(); //Precondition: list is not empty. Will throw EmptyListException otherwise.
    T GetNextItem(); //Precondition: GetFirstItem has been called at least once.  Undefined behavior otherwise.
    T GetPreviousItem(); //Precondition: GetFirstItem has been called at least once.  Undefined behavior otherwise.
    int GetCurrentIndex(); //Gets index number of current item in iteration. Precondition: GetFirstItem has been called at least once.

private:    
    NodeType<T>* FindItem(T item, bool& found);
    int length;
    NodeType<T>* listData; 
    NodeType<T>* currentItem;
    int currentItemIndex; //Keeps track of number/total records to enable browsing.
};

//class ContactType;
//SortedListType<ContactType> adressBook;
