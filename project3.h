/*
 * Title: Project #3: Inventory part 2
 * 
 * Filename: project3.h
 * 
 * Description: This program reads in sales orders from sales people and completes/displays a sale ticket for each
 * 				order. After processing the sales order, will display the status of the store inventory.  This program
 * 				also is capable of processing multiple sales orders passed in from files via the command line.
 * 
 * Author: Joseph Matzen
 * Date: 12/19/2018
 * 
 */
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "item.h"
#include "sales.h"
#include <stdio.h>
#define MAXCHAR 120


int getNewLine(char s[], int lim);
char * getPrice(char in[], char *p);
char * getDesc(char in[]);
int isnumeric(char *n);
