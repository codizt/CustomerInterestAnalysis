#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <string.h>
#include <ctype.h>
#include<stdbool.h>
#define MAXINPUT 100


int i,j,k; //Iter variables

int ind=0; //Global index

/* --------------------------------------------------------------------------- */
// Structures

struct Customer{
	char name[MAXINPUT];
	int age;
	int purchase[MAXINPUT];
	int total;
};

struct Customer * customers;

void createCustomers(){
	customers = malloc((ind+1) * sizeof(customers));
	if (customers==NULL){
		printf("\nMalloc for customers failed\n");
	}
}

void growCustomers(){
	customers = (struct Customer *) realloc(customers, (ind+1)*sizeof(struct Customer));
	if (customers==NULL){
		printf("\nRealloc for customers failed\n");
	}
}

/* --------------------------------------------------------------------------- */
// Support Functions

void printCurrentTime(){ // Prints Current Time
	time_t t;
    time(&t);
    printf("\nCurrent Time: %s\n",ctime(&t));
}

int verifyInt(){ //Verifies if input is int
	char n[MAXINPUT];
	bool condition = true;
	while(condition){
		scanf("%s", n);
		condition = false;
		for(i=0;i<strlen(n);i++){
			char ch = n[i];
			if (!(isdigit(ch))){
				condition = true;
				printf("Enter valid input: ");
				break;
			}
		}
	}
	return atoi(n);
}

int printMenu(){ // Prints the menu (HARDCODED) 
	char menu[9][MAXINPUT];
	strcpy(menu[0], "Exit");
	strcpy(menu[1], "Add data");
	strcpy(menu[2], "Most Visited Customer");
	strcpy(menu[3], "Most Purchased Item");
	strcpy(menu[4], "Most Purchased Item in given age range");
	strcpy(menu[5], "Age range for particular item");
	strcpy(menu[6], "Statistics on data");
	strcpy(menu[7], "Display data");
	strcpy(menu[8], "Add random data");
	printf("\n~~ MENU ~~\n\n");
	for (i=0;i<9;i++){
		printf("%d. %s \n", i, menu[i]);
	}
	printf("\n~~~~\n");
	printf("\nEnter your choice: ");
	int choice=verifyInt();
	while(choice<0 || choice>8){
		printf("Enter valid choice: ");
		choice = verifyInt();
	}
	return choice;
}

void printList(char itemName[][MAXINPUT], int price[], int totalItems){
	printf("\n~~ Available Items ~~\n\n");
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
	
	customers[ind].purchase[iNum-1] = newQuantity;
	return iNum;
}

int findQuote(int totalItems, int price[]){
	int quote = 0;
	for(i=0;i<totalItems;i++){
		quote+=price[i]*customers[ind].purchase[i];
	}
	return quote;
}

void ageStats(int totalItems){
	int mode=0, range=0;
	float median=0, mean=0;
	
	int ageArray[ind];
	for(i=0;i<ind;i++){
		ageArray[i]=customers[i].age;
	}
	
	int temp;
    for (i = 0; i < ind; i++){
        for (j = i + 1; j < ind; j++){
        	if (ageArray[i] > ageArray[j]){
                    temp =  ageArray[i];
                    ageArray[i] = ageArray[j];
                    ageArray[j] = temp;
            }
       }
    }
    printf("\nSorted data: \n");
    for (i=0;i<ind;i++){
    	printf("%d\t", ageArray[i]);
	}
	
	for (i=0;i<ind;i++){
		mean+=ageArray[i];
	}
	mean=mean/ind;
	
    if (ind%2==0){
    	median = (ageArray[ind/2]+ageArray[(ind/2)-1])/2.0;
	}
	else{
		median = ageArray[ind/2];
	}
	
	int maxv=0, maxi=0;
	for (i=0;i<ind;i++){
		int aCount = 0;
		for (j=i;j<ind;j++){
			if (ageArray[i]==ageArray[j]){
				aCount+=1;
			}
		}
		if (maxv<aCount){
			maxv=aCount;
			maxi=i;
		}
	}
	mode = ageArray[maxi];
	printf("\n\nMean is: %.2f", mean);
	printf("\nMedian is: %.2f", median);
	if(maxv==1){
		printf("\nMode is: None");
	}
	else{
		printf("\nMode is: %d ", mode);
	}
	printf("\nRange is: %d\n", ageArray[ind-1]-ageArray[0]);
}

void quoteStats(int totalItems){
	int mode=0, range=0;
	float median=0, mean=0;
	
	int totalArray[ind];
	for(i=0;i<ind;i++){
		totalArray[i]=customers[i].total;
	}
	
	int temp;
    for (i = 0; i < ind; i++){
        for (j = i + 1; j < ind; j++){
        	if (totalArray[i] > totalArray[j]){
                    temp =  totalArray[i];
                    totalArray[i] = totalArray[j];
                    totalArray[j] = temp;
            }
       }
    }
    
    printf("\nSorted data: \n");
    for (i=0;i<ind;i++){
    	printf("%d\t", totalArray[i]);
	}
	
	for (i=0;i<ind;i++){
		mean+=totalArray[i];
	}
	mean=mean/ind;
	
    if (ind%2==0){
    	median = (totalArray[ind/2]+totalArray[(ind/2)-1])/2.0;
	}
	else{
		median = totalArray[ind/2];
	}
	
	int maxv=0, maxi=0;
	for (i=0;i<ind;i++){
		int aCount = 0;
		for (j=i;j<ind;j++){
			if (totalArray[i]==totalArray[j]){
				aCount+=1;
			}
		}
		if (maxv<aCount){
			maxv=aCount;
			maxi=i;
		}
	}
	mode = totalArray[maxi];
	printf("\n\nMean is: %.2f", mean);
	printf("\nMedian is: %.2f", median);
	if(maxv<2){
		printf("\nMode is: None");
	}
	else{
		printf("\nMode is: %d", mode);
	}
	printf("\nRange is: %d\n", totalArray[ind-1]-totalArray[0]);
}

void purchaseStats(char itemName[][MAXINPUT], int totalItems){
	for (k=0;k<totalItems;k++){
		printf("\n~~ %s ~~\n", itemName[k]);
		int mode=0, range=0;
		float median=0, mean=0;
	
		int itemArray[ind];
		for(i=0;i<ind;i++){
			itemArray[i]=customers[i].purchase[k];
		}
		
		int temp;
    	for (i = 0; i < ind; i++){
    	    for (j = i + 1; j < ind; j++){
        		if (itemArray[i] > itemArray[j]){
                    temp =  itemArray[i];
                    itemArray[i] = itemArray[j];
                    itemArray[j] = temp;
            	}
       		}
    	}
    	printf("\nSorted data: \n");
    	for (i=0;i<ind;i++){
    		printf("%d\t", itemArray[i]);
		}
	
		for (i=0;i<ind;i++){
			mean+=itemArray[i];
		}
		mean=mean/ind;
		
    	if (ind%2==0){
    		median = (itemArray[ind/2]+itemArray[(ind/2)-1])/2.0;
		}
		else{
			median = itemArray[ind/2];
		}
	
		int maxv=0, maxi=0;
		for (i=0;i<ind;i++){
			int aCount = 0;
			for (j=i;j<ind;j++){
				if (itemArray[i]==itemArray[j]){
					aCount+=1;
				}
			}
			if (maxv<aCount){
				maxv=aCount;
				maxi=i;
			}
		}
		mode = itemArray[maxi];
		printf("\n\nMean is: %.2f", mean);
		printf("\nMedian is: %.2f", median);
		if(maxv<1){
			printf("\nMode is: None");
		}
		else{
			printf("\nMode is: %d", mode);
		}
		printf("\nRange is: %d\n", itemArray[ind-1]-itemArray[0]);
	}	
}

int randBtwn(int lower, int upper){
	int num = (rand() % (upper - lower + 1)) + lower;
	return num;
}

void addRandom(int ageLow, int ageUp, int pUp, int totalItems, int price[]){
	if (ind==0){
		createCustomers();
	}
	else{
		growCustomers();
	}
	int x =  randBtwn(10,100);
	sprintf(customers[ind].name,"random-%d",x);
	customers[ind].age = randBtwn(ageLow, ageUp);
	
	for(i=0;i<MAXINPUT;i++){
		customers[ind].purchase[i]=0;
	}
	
	int rChoice=randBtwn(1,totalItems);
	while(rChoice!=0){
		int a = randBtwn(1, pUp);
		if ((customers[ind].purchase[rChoice-1] + a)<pUp){
			customers[ind].purchase[rChoice-1] += a;	
		}
		rChoice = randBtwn(0, totalItems);
	}
	
	customers[ind].total = findQuote(totalItems, price);
	
	ind+=1;
}

/* ------------------------------------------------------------------------------ */
// MAIN Functions

void addData(char itemName[][MAXINPUT], int price[], int totalItems){ //FUNCTION 1
	printf("\n~~ ADD DATA ~~\n\n");
	
	if (ind<=0){
		createCustomers();
	}
	else{
		growCustomers();
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
	printf("\n~~~~\n");
	
	int iNum=-1;
	while(iNum!=0){
		printf("Enter item number from the list: ");
		iNum = verifyAndUpdatePurchase(totalItems);
	}
	customers[ind].total = findQuote(totalItems, price);
	printf("\nTotal cost: %d", customers[ind].total);
	ind+=1;
	printf("\n~~~~~~~~~~~~~\n\n");
}

void mostVisitedCustomer(){ // FUNCTION 2
	if(ind==0){
		printf("\nEnter data first \n");
		return;
	}
	char cName[ind][MAXINPUT], freq[ind];
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
        printf("\n\n~~ MOST VISITED CUSTOMER \n\nName: %s \n\n~\n", cName[maxi]);
    }
    else{
        printf("\nAll Are Unique Customers. \n");
    }
}

void mostPurchasedItem(char itemName[][MAXINPUT], int totalItems){ //FUNCTION 3
	if(ind==0){
		printf("\nEnter data first \n");
		return;
	}
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
	printf("\n~~ Most Purchased Item \n\nItem Name: %s \nQuantity: %d \n\n~~~~\n", itemName[maxi], maxv);
}

void mpiAgeRange(char itemName[][MAXINPUT],int totalItems){ //FUNTION 4
	if(ind==0){
		printf("\nEnter data first \n");
		return;
	}
	printf("\n\n~~ Most Frequently Purchased Item in Given Age Range ~~\n\n");
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
	printf("\n\n~~~~~~~\n");
}

void itemAgeRange(char itemName[][MAXINPUT], int price[], int totalItems){ // FUNCTION 5
	if(ind==0){
		printf("\nEnter data first \n");
		return;
	}
	int maxage=0, minage=10000;
	printf("\n\n~~ Age Range for Given Item ~~\n\n");
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
	printf("\n\n~~~~~\n");
}

void stats(char itemName[][MAXINPUT],int totalItems,int price[]){ // FUNCTION 6
	if(ind==0){
		printf("\nEnter data first \n");
		return;
	}
	
	printf("\n\n~~ Statistics ~~\n\n");
	
	printf("~ MENU ~\n\n1. Age statistics\n2. Quote statistics\n3. Purchase statistics\n\n");
	
	printf("Enter your choice: ");
	int sChoice = verifyInt();
	while(sChoice<1 || sChoice>3){
		printf("Enter valid choice: ");
		sChoice = verifyInt();
	}
	if (sChoice==1){
		ageStats(totalItems);
	}
	if (sChoice==2){
		quoteStats(totalItems);
	}
	if (sChoice==3){
		purchaseStats(itemName, totalItems);
	}
}

void displayData(char itemName[][MAXINPUT], int totalItems){ //FUNCTION 7
	if(ind==0){
		printf("\nEnter data first \n");
		return;
	}
	printf("\n\n~~ DISPLAY DATA ~~\n");
	for(i=0;i<ind;i++){
		printf("\nName: %s", customers[i].name);
		printf("   |  Age: %d   |   Purchases: ", customers[i].age);
		for(j=0;j<totalItems;j++){
			printf("%d ", customers[i].purchase[j]);
		}
		printf("  |  Total: %d", customers[i].total);
	}
	printf("\n\n~~~~~~~~~\n");
}

void addRandomDataHandler(char itemName[][MAXINPUT], int totalItems, int price[]){ //FUNCTION 8
	printf("\n\n~~ ADD RANDOM DATA ~~\n");
	printf("\nEnter the number of entries: ");
	int num = verifyInt();
	printf("\nEnter lower limit of age: ");
	int ageLow = verifyInt();
	printf("\nEnter upper limit of age: ");
	int ageUp = verifyInt();
	while(ageLow>ageUp){
		printf("\nEnter valid Data.\n");
		printf("\nEnter lower limit of age: ");
		ageLow = verifyInt();
		printf("\nEnter upper limit of age: ");
		ageUp = verifyInt();
	}
	printf("\nEnter upper limit for purchases: ");
	int pUp=verifyInt();
	int l;
	for (l=0;l<num;l++){
		addRandom(ageLow, ageUp, pUp, totalItems, price);
	}
}

/* ------------------------------------------------------------ */
int main(){
	printf("\n~~~~ Customer Interest Analysis ~~~~\n");
	
	char shopName[MAXINPUT];
	printf("\nEnter the shop name: ");
	scanf("%s", shopName);
	
	printf("\nEnter the total number of items in shop: ");
	int totalItems=verifyInt();
	
	int price[totalItems];
	char itemName[totalItems][MAXINPUT];
	
	for (i=0;i<totalItems;i++){
		strcpy(itemName[i],"");
	}
	
	for(k=0;k<totalItems;k++){
		printf("\nEnter name of item %d : ", k+1);
		scanf("%s",itemName[k]);
		printf("Enter price of item %d : ", k+1);
		price[k]=verifyInt();
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
			mostPurchasedItem(itemName, totalItems);
		}
		if (choice==4){
			mpiAgeRange(itemName, totalItems);
		}
		if (choice==5){
			itemAgeRange(itemName, price, totalItems);
		}
		if (choice==6){
			stats(itemName, totalItems, price);
		}
		if (choice==7){
			displayData(itemName, totalItems);
		}
		if (choice==8){
			addRandomDataHandler(itemName, totalItems, price);
		}
		choice=printMenu();
	}
	printf("\n~~ The END ~~");
	free(customers);
	return 0;
}
