#include <iostream>
#include <vector>
#include <algorithm> // Required for std::reverse

using namespace std;

// Helper function to print the contents of a vector
void printVector(const string& message, const vector<int>& vec) {
    cout << message << ": ";
    for (vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";
}

int main() {
    vector<int> originalVec;
    int input;

    cout << "=== Vector Reversal Using Iterators ===\n";
    cout << "Enter a sequence of integers (enter any non-number character like 'q' to finish):\n";

    // Read integers until the user inputs a non-integer
    while (cin >> input) {
        originalVec.push_back(input);
    }

    if (originalVec.empty()) {
        cout << "No integers were entered. Exiting program." << endl;
        return 0;
    }

    cout << "\n----------------------------------------\n";
    printVector("Original Vector", originalVec);

    // =========================================================
    // Method 1: Reversal using std::reverse()
    // =========================================================
    vector<int> vec1 = originalVec; // Make a copy to preserve the original

    // std::reverse takes two iterators: the beginning and the end
    reverse(vec1.begin(), vec1.end());

    printVector("Method 1 (std::reverse)", vec1);

    // =========================================================
    // Method 2: Manual reversal using iterators
    // =========================================================
    vector<int> vec2 = originalVec; // Make another copy

    // Set up two iterators: one at the start, one at the last element
    // Note: vec2.end() points to the space *after* the last element, so we subtract 1.
    vector<int>::iterator left = vec2.begin();
    vector<int>::iterator right = vec2.end() - 1;

    // Loop until the two iterators meet or cross each other in the middle
    while (left < right) {
        // Swap the values pointed to by the iterators
        int temp = *left;
        *left = *right;
        *right = temp;

        // Alternatively, you could use the built-in swap function:
        // std::swap(*left, *right);

        // Move the iterators toward the center
        ++left;
        --right;
    }

    printVector("Method 2 (Manual Iterators)", vec2);
    cout << "----------------------------------------\n";

    return 0;
}
