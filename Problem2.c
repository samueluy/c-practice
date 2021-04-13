#include <stdio.h>
#include <string.h>

#define STRING_SIZE 256
#define MAX 256

struct stock{
	char name[STRING_SIZE];
	float price;
	int available;
};

struct stockholder{
	char name[STRING_SIZE];
	struct stock stock[MAX];
};

int validInput(int nMaxInput){ // Asks the user for input till valid (use for integer-navigated menus)
	int nInput=0, nValid=0;\
	
	printf("Enter: ");
	scanf("%d", &nInput);
	while(!nValid){
		if(nInput > 0 && nInput <= nMaxInput)
			nValid=1;
		else{
		printf("Invalid!\nPlease enter a valid input: ");
		getc(stdin);
		scanf("%d", &nInput);
		}
	}
	
	return nInput;
}

void displayStocks(int max, struct stock stock[]){
	int i;

	printf("Stocks: \n");

	for(i=0; i<max; i++){
		printf("[%d] %s; PhP %f; %d\n", i+1, stock[i].name, stock[i].price, stock[i].available);
	}
}
int mainMenu(){
    int nInput;

    printf("[1] Add a stockholder\n");
    printf("[2] Add a stock\n");
    printf("[3] Record a stock purchase\n");
    printf("[4] Change stock price\n");
    printf("[5] Increase stock\n");
    printf("[6] Display all stocks\n");
    printf("[7] Display all stockholders\n");
    printf("[8] Quit\n");

    nInput = validInput(8);
    return nInput;
}

int main(void){

	int mainMenuSelection=0, exitProgram=0; // navigation
	int selectStockHolder=0, selectStock=0, selectQuantity=0; // selection
	float fInput; // price
	int nInput; // number inputs
	int holderNumber=0, stockNumber=0; // default counters
	struct stockholder person[MAX];
	struct stock stock[MAX];

    while(!exitProgram){
        mainMenuSelection = mainMenu();
		switch(mainMenuSelection){
			case 1: printf("Enter stockholder name: ");
					getc(stdin);
					fgets(person[holderNumber].name, STRING_SIZE, stdin);
					holderNumber++;
					break;

			case 2: printf("Enter stock name: ");
					getc(stdin);
					fgets(stock[stockNumber].name, STRING_SIZE, stdin);
					printf("Enter stock price: ");
					scanf("%f", &stock[stockNumber].price);
					printf("Enter available stock: ");
					scanf("%d", &stock[stockNumber].available);
					stockNumber++;
					break;

			case 3: printf("Enter stockholder number: ");
					scanf("%d", &selectStockHolder);
					printf("Enter stock number: ");
					scanf("%d", &selectStock);
					printf("Enter quantity: ");
					scanf("%d", &selectQuantity);

					break;

			case 4: printf("Enter stock number: ");
					scanf("%d", &selectStock);
					printf("Enter new price: ");
					scanf("%f", &fInput);
					stock[selectStock].price = nInput;
					break;

			case 5: printf("Enter stock number: ");
					scanf("%d", &selectStock);
					printf("Enter new quantity: ");
					scanf("%d", &nInput);
					stock[selectStock].available = nInput;
					break;
			
			case 6: //displayStocks(stockNumber, stock);
					break;
		}
    }

    return 0;
}