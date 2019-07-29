/*
 * Title: Project #3: Inventory part 2
 * 
 * Filename: item.c
 * 
 * Description: This program reads in sales orders from sales people and completes/displays a sale ticket for each
 * 				order. After processing the sales order, will display the status of the store inventory.  This program
 * 				also is capable of processing multiple sales orders passed in from files via the command line.
 * 
 * Author: Joseph Matzen
 * Date: 12/19/2018
 * 
 */
#include "item.h"

struct node *head= NULL;

/*
* printList method - Prints the contents of the linked list.
*/
void printList()
{
	
	struct node *trav = head;
	printf("\nstatus of the list\n");
	while(trav != NULL)
	{
	
		printf("%d %s: %d in stock at $%s\n",trav->sku, trav->desc,trav->count, trav->price);
		//printf(":%s \n", str);

		trav = trav->next;
	}
	
}

/*
* printSaleList method - Prints the contents of the list unless there are no items in stock.
*/
void printSaleList()
{
	
	struct node *trav = head;
	
	printf("\nstatus of the list\n");
	
	while(trav != NULL) 
	{
		if(trav->count != 0 && trav->sku != -123123123) // if count isnt 0 and the sku isnt where I am storing my total sales price
		{
			printf("%d %s: %d in stock at $%s\n",trav->sku, trav->desc,trav->count, trav->price);
		}

		trav = trav->next;
	}
	
}
/*
* insertSku method - Creates a new node in the list and sets the nodes sku value to the one that was passed
* @param int data
*/
void insertSku(int data) {
   //creating new node
   struct node *newNode = (struct node*) malloc(sizeof(struct node));

   //Setting the passed sku to the nodes sku
   newNode->sku = data;

   //point it to old first node
   newNode->next = head;

   //point first to new first node
   head = newNode;
   
   //increment count
   newNode->count++;
}

/*
* insertDesc method - Creates a new node in the list and sets the nodes desc value to the one that was passed
* @param char data[]
*/
void insertDesc(char data[]) {
   //creating new node
   struct node *newNode = (struct node*) malloc(sizeof(struct node));

   //Setting the passed desc to the nodes desc
   
   newNode->desc = strdup(data);

   //point it to old first node
   newNode->next = head;

   //point first to new first node
   head = newNode;
   
   //increment count
   newNode->count++;
}

/*
* containsSku method - Searches whether a sku is stored in one of the nodes of the list, and increments count if it is.
* @param int sku
* @return 1 if sku is present, 0 otherwise
*/
int containsSku(int sku)
{
	struct node *trav = head;
	
	while(trav != NULL)
	{
		if(trav->sku == sku)
		{
			trav->count++;
			return 1;
		}else
		{
			trav = trav->next;
		}
			
	}
	
		return 0;	
	
}

/*
* printSaleList method - Prints the total for sales order, the sales tax for order, and then the adjusted final price of order
*/
double printFinalPrice()
{
	struct node *trav2 = head;
	
	while(trav2 != NULL) 
	{
		if(trav2->sku == -123123123)  // looking for node that is holding total sales information with unique negative sku number
		{
			break;
		}else
			trav2 = trav2->next;
	}

	printf("Total sales: $%.2f\n", trav2->tSales);  //prints total sales
	printf("Sales Tax(8.25%%): $%.2f\n", trav2->tSales*.0825);  // prints sales tax
	printf("Final Price: $%.2f\n", trav2->tSales+(trav2->tSales*.0825));  //prints price with tax included

	trav2->tSales = 0; // resesting totalSales in case of new order needing to be processed
}

/*
* inStock method - Finds the sku entered and subtracts the amount of product needed from the inventory. Also handles requests for more 
* 				   items than there are in stock by prints that there arent enough in stock and adds however many items
*  				   we do have to  the sales order.
* @param int sku, int amt
* @return 1 if sale processing was successful, 0 otherwise
*/
double inStock(int sku, int amt)
{	
	int i;  // used for tracking the amount of an item sold to later multiply with price for a total
	double price;
	double total;
	struct node *trav = head; // used for finding items in inventory
	struct node *trav2 = head; // used for updating total sales number within linked list
	
	// looking for node that is holding total sales information with unique negative sku number
	while(trav2 != NULL)
	{
		if(trav2->sku == -123123123) // looking for node that is holding total sales information with unique negative sku number
		{
			break;
		}else
			trav2 = trav2->next;
	}

	
	while(trav != NULL)
	{
		if(trav->sku == sku)
		{
			trav->count--; // correcting an error where count is 1 higher than it should be, why the value prints normally everywhere else is a mystery.
			
			price = atof(trav->price); //storing price as a float
			total = price*amt; //calculating total
			
			if(amt > trav->count) // if sales ordered requests more items than are in stock
			{
				if(trav->count > 0) // has the item in stock
				
				{
					printf("Requested %d %s: only %d in stock \n", amt, trav->desc, trav->count);
				
					for(i = -1; i <= trav->count; ++i)
					{
						trav->count--; // decrementing count for amount of items sold
					}
				
					total = price*(i+1); //getting total price for specific item
					
					trav2->tSales += total; // updating total sales node
					
					printf("%d x %s @ $%.2f: $%.2f \n", i+1, trav->desc, price, total); //printing sale line
				return 1;
			}else
				printf("SKU %d not in stock \n", sku); // item not in stock

			}
			if(amt <= trav->count) // if sales order requested a quantity of items that we have
			{
				for(int i = 0; i < amt; ++i)
				{
					trav->count--; // decrementing item count for amount of items being sold
				}
				
				trav2->tSales += total;  // updating total sales node

				printf("%d x %s @ $%.2f: $%.2f \n", amt, trav->desc, price, total);  //printing sale line
			}
			
				return 1;
		}else
			{
				trav = trav->next; // moving through list
			}		

	}

		return 0;	
	
}

/*
* containsDesc method - Searches whether a description is stored in one of the nodes of the list, and increments count if it is.
* @param int sku
* @return 1 if desc is present, 0 otherwise
*/
int containsDesc(char *d)
{
	struct node *trav = head;
	char *tempD;
	tempD = strdup(d);
	while(trav != NULL)
	{
		if(trav->desc != NULL &&  strcmp(trav->desc, tempD) == 0)
		{
			trav->count++;
			return 1;
		}else
		{
			trav = trav->next;
		}
			
	}
	
		return 0;	
	
}

/*
* findSkuInsertDesc method - Searches for a specific sku and adds desc value to node with matching sku
* @param int i, char d[]
* @return 1 if successful, 0 otherwise
*/
int findSkuInsertDesc(int i, char d[])
{
	
	struct node *trav = head;
	
	while(trav != NULL)
	{
		if(trav->sku == i)
		{		
			trav->desc = strdup(d);
			
			return 1;
		}else
		{
			trav = trav->next;
		}
	}
	return 0;
	
}

/*
* findSkuInsertPrice method - Searches for a specific sku and adds price value to node with matching sku
* @param int i, char p[]
* @return 1 if successful, 0 otherwise
*/
int findSkuInsertPrice(int i, char p[])
{
	
	struct node *trav = head;
	
	while(trav != NULL)
	{
		if(trav->sku == i)
		{		
			trav->price = strdup(p);
			
			return 1;
		}else
		{
			trav = trav->next;
		}
	}
	return 0;
	
}

/*
* findDescInsertPrice method - Searches for a specific description and adds price value to node with matching description
* @param char d[], char p[]
* @return 1 if successful, 0 otherwise
*/
int findDescInsertPrice(char d[], char p[])
{
	
	struct node *trav = head;
	
	while(trav != NULL)
	{
		if(trav->desc != NULL && strcmp(trav->desc,d) == 0)
		{		
			trav->price = strdup(p);
			
			return 1;
		}else
		{
			trav = trav->next;
		}
	}
	return 0;
	
}

/*
* findDescInsertSku method - Searches for a specific description and adds sku value to node with matching description
* @param char d[], int p
* @return 1 if successful, 0 otherwise
*/
int findDescInsertSku(char d[], int p)
{
	
	struct node *trav = head;
	
	while(trav != NULL)
	{
		if(trav->desc != NULL && strcmp(trav->desc,d) == 0)
		{		
			trav->sku = p;
			
			return 1;
		}else
		{
			trav = trav->next;
		}
	}
	return 0;
	
}
/*
* Copy method - Copies one string into another string
* 
* @param char to[], char from[]
* (c) Kernighan and Ritchie / class notes
*/
void copy(char to[], char from[])
{
	int i = 0;
	while((to[i]=from[i])!= '\0')
	{
		++i;
	}
}
