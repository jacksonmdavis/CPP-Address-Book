#include "SortedList.hpp"
#include "ContactType.hpp"
#include <iostream>

using namespace std;

//Apparently I have to include these when using templates, otherwise
//I can't separate implementation and header files.  C++ is weird sometimes.
template class SortedListType<float>;
template class SortedListType<ContactType>;
template struct NodeType<ContactType>;

template<class T>
SortedListType<T>::SortedListType()
{
    length = 0;
    listData = nullptr;
    currentItem = nullptr;
    int currentItemIndex = 0;
}

template<class T>
SortedListType<T>::~SortedListType()
{
    if (listData == nullptr)
        return;
    NodeType<T>* tmpptr = listData->next;
    while (listData != tmpptr)
    {
        tmpptr = tmpptr->next;
        delete tmpptr->back;
    }
    delete listData;
}

template<class T>
NodeType<T>* SortedListType<T>::FindItem(T item, bool& found)
{
    found = false;
    if (listData == nullptr)
        return nullptr;
    
    NodeType<T>* location = listData->next;

    while (true)
    {
        if (location ->info == item)
        {
            found = true;
            return location;
        }

        else if (item < location->info)
            return location->back;

        else if (location == listData)
            return location->next;

        location = location ->next;
        //#DEBUG cout << "Finding " << item << endl;
    }
}

template<class T>
T SortedListType<T>::SearchList(T item)
{
    bool found;
    NodeType<T>* location = SortedListType::FindItem(item,found);
    if (found == false)
        throw ItemNotFoundException();
    else
        return location ->info;
}

template<class T>
void SortedListType<T>::PutItem(T item)
{
    NodeType<T>* itemNode = new NodeType<T>;
    itemNode->info = item;
    if (listData == nullptr)
    {
        listData = itemNode;
        listData->next = listData;
        listData->back = listData;
        length++;
        //#DEBUG cout << "First item added" << endl;
    }
    else if (listData->info < item)
    {
        itemNode ->next = listData ->next;
        (listData->next)->back = itemNode;
        itemNode ->back = listData;
        listData ->next = itemNode;
        listData = itemNode;
        length++;
        //#DEBUG cout <<"Item added to last slot" << endl;
    }
    else
    {
        bool found;
        NodeType<T>* location = SortedListType::FindItem(item,found);
        //#DEBUG cout << "Next smaller number:" << location->info;
        if (found == true)
            throw DuplicateItemException();
        else
        {
            itemNode ->next = location ->next;
            (location->next)->back = itemNode;
            itemNode ->back = location;
            location ->next = itemNode;
            length++;
            //#DEBUG cout << "Item added in middle" << endl;
        }
    }
    //#DEBUG cout << "Length: " << length << endl;
}

template<class T>
void SortedListType<T>::DeleteItem(T item)
{
    bool found;
    NodeType<T>* location = SortedListType::FindItem(item,found);
    if (found == false)
        throw ItemNotFoundException();
    
    else
    {
        if (location == listData)
            listData = location->back;
        (location->next)->back = location->back;
        (location->back)->next = location->next;
        delete location;
        length--;
        if (length == 0)
            listData = nullptr;
    }
}

template<class T>
int SortedListType<T>::GetLength() const
{
    return length;
}

template<class T>
T SortedListType<T>::GetFirstItem()
{
    if (listData == nullptr)
        throw EmptyListException();
    else
    {
        currentItem = listData->next;
        currentItemIndex = 1;
        //#DEBUG cout << "first item got" << endl;
        return (currentItem ->info);
    }
}

template<class T>
T SortedListType<T>::GetNextItem()
{
    currentItem = currentItem->next;
    if (currentItemIndex == length)
        currentItemIndex = 0;
    currentItemIndex++;
    //#DEBUG cout << "next item got" << endl;
    return (currentItem->info);
}

template<class T>
T SortedListType<T>::GetPreviousItem()
{
    currentItem = currentItem->back;
    currentItemIndex--;
    if (currentItemIndex == 0)
        currentItemIndex = length;
    return (currentItem->info);
}

template<class T>
int SortedListType<T>::GetCurrentIndex()
{
    return currentItemIndex;
}