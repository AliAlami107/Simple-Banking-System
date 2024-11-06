#ifndef BANK_H_
#define BANK_H_

typedef struct {
    int account_number;
    char name[50];
    double balance;
} Account;


typedef struct {
    int transaction_id;
    int account_number;
    double amount;
    char type[10]; // deposit or withdrawal
} Transaction;


void create_account();

void deposit(int account_number, double amount);

void withdrawal(int account_number, double amount);

double check_balance(int account_number);

void transfer(int from_account, int to_account, double amount );

void print_statement(int account_number);



#endif