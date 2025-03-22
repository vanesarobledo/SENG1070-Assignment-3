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
	int* wallet = (int*)malloc(ARRAY_SIZE*sizeof(int));

	// Ensure memory is allocated
	if (wallet == NULL) {
		printf("Failed to allocate memory");
		return EXIT_FAILURE;
	}

	// Add Transaction

	return EXIT_SUCCESS;
}

// Functions

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

//
// FUNCTION     : addTransaction
// DESCRIPTION  : Asks a user to 
// PARAMETERS   : int* arr	:	Pointer to dynamic array
// RETURNS      : void
//
void addTransaction(int* arr) {

}

//
// FUNCTION     : displayTransactions
// DESCRIPTION  :
// PARAMETERS   : int* arr	:	Pointer to dynamic array
// RETURNS      : void
//
void displayTransactions(int* arr) {

}

//
// FUNCTION     : applyTransactionFees
// DESCRIPTION  :
// PARAMETERS   : int* arr	:	Pointer to dynamic array
// RETURNS      : void
//
void applyTransactionFees(int* arr) {

}

//
// FUNCTION     : findHighestTransaction
// DESCRIPTION  :
// PARAMETERS   : int* arr	:	Pointer to dynamic array
// RETURNS      : void
//
void findHighestTransaction(int* arr) {

}

//
// FUNCTION     : swapTransactions
// DESCRIPTION  :
// PARAMETERS   : int* arr	:	Pointer to dynamic array
// RETURNS      : void
//
void swapTransactions(int* arr) {

}

//
// FUNCTION     : toggleTransactionStatus
// DESCRIPTION  :
// PARAMETERS   : int* arr	:	Pointer to dynamic array
// RETURNS      : void
//
void toggleTransactionStatus(int* arr) {

}

//
// FUNCTION     : exit
// DESCRIPTION  : Frees memory of dynamically allocated array
// PARAMETERS   : int* arr	:	Pointer to dynamic array
// RETURNS      : void
//
void exit(int* arr) {
	free(arr);
}

//
// FUNCTION     : getNum
// DESCRIPTION  : Gets a double from the user - returns 0.0 if invalid
// PARAMETERS   : none
// RETURNS      : double
//
double getNum(void) {
	double num = 0.0; // Store double to return
	char input[INPUT_SIZE] = ""; // Buffer for user input
	char extraChar = '0'; // Store any extraneous input from user

	// Ask for number
	fgets(input, sizeof(input), stdin);
	input[strlen(input) - 1] = '\n'; // Remove trailing newline character from input

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
int getIndex(void) {

}

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