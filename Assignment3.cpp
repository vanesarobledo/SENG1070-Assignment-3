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

}

//
// FUNCTION     : getMenuOperation
// DESCRIPTION  : Gets number from user for menu operation
// PARAMETERS   : int* operation	:	Pointer to menu operation
// RETURNS      : void
//
void getMenuOperation(int* operation) {

}

//
// FUNCTION     : addTransaction
// DESCRIPTION  :
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
// FUNCTION     : changeTransactionStatus
// DESCRIPTION  :
// PARAMETERS   : int* arr	:	Pointer to dynamic array
// RETURNS      : void
//
void changeTransactionStatus(int* arr) {

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
// DESCRIPTION  : Gets a double from the user - returns -1 if invalid
// PARAMETERS   : none
// RETURNS      : double
//
double getNum(void) {

}

//
// FUNCTION     : getIndex
// DESCRIPTION  : Gets an integer from the user - returns -1 if invalid
// PARAMETERS   : none
// RETURNS      : int
//
int getIndex(void) {

}