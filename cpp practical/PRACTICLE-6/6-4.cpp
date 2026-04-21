#include <iostream>
#include <string>
#include <stack>
#include <iomanip>

using namespace std;

// Enumeration to represent the type of transaction
enum TransactionType { DEPOSIT, WITHDRAW };

// Structure to store transaction details
struct Transaction {
    TransactionType type;
    double amount;
};

// ==========================================
// 1. Base Class: Account
// ==========================================
class Account {
protected:
    string accountNumber;
    double balance;
    stack<Transaction> history; // Stack to track sequence of transactions for undo

public:
    // Constructor
    Account(string accNum, double initialBalance) {
        accountNumber = accNum;
        balance = initialBalance;
        cout << "[System] Account " << accountNumber << " initialized." << endl;
    }

    // Virtual Destructor ensures proper cleanup of derived classes
    virtual ~Account() {
        cout << "[System] Account " << accountNumber << " closed and resources cleaned up." << endl;
    }

    // Deposit operation (Common for all accounts)
    virtual void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            history.push({DEPOSIT, amount}); // Log transaction
            cout << "Deposited: $" << fixed << setprecision(2) << amount
                 << " | New Balance: $" << balance << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    // Virtual withdraw operation (To be overridden by derived classes)
    virtual void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            history.push({WITHDRAW, amount}); // Log transaction
            cout << "Withdrew: $" << fixed << setprecision(2) << amount
                 << " | New Balance: $" << balance << endl;
        } else {
            cout << "Withdrawal failed: Insufficient funds or invalid amount." << endl;
        }
    }

    // Undo the last transaction
    void undoLastTransaction() {
        if (history.empty()) {
            cout << "No transactions to undo." << endl;
            return;
        }

        Transaction lastTx = history.top();
        history.pop();

        cout << "\n--- Undoing Last Transaction ---" << endl;
        if (lastTx.type == DEPOSIT) {
            balance -= lastTx.amount;
            cout << "Reverted Deposit of $" << lastTx.amount << endl;
        } else if (lastTx.type == WITHDRAW) {
            balance += lastTx.amount;
            cout << "Reverted Withdrawal of $" << lastTx.amount << endl;
        }
        cout << "Restored Balance: $" << balance << endl << "--------------------------------\n";
    }

    // Pure virtual function makes Account an abstract base class (optional but good practice)
    virtual void displayDetails() const {
        cout << left << "Account: " << setw(10) << accountNumber
             << " | Balance: $" << fixed << setprecision(2) << balance;
    }
};

// ==========================================
// 2. Derived Class: Savings Account
// ==========================================
class SavingsAccount : public Account {
private:
    double interestRate;

public:
    // Constructor chaining to base class
    SavingsAccount(string accNum, double initialBalance, double rate)
        : Account(accNum, initialBalance), interestRate(rate) {
        cout << "[System] Savings features enabled." << endl;
    }

    // Destructor
    ~SavingsAccount() override {
        cout << "[System] Savings features for " << accountNumber << " dismantled." << endl;
    }

    // Display Savings specific details
    void displayDetails() const override {
        Account::displayDetails();
        cout << " | Type: Savings | Int. Rate: " << interestRate << "%" << endl;
    }
};

// ==========================================
// 3. Derived Class: Current Account
// ==========================================
class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    // Constructor chaining to base class
    CurrentAccount(string accNum, double initialBalance, double limit)
        : Account(accNum, initialBalance), overdraftLimit(limit) {
        cout << "[System] Current features with Overdraft enabled." << endl;
    }

    // Destructor
    ~CurrentAccount() override {
        cout << "[System] Current features for " << accountNumber << " dismantled." << endl;
    }

    // Override withdraw to include overdraft logic
    void withdraw(double amount) override {
        if (amount > 0 && (balance + overdraftLimit) >= amount) {
            balance -= amount;
            history.push({WITHDRAW, amount});
            cout << "Withdrew: $" << fixed << setprecision(2) << amount
                 << " | New Balance: $" << balance << endl;
        } else {
             cout << "Withdrawal failed: Exceeds overdraft limit of $" << overdraftLimit << "." << endl;
        }
    }

    // Display Current specific details
    void displayDetails() const override {
        Account::displayDetails();
        cout << " | Type: Current | Overdraft Limit: $" << overdraftLimit << endl;
    }
};

// ==========================================
// Main Function
// ==========================================
int main() {
    cout << "=== Banking System Initialization ===" << endl;

    // Scoping block to demonstrate destructors triggering automatically at the end
    {
        cout << "\n--- Creating Accounts ---" << endl;
        SavingsAccount savings("SAV-1001", 1000.00, 3.5);
        CurrentAccount current("CUR-2001", 500.00, 1000.00); // Balance: 500, Overdraft: 1000

        cout << "\n--- Account Details ---" << endl;
        savings.displayDetails();
        current.displayDetails();

        cout << "\n--- Processing Savings Transactions ---" << endl;
        savings.deposit(200);
        savings.withdraw(150);
        savings.undoLastTransaction(); // Should revert the $150 withdrawal
        savings.displayDetails();

        cout << "\n--- Processing Current Transactions ---" << endl;
        current.withdraw(800); // Allowed due to overdraft (500 + 1000 = 1500 limit)
        current.withdraw(1000); // Should fail (Balance is now -300, only 700 overdraft left)
        current.undoLastTransaction(); // Should revert the $800 withdrawal
        current.displayDetails();

        cout << "\n--- Shutting Down System (Simulating Cleanup) ---" << endl;
    } // Objects go out of scope here, triggering destructors

    return 0;
}
