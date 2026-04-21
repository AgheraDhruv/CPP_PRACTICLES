#include <iostream>
#include <limits>

using namespace std;

class DynamicArray {
private:
    int* arr;       // Raw pointer to the dynamically allocated array
    int capacity;   // Total memory capacity currently allocated
    int size;       // Number of actual elements currently in the array

    // Helper function to handle memory reallocation when the array gets full
    void resize() {
        capacity *= 2; // Double the capacity
        int* temp = new int[capacity]; // Allocate new, larger memory block

        // Copy existing elements to the new block
        for (int i = 0; i < size; i++) {
            temp[i] = arr[i];
        }

        delete[] arr; // Free the old memory block to prevent memory leaks
        arr = temp;   // Point arr to the new memory block
    }

public:
    // Constructor
    DynamicArray(int initialCapacity = 2) {
        capacity = initialCapacity;
        size = 0;
        arr = new int[capacity];
    }

    // Destructor: CRITICAL for raw pointers to ensure memory is released when the object is destroyed
    ~DynamicArray() {
        delete[] arr;
    }

    // 1. Insert an element at the end
    void insert(int value) {
        // Check if there is enough space; if not, resize the array
        if (size == capacity) {
            resize();
        }
        arr[size] = value;
        size++;
        cout << "Success: Inserted " << value << ".\n";
    }

    // 2. Delete an element from a specified position
    void removeAt(int index) {
        if (index < 0 || index >= size) {
            cout << "Error: Invalid index. Valid range is 0 to " << (size > 0 ? size - 1 : 0) << ".\n";
            return;
        }

        // Shift elements to the left to overwrite the deleted element and fill the gap
        for (int i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
        cout << "Success: Element at position " << index << " deleted.\n";
    }

    // 3. Display the current array contents
    void display() const {
        if (size == 0) {
            cout << "The array is currently empty.\n";
            return;
        }
        cout << "\n--- Array Contents ---\n";
        cout << "Elements : [ ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << "]\n";
        cout << "Metrics  : Size = " << size << " | Capacity = " << capacity << "\n";
        cout << "----------------------\n";
    }
};

int main() {
    // Instantiate the custom dynamic array
    DynamicArray myArr;
    int choice;

    cout << "=== Lightweight Dynamic Array Manager ===\n";

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert an element at the end\n";
        cout << "2. Delete an element by position (index)\n";
        cout << "3. Display array contents\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        // Input validation to prevent infinite loops on bad input
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                int val;
                cout << "Enter the integer to insert: ";
                cin >> val;
                myArr.insert(val);
                break;
            }
            case 2: {
                int pos;
                cout << "Enter the position (0-based index) to delete: ";
                cin >> pos;
                myArr.removeAt(pos);
                break;
            }
            case 3:
                myArr.display();
                break;
            case 4:
                cout << "Exiting system. Memory will be safely deallocated. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please select an option between 1 and 4.\n";
        }
    } while (choice != 4);

    return 0;
}
