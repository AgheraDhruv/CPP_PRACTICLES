#include <iostream>
#include <stdexcept>
#include <limits>

using namespace std;

int main() {
    cout << "=== Immediate Evaluation Division ===" << endl;

    try {
        int numerator, denominator;
        cout << "Enter two integers (Numerator Denominator): ";

        // 1. Extract and immediately validate the numerator
        if (!(cin >> numerator)) {
            throw invalid_argument("Non-integer input detected for the numerator.");
        }

        // 2. Extract and immediately validate the denominator
        if (!(cin >> denominator)) {
            throw invalid_argument("Non-integer input detected for the denominator.");
        }

        // 3. Immediately evaluate for Division by Zero
        if (denominator == 0) {
            throw runtime_error("Math Error: Cannot divide by zero.");
        }

        // If all immediate checks pass, perform and display the division
        double result = static_cast<double>(numerator) / denominator;
        cout << "Result: " << result << endl;

    }
    // Catching the invalid input exceptions (e.g., entering "A" instead of 5)
    catch (const invalid_argument& e) {
        cout << "\nException Caught: " << e.what() << endl;

        // Clean up the input stream so the program doesn't get stuck in an error state
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    // Catching the mathematical runtime exceptions
    catch (const runtime_error& e) {
        cout << "\nException Caught: " << e.what() << endl;
    }

    cout << "Program execution continues safely..." << endl;

    return 0;
}
