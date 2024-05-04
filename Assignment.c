#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Item 
{
	char name[50];
	float price;
	int quantity;
};

struct Bill 
{
  struct Item items[50];
  int itemCount;
  float total;
  float discount;
  float totalamount;
};

void Displaybill(struct Bill* bill);
float CalculateDiscount(struct Bill* bill);

int main() 
{	
	FILE *fread;
	fread = fopen("menu.txt", "r");
    if(fread != NULL)
	{
        char c;
        while((c = fgetc(fread)) != EOF) 
		{
            putchar(c);
        }
        fclose(fread);
	} 
	else 
	{
        printf("Error opening file\n");
	}
	
	struct Bill bill;
	bill.itemCount = 0;
	bill.total = 0;
	bill.discount = 0;
	bill.totalamount = 0;

	char choice;
	do {
		struct Item item;
		printf("Enter item code: ");
		scanf(" %c", &choice);
		switch(choice)
		{
			case 'A' :
				strcpy(item.name, "French Toast");
				item.price = 10.00;
				break;
			
			case 'B':
				strcpy(item.name, "Egg Benedict");
				item.price = 12.90;
				break;
			
			case 'C':
				strcpy(item.name, "Butter Pancakes");
				item.price = 11.50;
				break;
			
			case 'D':
				strcpy(item.name, "Coffee");
				item.price = 8.00;
				break;
			
			case 'E':
				strcpy(item.name, "Green Tea");
				item.price = 5.60;
				break;
			
			case 'F':
				strcpy(item.name, "Orange Fruit Juice");
				item.price = 7.00;
				break;
			
			case 'G':
				strcpy(item.name, "Apple Pie");
				item.price = 4.60;
				break;
			
			case 'H':
				strcpy(item.name, "Donuts");
				item.price = 4.00;
				break;
			
			case 'I':
				strcpy(item.name, "Chocolate Chip Cookies");
				item.price = 3.50;
				break;
			
			default:
				printf("\n\nInvalid choice,  please enter a valid code\n\n\n");
				main();
				continue;

		}
		
	printf("Enter item quantity: ");
	scanf("%d", &item.quantity);
	bill.items[bill.itemCount] = item;
	bill.itemCount++;
	bill.total += item.price * item.quantity;
	
	printf("Do you want to enter another item? (y/n) ");
	scanf(" %c", &choice);
	} while (choice == 'y');

	CalculateDiscount(&bill);
	bill.totalamount = bill.total - bill.discount;

	Displaybill(&bill);	

	return 0;
}

void Displaybill(struct Bill* bill) 
{
	printf("\n\tBill:\n\n");
	for (int i = 0; i < bill->itemCount; i++) 
	{
		struct Item item = bill->items[i];
		printf("%d. %s,\t Price of one: %.2f\t Quantity: %d\t Total: %.2f\n", i + 1, item.name, item.price, item.quantity, item.price * item.quantity);  
	}

	printf("\nTotal Amount: %.2f\n", bill->total);
	printf("Discount: %.2f\n", bill->discount);
	printf("Net Payable: %.2f\n", bill->totalamount);
}

float CalculateDiscount(struct Bill* bill)
{
    char code;
    printf("Do you have a discount code (y/n) :  ");
    scanf(" %c", &code);

    if(code == 'y')
    {
        printf("Enter Discount Code (disTen or disTwenty): ");
        char discount[10];
        scanf("%s",  discount);

        if (strcmp(discount, "disTen")== 0)
            bill->discount = (10.0 / 100.0) * bill->total;

        else if(strcmp(discount, "disTwenty")== 0)
            bill->discount = (20.0 / 100.0) * bill->total;

        else
            printf("Your Discount Code is Invalid. Discount has been set to Zero.\n");

    }
    else if (code == 'n')
    {
        bill->discount = 0;
  
    }
    else
    {
        printf("Invalid input. Please enter 'y' or 'n'\n");
        CalculateDiscount(bill);
    }
	
	return bill->discount;
}