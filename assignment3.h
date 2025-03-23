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

// Bit positions of where flags are stored in data
#define	PROCESSED_FLAG	31
#define	REFUNDED_FLAG	30

#define	MASK	0b00111111111111111111111111111111
	// First two bits are reserved for flags & the last 30 bits are for transaction amount
	// This mask is applied to get the transaction amount

#define	MAX_TRANSACTION	100000
	// The maximum amount of significant digits available to store a transaction is 30, therefore the highest number that can be stored as a transaction amount is 2^30
	// The units for transaction are stored as hundredth cents and printed as dollars to the console.
	// Therefore, the maximum amount is (2^30)/4 dollars, or $107374.1824.
	// For simplicity's sake, the maximum dollar amount is set to $100,000.

// Menu
enum functions {
	ADD_TRANSACTIONS = 1,
	DISPLAY_TRANSACTIONS = 2,
	APPLY_FEES = 3,
	FIND_HIGHEST = 4,
	SWAP_TRANSACTIONS = 5,
	TOGGLE_TRANSACTION_STATUS = 6,
	EXIT = 7
} OPERATIONS;

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
void addTransactions(Transactions* allTransactions);
void displayTransactions(Transactions* allTransactions);
void printTransaction(Transactions* allTransactions, int index);
void applyTransactionFees(Transactions* allTransactions);
void findHighestTransaction(Transactions* allTransactions);
void swapTransactions(Transactions* allTransactions);
void toggleTransactionStatus(Transactions* allTransactions);
void exit(Transactions* allTransactions);

// Bitmasking Library
void set_bit(uint32_t* reg, uint8_t bit);
void clear_bit(uint32_t* reg, uint8_t bit);
void toggle_bit(uint32_t* reg, uint8_t bit);
uint8_t is_bit_set(uint32_t reg, uint8_t bit);

// Bit Operations
void toggleProcessed(unsigned int* transaction);
void toggleRefunded(unsigned int* transaction);

bool extractProcessed(unsigned int transaction);
bool extractRefunded(unsigned int transaction);
unsigned int extractTransaction(unsigned int transaction);

// User Input Functions
float getNum(void);
int getInt(void);