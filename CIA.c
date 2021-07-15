#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <string.h>
#include <ctype.h>
#define MAXINPUT 10000


int i,j,k,ind=0; //Iter variables
int totalItems;
/*---------------------------------------------------------------------------*/
// Structures

struct Customer{
	char name[MAXINPUT];
	int age;
	char mobnum[10];
	int purchase[MAXINPUT];
};

struct Customer * customers; //TODO: free it

void createCustomers(){
	customers = malloc((ind+1) * sizeof(customers));
	if (customers==NULL){
		printf("Malloc for customers failed");
	}
}

void growCustomers(){
	customers = (struct Customer *) realloc(customers, (ind+1)*sizeof(struct Customer));
}

/*---------------------------------------------------------------------------*/
// Support Functions

void printCurrentTime(){ // Prints Current Time
	time_t t;
    time(&t);
    printf("\nCurrent Time: %s\n",ctime(&t));
}

int verifyInt(){ //Verifies if input is int
	char n[MAXINPUT];
	scanf("%s", n);
	while(!atoi(n)){
		if (strcmp(n,"0")==0){
			return 0;
		}
		printf("Enter valid integer: ");
		scanf("%s", n);
	}
	return atoi(n);
}

int printMenu(){ // Prints the menu (HARDCODED) 
	char menu[6][MAXINPUT];
	strcpy(menu[0], "Exit");
	strcpy(menu[1], "Add data");
	strcpy(menu[2], "Most Visited Customer");
	strcpy(menu[3], "Most Purchased Item");
	strcpy(menu[4], "Most Purchased Item in given age range");
	strcpy(menu[5], "Age range for particular item");
	printf("\n~~~ MENU ~~~\n\n");
	for (i=0;i<6;i++){
		printf("%d. %s \n", i, menu[i]);
	}
	printf("\n~~~~~~~~~~~~\n");
	printf("\nEnter your choice: ");
	int choice=verifyInt();
	while(choice<0 || choice>5){
		printf("Enter valid choice: ");
		choice = verifyInt();
	}
	return choice;
}

void printList(char itemName[][MAXINPUT], int price[], int totalItems){
	printf("\n~~~ Available Items ~~~\n\n");
	for (i=0;i<totalItems;i++){
		printf("%d. %s %d\n", i+1, itemName[i], price[i]);
	}
}

int verifyAndUpdatePurchase(int totalItems){
	int iNum = verifyInt();
	if (iNum==0){
		return 0;
	}
	while(iNum<0 || iNum>totalItems){
		printf("Enter valid item number: ");
		iNum = verifyInt();
	}
	printf("Enter quantity: ");
	int iQuantity = verifyInt();
	int newQuantity = customers[ind].purchase[iNum-1]+iQuantity;
	char cQuantity = newQuantity;
	customers[ind].purchase[iNum-1] = cQuantity;
	return iNum;
}

int findQuote(int totalItems, int price[]){
	int quote = 0;
	for(i=0;i<totalItems;i++){
		quote+=price[i]*customers[ind].purchase[i];
	}
	return quote;
}

/* ------------------------------------------------------------------------------ */
// MAIN Functions

void addData(char itemName[][MAXINPUT], int price[], int totalItems){ //FUNCTION 1
	printf("\n~~~ ADD DATA ~~~\n\n");
	
	if (ind==0){
		createCustomers();
		printf("Customer array initially created successfully.\n");
	}
	
	if (ind!=0){
		growCustomers();	
		printf("Customer array Grown successfully.\n\n");
	}
	
	printCurrentTime();
	
	printf("Enter name: ");
	scanf("%s", customers[ind].name);
	
	printf("Enter age: ");
	customers[ind].age = verifyInt();
	
	for(i=0;i<MAXINPUT;i++){
		customers[ind].purchase[i]=0;
	}
	
	printCurrentTime();
	
	printList(itemName, price, totalItems);
	
	printf("Enter 0 to finish\n");
	printf("\n~~~~~~~~~~~~~~~~~~~~~~\n");
	
	int iNum=-1;
	while(iNum!=0){
		printf("Enter item number from the list: ");
		iNum = verifyAndUpdatePurchase(totalItems);
	}
	
	printf("\nTotal cost: %d", findQuote(totalItems, price));
	ind+=1;
	printf("\n~~~~~~~~~~~~~~~~~~\n\n");
}

void mostVisitedCustomer(){ // FUNCTION 2
	char cName[ind][MAXINPUT];
	int max=0,maxi=0;
	for (i=0;i<ind;i++){
		strcpy(cName[i],customers[i].name);
	}
	
	for(i=0;i<ind;i++){
		int count=0;
		for (j=i;j<ind;j++){
			if (strcmp(cName[i],cName[j])==0){
				count += 1;
			}
		}
		if (count>max){
			max=count;
			maxi=i;
		}
	}
	if(max>1){
        printf("\n\n~~ MOST VISITED CUSTOMER ~\n\nName: %s \n\n~~~~\n", cName[maxi]);
    }
    else{
        printf("\nAll Are Unique Customers. \n");
    }
}

void mostPurchasedItem(char itemName[][MAXINPUT]){ //FUNCTION 3
	int maxi=0, maxv=0;
	for (i=0;i<totalItems;i++){
		int count=0;
		for (j=0;j<ind;j++){
			count+=customers[j].purchase[i];
		}
		if (count>maxv){
			maxv=count;
			maxi=i;
		}
	}
	printf("\n~~~ Most Purchased Item ~~~\n\nItem Name: %s \nQuantity: %d \n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", itemName[maxi], maxv);
}

void mpiAgeRange(char itemName[][MAXINPUT]){ //FUNTION 4
	printf("\n\n~~~ Most Frequently Purchased Item in Given Age Range\n\n");
	int maxv=0, maxi=0;
	int maxage,minage;
	printf("Enter lower limit for age: ");
	minage = verifyInt();
	printf("Enter upper limit for age: ");
	maxage = verifyInt();
	while(minage>maxage){
		printf("Enter valid inputs. \n");
		printf("Enter lower limit for age: ");
		minage = verifyInt();
		printf("Enter upper limit for age: ");
		maxage = verifyInt();
	}
	for (i=0;i<totalItems;i++){
		int count = 0;
		for (j=0;j<ind;j++){
			if (customers[j].age>=minage && customers[j].age<=maxage){
				count+=customers[j].purchase[i];
			}
		}
		if (count>maxv){
			maxv=count;
			maxi=i;
		}
	}
	if(maxv>0){
		printf("Item name: %s \nItem quantity: %d", itemName[maxi], maxv);
	}
	else{
		printf("No customers in the given age range.");
	}
	printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void itemAgeRange(char itemName[][MAXINPUT], int price[], int totalItems){ // FUNCTION 5
	int maxage=0, minage=10000;
	printf("\n\n~~~ Age Range for Given Item ~~~\n\n");
	printList(itemName, price, totalItems);
	printf("Enter the item number: ");
	int iNum = verifyInt();
	while(iNum<1 || iNum>totalItems ){
		printf("Enter valid data.\n");
		printf("Enter the item number: ");
		iNum = verifyInt();
	}
	for (i=0;i<ind;i++){
		if(customers[i].purchase[iNum-1]){
			if (minage>customers[i].age){
				minage = customers[i].age;
			}
			if (maxage<customers[i].age){
				maxage = customers[i].age;
			}
		}
	}
	printf("\nMinimum age is: %d", minage);
	printf("\nMaximum age is: %d", maxage);
	printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

/*------------------------------------------------------------*/
int main(){
	printf("~~~~ Customer Interest Analysis ~~~~\n\n");
	
	char shopName[MAXINPUT];
	printf("\nEnter the shop name: ");
	scanf("%s", shopName);
	
	printf("\nEnter the total number of items in shop: ");
	totalItems=verifyInt();
	
	int price[totalItems];
	char itemName[totalItems][MAXINPUT];
	
	for(i=0;i<totalItems;i++){
		printf("\n");
		char iname[MAXINPUT];
		printf("Enter name of item %d : ", i+1);
		scanf("%s",iname);
		strcpy(itemName[i], iname);
		printf("Enter price of item %d : ", i+1);
		price[i]=verifyInt();
	}
	
	
	int choice=printMenu();
	while(choice!=0){
		if (choice==1){
			addData(itemName, price, totalItems);
		}
		if (choice==2){
			mostVisitedCustomer();
		}
		if (choice==3){
			mostPurchasedItem(itemName);
		}
		if (choice==4){
			mpiAgeRange(itemName);
		}
		if (choice==5){
			itemAgeRange(itemName, price, totalItems);
		}	
		choice=printMenu();
	}
	printf("\n~~~~ The END ~~~~");
	free(customers);
	return 0;
}
