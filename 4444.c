/****************
Course: DCP5101 Program Design
Assignment: 1
Session: T2215
Group Name:
ID & Name 1:<1221201013>,<Koh Soon Keat>
Phone,Email:<YOUR PHONE NO>,<YOUR MAIN EMAIL ADDRESS>
ID & Name 2:<1221201358>,<Lee Di Xiang>
Phone,Email:<YOUR PHONE NO>,<YOUR MAIN EMAIL ADDRESS>
ID & Name 3:<1221200988>,<Ng Way Hong>
Phone,Email:<YOUR PHONE NO>,<YOUR MAIN EMAIL ADDRESS>
ID & Name 4:<1221201243>,<Danieal Hakim Bin Abu Hashim >
Phone,Email:<YOUR PHONE NO>,<YOUR MAIN EMAIL ADDRESS>
****************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	int orderNum;
	int orderTotal;
	char name[50];
	char code[50];
	char couponCode[30];
	double price;
	double total;
	double totalnett;
	double discount;
} Item;

void mainpage();
void mainpageorder();
int mainpageAddmore();
void orderFood();
void orderDrink();
void orderCart();
void totalOrderNgetdiscount() ;
void discountCoupon();
void addMore();
void receipt();
void cusdetails();
float calculatePrice(float itemPrice, float discount);
float afterDiscount(float subtotal,int discountpercentage);
int tNumber;
char guest[50];
int menu(int orderTypeSelection);
int menumenu(int orderTypeSelection);
Item getFoodInfo(int fCode);
Item getDrinkInfo(int dCode);
int foodItemList[100], foodQuantityList[100], foodCount = -1;
int drinkItemList[100], drinkQuantityList[100], drinkCount = -1;
float subtotal, discount, total;

int main() {
	
	printf("                 _______         _____  _______            _______     \n");
	printf(" \\      /\\      /|       |      |       |      | |\\      /||        \n");
	printf("  \\    /  \\    / |______ |      |       |      | | \\    / ||______  \n");
	printf("   \\  /    \\  /  |       |      |       |      | |  \\  /  ||	       \n");
	printf("    \\/      \\/   |______ |_____ |______ |______| |   \\/   ||______  \n");
	printf("---------------------------------------------------------------------  \n");
	printf("                 WELCOME TO WESTERN MMU RESTAURANT                     \n");
	printf("---------------------------------------------------------------------  \n\n");
	printf("                          MMU RESTAURANT MENU                          \n\n");
	fflush(stdin);
	cusdetails();
	mainpageorder();
	return 0;
}
void mainpageorder(){
    int selection = 0;
	do {
		printf("\nMENU MAINPAGE\n");
		printf("---------------\n");
		printf("Select an option:\n");
		printf("Enter 1 to order Food\n");
		printf("Enter 2 to order Drinks\n");
		scanf("%d", &selection);
		switch (selection) {
			case 1:
				menumenu(1);
				break;
			case 2:
				menumenu(2);
				break;
		}
	} while(selection >2);
}

int mainpageAddmore() {
	int selection;
	printf("Enter 1 to Add More?\n");
	printf("Enter 2 to back mainpage order\n");
	printf("Enter 3 to order cart view order\n");
	printf("Your selection: ");
	scanf("%d", &selection);
	return selection;
}

int menumenu(int orderTypeSelection) {
	int selection;
	FILE *fmenuFood;
	FILE *fmenuDrink;

	fmenuFood  = fopen("foodmenu.txt","r");
	fmenuDrink = fopen("drinkmenu.txt","r");

	if(orderTypeSelection == 1) {
		if( fmenuFood != NULL) {
			char c;
			while( (c = fgetc(fmenuFood)) != EOF )
				putchar(c);
			fclose(fmenuFood);
			printf("\n\n");
			orderFood();
			do {
			selection = mainpageAddmore();
			if(selection == 1) {
				orderFood();
			}
			else if (selection == 2) {
				mainpageorder();
			}
			else if (selection == 3) {
				printf("Now came to the order cart \n");
				orderCart();
			}
			} while(selection != 3);
			
		} else {
			printf("Error opening file. \n");
		}
	} else if(orderTypeSelection == 2) {
		if( fmenuDrink != NULL) {
			char c;
			while( (c = fgetc(fmenuDrink)) != EOF )
				putchar(c);

			fclose(fmenuDrink);
			printf("\n\n");
			orderDrink();
			do {
			selection = mainpageAddmore();
			if(selection == 1) {
				orderDrink();
			}
			else if (selection == 2) {
				mainpageorder();
			}
			else if (selection == 3) {
				printf("Now came to the order cart \n");
				orderCart();
			}
			} while(selection != 3);
			
		} else {
			printf("Error opening file. \n");
		}
	}
	return orderTypeSelection;
}
void orderFood() {
	int  fCode, selectMainpage = 0, quantity, foodSelected;

	printf("Please enter your food code : ");
    scanf("%d", &fCode);
    while(fCode>7 || fCode<1) {
        printf("Invalid Food Code. Please Try Again.\n");
        printf("Please enter your food code : ");
        scanf("%d", &fCode);
    }
    printf("Please enter your food quantity :");
    scanf("%d", &quantity);
    
	foodCount++;
	
	foodItemList[foodCount] = fCode;
	foodQuantityList[foodCount] = quantity;

}

void orderDrink() {
	int dCode, selectMainpage = 0, quantity, foodSelected;

	printf("Please enter your drink code : ");
	scanf("%d",&dCode);
	while(dCode>7 || dCode<1) {
        printf("Invalid Drink Code. Please Try Again.\n");
        printf("Please enter your drink code : ");
        scanf("%d", &dCode);
    }
    printf("Please enter your drink quantity :");
    scanf("%d", &quantity);

	drinkCount++;

	drinkItemList[drinkCount] = dCode;
	drinkQuantityList[drinkCount] = quantity;
}

void orderCart() {
	total=0;
	char selection, E, e, A, a;
	printf("\nHere is your orderlist\n");
	printf("Please check  your order\n ");
	printf("\nNo.\tItem Name\tQuantity\tPrice\tSubTotal\n");
	printf("--------------------------------------------------------\n");
	
	for(int i=0; i< foodCount + 1; i++) {
		printf("%d", i + 1);
		Item foodDetails = getFoodInfo(foodItemList[i]);
		printf("\t%-10s", foodDetails.name);
		printf("\t\tx%d", foodQuantityList[i]);
		printf("\t%.2f", foodDetails.price);
		printf("\t%.2f\n", foodDetails.price * foodQuantityList[i]);
		subtotal=foodDetails.price * foodQuantityList[i];
		total+=subtotal;
	}
	for(int j=0; j< drinkCount + 1; j++) {
		printf("%d",j + 1);
		Item drinkDetails = getDrinkInfo(drinkItemList[j]);
		printf("\t%-10s", drinkDetails.name);
		printf("\t\tx%d", drinkQuantityList[j]);
		printf("\t%.2f", drinkDetails.price);
		printf("\t%.2f\n", drinkDetails.price * drinkQuantityList[j]);
		subtotal=drinkDetails.price * drinkQuantityList[j];
		total+=subtotal;
	}
	printf("\nTotal is %.2f\n\n",total);
	addMore();
}

void totalOrderNgetdiscount(){
	char selection, E, e, A, a;
	printf("Here is your orderlist\n");
	printf("Please check  your order\n ");
	printf("No.\tItem Name\t\tQuantity\tPrice\tSubTotal\n");
	for(int i=0; i< foodCount + 1; i++) {
		printf("%d", i + 1);
		Item foodDetails = getFoodInfo(foodItemList[i]);
		printf("\t%s", foodDetails.name);
		printf("\t\t\tx%d", foodQuantityList[i]);
		printf("\t\t%.2f", foodDetails.price);
		printf("\t%.2f\n\n", foodDetails.price * foodQuantityList[i]);
		subtotal+=foodDetails.price * foodQuantityList[i];
	}
	for(int j=0; j< drinkCount + 1; j++) {
		printf("%d",j + 1);
		Item drinkDetails = getDrinkInfo(drinkItemList[j]);
		printf("\t%s", drinkDetails.name);
		printf("\t\tx%d", drinkQuantityList[j]);
		printf("\t\t%.2f", drinkDetails.price);
		printf("\t%.2f\n", drinkDetails.price * drinkQuantityList[j]);
		subtotal+=drinkDetails.price * drinkQuantityList[j];
	}
	printf("this is your subtotal%f",subtotal);
}

Item getFoodInfo(int fCode) {
	Item food[7];
	strcpy(food[0].name,"Burger");
	food[0].price = 6.00;
	strcpy(food[1].name,"Chicken chop");
	food[1].price = 12.00;
	strcpy(food[2].name,"Pizza");
	food[2].price = 15.90;
	strcpy(food[3].name,"Nasi goreng");
	food[3].price = 7.00 ;
	strcpy(food[4].name,"Mee goreng");
	food[4].price = 7.00;
	strcpy(food[5].name,"French fries");
	food[5].price = 5.90;
	strcpy(food[6].name,"Cheezy wedges");
	food[6].price = 6.90;

	switch(fCode) {
		case 1:
			//printf("here %s", food[0].name);
			return food[0];
			break;
		case 2:
			return food[1];
			break;
		case 3:
			return food[2];
			break;
		case 4:
			return food[3];
			break;
		case 5:
			return food[4];
			break;
		case 6:
			return food[5];
			break;
		case 7:
			return food[6];
			break;
		default:
			printf("Invalid Food Code. Please Try Again.\n");
	}
}

Item getDrinkInfo(int dCode) {
	Item drink[7];
	strcpy(drink[0].name, "Coca-cola");
	drink[0].price = 3.00;
	strcpy(drink[1].name, "Teh ice");
	drink[1].price = 2.50;
	strcpy(drink[2].name, "Teh o");
	drink[2].price = 2.00;
	strcpy(drink[3].name, "Limao ice");
	drink[3].price = 2.00;
	strcpy(drink[4].name, "Milo ice");
	drink[4].price = 3.50;
	strcpy(drink[5].name, "Sirap");
	drink[5].price = 2.60;
	strcpy(drink[6].name, "Mineral water");
	drink[6].price = 1.80;

	switch(dCode) {
		case 1:
			//printf("here %s", drink[0].name);
			return drink[0];
			break;
		case 2:
			return drink[1];
			break;
		case 3:
			return drink[2];
			break;
		case 4:
			return drink[3];
			break;
		case 5:
			return drink[4];
			break;
		case 6:
			return drink[5];
			break;
		case 7:
			return drink[6];
			break;
		default:
			printf("Invalid Drink Code. Please Try Again.\n");
	}
}

void addMore(){
	char choice;
	printf("Are you done ordering? (A = Addmore/ E = Enough): ");
	scanf(" %c", &choice);
	if(choice == 'A' ) {
		printf("Now you can continue add your order");
		mainpageorder();
	}
	else if(choice == 'E' || choice == 'e') {
		discountCoupon(); 
	}
}
void discountCoupon() {
	int couponOff;
	char pick, Y, N;
	printf("\nThanks For Patronage\n");
	printf("Are you having coupon? Enter( Y = yes/ N = no) :");
	scanf("%c", &pick);
	
	if(getchar() == 'Y') {
		printf("What kind of coupon do you have? 10%% Off or 20%% Off?\n");
		printf("Enter 10 if 10%% Off\n");
		printf("Enter 20 if 20%% Off\n");
		printf("Please enter type of your coupon : ");
		scanf("%d", &couponOff);
		printf("You get %d %% Off\n",couponOff);  
		
		if(couponOff == 10){
			discount = afterDiscount(total,couponOff);
			printf("\nAfter discount value: RM%.2f\n",discount);
		}
		else if(couponOff == 20){
			discount = afterDiscount(total,couponOff);
			printf("\nAfter discount value: RM%.2f\n",discount);
		}	
	}
	else(getchar() == 'N');{
		receipt();
	}
}


float calculatePrice(float itemPrice, float discount) 
{
	float discountPrice;
	discountPrice = itemPrice * discount;
	printf("%f",discountPrice);
	return itemPrice * discount;
}

float afterDiscount(float total,int discountpercentage)
{
	printf("Total %.2f, ",total);
	printf("Discount Percentage %d%%",discountpercentage);
	switch(discountpercentage){
		case 10:
			return total*0.9;
		case 20:
			return total*0.8;
	}
}

void receipt(){
	FILE *pFile;
	
	pFile = fopen ("printreceipt.txt","w");
	
	
	if( pFile == NULL)
	{
		printf("Error opening file. \n");
	}
	else
	{
	time_t tm;
    time(&tm);
	fprintf(pFile,"-------------------------------------\n");
	fprintf(pFile,"            MMU RESTAURANT           \n");
	fprintf(pFile,"-------------------------------------\n");
	fprintf(pFile,"        MMU Restaurant Sdn Bhd       \n");
	fprintf(pFile,"       Persiaran Multimedia,63100    \n");
	fprintf(pFile,"         Cyberjaya,Selangor          \n");
	fprintf(pFile,"               Malaysia              \n\n");
	fprintf(pFile,"Date/Time = %s", ctime(&tm));
	fprintf(pFile,"Phone Number: +603 3123 4564\n");
	fprintf(pFile,"Fax: +603 3123 7897\n");
	fprintf(pFile,"-------------------------------------\n");
	fprintf(pFile,"Dear %s,\n",guest);
	fprintf(pFile,"Table Number: %d\n",tNumber);
	total=0;
	fprintf(pFile,"No.\tItem Name\tQuantity\tPrice\tSubTotal\n");
	fprintf(pFile,"--------------------------------------------------------\n");
	
	for(int i=0; i< foodCount + 1; i++) {
		fprintf(pFile,"%d", i + 1);
		Item foodDetails = getFoodInfo(foodItemList[i]);
		fprintf(pFile,"\t%-10s", foodDetails.name);
		fprintf(pFile,"\t\tx%d", foodQuantityList[i]);
		fprintf(pFile,"\t%.2f", foodDetails.price);
		fprintf(pFile,"\t%.2f\n", foodDetails.price * foodQuantityList[i]);
		subtotal=foodDetails.price * foodQuantityList[i];
		total+=subtotal;
	}
	for(int j=0; j< drinkCount + 1; j++) {
		fprintf(pFile,"%d",j + 1);
		Item drinkDetails = getDrinkInfo(drinkItemList[j]);
		fprintf(pFile,"\t%-10s", drinkDetails.name);
		fprintf(pFile,"\t\tx%d", drinkQuantityList[j]);
		fprintf(pFile,"\t%.2f", drinkDetails.price);
		fprintf(pFile,"\t%.2f\n", drinkDetails.price * drinkQuantityList[j]);
		subtotal=drinkDetails.price * drinkQuantityList[j];
		total+=subtotal;
	}
	fprintf(pFile,"\n\t\t\t\t\t  Total    : RM%.2f\n",total);
	if(discount != 0){
	fprintf(pFile,"\t\t\t\tdiscount price  : RM%.2f\n",total-discount);
	fprintf(pFile,"\t\t\t\tAfter Discount  : RM%.2f\n\n",discount);
	}
	fprintf(pFile,"Thank you for your purchase\n");
}
	
	time_t tm;
    time(&tm);
	printf("-------------------------------------\n");
	printf("            MMU RESTAURANT           \n");
	printf("-------------------------------------\n");
	printf("        MMU Restaurant Sdn Bhd       \n");
	printf("       Persiaran Multimedia,63100    \n");
	printf("         Cyberjaya,Selangor          \n");
	printf("               Malaysia              \n\n");
	printf("Date/Time = %s", ctime(&tm));
	printf("Phone Number: +603 3123 4564\n");
	printf("Fax: +603 3123 7897\n");
	printf("-------------------------------------\n");
	printf("Dear %s,\n",guest);
	printf("Table Number: %d\n",tNumber);
	total=0;
	printf("No.\tItem Name\tQuantity\tPrice\tSubTotal\n");
	printf("--------------------------------------------------------\n");
	
	for(int i=0; i< foodCount + 1; i++) {
		printf("%d", i + 1);
		Item foodDetails = getFoodInfo(foodItemList[i]);
		printf("\t%-10s", foodDetails.name);
		printf("\t\tx%d", foodQuantityList[i]);
		printf("\t%.2f", foodDetails.price);
		printf("\t%.2f\n", foodDetails.price * foodQuantityList[i]);
		subtotal=foodDetails.price * foodQuantityList[i];
		total+=subtotal;
		
	}
	for(int j=0; j< drinkCount + 1; j++) {
		printf("%d",j + 1);
		Item drinkDetails = getDrinkInfo(drinkItemList[j]);
		printf("\t%-10s", drinkDetails.name);
		printf("\t\tx%d", drinkQuantityList[j]);
		printf("\t%.2f", drinkDetails.price);
		printf("\t%.2f\n", drinkDetails.price * drinkQuantityList[j]);
		subtotal=drinkDetails.price * drinkQuantityList[j];
		total+=subtotal;
	}
	printf("\n\t\t\t\t\tTotal   : RM%.2f\n",total);
	if(discount != 0){
	printf("\t\t\t\tdiscount price  : RM%.2f\n",total-discount);
	printf("\t\t\t\tAfter Discount  : RM%.2f\n\n",discount);
	}
	printf("Thank you for your purchase\n");
	printf("Enter q to quit program : ");
	scanf("%d");
}

void cusdetails(){
	printf("Please enter your table number : ");
	scanf("%d",&tNumber);
	printf("Enter your name : ");
	scanf("%s",&guest);
}