#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// ==========================================
// Global Logging System (Using a basic array)
// ==========================================
const int MAX_LOGS = 100;
string transactionLogs[MAX_LOGS];
int logIndex = 0;

// Helper function to safely add messages to our log array
void logMessage(const string& message) {
    if (logIndex < MAX_LOGS) {
        transactionLogs[logIndex] = message;
        logIndex++;
    }
}

// ==========================================
// BankAccount Class Definition
// ==========================================
class BankAccount {
private:
    double balance;

public:
    BankAccount(double initialBalance) {
        if (initialBalance < 0) {
            balance = 0;
        } else {
            balance = initialBalance;
        }
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        logMessage("  -> Entering BankAccount::deposit()");
        if (amount <= 0) {
            throw invalid_argument("Deposit amount must be strictly greater than zero.");
        }
        balance += amount;
        logMessage("  <- Exiting BankAccount::deposit() [Success]");
    }

    void withdraw(double amount) {
        logMessage("      -> Entering BankAccount::withdraw()");

        if (amount <= 0) {
            throw invalid_argument("Withdrawal amount must be strictly greater than zero.");
        }
        if (amount > balance) {
            // This is where the exception is thrown for our test case
            throw runtime_error("Overdraft Error: Insufficient funds for this withdrawal.");
        }

        balance -= amount;

        // If an exception is thrown above, this line will NEVER execute
        logMessage("      <- Exiting BankAccount::withdraw() [Success]");
    }
};

// ==========================================
// Transaction Processing Chain
// ==========================================

void performWithdrawal(BankAccount& account, double amount) {
    logMessage("    -> Entering performWithdrawal()");

    account.withdraw(amount);

    // If withdraw() throws, stack unwinding skips this line
    logMessage("    <- Exiting performWithdrawal() [Success]");
}

void processTransaction(BankAccount& account, double amount) {
    logMessage("  -> Entering processTransaction()");

    performWithdrawal(account, amount);

    // If performWithdrawal() propagates an exception, this is skipped
    logMessage("  <- Exiting processTransaction() [Success]");
}

// ==========================================
// Main Function
// ==========================================
int main() {
    cout << "=== Banking System Initiated ===" << endl;
    BankAccount myAccount(100.0); // Starting with $100

    logMessage("[System] Initial Balance: $" + to_string(myAccount.getBalance()));

    // 1. A successful transaction to show normal flow
    try {
        logMessage("\n[System] Attempting valid deposit of $50...");
        myAccount.deposit(50.0);
    } catch (const exception& e) {
        logMessage(string("[Exception Caught]: ") + e.what());
    }

    // 2. A failing transaction to demonstrate stack unwinding
    try {
        logMessage("\n[System] Attempting invalid withdrawal of $200...");
        logMessage("-> Entering main() try block");

        // This will trigger the exception chain
        processTransaction(myAccount, 200.0);

        logMessage("<- Exiting main() try block [Success]");
    }
    catch (const exception& e) {
        // Stack unwinding brings control directly here
        logMessage(string("-> [Exception Caught in main]: ") + e.what());
    }

    logMessage("\n[System] Final Balance: $" + to_string(myAccount.getBalance()));

    // ==========================================
    // Displaying the Logs
    // ==========================================
    cout << "\n=== Transaction Execution Log ===" << endl;
    for (int i = 0; i < logIndex; i++) {
        cout << transactionLogs[i] << endl;
    }

    cout << "\nNotice in the log above that after the Overdraft Error is thrown, the program skips the 'Exiting' logs for performWithdrawal() and processTransaction(). This is stack unwinding in action!" << endl;

    return 0;
}
