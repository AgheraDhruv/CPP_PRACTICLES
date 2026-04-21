#include <iostream>
#include <string>
using namespace std;

class Item {
private:
    int id;
    string name;
    double price;
    int quantity;

public:
    // Default Constructor
    Item() {
        id = 0;
        name = "Default Item";
        price = 0.0;
        quantity = 0;
    }

    // Parameterized Constructor
    Item(int i, string n, double p, int q) {
        id = i;
        name = n;
        price = p;
        quantity = q;
    }

    void addStock(int qty) {
        if (qty > 0)
            quantity += qty;
        else
            cout << "Invalid stock amount!\n";
    }

    void sellItem(int qty) {
        if (qty <= 0)
            cout << "Invalid sale quantity!\n";
        else if (qty > quantity)
            cout << "Insufficient stock! Sale denied.\n";
        else
            quantity -= qty;
    }

    void display() {
        cout << "\n--- Item Details ---";
        cout << "\nItem ID   : " << id;
        cout << "\nName      : " << name;
        cout << "\nPrice     : " << price;
        cout << "\nQuantity  : " << quantity << "\n";
    }
};

int main() {
    int n;
    cout << "Enter number of items: ";
    cin >> n;

    Item items[n];

    // Default initialization test
    cout << "\n--- Default Item Example ---";
    items[0].display();

    // Parameterized initialization
    for (int i = 0; i < n; i++) {
        int id, qty;
        double price;
        string name;

        cout << "\nEnter details for item " << i + 1 << endl;
        cout << "ID: ";
        cin >> id;
        cin.ignore();

        cout << "Name: ";
        getline(cin, name);

        cout << "Price: ";
        cin >> price;

        cout << "Quantity: ";
        cin >> qty;

        items[i] = Item(id, name, price, qty);
    }

    // Stock operations
    for (int i = 0; i < n; i++) {
        int add, sell;

        cout << "\nStock update for " << i + 1 << " item\n";
        cout << "Add stock: ";
        cin >> add;
        items[i].addStock(add);

        cout << "Sell quantity: ";
        cin >> sell;
        items[i].sellItem(sell);
    }

    // Display final data
    cout << "\n--- Final Inventory Status ---";
    for (int i = 0; i < n; i++)
        items[i].display();

    return 0;
}
