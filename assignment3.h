#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define macros
#define ARRAY_SIZE	100
#define	INPUT_SIZE	10
#define	MENU_SIZE	2

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

// Function Prototypes
void menu(void);
void getMenuOperation(int* operation);

void addTransaction(int* arr);
void displayTransactions(int* arr);
void applyTransactionFees(int* arr);
void findHighestTransaction(int* arr);
void swapTransactions(int* arr);
void toggleTransactionStatus(int* arr);
void exit(int* arr);

double getNum(void);
int getIndex(void);
void swapNum(int num1, int num2);
