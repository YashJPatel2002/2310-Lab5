/*************************
 *Yash Patel                      *
 *CPSC 2311 Sprint 23 Section 005 *
 *yjpatel                         *
 *yjpatel@clemson.edu             *
 Instructor: Dr. Yvon Feaster     *
 *************************/
#include "functions.h"

/*This file will have minimal code. Most of your code should be in your
functions.c file. In this file, you should
★ Use assert to check for the correct number of command line arguments and that
the files opened correctly
★ Open your input and output files
★ Call createList to create and fill your linked list with input data
★ Call printList to print out the linked list
★ Free memory from the linked list by calling deleteList
★ Take in an additional command line argument, either “1” or “2”. If ran with
1, then you should sort the list by first name. If 2, then sort by last name.
★ Call sortList to sort the linked list (different calls depending on last name
or first name) sortList should be called after createList, 
but before printList.*/

int main(int argc, char *argv[])
{
    // check for correct number of command line arguments
    assert(argc == 4);

    // open input and output files
    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    // check if files opened correctly
    assert(input != NULL);
    assert(output != NULL);

    // create and fill linked list with input data
    node_t *head = NULL;
    head = createList(input, &head);

    // sort linked list by first name
    if (strcmp(argv[3], "1") == 0) {
        sortList(&head, compare_by_firstname);
    }
    // sort linked list by last name
    else if (strcmp(argv[3], "2") == 0) {
        sortList(&head, compare_by_lastname);
    }
    // remove duplicate entries of students in list
    removeDuplicates(head);

    // print linked list
    printList(output, head);

    // free memory from linked list
    deleteList(&head);
    
    
    // close files
    fclose(input);
    fclose(output);

    return 0;
}