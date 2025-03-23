/*
* FILE          : Assignment3.cpp
* PROJECT       : SENG1070 Assignment 3: Array & Pointer Techniques with Bitwise Operations
* PROGRAMMER    : Vanesa Robledo
* FIRST VERSION : 2025-03-21
* DESCRIPTION   : This is a console-based cryptocurrency Transactions manager. Users can add and view transactions,
				  apply transaction fees, find the highest transactions, swap transactions, and manage transaction flags
				  (processed and refunded).
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "assignment3.h"

int main(void)
{
	// Initialize dynamic array
	Transactions* allTransactions = initializeArray();

	int choice = 0; // Store user menu choice
	bool running = true; // Flag for menu

	while (running) {
		menu();
		getMenuOperation(&choice);
		switch (choice) {
			case ADD_TRANSACTIONS:
				addTransactions(allTransactions);
				break;
			case DISPLAY_TRANSACTIONS:
				displayTransactions(allTransactions);
				break;
			case APPLY_FEES:
				applyTransactionFees(allTransactions);
				break;
			case FIND_HIGHEST:
				findHighestTransaction(allTransactions);
				break;
			case SWAP_TRANSACTIONS:
				swapTransactions(allTransactions);
				break;
			case UPDATE_TRANSACTION_STATUS:
				updateTransactionStatus(allTransactions);
				break;
			case EXIT:
				running = false;
				break;
			default:
				printf("Invalid menu option.\n");
				break;
		}
		printf("\n");
	}
	exit(allTransactions);
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
	printf("Cryptocurrency Transactions\n");
	printf("1. Add a transaction\n");
	printf("2. Display all transactions\n");
	printf("3. Apply fee to all transactions\n");
	printf("4. Find highest transaction\n");
	printf("5. Swap transactions\n");
	printf("6. Update transaction status\n");
	printf("7. Exit\n");
}

//
// FUNCTION     : getMenuOperation
// DESCRIPTION  : Gets number from user for menu operation
// PARAMETERS   : int* operation : Pointer to menu operation
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
		if (!(*operation >= kStart && *operation <= EXIT)) {
			printf("Please enter a valid menu number.\n");
			continue;
		}
		// Input is valid, break loop
		loopFlag = false;
	}
}

//
// FUNCTION     : initializeArray
// DESCRIPTION  : Dynamically allocates memory for an array
// PARAMETERS   : none
// RETURNS      : int* : Pointer to dynamic array
//
Transactions* initializeArray(void) {
	Transactions* array = (Transactions*)malloc(sizeof(Transactions));

	// Ensure memory is allocated
	if (array == NULL) {
		printf("Failed to allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	// Dynamically allocate array
	array->data = (unsigned int*)malloc(ARRAY_SIZE * sizeof(unsigned int));

	// Initialize size of array, -1 means empty
	array->size = EMPTY;

	return array;
}

//
// FUNCTION     : isEmpty
// DESCRIPTION  : Checks if size of array is 0 (i.e. size is not -1)
// PARAMETERS   : Transactions* allTransactions : Pointer to struct containing dynamic array
// RETURNS      : bool
//
bool isEmpty(Transactions* allTransactions) {
	if (allTransactions != NULL) {
		return allTransactions->size == -1;
	}
	else {
		return true;
	}
}

//
// FUNCTION     : addTransactions
// DESCRIPTION  : Asks a user to to enter transaction amounts to store in dynamic array until they enter -1
// PARAMETERS   : Transactions* allTransactions : Pointer to struct containing dynamic array
// RETURNS      : void
//
void addTransactions(Transactions* allTransactions) {
	float amount = 0.0; // Store user-inputted float
	unsigned int transaction = 0; // Store amount of transaction

	// Ask user for amount of transaction and validate
	do {
		printf("Enter transaction amount (or -1 to stop): $");
		amount = getNum();
		if (amount == 0) { // Check for valid return from getNum
			printf("Please enter a valid number.\n");
		}
		else if (amount < 0 && amount != SENTINEL) { // Check if negative
			printf("Please enter a positive number.\n");
		}
		else if (amount > MAX_TRANSACTION) {
			printf("Maximum dollar amount is $%.2lf. Please enter a lower number.\n", (float)(MAX_TRANSACTION));
		}
		else if (amount != SENTINEL) { // Number is valid
			// Add to dynamic array as long as it does not exceed maximum size
			if (allTransactions->size == ARRAY_SIZE - 1) {
				// Print error to screen when array sized is reached
				printf("Max transactions reached (100).\n");
				break;
			}
			else {
				// Multiply by 10000 to convert dollar amount to hundredth cents
				amount = amount * CURRENCY;
				// Store as integer
				transaction = (int)amount;
				// Increase index of transactions
				allTransactions->data[++allTransactions->size] = transaction;
			}
		}
	} while (amount != SENTINEL);

	// Print all transactions to screen
	if (!isEmpty(allTransactions)) {
		displayTransactions(allTransactions);
	}
}

//
// FUNCTION     : displayTransactions
// DESCRIPTION  : Displays all transactions on screen and their runtime
// PARAMETERS   : Transactions* allTransactions :	Pointer to struct containing dynamic array
// RETURNS      : void
//
void displayTransactions(Transactions* allTransactions) {
	printf("\nAll Transactions:\n");
	if (allTransactions != NULL && !isEmpty(allTransactions)) {
		// Calculate sum and average
		float sum = 0.0;
		float average = 0.0;
		for (int i = 0; i <= allTransactions->size; i++) {
			sum += (float)extractTransaction(allTransactions->data[i]) / CURRENCY;
			printTransaction(allTransactions, i);
		}
		average = sum / (float)(allTransactions->size + 1);
		printf("Total Transaction Amount: $%.2f\n", sum);
		printf("Average Transaction Value: $%.2f\n", average);
	}
	// If dynamic array is empty, print error message
	else if (isEmpty(allTransactions)) {
		printf("No transactions stored to display.\n");
	}
	else {
		printf("Error displaying transactions.\n");
	}
}

//
// FUNCTION     : printTransaction
// DESCRIPTION  : Displays transaction and information given its index
// PARAMETERS   : Transactions* allTransactions : Pointer to struct containing dynamic array
//				  int index						: Index of dynamic array
// RETURNS      : void
//
void printTransaction(Transactions* allTransactions, int index) {
	if (allTransactions != NULL) { // Do not dereference NULL pointer
		if (!isEmpty(allTransactions)) { // Only check if there are values in array
			if (index >= 0 && index <= allTransactions->size) { // Only check if index is valid
				// Extract transaction amount
				float dollar = (float)extractTransaction(allTransactions->data[index]) / CURRENCY;
				printf("[%d] Transaction %d: $%.2f ", index, index + 1, dollar);
				// Check processed flag
				printf("| Processed: ");
				extractProcessed(allTransactions->data[index]) ? printf("Yes") : printf("No");
				// Check refunded flag
				printf(" | Refunded: ");
				extractRefunded(allTransactions->data[index]) ? printf("Yes") : printf("No");
				printf("\n");
			}
		}
	}
}

//
// FUNCTION     : applyTransactionFees
// DESCRIPTION  : Applies a user-specified percentage of fees onto all transactions
// PARAMETERS   : Transactions* allTransactions : Pointer to struct containing dynamic array
// RETURNS      : void
//
void applyTransactionFees(Transactions* allTransactions) {
	if (allTransactions != NULL) {
		if (!isEmpty(allTransactions)) {
			// Ask user to enter percentage
			float percent = 0.0; // Store percent
			bool validNum = false; // Flag for valid number
			do {
				printf("Enter percentage fee to apply (1-99) or -1 to cancel: ");
				percent = getNum();
				if (percent > 0 && percent < 100) { // User enters valid number
					validNum = true;
				}
				else if (percent == SENTINEL) { // User cancels transaction
					return;
				}
				else { // User enters invalid number
					printf("Please enter a valid number from 1-99.\n");
				}
			} while (percent != SENTINEL && !validNum);

			// Apply percentage transaction to all transactions
			percent = ((100 - percent) / 100);
			int current; // Store current masked integer
			float calculatedValue; // Store calculated new value
			unsigned int newValue; // Store new integer

			// Store flags to re-set bits
			bool processedFlag = false; 
			bool refundedFlag = false; 

			for (int i = 0; i <= allTransactions->size; i++) {
				// Store data about transaction
				current = extractTransaction(allTransactions->data[i]);
				processedFlag = extractProcessed(allTransactions->data[i]);
				refundedFlag = extractRefunded(allTransactions->data[i]);
				
				// Calculate new value
				calculatedValue = (float)current * percent;
				newValue = calculatedValue;
				// Re-set processed and refunded flags
				if (processedFlag) {
					setProcessed(&newValue);
				}
				if (refundedFlag) {
					toggleRefunded(&newValue);
				}

				// Store new value
				allTransactions->data[i] = newValue;
			}

			// Display new amounts
			printf("New transaction amounts:\n");
			displayTransactions(allTransactions);
		}
		else {
			printf("No transactions stored.\n");
		}
	}
}

//
// FUNCTION     : findHighestTransaction
// DESCRIPTION  : Finds the highest transaction fee in a list
// PARAMETERS   : Transactions* allTransactions : Pointer to struct containing dynamic array
// RETURNS      : void
//
void findHighestTransaction(Transactions* allTransactions) {
	float highestTransaction; // Store highest transaction
	int current; // Store current masked integer
	int highest = 0; // Find highest number in list
	int highestIndex = EMPTY;
	if (allTransactions != NULL) {
		if (!isEmpty(allTransactions)) {
			for (int i = 0; i <= allTransactions->size; i++) {
				current = allTransactions->data[i] & MASK;
				if (current > highest) {
					highest = current;
					highestIndex = i;
				}
			}
			highestTransaction = (float)highest / CURRENCY;
			printf("Highest Transaction is Transaction %d: $%.2f\n", highestIndex + 1, highestTransaction);
		}
		else {
			printf("No transactions stored.\n");
		}
	}
	// If list is NULL
	else {
		printf("No transactions stored.\n");
	}
}

//
// FUNCTION     : swapTransactions
// DESCRIPTION  : Swaps the values of two transactions
// PARAMETERS   : Transactions* allTransactions : Pointer to struct containing dynamic array
// RETURNS      : void
//
void swapTransactions(Transactions* allTransactions) {
	if (allTransactions != NULL) {
		if (!isEmpty(allTransactions)) {
			// Only perform swap if there are at least 2 transactions
			if (allTransactions->size >= 1) {
				int max = allTransactions->size; // Store maximum index

				// Store indices of transactions to swap
				int index1;
				int index2;

				// Ask user for indices to swap & validate
				do {
					printf("Enter 1st transaction index to swap: ");
					index1 = getInt();
					if (index1 < 0) {
						printf("Index must be at least 0.\n");
					}
					if (index1 > max) {
						printf("Index cannot be greater than %d.\n", max);
					}
				} while (index1 < 0 || index1 > max);

				do {
					printf("Enter 2nd transaction index to swap: ");
					index2 = getInt();
					if (index2 < 0) {
						printf("Index must be at least 0.\n");
					}
					if (index2 > max) {
						printf("Index cannot be greater than %d.\n", max);
					}
				} while (index2 < 0 || index2 > max);

				// Swap indices with XOR Swap
				if (index1 == index2) { // Indices were the same
					printf("Indices provided were the same; values not swapped.\n");
				}
				else if (index1 >= 0 && index2 >= 0 && index1 <= max && index2 <= max) {
					allTransactions->data[index1] = allTransactions->data[index1] ^ allTransactions->data[index2];
					allTransactions->data[index2] = allTransactions->data[index1] ^ allTransactions->data[index2];
					allTransactions->data[index1] = allTransactions->data[index1] ^ allTransactions->data[index2];
				}

				// Print swapped transactions to screen
				displayTransactions(allTransactions);
			}
			else if (allTransactions->size == 0) {
				printf("Cannot swap transactions - only one transaction is stored.\n");
			}
		}
		else {
			printf("No transactions stored.\n");
		}
	}
}

//
// FUNCTION     : updateTransactionStatus
// DESCRIPTION  : Asks the user for an index 
// PARAMETERS   : Transactions* allTransactions : Pointer to struct containing dynamic array
// RETURNS      : void
//
void updateTransactionStatus(Transactions* allTransactions) {
	// Constants for menu
	const int kSetProcessed = 1;
	const int kClearProcessed = 2;
	const int kToggleRefunded = 3;
	const int kDisplayAllFlags = 4;

	if (allTransactions != NULL) {
		if (!isEmpty(allTransactions)) {
			int index = SENTINEL; // Store index to change
			int max = allTransactions->size; // Store highest index
			int choice = SENTINEL; // Store user option

			// Ask user for option
			do {
				printf("\n1. Set Processed\n");
				printf("2. Clear Processed\n");
				printf("3. Toggle Refunded\n");
				printf("4. Display All Flags\n");
				printf("Enter your choice: ");
				choice = getInt();
				if (choice < kSetProcessed || choice > kDisplayAllFlags) {
					printf("Invalid option. Please select an option from 1-4.\n");
				}
			} while (choice < kSetProcessed || choice > kDisplayAllFlags);

			if (choice != kDisplayAllFlags) {
				// Ask user for index to toggle
				do {
					printf("Enter transaction index to modify: ");
					index = getInt();
					if (index < 0 || index > max) {
						printf("Invalid input. Transaction index must be between 0 - %d.\n", max);
					}
				} while (index < 0 || index > max);
			}

			switch (choice) {
			case kSetProcessed:
				setProcessed(&allTransactions->data[index]);
				break;
			case kClearProcessed:
				clearProcessed(&allTransactions->data[index]);
				break;
			case kToggleRefunded:
				toggleRefunded(&allTransactions->data[index]);
				break;
			case kDisplayAllFlags:
				printf("\nAll Flags:\n");
				for (int i = 0; i <= allTransactions->size; i++) {
					printf("[%d] Transaction %d: ", i, i + 1);
					printf("Processed: ");
					extractProcessed(allTransactions->data[i]) ? printf("Yes") : printf("No");
					printf(" | Refunded: ");
					extractRefunded(allTransactions->data[i]) ? printf("Yes") : printf("No");
					printf("\n");
				}
				break;
			default:
				break;
			}
			// Display updated transaction if changed
			if (choice != kDisplayAllFlags) {
				printf("\nUpdated transaction:\n");
				printTransaction(allTransactions, index);
			}
		}
		else {
			printf("No transactions stored.\n");
		}
	}
}

//
// FUNCTION     : exit
// DESCRIPTION  : Frees memory of dynamically allocated array
// PARAMETERS   : Transactions* allTransactions : Pointer to struct containing dynamic array
// RETURNS      : void
//
void exit(Transactions* allTransactions) {
	if (allTransactions != NULL) {
		free(allTransactions->data);
		free(allTransactions);
		printf("Freed dynamically allocated memory.\n");
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
// FUNCTION     : getInt
// DESCRIPTION  : Gets an integer from the user - returns -1 if invalid
// PARAMETERS   : none
// RETURNS      : int
//
int getInt(void) {
	int num = 0; // Store integer to return

	char input[INPUT_SIZE] = ""; // Buffer for user input
	char extraChar = '0'; // Store any extraneous input from user

	// Ask user for number
	fgets(input, sizeof(input), stdin);
	input[strlen(input) - 1] = '\0'; // Remove trailing newline character from input

	// Validate input - return 0.0 if invalid
	if (sscanf_s(input, "%d %c", &num, &extraChar, (unsigned int)sizeof(extraChar)) != 1) {
		return SENTINEL;
	}
	else {
		return num;
	}
}

// Bitmasking Library
// Based on Bitmasking Library Example from "SENG1070: Bitwise Operations" slides

//
// FUNCTION     : set_bit
// DESCRIPTION  : Sets a bit in given data
// PARAMETERS   : unsigned int* data : Pointer to data containing bit
//				  int bit			 : Bit that is being set
// RETURNS      : void
//
void set_bit(unsigned int* data, int bit) {
	*data |= (1U << bit);
}

//
// FUNCTION     : clear_bit
// DESCRIPTION  : Clears a bit in given data
// PARAMETERS   : unsigned int* data : Pointer to data containing bit
//				  int bit			 : Bit that is being cleared
// RETURNS      : void
//
void clear_bit(unsigned int* data, int bit) {
	*data &= ~(1U << bit);
}

//
// FUNCTION     : toggle_bit
// DESCRIPTION  : Toggles a bit in given data
// PARAMETERS   : unsigned int* data : Pointer to data containing bit
//				  int bit			 : Bit that is being toggled
// RETURNS      : void
//
void toggle_bit(unsigned int* data, int bit) {
	*data ^= (1U << bit);
}

//
// FUNCTION     : is_bit_set
// DESCRIPTION  : Checks if a bit is set
// PARAMETERS   : unsigned int data : Data containing bit
//				  int bit			: Bit that is being checked
// RETURNS      : bool - returns 1 if bit is set, 0 if not
//
bool is_bit_set(unsigned int data, int bit) {
	return (data & (1U << bit)) ? 1 : 0;
}

//
// FUNCTION     : setProcessed
// DESCRIPTION  : Sets processed flag
// PARAMETERS   : unsigned int transaction : Pointer to data holding transaction
// RETURNS      : void
//
void setProcessed(unsigned int* transaction) {
	set_bit(transaction, PROCESSED_FLAG);
}

//
// FUNCTION     : clearProcessed
// DESCRIPTION  : Clears processed flag
// PARAMETERS   : unsigned int transaction : Pointer to data holding transaction
// RETURNS      : void
//
void clearProcessed(unsigned int* transaction) {
	clear_bit(transaction, PROCESSED_FLAG);
}

//
// FUNCTION     : toggleRefunded
// DESCRIPTION  : Toggles refunded flag
// PARAMETERS   : unsigned int transaction : Pointer to data holding transaction
// RETURNS      : void
//
void toggleRefunded(unsigned int* transaction) {
	toggle_bit(transaction, REFUNDED_FLAG);
}

//
// FUNCTION     : extractProcessed
// DESCRIPTION  : Checks if transaction is processed by checking if its flag was set
// PARAMETERS   : unsigned int transaction : Data holding transaction
// RETURNS      : bool - 1 if set, 0 if not
//
bool extractProcessed(unsigned int transaction) {
	return is_bit_set(transaction, PROCESSED_FLAG) ? true : false;
}

//
// FUNCTION     : extractRefunded
// DESCRIPTION  : Checks if transaction is refunded by checking if its flag was set
// PARAMETERS   : unsigned int transaction : Data holding transaction
// RETURNS      : bool - 1 if set, 0 if not
//
bool extractRefunded(unsigned int transaction) {
	return is_bit_set(transaction, REFUNDED_FLAG) ? true : false;
}

//
// FUNCTION     : extractTransaction
// DESCRIPTION  : Masks the processed & refunded flags to get transaction value
// PARAMETERS   : unsigned int transaction : Data holding transaction
// RETURNS      : unsigned int
//
unsigned int extractTransaction(unsigned int transaction) {
	return transaction & MASK;
}

//
// FUNCTION		: printBinary
// DESCRIPTION	: This function prints an int in binary form
// PARAMETERS	: unsigned char data : Data to print to binary
// RETURNS		: void
//
//void printBinary(unsigned int data)
//{
//	const int sizeofByte = 31; // Most significant bit position in int
//	// Print bit positions by iterating backward and print 1 or 0 by checking if bit was set
//	for (int i = sizeofByte; i >= 0; i--)
//	{
//		data& (1 << i) ? printf("1") : printf("0");
//	}
//	printf("\n");
//}