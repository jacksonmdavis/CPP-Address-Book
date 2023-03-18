# C++ Address Book
## An simple, interactive Address Book project, written in C++.

This project, written in Nov. 2022, is a terminal-interface address book created for a Data Structures course in C++.

It is a relatively small project, and was meant as a simple vertical slice of the coding I had learned over a couple of months.  It uses class templates, a circular doubly-linked list ADT, menu functions, and many simple operations, including a homebrew serialization format that I made up for the project.  All code is original by me; work is not continuing on this project.<br><br>

<ins>**Usage Guide:**</ins><br><br>
All files needed are located in the project (except C++ std. libraries).  Compilation was done via: *g++ SortedList.cpp DateType.cpp ContactType.cpp ProjectMain.cpp  -Werror -o "../Address_Book.exe"* executed in the <SourceCode> folder.  There is also a “Unit_Tests.exe” file in the *SourceCode* folder that uses the files located in the *TestFiles* folder.<br>
When the “Address_Book.exe” file is run, the option is given to run an automatic test that executes each option in the menu, prints the output to a file, and saves a new “addressbook.txt” at the end.  Alternatively, the program can run with manual control, and the user can load, modify, and save their own address book.<br><br>


<ins>**Source File Guide:**</ins><br><br>
**ContactType.hpp/cpp** – This is a class containing information and simple methods for storing contacts for use in an address book system.  The amount of data is rather small, so the class is fairly simple, with most methods being fairly self-explanatory.  It provides the ‘<’ and ‘==’ operators so Contacts can be stored in a sorted structure.<br><br>
**DateType.hpp/cpp** – This is a class for storing, manipulating, and comparing simple dates.  It is also relatively simple.  I included the ability to store an uninitialized date, so that when entering records into the address book one isn’t required to enter a birthday and anniversary, as those might not be known.<br><br>
**SortedList.hpp/cpp** – This is a circular, doubly-linked template implementation of a Sorted List ADT.  The list itself is relatively straightforward, made slightly more complicated because it is a class template.  One way in which it differs from the linked-list examples in the textbook is that it also keeps track of an “index” number for each list node, which is useful for browsing the list.<br><br>
**ProjectMain.cpp** – This is the main function and a series of helper functions implementing the menus and actions, and it is the most complex (spaghetti) file in the bunch.  Looking at the forward declarations of functions at the beginning of the file, it seems obvious that this should have been multiple files or an AddressBook class, but I realized that too late in the process and it needed to get out the door.
