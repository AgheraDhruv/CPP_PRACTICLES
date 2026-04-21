#include <iostream>
#include <string>

using namespace std;

// Recursive function to calculate the super digit
int superDigit(string s) {
    // Base Case: If the string has only 1 digit, it is the super digit.
    if (s.length() == 1) {
        return s[0] - '0'; // Convert char to integer
    }

    // Recursive Step: Sum the digits of the current string
    long long sum = 0;
    for (char c : s) {
        sum += c - '0';
    }

    // Convert the sum back to a string and call the function recursively
    return superDigit(to_string(sum));
}

int main() {
    string n;
    int k;

    cout << "=== Super Digit Calculator ===\n";
    cout << "Enter the string representation of the number (n): ";
    cin >> n;

    cout << "Enter the number of concatenations (k): ";
    cin >> k;

    // Mathematical Optimization Step:
    // Instead of concatenating the string k times, calculate the sum
    // of the digits of 'n' once, and multiply it by 'k'.
    long long initialSum = 0;
    for (char c : n) {
        initialSum += c - '0';
    }

    initialSum *= k;

    // Pass the simplified initial sum into the recursive function
    int result = superDigit(to_string(initialSum));

    cout << "\nCalculating...\n";
    cout << "The Super Digit is: " << result << "\n";

    return 0;
}
