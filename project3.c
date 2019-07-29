/*
 * Title: Project #3: Inventory part 2
 * 
 * Filename: project3.c
 * 
 * Description: This program reads in sales orders from sales people and completes/displays a sale ticket for each
 * 				order. After processing the sales order, will display the status of the store inventory.  This program
 * 				also is capable of processing multiple sales orders passed in from files via the command line.
 * 
 * Author: Joseph Matzen
 * Date: 12/19/2018
 * 
 */
#include "project3.h"


int main(int argc, char **argv)
{
	int len = 0;
	char line[MAXCHAR];
	int i = 0;
	int len2 = 0;
	char line2[MAXCHAR];
	

	char sku [20]; // holds value for sku
	char desc [20]; // holds value for description
	char price [8]; // holds value for price
	
	while((len = getNewLine(line, MAXCHAR)) > 0)
		{
			sscanf(line, "%s %[^,\t\n0123456789]%s ", sku, desc, price);
			
			if(!isalpha(sku[0])) // sku is present
			{
			  i = atoi (sku); // storing sku as an int
		    }
			
			getPrice(line,price); // getting the price from line, storing it in price
	        
	        //if first char of sku is a number
			if(isnumeric(sku))
			{

				if(!containsSku(i) && !containsDesc(desc))
				 {
				  insertSku(i); // making new list entry with sku
			     }else
			     {
					 if(containsDesc(desc))
					 {
					   findDescInsertSku(desc,i); // inserting sku if description is already stored in list
				     }
				 }
			     
			     if(isnumeric(price)) // inserting price here if description isnt present
			     {
					findSkuInsertPrice(i,price); // insert price into node with matching sku
				 }
			 
			}else
			{
			//if no sku number in line, sscanf puts description in sku field
			if(isalpha(sku[0]))
			{
				if(containsDesc(sku))
				{
					if(isnumeric(price)) // inserting price if there is one
					{
						findDescInsertPrice(sku,price); // inserting price based on desc location
					}
					
				}else
				{
					insertDesc(sku); // creating new list node with just description
					
					if(isnumeric(price)) // inserting price if there is one
					{  
						findDescInsertPrice(sku,price);
					}
				}
			}
		}
            

			if(isalpha(desc[0])) // if desc parsed correctly
			{
				i = atoi (sku); // turning sku string to int
				
				findSkuInsertDesc(i,desc); //inserting description into matching sku number
					if(isnumeric(price))
					{
						findDescInsertPrice(sku,price);  // inserting price based on location of description
					}
			}
			 
			 
			//Emptying the previous contents of sku, price, and description. Probably not correct to do it this way.  
			for(int i=0; i<20; ++i)
			{
				desc[i] = '\0';
			}
			for(int i=0; i<7; ++i)
			{
				price[i] = '\0';
			}
			for(int i=0; i<7; ++i)
			{
				sku[i] = '\0';
			}

		}
	
	printList(); // printing resulting list
	
	/*
	 *  Sales order processing portion
	 */
	
	insertSku(-123123123); // Although this is a bad idea, I made a node in my list for storing/updating total price of sales order.
						  // Multiple methods in the item module need to look at total sales and I cant declare variables outside of function scope.

	
	FILE *fp; // file pointer
	
	if(argc == 1) // If no command line arguments, carries out code to earn project grade of 65
	{
	  // demonstrating processing sales based on sample inventory from project pdf
	  processSale(325,1); 
	  processSale(218,4);
	  processSale(222,4);
	  processSale(404,3);

	  printFinalPrice();  //prints final price of order with tax
	  
	}else
		while(--argc > 0)
			if((fp = fopen(*++argv, "r")) == NULL) // opens a file for reading with a condition for when a passed file can't be opened
			{
				printf("Project3: Can't open file %s\n", *argv);
				return 1;
			}
			else 
			{
				processSaleFromFile(fp); // processes sale order using file pointer				
				
				fclose(fp);				// closes the file that was opened for reading
			}	
	
	printSaleList(); // printing end status of inventory
	
	return 0;
}


	/*
	 * getNewLine method - Retrieves and stores line of certain number of characters
	 * 						from standard input
	 * @param char s[], int lim
	 * @returns int i
	 * (c) Kernighan and Ritchie / class notes
	 */
	int getNewLine(char s[], int lim)
	{
		int c,i;
		
		for(i=0; i<lim-1 && (c = getchar())!= EOF && c!= '\n';++i)
		{
			s[i]=c;
		}
		if(c == '\n')
		{
			s[i] = c;
			++i;
			s[i] = '\0';
		}
		return i;
	}
	/*
	 * getPrice method - Retrieves the price from a string based on the price having a '.' in it.
	 * @param char in[], char *p
	 * @returns returns null if no price in the string else returns price in string form
	 */
	char * getPrice(char in[], char p[])
	{
		int found = 0;
		char *tempPrice = malloc(10);
		int j,i = 0;
		for(i=0;in[i] != '.' && in[i]!='\0';i++)
		{
			if(in[i+1] == '.')
			{
				found =1;
			}				

		}
		if(found == 0)
		{
			return NULL;
		}else
		{
		   //getting to start of price, moving back from when i points to '.'
		   while(in[i]!= ' ')
		   {
			   --i;
		   }
		   i++;  // gets rid of the space before the actual price
		   while(in[i]!='\0')
		   {
			p[j++] = in[i];
			++i;
		   }
		   p[j] = '\0';
	     }
		return strdup(p);
	}
	

	
	/*
	 * isNumeric method - determines if first char of a string is a number.
	 * @param char *n
	 * @returns returns 1 if first char is number, 0 if not
	 */
	int isnumeric(char *n)
	{
		if(n[0] == '0' || n[0] == '1' || n[0] == '2' || n[0] == '3' || n[0] == '4' ||
		n[0] == '5' || n[0] == '6' || n[0] == '7' || n[0] == '8' || n[0] == '9')
		{
			return 1;
		}else
			return 0;
	}
	
	
		//char * getDesc(char in[])
	//{
		//int found = 0;
		//char *tempDesc = malloc(25);
		//int j,i = 0;
		//while(in[i] != '\0')
		//{
			//if(isalpha(in[i]) || in[i]==' ')
			//{
				//tempDesc[j++] = in[i];
			//}
			//++i;
		//}
		//return strdup(tempDesc);
	//}
	//char * getSku(char in[])
	//{
		
		//char *tempSku = malloc(10);
		//int i,r =0;
		
		//if(isalpha(in[0]))
		//{
			//return NULL;
		//}else
		//{
			//while(in[i]!= ' ' &&in[i]!= '$')
			//{
				//tempSku[i] = in[i];
				//++i;
			//}
		  //r = atoi (tempSku);

		//}
		//return tempSku;
	//}	
