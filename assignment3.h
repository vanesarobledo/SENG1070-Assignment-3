#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define macros
#define ARRAY_SIZE	100
#define	INPUT_SIZE	10
#define	MENU_SIZE	2
#define	EMPTY	-1
#define	STOP	-1

// Bitmasking Library
#define set_bit(reg, bit)	((reg) |= (1U << (bit)))
#define	clear_bit(reg, bit)	((reg &= ~(1U << (bit))))
#define	toggle_bit(reg, bit)	((reg) ^= (1U << (bit)))
#define is_bit_set(reg, bit)	reg & (1U << bit)) ? 1: 0

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
typedef struct Wallet {
	float* transactions; // Stores all the transactions
	int size; // Stores size of array
} Wallet;

// Function Prototypes
Wallet* initializeArray(void);
bool isEmpty(Wallet*);

void menu(void);
void getMenuOperation(int* operation);

void addTransaction(Wallet* wallet);
void displayTransactions(Wallet* wallet);
void applyTransactionFees(Wallet* wallet);
void findHighestTransaction(Wallet* wallet);
void swapTransactions(Wallet* wallet);
void toggleTransactionStatus(Wallet* wallet);
void exit(Wallet* wallet);

float getNum(void);
int getIndex(void);
void swapNum(int num1, int num2);
