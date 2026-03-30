# Bank Management System

A console-based Bank Management System built in C that allows users to manage bank accounts efficiently using file handling.

## Features

- Create a new bank account
- Deposit money
- Withdraw money
- Check account balance
- View all accounts
- Search account by account number
- Delete account
- Persistent data storage using file handling


## Advanced Features

- Binary file storage (`accounts.dat`) for permanent data saving
- Real-time balance updates using file pointer manipulation
- Efficient record searching using sequential file access
- Safe delete operation using temporary file handling
- Input handling with buffer clearing to avoid runtime issues


## Tech Stack

- **Language:** C
- **Core Concepts Used:**
  - Structures
  - File Handling (fopen, fread, fwrite, fseek)
  - Pointers
  - Functions
  - Control Statements
  - Modular Programming


## File Structure
 -main.c        - Core program logic  / source code 

-accounts.dat  - Stores account data  

-README.md     - Project documentation

## How It Works

- Each account is stored as a record in a binary file.
- Operations like deposit and withdrawal update records directly using file pointers.
- Deletion is handled by copying records to a temporary file and replacing the original file.

## How to Run

clang main.c -o bank
./bank
