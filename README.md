# Simple Banking System

This is a console-based banking system written in C. It allows users to create accounts, deposit and withdraw funds, check balances, transfer money between accounts, and view account statements. The program stores account information in a local file, `accounts.txt`, for persistence.

## Features

- **Create Account**: Allows the user to create a new account with a unique account number and name. Accounts start with a balance of `0.00`.
- **Deposit**: Adds a specified amount to an existing account's balance.
- **Withdraw**: Deducts a specified amount from an existing account's balance if sufficient funds are available.
- **Check Balance**: Displays the current balance of a specified account.
- **Transfer**: Transfers a specified amount from one account to another if the source account has sufficient funds.
- **Print Statement**: Displays account details, including account number, name, and balance.
- **Exit**: Exits the program.

## Getting Started

### Prerequisites
- C Compiler (e.g., GCC)

### Running the Program

1. **Clone the repository**:
    ```bash
    git clone https://github.com/yourusername/Simple-Banking-System.git
    cd Simple-Banking-System
    ```

2. **Compile the code**:
    ```bash
    gcc -o banking_system main.c
    ```

3. **Run the program**:
    ```bash
    ./banking_system
    ```



