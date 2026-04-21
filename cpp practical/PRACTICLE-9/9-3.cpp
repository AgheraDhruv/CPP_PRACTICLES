#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
    // std::set automatically stores only unique elements in sorted (ascending) order
    set<int> uniqueNumbers;
    int input;

    cout << "=== Duplicate Removal Using std::set ===\n";
    cout << "Enter a sequence of integers, including some duplicates.\n";
    cout << "(Enter any letter, like 'q', to finish inputting):\n";

    // Read integers until the user inputs a non-integer character
    while (cin >> input) {
        // insert() adds the element. If it already exists, the set ignores it.
        uniqueNumbers.insert(input);
    }

    if (uniqueNumbers.empty()) {
        cout << "No integers were entered. Exiting program." << endl;
        return 0;
    }

    cout << "\n----------------------------------------\n";
    cout << "Data processed! Duplicates removed and numbers sorted.\n\n";

    // =========================================================
    // Method 1: Direct traversal of the set using iterators
    // =========================================================
    cout << "Direct Set Traversal: \n";
    cout << "[ ";
    for (set<int>::const_iterator it = uniqueNumbers.begin(); it != uniqueNumbers.end(); ++it) {
        cout << *it << " ";
    }
    cout << "]\n\n";

    // =========================================================
    // Method 2: Converting the set to a vector using iterators
    // =========================================================
    cout << "Converting std::set to std::vector...\n";

    // You can initialize a vector by passing it the beginning and ending iterators of another container
    vector<int> uniqueVector(uniqueNumbers.begin(), uniqueNumbers.end());

    cout << "Vector Traversal: \n";
    cout << "[ ";
    for (vector<int>::const_iterator it = uniqueVector.begin(); it != uniqueVector.end(); ++it) {
        cout << *it << " ";
    }
    cout << "]\n";

    cout << "----------------------------------------\n";

    return 0;
}
