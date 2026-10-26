# ATM System

A console-based ATM simulation built with C++. This project demonstrates solid logic, Clean Code architecture, and proper memory management.

## Core Features
- **Session Management:** Stores current user data in memory after login to avoid repetitive account number inputs.
- **File I/O:** Reads and updates client balances dynamically from a local database file (`Clients.txt`).
- **Memory Safety:** Uses a continuous main loop instead of recursion to prevent Stack Overflow during continuous running.
- **Transactions:** Supports Deposit, Normal Withdraw, Quick Withdraw, and Check Balance.

## Tech Stack
- C++
- Clean Code / Separation of Concerns (SoC)
