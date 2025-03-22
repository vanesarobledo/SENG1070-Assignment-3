/*
* FILE          : Assignment3.cpp
* PROJECT       : SENG1070 Assignment 3: Array & Pointer Techniques with Bitwise Operations
* PROGRAMMER    : Vanesa Robledo
* FIRST VERSION : 2025-03-21
* DESCRIPTION   : This is a console-based cryptocurrency wallet manager. Users can add and view transactions,
				  apply transaction fees, find the highest transactions, swap transactions, and toggle transactions
				  as processed or refunded.
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "assignment3.h"

int main(void)
{
	// Initialize dynamic array
	Wallet* wallet = initializeArray();

	// Add Transaction
	addTransaction(wallet);

	printf("%f\n", wallet->transactions[0]);
	printf("%f\n", wallet->transactions[1]);
	printf("%f\n", wallet->transactions[2]);

	// Free memory & exit
	exit(wallet);
	
	return EXIT_SUCCESS;
}

// Functions

//
// FUNCTION     : initializeArray
// DESCRIPTION  : Dynamically allocates memory for an array
// PARAMETERS   : none
// RETURNS      : int* : Pointer to dynamic array
//
Wallet* initializeArray(void) {
	Wallet* array = (Wallet*)malloc(sizeof(Wallet));

	// Ensure memory is allocated
	if (array == NULL) {
		printf("Failed to allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	// Dynamically allocate array
	array->transactions = (float*)malloc(ARRAY_SIZE * sizeof(float));

	// Initialize size of array, -1 means empty
	array->size = EMPTY;

	return array;
}

//
// FUNCTION     : isEmpty
// DESCRIPTION  : Checks if size of array is 0 (i.e. size is not -1)
// PARAMETERS   : Wallet* wallet :	Pointer to struct containing dynamic array
// RETURNS      : bool
//
bool isEmpty(Wallet* wallet) {
	if (wallet != NULL) {
		return wallet->size == -1;
	}
	else {
		return true;
	}
}

//
// FUNCTION     : addTransaction
// DESCRIPTION  : Asks a user to to enter transaction amounts to store in dynamic array until they enter -1
// PARAMETERS   : Wallet* wallet :	Pointer to struct containing dynamic array
// RETURNS      : void
//
void addTransaction(Wallet* wallet) {
	float amount = 0.0; // Store amount of transaction

	// Ask user for amount of transaction and validate
	do {
		printf("Enter transaction amount (or -1 to stop): ");
		amount = getNum();
		if (amount == 0) { // Check for valid return from getNum
			printf("Please enter a valid number.\n");
		}
		else if (amount < 0 && amount != STOP) { // Check if negative
			printf("Please enter a positive number.\n");
		}
		else if (amount != STOP) { // Number is valid
			// Increase index of wallet
			wallet->transactions[++wallet->size] = amount;
		}
	} while (amount != STOP);

}

//
// FUNCTION     : displayTransactions
// DESCRIPTION  :
// PARAMETERS   : Wallet* wallet :	Pointer to struct containing dynamic array
// RETURNS      : void
//
//void displayTransactions(Wallet* wallet) {
//
//}

//
// FUNCTION     : applyTransactionFees
// DESCRIPTION  :
// PARAMETERS   : Wallet* wallet :	Pointer to struct containing dynamic array
// RETURNS      : void
//
//void applyTransactionFees(Wallet* wallet) {
//
//}

//
// FUNCTION     : findHighestTransaction
// DESCRIPTION  :
// PARAMETERS   : Wallet* wallet :	Pointer to struct containing dynamic array
// RETURNS      : void
//
//void findHighestTransaction(Wallet* wallet) {
//
//}

//
// FUNCTION     : swapTransactions
// DESCRIPTION  :
// PARAMETERS   : Wallet* wallet :	Pointer to struct containing dynamic array
// RETURNS      : void
//
//void swapTransactions(Wallet* wallet) {
//
//}

//
// FUNCTION     : toggleTransactionStatus
// DESCRIPTION  :
// PARAMETERS   : Wallet* wallet :	Pointer to struct containing dynamic array
// RETURNS      : void
//
//void toggleTransactionStatus(Wallet* wallet) {
//
//}

//
// FUNCTION     : exit
// DESCRIPTION  : Frees memory of dynamically allocated array
// PARAMETERS   : Wallet* wallet :	Pointer to struct containing dynamic array
// RETURNS      : void
//
void exit(Wallet* wallet) {
	if (wallet != NULL) {
		printf("Freeing dynamically allocated memory...\n");
		free(wallet->transactions);
		free(wallet);
	}
	exit(EXIT_SUCCESS);
}

//
// FUNCTION     : getNum
// DESCRIPTION  : Gets a float from the user - returns 0.0 if invalid
// PARAMETERS   : none
// RETURNS      : float
//
float getNum(void) {
	float num = 0.0; // Store float to return
	char input[INPUT_SIZE] = ""; // Buffer for user input
	char extraChar = '0'; // Store any extraneous input from user

	// Ask user for number
	fgets(input, sizeof(input), stdin);
	input[strlen(input) - 1] = '\0'; // Remove trailing newline character from input

	// Validate input - return 0.0 if invalid
	if (sscanf_s(input, "%f %c", &num, &extraChar, (unsigned int)sizeof(extraChar)) != 1) {
		return 0.0;
	}
	else {
		return num;
	}
}

//
// FUNCTION     : getIndex
// DESCRIPTION  : Gets an integer from the user - returns -1 if invalid
// PARAMETERS   : none
// RETURNS      : int
//
//int getIndex(void) {
//
//}

//
// FUNCTION     : swapNum
// DESCRIPTION  : Swaps the value of two numbers
// PARAMETERS   : int num1	:	The first number to swap
//				  int num2	:	The second number to swap
// RETURNS      : void
//
void swapNum(int num1, int num2) {
	num1 = num1 ^ num2;
	num2 = num2 ^ num1;
	num1 = num1 ^ num2;
}

//
// FUNCTION     : menu
// DESCRIPTION  : Prints the menu to the screen
// PARAMETERS   : none
// RETURNS      : void
//
void menu(void) {
	printf("Cryptocurrency Wallet");
	printf("1. Add a transaction");
	printf("2. Display all transactions");
	printf("3. Apply fee to all transactions");
	printf("4. Find highest transaction");
	printf("5. Swap transactions");
	printf("6. Toggle transaction status");
	printf("7. Exit");
}

//
// FUNCTION     : getMenuOperation
// DESCRIPTION  : Gets number from user for menu operation
// PARAMETERS   : int* operation	:	Pointer to menu operation
// RETURNS      : void
//
void getMenuOperation(int* operation) {
	char input[INPUT_SIZE] = ""; // Buffer to store input
	bool loopFlag = true; // Flag to loop getting a valid menu number
	const int kStart = 1; // First menu number

	// Ask user for menu number
	while (loopFlag) {
		printf("Enter your choice: ");
		fgets(input, sizeof(input), stdin);

		// If input is too large or not an integer
		if (strlen(input) > EXIT || sscanf_s(input, "%d", operation) == 0) {
			printf("Please enter a valid input.\n");
			continue;
		}

		// If integer is not a valid menu option
		if (!(*operation >= kStart && *operation < EXIT)) {
			printf("Please enter a valid menu number.\n");
			continue;
		}
		// Input is valid, break loop
		loopFlag = false;
	}
}