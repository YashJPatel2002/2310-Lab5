/*************************
 *Yash Patel                      *
 *CPSC 2311 Sprint 23 Section 005 *
 *yjpatel                         *
 *yjpatel@clemson.edu             *
 Instructor: Dr. Yvon Feaster     *
 *************************/
#include "functions.h"

/*This function will add a node to a linked list. You will take in two
parameters, a double pointer to the node you want to add and a double
pointer to the head of the list. You should check if the list is empty and
add the node to the list. You will have to print out the data in order so you
may want to add the node to the end of your linked list.*/
void add(node_t **node, node_t **head)
{
    node_t *temp = *head;
    //check if list is empty
    if(*head == NULL)
    {
        //add node to list
        *head = *node;
        return;
    }
    //list is not empty
    while(temp->next != NULL)
    {
        //traverse list
        temp = temp->next;
    }
    //add node to end of list
    temp->next = *node;
}

/*This function will read the data from the input file, returning a pointer to
the populated node. Use malloc to allocate the memory for the node that will
eventually be added to the linked list. Using scanset conversion, read the data
and store it in the node allocated. (You must use scanset conversion to read
ALL the data, not just part of the data.)*/
node_t* readNodeInfo(FILE* input)
{
    char tempDay[50];
    char tempYear[50];
    //allocate memory for node
    node_t *node = (node_t*)malloc(sizeof(node_t));
    //read data from input file using scanset conversion
    fscanf(input, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
    node->lastName, node->firstName, node->birthday.month, tempDay, tempYear,
    node->major, node->classStanding);

    //use atoi to convert string to int
    node->birthday.day = atoi(tempDay);
    node->birthday.year = atoi(tempYear);


    //return pointer to node
    return node;
    
}

/*This function will print out your linked list. The first argument is a file
pointer to your output file and the second is a pointer to the head of your
list. If the list is empty, print “LIST IS EMPTY\n” to stderr. Else, your
output should look like the following:*/
void printList(FILE* output, node_t *head)
{
    //check if list is empty
    if(head == NULL)
    {
        //print error message to stderr
        fprintf(stderr, "LIST IS EMPTY \n");
        return;
    }
    //list is not empty
    //print header
    printBorder(output);
    fprintf(output, "\nList Info:\n");
    // while loop to traverse list
    while (head->next != NULL)
    {
        // print data
        fprintf(output, "Name:\t%s %s\n", head->firstName, head->lastName);
        fprintf(output, "Date of Birth:\t%s %d, %d\n", head->birthday.month,
        head->birthday.day, head->birthday.year);
        fprintf(output, "Major:\t%s\n", head->major);
        fprintf(output, "Year:\t%s\n", head->classStanding);
        fprintf(output, "\n");
        // traverse list
        head = head->next;
    }
    // print last node
    fprintf(output, "Name:\t%s %s\n", head->firstName, head->lastName);
    fprintf(output, "Date of Birth:\t%s %d, %d\n", head->birthday.month,
    head->birthday.day, head->birthday.year);
    fprintf(output, "Major:\t%s\n", head->major);
    fprintf(output, "Year:\t%s\n", head->classStanding);
    fprintf(output, "\n");
    // print footer
    printBorder(output);
}

void printBorder(FILE *out)
{
    int i = 0;
    for (i = 0; i < 80; i++)
        fprintf(out, "*");

    fprintf(out, "\n");
}

/*This function will deallocate the memory used in your linked list to
avoid any memory leaks. You will take in one parameter, a double pointer to
the head of your linked list. These functions are required but you are free to
implement helper functions as you see fit. As long as the required functions
(with the correct parameters and return values) are present, the
implementation is flexible. You will also need to check for duplicate entries.
If there are two identical entries in your input file, you should only print
out the first one. There are a few different ways to do this. The simplest
method is to exhaustively search your linked list and check to see if
there are any matching entries. You can do this check when adding to the linked
list or when printing to the output file. If you’ve taken 2120, you could also
use a data structure like a hash table or a trie to keep track of duplicates
(this is not required, just a fun option). You may implement any additional
functions to perform the check.*/

void deleteList(node_t** head){
    node_t* temp = *head;
    node_t* next;
    //traverse list
    while(temp != NULL)
    {
        //delete node
        next = temp->next;
        free(temp);
        temp = next;
    }
    //set head to null
    *head = NULL;
}

/*This function will be called in your driver and will create the linked list.
The first argument will be a file pointer to your input file and the second
will be a double pointer to the head of your list. Use a loop to read from your
input file, calling readNodeInfo for each node and then calling add to add that
node to the list. After all of the information from the input file has been
added to the list, return a pointer to the head of the list.*/
node_t* createList(FILE* input, node_t** head)
{
    //read data from input file
    while(!feof(input))
    {
        //read data from input file
        node_t *node = readNodeInfo(input);
        
        //check invalid dates
        if(checkInvalidDate(node))
        {
            // add node to list
            add(&node, head);
        }
    }
    //return pointer to head of list
    return *head;
}

/*You will also need to check for duplicate entries.If there are two identical
entries in your input file, you should only print out the first one. There are
a few different ways to do this. The simplest method is to exhaustively search
your linked list and check to see if there are any matching entries. You can do
this check when adding to the linked list or when printing to the output file.
If you’ve taken 2120, you could also use a data structure like a hash table or
a trie to keep track of duplicates (this is not required, just a fun option).*/
void removeDuplicates(node_t *head)
{
    node_t *temp = head;
    node_t *prev = head;
    //list is not empty
    //nested while loop to have the first node stay while the second node
    //traverses the list and compares to the first node to see if there are any
    //duplicates and if there are, it will remove the duplicate
    while(head != NULL)
    {
        //set the temp to the next node
        temp = head->next;
        prev = head;
        while(temp != NULL)
        {
            //if the first and last name are the same, then it will remove the
            //duplicate
            if(strcmp(temp->firstName, head->firstName) == 0 &&
            strcmp(temp->lastName, head->lastName) == 0)
            {
                //set the previous node to the next node
                prev->next = temp->next;
                //free the duplicate
                free(temp);
                //set the temp to the next node
                temp = prev->next;
            }
            //if the first and last name are not the same, then it will set the
            //previous node to the next node and set the temp to the next node
            else
            {
                prev = temp;
                temp = temp->next;
            }
        }
        //advance the head to the next node
        head = head->next;
    }
}

/*bool checkInvalidDate(node_t *node);
This function should take in a node ptr and check that the node being pointed
to contains a valid date. We will not give you incorrectly spelled months, but
you must check that the day is in the month. To do this, you will also need to 
check for leap years (I did this in a helper function). If a node has an 
invalid date, don’t add it to the list (or don’t print it out). However you
chose to implement, it shouldn’t be in your output file.*/
bool checkInvalidDate(node_t *node)
{   
    
    //check if the month is January, March, May, July, August, October, or
    //December
    if(strcmp(node->birthday.month, "January") == 0 ||
    strcmp(node->birthday.month, "March") == 0 ||
    strcmp(node->birthday.month, "May") == 0 ||
    strcmp(node->birthday.month, "July") == 0 ||
    strcmp(node->birthday.month, "August") == 0 ||
    strcmp(node->birthday.month, "October") == 0 ||
    strcmp(node->birthday.month, "December") == 0)
    {
        //check if the day is greater than 31
        if(node->birthday.day > 31)
        {
            //return false
            return false;
        }
        //check if the day is less than 1
        else if(node->birthday.day < 1)
        {
            //return false
            return false;
        }
    }
    //check if the month is April, June, September, or November
    else if(strcmp(node->birthday.month, "April") == 0 ||
    strcmp(node->birthday.month, "June") == 0 ||
    strcmp(node->birthday.month, "September") == 0 ||
    strcmp(node->birthday.month, "November") == 0)
    {
        //check if the day is greater than 30
        if(node->birthday.day > 30)
        {
            //return false
            return false;
        }
        //check if the day is less than 1
        else if(node->birthday.day < 1)
        {
            //return false
            return false;
        }
    }
    //check if the month is February
    else if(strcmp(node->birthday.month, "February") == 0)
    {
        //check if the year is a leap year
        if(checkLeapYear(node->birthday.year))
        {
            //check if the day is greater than 29
            if(node->birthday.day > 29)
            {
                //return false
                return false;
            }

            //check if the day is less than 1
            else if(node->birthday.day < 1)
            {
                //return false
                return false;
            }
        }
        //check if the year is not a leap year
        else
        {
            //check if the day is greater than 28
            if(node->birthday.day > 28)
            {
                //return false
                return false;
            }

            //check if the day is less than 1
            else if(node->birthday.day < 1)
            {
                //return false
                return false;
            }
        }
    }
    //return true
    return true;
}

/*void sortList(node_t **head, <function pointer> comp);
This function takes in two arguments. The first is the head of your linked list
and the second is a function pointer to the compare function you want to use in
your sort. This will be either compare_by_lastname() or compare_by_firstname().
As far as algorithms go, I recommend using bubble sort for those totally new to
sorting (here’s a helpful guide: https://www.geeksforgeeks.org/bubble-sort/)*/
void sortList(node_t **head, int (*comp)(node_t *a, node_t *b))
{
    //set the swapped to true
    bool swapped = true;
    //set the temp to the head
    node_t *temp = *head;
    //set the prev to the head
    node_t *prev = *head;
    //set the next to the head
    node_t *next = *head;
    //while the list is not sorted
    while(swapped)
    {
        //set the swapped to false
        swapped = false;
        //set the temp to the head
        temp = *head;
        //set the prev to the head
        prev = *head;
        //set the next to the head
        next = *head;
        //while the temp is not null
        while(temp != NULL)
        {
            //set the next to the next node
            next = temp->next;
            //if the next node is not null
            if(next != NULL)
            {
                //if the compare function returns a positive number
                if(comp(temp, next) > 0)
                {
                    //if the temp is the head
                    if(temp == *head)
                    {
                        //set the head to the next node
                        *head = next;
                    }
                    //set the previous node to the next node
                    prev->next = next;
                    //set the temp to the next node
                    temp->next = next->next;
                    //set the next node to the temp
                    next->next = temp;
                    //set the swapped to true
                    swapped = true;
                }
            }
            //set the previous node to the temp
            prev = temp;
            //set the temp to the next node
            temp = next;
        }
    }
}

/*int compare_by_lastname(node_t *a, node_t *b);
This function should take in two node pointers and compare the two nodes by 
last name. You should return 0 if the strings are the same, a positive number
if the first node is "greater", and a negative number if the second node is
"greater". HINT: read the man page for strcmp, especially the section on return
values;)*/
int compare_by_lastname(node_t *a, node_t *b)
{
    //return the strcmp of the last name
    return strcmp(a->lastName, b->lastName);
}

/*int compare_by_firstname(node_t *a, node_t *b);
This function should take in two node pointers and compare the two nodes by
first name. You should return 0 if the strings are the same, a positive number
if the first node is "greater", and a negative number if the second node is
"greater".*/
int compare_by_firstname(node_t *a, node_t *b)
{
    //return the strcmp of the first name
    return strcmp(a->firstName, b->firstName);
}

/*bool checkLeapYear(int year);
This function should take in a year and return true if the year is a leap year
and false if it is not.*/
bool checkLeapYear(int year)
{
    //check if the year is divisible by 4
    if(year % 4 == 0)
    {
        //check if the year is divisible by 100
        if(year % 100 == 0)
        {
            //check if the year is divisible by 400
            if(year % 400 == 0)
            {
                //return true
                return true;
            }
            //return false
            return false;
        }
        //return true
        return true;
    }
    //return false
    return false;
}