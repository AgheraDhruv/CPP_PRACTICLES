#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Define the file name where inventory data will be stored
const string FILE_NAME = "inventory.txt";

// 1. Function to add a new item to the file
void addItem() {
    // Open file in append mode so new items are added to the end
    ofstream file(FILE_NAME, ios::app);
    if (!file) {
        cout << "Error: Unable to open file for writing!" << endl;
        return;
    }

    string name;
    int quantity;
    double price;

    cout << "\n--- Add New Item ---" << endl;
    cout << "Enter Item Name (single word/no spaces): ";
    cin >> name;
    cout << "Enter Quantity: ";
    cin >> quantity;
    cout << "Enter Price: ";
    cin >> price;

    // Write the data to the file separated by spaces
    file << name << " " << quantity << " " << price << "\n";
    file.close();

    cout << "Item '" << name << "' added successfully!" << endl;
}

// 2. Function to view all items stored in the file
void viewItems() {
    // Open file in read mode
    ifstream file(FILE_NAME);
    if (!file) {
        cout << "\nNo inventory data found. The file might be empty or doesn't exist yet." << endl;
        return;
    }

    string name;
    int quantity;
    double price;

    cout << "\n--- Inventory List ---" << endl;
    // Formatting the output into aligned columns
    cout << left << setw(20) << "Item Name" << setw(15) << "Quantity" << "Price" << endl;
    cout << "---------------------------------------------------" << endl;

    // Sequentially read until the End Of File (EOF)
    while (file >> name >> quantity >> price) {
        cout << left << setw(20) << name << setw(15) << quantity << "$" << fixed << setprecision(2) << price << endl;
    }

    file.close();
    cout << "---------------------------------------------------" << endl;
}

// 3. Function to search for an item by its name
void searchItem() {
    ifstream file(FILE_NAME);
    if (!file) {
        cout << "\nNo inventory data found." << endl;
        return;
    }

    string searchName;
    cout << "\nEnter the exact name of the item to search: ";
    cin >> searchName;

    string name;
    int quantity;
    double price;
    bool found = false;

    // Sequentially read each record and compare the name
    while (file >> name >> quantity >> price) {
        if (name == searchName) {
            cout << "\n--- Item Found ---" << endl;
            cout << "Name:     " << name << endl;
            cout << "Quantity: " << quantity << endl;
            cout << "Price:    $" << fixed << setprecision(2) << price << endl;
            found = true;
            break; // Stop searching once the item is found
        }
    }

    if (!found) {
        cout << "\nItem '" << searchName << "' was not found in the inventory." << endl;
    }

    file.close();
}

// Main function to run the menu-driven program
int main() {
    int choice;

    do {
        cout << "\n=== Inventory Management System ===" << endl;
        cout << "1. Add Item" << endl;
        cout << "2. View All Items" << endl;
        cout << "3. Search Item by Name" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice (1-4): ";

        // Input validation to prevent infinite loops if a user enters a letter
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = 0;
        }

        switch (choice) {
            case 1:
                addItem();
                break;
            case 2:
                viewItems();
                break;
            case 3:
                searchItem();
                break;
            case 4:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
        }
    } while (choice != 4);

    return 0;
}
