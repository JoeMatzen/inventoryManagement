/*
 * Title: Project #3: Inventory part 2
 * 
 * Filename: item.h
 * 
 * Description: This program reads in sales orders from sales people and completes/displays a sale ticket for each
 * 				order. After processing the sales order, will display the status of the store inventory.  This program
 * 				also is capable of processing multiple sales orders passed in from files via the command line.
 * 
 * Author: Joseph Matzen
 * Date: 12/19/2018
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void insertSku(int data) ;
void printList();
int containsSku(int sku);
int findSkuInsertDesc(int sku, char d[]);
void copy(char to[], char from[]);
int findSkuInsertPrice(int i, char p[]);
int containsDesc(char *d);
int findDescInsertPrice(char d[], char p[]);
void insertDesc(char data[]);
int findDescInsertSku(char d[], int p);
void printSaleList();
double printFinalPrice();


struct node {
	int sku;
	double tSales; // for special node calculating total sales of an order.
	char *price;
	char *desc;
	int count;
	struct node *next;
};
