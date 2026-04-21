
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    string accountHolderName;
    double balance;

    // Static data member to track the total number of accounts created
    static int totalAccounts;

public:
    // Constructor
    BankAccount(int accNum, string name, double initialBalance) {
        accountNumber = accNum;
        accountHolderName = name;
        if (initialBalance >= 0) {
            balance = initialBalance;
        } else {
            cout << "Warning: Initial balance cannot be negative. Setting to $0.00.\n";
            balance = 0.0;
        }
        // Increment the static variable every time a new account is created
        totalAccounts++;
    }

    // Getters
    int getAccountNumber() const { return accountNumber; }
    string getAccountHolderName() const { return accountHolderName; }
    double getBalance() const { return balance; }

    // Setter to update account information
    void updateAccountName(string newName) {
        accountHolderName = newName;
        cout << "Account name updated successfully to: " << accountHolderName << "\n";
    }

    // Static member function to access the static data member
    static int getTotalAccounts() {
        return totalAccounts;
    }

    // Method to transfer money securely
    void transferMoney(BankAccount& receiver, double amount) {
        if (amount <= 0) {
            cout << "Error: Transfer amount must be greater than zero.\n";
            return;
        }
        if (balance >= amount) {
            balance -= amount;               // Deduct from sender
            receiver.balance += amount;      // Add to receiver
            cout << "Success: Transferred $" << fixed << setprecision(2) << amount
                 << " to Account #" << receiver.getAccountNumber() << ".\n";
        } else {
            cout << "Error: Insufficient funds! Current Balance: $"
                 << fixed << setprecision(2) << balance << "\n";
        }
    }

    // Method to display account summary
    void displaySummary() const {
        cout << left << setw(15) << accountNumber
             << setw(25) << accountHolderName
             << "$" << fixed << setprecision(2) << balance << "\n";
    }
};

// Initialize the static data member outside the class
int BankAccount::totalAccounts = 0;

// Helper function to find an account index by account number
int findAccountIndex(const vector<BankAccount>& accounts, int accNum) {
    for (size_t i = 0; i < accounts.size(); i++) {
        if (accounts[i].getAccountNumber() == accNum) {
            return i;
        }
    }
    return -1; // Return -1 if account is not found
}

int main() {
    // Dynamic storage for scalability
    vector<BankAccount> bankDatabase;
    int choice;

    cout << "=== Community Bank Account Management System ===\n";

    do {
        cout << "\nMenu:\n";
        cout << "1. Open New Account\n";
        cout << "2. Update Account Holder Name\n";
        cout << "3. Transfer Money\n";
        cout << "4. Display All Accounts\n";
        cout << "5. View Bank Analytics (Total Accounts Created)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        // Input validation
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                int accNum;
                string name;
                double initialDeposit;

                cout << "Enter a new Account Number: ";
                cin >> accNum;

                // Ensure account number is unique
                if (findAccountIndex(bankDatabase, accNum) != -1) {
                    cout << "Error: Account number already exists!\n";
                    break;
                }

                cout << "Enter Account Holder's Name: ";
                cin.ignore();
                getline(cin, name);

                cout << "Enter Initial Deposit: $";
                cin >> initialDeposit;

                bankDatabase.push_back(BankAccount(accNum, name, initialDeposit));
                cout << "Account created successfully!\n";
                break;
            }
            case 2: {
                int accNum;
                cout << "Enter Account Number to update: ";
                cin >> accNum;

                int index = findAccountIndex(bankDatabase, accNum);
                if (index != -1) {
                    string newName;
                    cout << "Enter the new Account Holder Name: ";
                    cin.ignore();
                    getline(cin, newName);
                    bankDatabase[index].updateAccountName(newName);
                } else {
                    cout << "Error: Account not found.\n";
                }
                break;
            }
            case 3: {
                int senderAcc, receiverAcc;
                double amount;

                cout << "Enter Sender's Account Number: ";
                cin >> senderAcc;
                cout << "Enter Receiver's Account Number: ";
                cin >> receiverAcc;

                int senderIdx = findAccountIndex(bankDatabase, senderAcc);
                int receiverIdx = findAccountIndex(bankDatabase, receiverAcc);

                if (senderIdx != -1 && receiverIdx != -1) {
                    if (senderIdx == receiverIdx) {
                        cout << "Error: Cannot transfer money to the same account.\n";
                    } else {
                        cout << "Enter amount to transfer: $";
                        cin >> amount;
                        // Execute transfer
                        bankDatabase[senderIdx].transferMoney(bankDatabase[receiverIdx], amount);
                    }
                } else {
                    cout << "Error: One or both account numbers are invalid.\n";
                }
                break;
            }
            case 4: {
                if (bankDatabase.empty()) {
                    cout << "No accounts to display.\n";
                } else {
                    cout << "\n--- Bank Account Summaries ---\n";
                    cout << left << setw(15) << "Account No."
                         << setw(25) << "Account Holder"
                         << "Balance\n";
                    cout << "--------------------------------------------------\n";
                    for (const auto& account : bankDatabase) {
                        account.displaySummary();
                    }
                    cout << "--------------------------------------------------\n";
                }
                break;
            }
            case 5: {
                // Calling the static function directly using the class name
                cout << "\n--- Bank Analytics ---\n";
                cout << "Total accounts ever created: " << BankAccount::getTotalAccounts() << "\n";
                cout << "Active accounts in database: " << bankDatabase.size() << "\n";
                break;
            }
            case 6:
                cout << "Shutting down system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please select an option from 1 to 6.\n";
        }
    } while (choice != 6);

    return 0;
}
