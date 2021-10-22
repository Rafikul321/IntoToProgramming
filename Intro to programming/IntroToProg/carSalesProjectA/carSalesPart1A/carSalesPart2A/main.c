// needed to allow Visual Studio to work with scanf()
#define _CRT_SECURE_NO_WARNINGS
// required to enable use of scanf() and printf()
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
// allow me to use sleep() function



// ||These are the constants that will be used in this program, they cannot change||
#define MENU_OPTION_VIEW_CARS '1'// if user chooses '1' MENU_OPTION_VIEWS_CARS will be performed
#define MENU_OPTION_BUY_CAR '2' // if user chooses '2' MENU_OPTION_BUY_CARS will be performed
#define MENU_OPTION_VIEW_SALES '3' // if user chooses '3' MENU_OPTION_VIEW_SALES will be performed
#define MENU_OPTION_EXIT '4' // if user chooses '4'MENU_OPTION_EXIT will be performed
#define TRUE 1 // this is for validating the users input, where true is correct and false is incorrect input
#define FALSE 0
#define MAX_SALES 50 // Whenever MAX_SALES is used, the value linked will be 50
//#define CSV_FILE "C:\UsersRafikulDocumentsIntroToProgcarSalesProjectA"
#define  CSV_FILE "C:\data.csv"
#define bool unsigned char






// ||These are the variables ||
char userChoice; // userChoice is defined so that switch can take place
// unsigned short is an interger type, range 0-65,535!
unsigned short correctInput = FALSE; // This is for validating the menu system
//carPrice is an array which hold car prices which ranges from £1500 to £10,000
int carPrice[10] = { 1500, 2000, 3500, 4500, 5000, 6000, 6500, 7000, 7500, 10000 };
int carStock[10] = { 0, 7, 12, 5, 4, 12, 24, 20, 12, 21 };
int carChoice, numberOfSales = 0, carChoice1;
char* carTypes[10] = { "Nissan", "Hyundai", "Mini","Kia ", "Fiat", "Ford","Toyota","Volkswagen"," BMW", "Mercedes" };
float totalSalesValue, totalPrice = 0;
float totalSalesAmountByType[10] = { 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 };
float totalSales[MAX_SALES];
char userName[MAX_SALES][201];
int carChoiceInASale[MAX_SALES];

// Files Variables & Constants
#define FILE_OPENED 0
#define FILE_CLOSED 1
#define FILE_ERROR 2
void removeClutter() {
	// this is only here to improve user experience... not essential but helpful
	system("cls");
}
//function to swap values, uses pointers as uses memory address to 'swap' values
void swapUnsignedShort(float* a, float* b) {
	unsigned short temp;
	// copy the value found at the pointer a's address into the newly created temp variable
	temp = *a;
	// copy the value found at the pointer a's address into the address represented by the pointer b
	*a = *b;
	// copy the value of the temp variable to the pointer b's address
	*b = temp;
}

// array to sort view sales array
void sortArraysByNumberOfCarsSoldPerSale() {
	
	// set up a loop that gives us an index "i" for accessing 
	


	for (int i = 0; i < numberOfSales - 1; i++) {

		for (int j = i + 1; j < numberOfSales; j++) {
			

				// check if the value at position i is less than the value at position j
				if (totalSalesAmountByType[i] < totalSalesAmountByType[j]) {
					// if so swap values
					swapUnsignedShort(&totalSalesAmountByType[i], &totalSalesAmountByType[j]);

					swapUnsignedShort(&carTypes[i], &carTypes[j]);

					char temp[201];
					strcpy(temp, userName[i]);
					// copy string from position j into position i
					strcpy(userName[i], userName[j]);
					// copy string from temp into position j
					strcpy(userName[j], temp);

				} 

			} 

		} 

	}





FILE * file;
unsigned char fileStatus = FILE_CLOSED;

FILE* createFile(char fileName[201]) {
	// open the file for writing
	file = fopen(fileName, "w");
	// then close it immediately if successful
	if (file != NULL) {
		fclose(file);
	}
	// return the pointer so that the success may be checked
	return file;
}

void openFile(char fileName[201], char mode[4]) {
	// open the file
	file = fopen(fileName, mode);

	
	if (file == NULL) {

		
		if (createFile(fileName) == NULL) {
			fileStatus = FILE_ERROR;
		}
		else {
			//file created
			openFile(fileName, mode);
		}

	}
	// otherwise, all OK
	else {
		fileStatus = FILE_OPENED;
	}
}

void closeFile() {
	// only attempt to close the file if it's already open
	if (fileStatus == FILE_OPENED) {
		fclose(file);
		fileStatus = FILE_CLOSED;
	}
}

void readDataFromFile() {
	// required to keep track on lines in the file
	int lineCounter = 0;

	// (1) is used as a infinite loop, will only end once we have read the whole file
	while (1) {
		
		char userNameValue[201] = "";
		
		int scanResult = fscanf(
			file, // the file stream
			"%f,%[^\n]s",&totalSalesValue,&userNameValue); // format types

		
		if (scanResult == EOF) {
			// loop is stopped if we reach EOF (end of file)
			break;
		}

		// add data that were read above into the correct arrays
		totalSales[lineCounter] = totalSalesValue;

		
		// strcpy is used as userName is a string
		strcpy(userName[lineCounter], userNameValue);

		// increment line counter
		lineCounter++;
	}

	// make sure the numberOfSales variable is also aware of how many sales are available after the above operation
	numberOfSales = lineCounter;
}
void getDataFromFile() {
	openFile(CSV_FILE, "r");

	if (fileStatus == FILE_OPENED) {
		readDataFromFile(); // calls this function to read data
	}
	else if (fileStatus == FILE_ERROR) {
		printf("\n\nThere was error with the file"); // lets us know whether the file was succesful or not
		
	}
	closeFile();
}
void writeDataToFile() {

	for (int i = 0; i < numberOfSales; i++) {

		// this string will be built up bit by bit before being written to the opened file
		char line[201];
		// this string will contain the converted int value
		char data[50];

		_itoa((int)totalSales[i], data, 10);
		strcpy(line, data);
		strcat(line, ","); 	// add comma to seperate values

		strcat(line, userName[i]);
	
			fprintf(file, line);

			// only add a newline character if we're not yet writing the very last
			// line in the file
			if (i < numberOfSales - 1) {
				fprintf(file, "\n");
			}
		}
	}

void saveDataToFile() {
	openFile(CSV_FILE, "w");

	if (fileStatus == FILE_OPENED) {
		writeDataToFile();
	}
	else if (fileStatus == FILE_ERROR) {
		printf("\n\nThere was an error with the file");
		
	}

	closeFile();
}



//function to view cars
void menu_viewCars() {
	for (int i = 0; i < 10; i++) {
		// loop to print out the carPrice array, allows the user to know each price of the cars
		printf("We have a %s. The cost is %d GBP \n\n Stock Level: %d \n\n", carTypes[i], carPrice[i], carStock[i]);
	}
}

//function to buy car
int menu_buyCars() {



	printf("Please enter your full name:\n");
	scanf("\n%[^\n]s", &userName[numberOfSales]);
	// this is storing customer name and position in the array that been allocated, each sale can be viewed effectively
	
	printf("Hello loyal customer :)\n\nThis is the perfect place for you to purchase your car! \n\nThese are the cars we sell:\n\n");
	Sleep(1000);// the number inside the bracket is set in milliseconds

	for (int i = 0; i < 10; i++) {
		// loop to print out the carPrice array, allows the user to know each price of the cars
		printf("car %d is a %s. The cost is %d GBP \n\n Stock Level: %d \n\n", i + 1, carTypes[i], carPrice[i], carStock[i]);
	}
	while (1) {
		printf("Which car would you like to purchase today(1-10)?");
		scanf("%d", &carChoice);// remembering what car they have chosen
		getchar();
		if (carChoice < 1 || carChoice > 10) {
			printf("\nThis is not a valid car :), please double check your input is between 1 - 10!\n");
			return; // enables user to start again
		}
		else
		{
			break;
		}
		break;
	}

	carChoice1 = carChoice - 1; // minus 1 as the index value starts at zero 
	// check if we have at least 1 car available
	if (carStock[carChoice1] > 1) { // if the car the user wishes to purchase is greater than 1, we have it in stock

	}
	else {
		printf("Unfortunately we don't have this model in stock as this current time\nWe usually recieve more intakes of stock the first of every month.\n"); // as we do not have at least 1 car, it is not in stock to purchase
		Sleep(2000); // gives reader time to read the message
		return; // returns the user to the main menu as we cannot process the car they wish to purchase 
	}

	carStock[carChoice1] = carStock[carChoice1] - 1; // this updates the stock levels, again required to minus 1 due to index value starting at 0

	printf("Please wait a few seconds while we process this... ");
	Sleep(1000);
	printf("\n\nCongratulations!, you have purchased your %s at %d GBP \n\n", carTypes[carChoice - 1], carPrice[carChoice - 1]);
	// outputing the price of the car they have bought

	carChoiceInASale[numberOfSales] = carChoice1;

	totalPrice = carPrice[carChoice - 1];
	// record the price in the totalSales array
	totalSales[numberOfSales] = totalPrice;
	
	numberOfSales++;
	// adding to the counter to help view sales

	return;


}
// this function shows the user the car models and how many we have in stock, also shows the total sales for each car model
// this will be called in menu_ViewSales 
void viewSalesTotalCarModel() {
	
	float totalSalesAmountByType[10] = { 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}; // setting to zero so sales are accurate

	sortArraysByNumberOfCarsSoldPerSale(); // this is called to sort arrays
	for (int model = 0; model < 10; model++) {
		printf("\nThere are %d cars remaining of type %s.\n", carStock[model], carTypes[model]);  // shows user stock levels
		
		
		for (int i = 0; i < numberOfSales; i++) {

			if (model == carChoiceInASale[i])
				totalSalesAmountByType[model] += totalSales[i];
		}		 printf("\nSales for model %s amount to %f. \n", carTypes[model], totalSalesAmountByType[model]); // shows user the total sales of each car type

	}

}

//function to view sales
void menu_viewSales() {


	totalSalesValue = 0;

	for (int i = 0; i < numberOfSales; i++) {
		// user can easily see each sale that has gone through with customer name and which car they bought
		printf("Sale : %d | Sale Amount: %f | Customer Name: %s \n ", i, totalSales[i], userName[i]);
		// also calculate the total sales value
		totalSalesValue += totalSales[i];

	}
	// Shows the overall total sales from the cars
	printf("\n %hd car(s) have been sold with a total value of %f GBP.\n", numberOfSales, totalSalesValue);
	viewSalesTotalCarModel();

}

void menu_Exit() {
	printf("\n\nThank you for using this cars Sales program, \nIf you have any questions please do not hesitate to email us at 'RafCarsSales@live.co.uk' Good-bye!");
	// thanking the user and leaving a very real email for them to use : )
	saveDataToFile(); // ensures data is not lost 
	Sleep(2000);
}

void show_Menu() {
	printf("Menu:\n");
	printf("Choose 1: To view the cars\n");
	printf("Choose 2: To buy a car\n");
	printf("Choose 3: To view sales (previous and present sales data) \n");
	printf("Choose 4: To exit the program :(\n\n");
}




// actual program !!
int main() {
	getDataFromFile();


	printf("Welcome to Rafs car sale ;) !!\n\n"); // introduces user to program

	do {
		// Menu System is shown here, three options: 1 to view cars, 2 to buy cars and 3 to view sales and 4 exit 
		show_Menu();

		correctInput = FALSE;
		// Assuming the data is entered incorrectly
		do {
			// ask user to choose an option
			printf("Please choose one an option (1-4): ");
			scanf("%c", &userChoice);

			// user choice is being used here to ensure the programme knows which block of code to run
			getchar();
			removeClutter();
			if (userChoice == MENU_OPTION_BUY_CAR || userChoice == MENU_OPTION_VIEW_SALES || userChoice == MENU_OPTION_EXIT || userChoice == MENU_OPTION_VIEW_CARS) {
				correctInput = TRUE;
				break;
			}
			else {
				printf("\n Sorry,this is an invalid respone, Please try again :)\n");
				show_Menu();
			}

			// This loop will continute to run until the condition ( while user input is accurate) is met
		} while (correctInput != TRUE);

		// for the user's benefit...
		printf("\n\n");

		// this is where each block of code is written, the code that runs is dependant on the users input
		switch (userChoice) {
			// If user inputs 1 this block of code will run

		case MENU_OPTION_VIEW_CARS:
			menu_viewCars();
			break;

		case MENU_OPTION_BUY_CAR:
			menu_buyCars();
			break;

		case MENU_OPTION_VIEW_SALES:
			menu_viewSales();
			break;

		case MENU_OPTION_EXIT:
			menu_Exit();
			break;
		}

	} while (userChoice != MENU_OPTION_EXIT);

	printf("\n\n Thank you for your time!\n\n");

	return 0;
}
// Program is finished.