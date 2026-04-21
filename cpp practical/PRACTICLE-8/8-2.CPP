#include <iostream>
#include <cmath>
#include <exception>
#include <string>

using namespace std;

// ==========================================
// Custom Exception Class Definition
// ==========================================
// Inheriting from std::exception is standard practice in C++
class NegativeNumberException : public exception {
private:
    string errorMessage;

public:
    // Constructor to format the error message with the invalid number
    NegativeNumberException(double invalidValue) {
        errorMessage = "Error: Cannot compute the square root of a negative number (" + to_string(invalidValue) + ").";
    }

    // Overriding the standard what() method to return our custom message
    // 'noexcept' guarantees this function itself won't throw an exception
    const char* what() const noexcept override {
        return errorMessage.c_str();
    }
};

// ==========================================
// Main Function
// ==========================================
int main() {
    cout << "=== Square Root Calculator ===" << endl;
    cout << "(Enter any letter to quit the program)\n" << endl;

    double number;
    cout << "Enter a number: ";

    // The loop processes one input at a time independently
    while (cin >> number) {
        try {
            // 1. Check for the error condition IMMEDIATELY
            if (number < 0) {
                // Throw our custom exception object
                throw NegativeNumberException(number);
            }

            // 2. If no exception is thrown, calculate and print the square root
            double result = sqrt(number);
            cout << "Success: The square root of " << number << " is " << result << "\n" << endl;

        }
        // 3. Catch specifically our custom exception
        catch (const NegativeNumberException& e) {
            cout << ">>> Exception Caught! " << e.what() << "\n" << endl;
        }

        cout << "Enter another number: ";
    }

    cout << "\nProgram terminated safely." << endl;
    return 0;
}
