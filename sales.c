/*
 * Title: Project #3: Inventory part 2
 * 
 * Filename: sales.c
 * 
 * Description: This program reads in sales orders from sales people and completes/displays a sale ticket for each
 * 				order. After processing the sales order, will display the status of the store inventory.  This program
 * 				also is capable of processing multiple sales orders passed in from files via the command line.
 * 
 * Author: Joseph Matzen
 * Date: 12/19/2018
 * 
 */

#include "sales.h"

/*
* processSale - Processes a sale by having  sku and quantity of item values passed to it.  If the sku # does not exist in
* 				the inventory, will display message that it is not in stock.  Otherwise, finds the sku entered and subtracts
* 				the amount of product needed. Also handles requests for more items than there are in stock.
				Prints that there arent enough in stock and adds however many items we do have to  the sales order.
							  
* @param int tempSku, int cnt
*/
void processSale(int tempSku, int cnt)
{
	if(!containsSku(tempSku))   // item not found
	{
		printf("SKU %d not in stock \n",tempSku);
	}else
		inStock(tempSku, cnt); // is handling output and manipulation of the linked list from
							   // the item class.  Finds the sku entered and subtracts the amount
							   // of product needed and prints a line of the order 
							   // based on items.  Also handles requests for more items than there are in stock.
							   // Prints that there arent enough in stock and adds however many items we do have to
							   // the sales order.
		
}


/*
* processSaleFromFile - Takes a file pointer in order to process a file line by line for a sales order.  After storing the
* 						sku and quantity, processes the order using the method processSale.  If there is a customer and salespersson
* 						name in the file, will process and store those names to be displayed.
* 
* @param FILE *F - file pointer
*/
void processSaleFromFile(FILE *f)
{
	char theSeller[20]; //used to store seller name for class methods in this class to use

	int ctr = 1;
	char line[25];
	char customer[25];
	char seller[25];
	int sku;
	int count;
	
	while(fgets(line, sizeof(line), f))  // getting individual lines from the txt file
	{
		if(ctr == 1 ) // seller always first line on sales form if at all
		{
			sscanf(line, "%[^,\t\n0123456789] ", seller); // saving sales person's name in seller
			
			strcpy(theSeller,seller);  //saving seller name for formatting purposes
			
		} 
		if(ctr == 2) // customer always second line on sales form if at all
		{
			sscanf(line, "%[^,\t\n0123456789] ", customer);
			
			if(isalpha(customer[0])) // did capture a name
				printf("Thank you, %s, for choosing CSC Music Stores!\n", customer);
			
		} 
	
		if(!isalpha(customer[0]) && !isalpha(seller[0])) // the line parsed contains no names
		{
			sscanf(line, "%d %d ", &sku, &count);
			
			processSale(sku,count);  //using the sku and count amount from line to process a sales order
		}
		
		for(int i = 0; i<25; ++i) // reseting string stored in customer
		{
			customer[i] = '\0';
		}
		for(int i = 0; i<25; ++i)  // reseting string stored in seller
		{
			seller[i] = '\0';
		}	
		++ctr; // counting run-throughs of loop
	}
	printFinalPrice(); // prints the final order price with sales tax included as well
	
	if(isalpha(theSeller[0])) // will only print if a name is stored in variable theSeller
		printf("Your salesperson: %s\n", theSeller);
		printf("\n");
	
	ctr = 0; // reseting counter
}
