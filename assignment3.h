#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

// Define macros
#define ARRAY_SIZE	100
#define	INPUT_SIZE	10
#define	MENU_SIZE	2
#define	EMPTY	-1
#define	SENTINEL	-1

// Menu
enum menu {
	ADD_TRANSACTION,
	DISPLAY_TRANSACTIONS,
	APPLY_FEES,
	FIND_HIGHEST,
	SWAP_TRANSACTIONS,
	TOGGLE_TRANSACTION_STATUS,
	EXIT
};

// Define Dynamic Array
typedef struct Transactions {
	unsigned int* data; // Stores all the transactions
	int size; // Stores size of array
} Transactions;

// Function Prototypes

// Dynamic Array
Transactions* initializeArray(void);
bool isEmpty(Transactions*);

// Menu
void menu(void);
void getMenuOperation(int* operation);

// Main User Functions
void addTransaction(Transactions* allTransactions);
void displayTransactions(Transactions* allTransactions);
void applyTransactionFees(Transactions* allTransactions);
void findHighestTransaction(Transactions* allTransactions);
void swapTransactions(Transactions* allTransactions);
void toggleTransactionStatus(Transactions* allTransactions);
void exit(Transactions* allTransactions);

// Bit Operations
void swapNum(float num1, float num2);
float extractProcessed(float num);
float extractRefunded(float num);

// User Input Functions
float getNum(void);
int getIndex(void);


