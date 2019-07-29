/*
 * Title: Project #3: Inventory part 2
 * 
 * Filename: sales.h
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
#include <ctype.h>
void processSaleFromFile(FILE *f);
void processSale(int tempSku, int cnt);
int containsSku(int sku);
double inStock(int sku, int amt);
void sellerMessage();
double printFinalPrice();
