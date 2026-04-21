#include <iostream>
#include <string>
#include <map>

using namespace std;

class DigitalWallet {
private:
    // Data Hiding: Attributes are private and cannot be accessed directly from outside
    string walletID;
    string userName;
    double balance;

public:
    // Default constructor (required for std::map)
    DigitalWallet() : walletID(""), userName(""), balance(0.0) {}

    // Parameterized constructor
    DigitalWallet(string id, string name, double initialBalance) {
        walletID = id;
        userName = name;
        if (initialBalance >= 0) {
            balance = initialBalance;
        } else {
            cout << "Initial balance cannot be negative. Setting to 0.0\n";
            balance = 0.0;
        }
    }

    // Encapsulation: Modifying balance through a controlled method
    void loadMoney(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Successfully loaded $" << amount << " into wallet " << walletID << ".\n";
        } else {
            cout << "Error: Amount to load must be greater than zero.\n";
        }
    }

    // Encapsulation: Business logic and validation handled internally
    void transferMoney(DigitalWallet& targetWallet, double amount) {
        if (amount <= 0) {
            cout << "Error: Transfer amount must be greater than zero.\n";
            return;
        }

        if (balance >= amount) {
            balance -= amount; // Deduct from sender
            targetWallet.balance += amount; // Add to receiver
            cout << "Success: Transferred $" << amount << " from " << walletID << " to " << targetWallet.getWalletID() << ".\n";
        } else {
            cout << "Error: Transfer failed. Insufficient balance! (Current Balance: $" << balance << ")\n";
        }
    }

    // Display method
    void displayDetails() const {
        cout << "\n--- Wallet Details ---\n";
        cout << "Wallet ID : " << walletID << "\n";
        cout << "User Name : " << userName << "\n";
        cout << "Balance   : $" << balance << "\n";
        cout << "----------------------\n";
    }

    // Getter for wallet ID
    string getWalletID() const {
        return walletID;
    }
};

int main() {
    // Using a map to store wallets using their unique walletID as the key
    map<string, DigitalWallet> systemWallets;
    int choice;

    do {
        cout << "\n=== Digital Wallet System ===\n";
        cout << "1. Create New Wallet\n";
        cout << "2. Load Money\n";
        cout << "3. Transfer Money\n";
        cout << "4. Check Wallet Details\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                string id, name;
                double initialAmount;
                cout << "Enter a unique Wallet ID: ";
                cin >> id;

                if (systemWallets.find(id) != systemWallets.end()) {
                    cout << "Error: Wallet ID already exists!\n";
                    break;
                }

                cout << "Enter User Name: ";
                cin.ignore(); // Clear newline character from buffer
                getline(cin, name);

                cout << "Enter initial balance: $";
                cin >> initialAmount;

                // Create and store the new wallet
                systemWallets[id] = DigitalWallet(id, name, initialAmount);
                cout << "Wallet created successfully!\n";
                break;
            }
            case 2: {
                string id;
                double amount;
                cout << "Enter Wallet ID to load money into: ";
                cin >> id;

                if (systemWallets.find(id) != systemWallets.end()) {
                    cout << "Enter amount to load: $";
                    cin >> amount;
                    systemWallets[id].loadMoney(amount);
                } else {
                    cout << "Error: Wallet not found!\n";
                }
                break;
            }
            case 3: {
                string senderId, receiverId;
                double amount;

                cout << "Enter your Wallet ID (Sender): ";
                cin >> senderId;
                cout << "Enter destination Wallet ID (Receiver): ";
                cin >> receiverId;

                // Verify both wallets exist
                if (systemWallets.find(senderId) != systemWallets.end() &&
                    systemWallets.find(receiverId) != systemWallets.end()) {

                    cout << "Enter amount to transfer: $";
                    cin >> amount;

                    // Execute transfer
                    systemWallets[senderId].transferMoney(systemWallets[receiverId], amount);
                } else {
                    cout << "Error: One or both Wallet IDs are invalid!\n";
                }
                break;
            }
            case 4: {
                string id;
                cout << "Enter Wallet ID to view details: ";
                cin >> id;

                if (systemWallets.find(id) != systemWallets.end()) {
                    systemWallets[id].displayDetails();
                } else {
                    cout << "Error: Wallet not found!\n";
                }
                break;
            }
            case 5:
                cout << "Exiting system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
