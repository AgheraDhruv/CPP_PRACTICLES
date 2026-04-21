#include <iostream>
#include <string>
using namespace std;

class Account {
private:
    string name;
    int accID;
    double balance;

public:
    // Constructor with zero balance
    Account(string n, int id) {
        name = n;
        accID = id;
        balance = 0;
    }

    // Constructor with custom initial balance
    Account(string n, int id, double bal) {
        name = n;
        accID = id;
        balance = bal;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit Successful!\n";
        } else {
            cout << "Invalid Deposit Amount!\n";
        }
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid Withdrawal Amount!\n";
        }
        else if (amount > balance) {
            cout << "Insufficient Balance! Withdrawal Denied.\n";
        }
        else {
            balance -= amount;
            cout << "Withdrawal Successful!\n";
        }
    }

    void display() {
        cout << "\n--- Account Summary ---";
        cout << "\nCustomer Name : " << name;
        cout << "\nAccount ID    : " << accID;
        cout << "\nBalance       : " << balance << "\n";
    }
};

int main() {
    int n;
    cout << "Enter number of accounts to create: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        string name;
        int id;
        double bal;

        cout << "\nEnter customer name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter account ID: ";
        cin >> id;

        cout << "Enter initial balance (0 for zero balance): ";
        cin >> bal;

        Account acc = (bal == 0) ? Account(name, id) : Account(name, id, bal);

        int choice;
        do {
            cout << "\n1. Deposit\n2. Withdraw\n3. Display Summary\n4. Next Account\nEnter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    double amt;
                    cout << "Enter deposit amount: ";
                    cin >> amt;
                    acc.deposit(amt);
                    break;
                }
                case 2: {
                    double amt;
                    cout << "Enter withdrawal amount: ";
                    cin >> amt;
                    acc.withdraw(amt);
                    break;
                }
                case 3:
                    acc.display();
                    break;
                case 4:
                    cout << "Moving to next account...\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
            }
        } while (choice != 4);
    }

    return 0;
}

