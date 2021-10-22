// needed to allow Visual Studio to work with scanf()
#define _CRT_SECURE_NO_WARNINGS
// required to enable use of scanf() and printf()
#include <stdio.h>
#include <string.h>
#include <windows.h>
// allow me to use sleep() function



// ||These are the constants that will be used in this program, they cannot change||
#define MENU_OPTION_BUY_TICKET '1' // if use chooses '1' MENU_OPTION_BUY_TICKET will be performed
#define MENU_OPTION_VIEW_SALES '2' // if use chooses '2' MENU_OPTION_VIEW_SALES will be performed
#define MENU_OPTION_EXIT '3' // if use chooses '3'MENU_OPTION_EXIT will be performed
#define TRUE 1 // this is for validating the users input, where true is correct and false is incorrect input
#define FALSE 0
#define MAX_SALES 10 // Whenever MAX_SALES is used, the value linked will be 10





// ||These are the variables ||
char userChoice; // userChoice is defined so that switch can take place
// unsigned short is an interger type, range 0-65,535!
unsigned short correctInput = FALSE; // This is for validated the menu system
//carPrice is an array which hold car prices which ranges from £1500 to £10,000
int carPrice[10] = { 1500, 2000, 3500, 4500, 5000, 6000, 6500, 7000, 7500, 10000 }, carChoice, numberOfSales = 0;
// First is the array for the prices of 10 cars, numberOfSales will be used as a data counter
float totalSalesValue, totalPrice = 0;
float totalSales[MAX_SALES];
char userName[MAX_SALES][201];
//another array but this is for consumer names, no more than 200 characters ( for array size always -1)


//function to buy car
void menu_BuyCars() {



	printf("Please enter your full name:\n");
	scanf("\n%[^\n]s", &userName[numberOfSales]);
	// this is storing customer name and position in the array that been allocated, each sale can be viewed effectively
	getchar();
	printf("Hello loyal customer :)\n\nThis is the perfect place for you to purchase your car! \n\nThese are the cars that we have available for you today:\n\n");
	Sleep(1000);// the number inside the bracket is set in milliseconds

	for (int i = 0; i < 10; i++) {
		// loop to print out the carPrice array, allows the user to know each price of the cars
		printf("car %d cost %d GBP \n\n", i + 1, carPrice[i]);
	}

	printf("Which car would you like to purchase today(1-10)?");
	scanf("%d", &carChoice);// remembering what car they have chosen
	getchar();
	printf("Please wait a few seconds while we process this... ");
	Sleep(2000);
	printf("\n\nCongratulations!, you have purchased your new car at %d GBP \n\n", carPrice[carChoice - 1]);
	// outputing the price of the car they have bought

	totalPrice = carPrice[carChoice - 1];
	// record the price in the totalSales array
	totalSales[numberOfSales] = totalPrice;
	numberOfSales++;
	// adding to the counter to help view sales
	return;
}


//function to view sales
void menu_ViewSales() {
	// value set to 0 to ensure sales are accurate
	totalSalesValue = 0;

	// set up a for loop that will execute the block of code as many times as indicated by the numberOfSales variable's value
	for (int i = 0; i < numberOfSales; i++) {

		// user can easily see each sale that has gone through with customer name and which car they bought
		printf("Sale : %d | Sale Amount: %f | Customer Name: %s\n", i, totalSales[i], userName[i]);

		// also calculate the total sales value
		totalSalesValue += totalSales[i];

	}

	// Shows the overall total sales from the cars
	printf("\n%hd car(s) have been sold with a total value of %f GBP.\n", numberOfSales, totalSalesValue);
	return;
}
// function to exit program
void menu_Exit() {
	printf("\n\nThank you for using this cars Sales program, \nIf you have any questions please do not hesitate to email us at 'RafCarsSales@live.co.uk' Good-bye!");
	// thanking the user and leaving a very real email for them to use : )
	Sleep(4000);
	return;
}



// actual program !!
int main() {
	// introduces user to program
	printf("Welcome to Rafs car sale ;) !!\n\n");

	do {
		// Menu System is shown here, three options: 1 to buy cars, 2 to view sales and 3 to exit program
		printf("Menu:\n");
		printf("Choose 1: To buy a car\n");
		printf("Choose 2: To view sales\n");
		printf("Chosse 3: To exit the program :(\n\n");
		correctInput = FALSE;
		// Assuming the data is entered incorrectly
		do {
			// ask user to choose an option
			printf("Please choose one an option (1-3): ");
			scanf("%c", &userChoice);
			// user choice is being used here to ensure the programme knows which block of code to run
			getchar();
			system("cls");

			if (userChoice == MENU_OPTION_BUY_TICKET || userChoice == MENU_OPTION_VIEW_SALES || userChoice == MENU_OPTION_EXIT) {
				correctInput = TRUE;
				break;
			}
			else {
				printf("\n Sorry,this is an invalid respone, Please try again :)\n");
			}

			// This loop will continute to run until the condition ( while user input is accurate) is met
		} while (correctInput != TRUE);

		// for the user's benefit...
		printf("\n\n");


		// this is where each block of code is written, the code that runs is dependant on the users input
		switch (userChoice) {
			// If user inputs 1 this block of code will run
		case MENU_OPTION_BUY_TICKET:
			menu_BuyCars();
			break;

		case MENU_OPTION_VIEW_SALES:
			menu_ViewSales();
			break;



		case MENU_OPTION_EXIT:
			menu_Exit();
			break;
		}

	} while (userChoice != MENU_OPTION_EXIT);

	printf("\n\n Thank you for your time!\n\n");

	
}
// Program is finished