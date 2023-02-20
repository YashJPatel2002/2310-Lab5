/*************************
 *Yash Patel                      *
 *CPSC 2311 Sprint 23 Section 005 *
 *yjpatel                         *
 *yjpatel@clemson.edu             *
 Instructor: Dr. Yvon Feaster     *
 *************************/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>


//add birthday struct here
typedef struct birthday {
    int day;
    int year;
    char month[50];
} birthday_t;

//add node_t struct here (this struct will represent a node in the
//linked list)
typedef struct node {
    birthday_t birthday;
    struct node *next;
    char firstName[50];
    char lastName[50];
    char major[50];
    char classStanding[50];
} node_t;

//function pointer for compare_by_lastname and compare_by_firstname
typedef int (*comp)(node_t *, node_t *);

//implement these:
void add(node_t **node, node_t **head);
node_t* readNodeInfo(FILE* input);
node_t* createList(FILE*, node_t**);
void printList(FILE*, node_t*);
void printBorder(FILE*);
void deleteList(node_t** );
void removeDuplicates(node_t *head);
bool checkInvalidDate(node_t *node);
void sortList(node_t **head, int  (*comp)(node_t * a, node_t * b));
int compare_by_lastname(node_t *a, node_t *b);
int compare_by_firstname(node_t *a, node_t *b);
bool checkLeapYear(int year);

#endif