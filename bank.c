#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bank.h"

void display_menu() {
    printf("\n============================\n");
    printf("          Banking System\n");
    printf("============================\n");
    printf("1. Create Account\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. Check Balance\n");
    printf("5. Transfer\n");
    printf("6. Print Statement\n");
    printf("7. Exit\n");
    printf("============================\n");
    printf("Enter your choice: ");
}

void create_account() {
    Account new_account;
    int account_exists = 0;

    printf("\n--- Create Account ---\n");

    // Get an account number
    printf("Enter account number: ");
    scanf("%d", &new_account.account_number);

    // Open the file in append mode first to ensure it exists
    FILE *file = fopen("accounts.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fclose(file);

    // Re-open the file in read mode to check for duplicate account number
    file = fopen("accounts.txt", "r");
    Account account;
    while (fscanf(file, "Account Number: %d\nName: %s\nBalance: %lf\n\n", &account.account_number, account.name, &account.balance) != EOF) {
        if (account.account_number == new_account.account_number) {
            account_exists = 1;
            break;
        }
    }
    fclose(file);

    if (account_exists) {
        printf("An account with this account number already exists.\n\n");
        return;
    }

    // Get a name if account number is unique
    printf("Enter a name: ");
    scanf("%s", new_account.name);

    // Initialize balance
    new_account.balance = 0.0;

    // Open file in append mode to save account details
    file = fopen("accounts.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Write account info in a readable format
    fprintf(file, "Account Number: %d\nName: %s\nBalance: %.2f\n\n", new_account.account_number, new_account.name, new_account.balance);
    fclose(file);

    printf("Account created successfully.\n\n");
}


void deposit(int account_number, double amount) {
    Account account;
    int found = 0;

    // Check if file exists
    FILE *file = fopen("accounts.txt", "r+");
    if (file == NULL) {
        printf("No accounts found. Please create an account first.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        perror("Error opening temporary file");
        fclose(file);
        return;
    }

    // Scan for the account and perform the deposit
    while (fscanf(file, "Account Number: %d\nName: %s\nBalance: %lf\n\n", &account.account_number, account.name, &account.balance) != EOF) {
        if (account.account_number == account_number) {
            account.balance += amount;
            found = 1;
            printf("Deposit successful! New balance: %.2f\n", account.balance);
        }
        fprintf(temp, "Account Number: %d\nName: %s\nBalance: %.2f\n\n", account.account_number, account.name, account.balance);
    }

    fclose(file);
    fclose(temp);

    // Update accounts.txt
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found) {
        printf("Account not found.\n");
    }
}

void withdrawal(int account_number, double amount) {
    Account account;
    int found = 0;

    // Check if file exists
    FILE *file = fopen("accounts.txt", "r+");
    if (file == NULL) {
        printf("No accounts found. Please create an account first.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        perror("Error opening temporary file");
        fclose(file);
        return;
    }

    // Scan for the account and perform the withdrawal
    while (fscanf(file, "Account Number: %d\nName: %s\nBalance: %lf\n\n", &account.account_number, account.name, &account.balance) != EOF) {
        if (account.account_number == account_number) {
            if (account.balance >= amount) {
                account.balance -= amount;
                found = 1;
                printf("Withdrawal successful! New balance: %.2f\n", account.balance);
            } else {
                printf("Insufficient balance.\n");
                found = 1;
            }
        }
        fprintf(temp, "Account Number: %d\nName: %s\nBalance: %.2f\n\n", account.account_number, account.name, account.balance);
    }

    fclose(file);
    fclose(temp);

    // Update accounts.txt
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found) {
        printf("Account not found.\n");
    }
}


double check_balance(int account_number) {
    Account account;
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    while (fscanf(file, "Account Number: %d\nName: %s\nBalance: %lf\n\n", &account.account_number, account.name, &account.balance) != EOF) {
        if (account.account_number == account_number) {
            fclose(file);
            return account.balance;
        }
    }

    fclose(file);
    printf("Account not found.\n");
    return -1;
}

void transfer(int from_account, int to_account, double amount) {
    double from_balance = check_balance(from_account);
    double to_balance = check_balance(to_account);

    if (from_balance == -1 || to_balance == -1) {
        printf("One or both accounts not found.\n");
        return;
    }

    if (from_balance < amount) {
        printf("Insufficient balance in the source account.\n");
        return;
    }

    withdrawal(from_account, amount);
    deposit(to_account, amount);

    printf("Transfer of %.2f from account %d to account %d completed.\n", amount, from_account, to_account);
}

void print_statement(int account_number) {
    Account account;
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    while (fscanf(file, "Account Number: %d\nName: %s\nBalance: %lf\n\n", &account.account_number, account.name, &account.balance) != EOF) {
        if (account.account_number == account_number) {
            printf("\n--- Account Statement ---\n");
            printf("Account Number: %d\nName: %s\nBalance: %.2f\n\n", account.account_number, account.name, account.balance);
            fclose(file);
            return;
        }
    }

    printf("Account not found.\n");
    fclose(file);
}

int main() {
    int choice;
    int account_number;
    double amount;
    char input[256];

    while (1) {
        display_menu();

        // Use fgets to read the input and parse it to an integer
        fgets(input, sizeof(input), stdin);
        choice = atoi(input);  // Convert input to integer, atoi will return 0 if input is invalid

        switch (choice) {
            case 1:
                create_account();
                break;
            case 2:
                printf("\n--- Deposit ---\n");
                printf("Enter account number: ");
                fgets(input, sizeof(input), stdin);
                account_number = atoi(input);

                printf("Enter deposit amount: ");
                fgets(input, sizeof(input), stdin);
                amount = atof(input);

                deposit(account_number, amount);
                break;
            case 3:
                printf("\n--- Withdraw ---\n");
                printf("Enter account number: ");
                fgets(input, sizeof(input), stdin);
                account_number = atoi(input);

                printf("Enter withdrawal amount: ");
                fgets(input, sizeof(input), stdin);
                amount = atof(input);

                withdrawal(account_number, amount);
                break;
            case 4:
                printf("\n--- Check Balance ---\n");
                printf("Enter account number: ");
                fgets(input, sizeof(input), stdin);
                account_number = atoi(input);

                double balance = check_balance(account_number);
                if (balance != -1) {
                    printf("Current balance: %.2f\n", balance);
                }
                break;
            case 5:
                printf("\n--- Transfer ---\n");
                printf("Enter source account number: ");
                fgets(input, sizeof(input), stdin);
                account_number = atoi(input);

                printf("Enter destination account number: ");
                fgets(input, sizeof(input), stdin);
                int to_account = atoi(input);

                printf("Enter transfer amount: ");
                fgets(input, sizeof(input), stdin);
                amount = atof(input);

                transfer(account_number, to_account, amount);
                break;
            case 6:
                printf("\n--- Print Statement ---\n");
                printf("Enter account number: ");
                fgets(input, sizeof(input), stdin);
                account_number = atoi(input);

                print_statement(account_number);
                break;
            case 7:
                printf("\nExiting the program. Thank you for using the Banking System!\n");
                return 0;
            default:
                printf("\nInvalid choice! Please enter a number between 1 and 7.\n");
        }
    }

    return 0;
}
