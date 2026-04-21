
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Data structure
struct Book {
    int id;
    string title;
    string author;
    int copies;
};

// Global Data
vector<Book> library;

// Functions
void addBook() {
    Book b;
    cout << "Enter Book ID: ";
    cin >> b.id;
    cin.ignore();
    cout << "Enter Title: ";
    getline(cin, b.title);
    cout << "Enter Author: ";
    getline(cin, b.author);
    cout << "Enter Number of Copies: ";
    cin >> b.copies;

    library.push_back(b);
    cout << "Book added successfully!\n";
}

void issueBook() {
    int id;
    cout << "Enter Book ID to issue: ";
    cin >> id;

    for (int i = 0; i < library.size(); i++) {
        if (library[i].id == id) {
            if (library[i].copies > 0) {
                library[i].copies--;
                cout << "Book issued successfully!\n";
            } else {
                cout << "Sorry, no copies available.\n";
            }
            return;
        }
    }
    cout << "Book not found.\n";
}

void returnBook() {
    int id;
    cout << "Enter Book ID to return: ";
    cin >> id;

    for (int i = 0; i < library.size(); i++) {
        if (library[i].id == id) {
            library[i].copies++;
            cout << "Book returned successfully!\n";
            return;
        }
    }
    cout << "Book not found.\n";
}

void displayBooks() {
    cout << "\n--- Library Collection ---\n";
    for (const auto& b : library) {
        cout << "ID: " << b.id << " | Title: " << b.title
             << " | Author: " << b.author << " | Copies: " << b.copies << "\n";
    }
    cout << "--------------------------\n";
}

int main() {
    int choice;
    do {
        cout << "\n--- Procedural Library Menu ---\n";
        cout << "1. Add Book\n2. Issue Book\n3. Return Book\n4. Display Books\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addBook(); break;
            case 2: issueBook(); break;
            case 3: returnBook(); break;
            case 4: displayBooks(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
