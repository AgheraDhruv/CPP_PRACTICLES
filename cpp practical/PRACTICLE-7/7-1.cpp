#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// ==========================================
// Calculator Class Definition
// ==========================================
class Calculator {
private:
    // Vector to store the sequential outcomes as formatted strings
    vector<string> history;

    // Private helper template to keep our history formatting clean
    template <typename T1, typename T2, typename Res>
    void recordHistory(const string& functionSignature, T1 a, T2 b, Res result) {
        ostringstream oss;
        oss << left << functionSignature << " -> " << a << " + " << b << " = " << result;
        history.push_back(oss.str());
    }

    // Overloaded helper for 3 parameters
    void recordHistory(const string& functionSignature, int a, int b, int c, int result) {
        ostringstream oss;
        oss << left << functionSignature << " -> " << a << " + " << b << " + " << c << " = " << result;
        history.push_back(oss.str());
    }

public:
    // ---------------------------------------------------------
    // Function Overloading: Multiple versions of add()
    // ---------------------------------------------------------

    // 1. Two Integers
    int add(int a, int b) {
        int result = a + b;
        recordHistory("add(int, int)", a, b, result);
        return result;
    }

    // 2. Two Floating-point numbers (Double)
    double add(double a, double b) {
        double result = a + b;
        recordHistory("add(double, double)", a, b, result);
        return result;
    }

    // 3. Mixed Types: Integer first, Double second
    double add(int a, double b) {
        double result = a + b;
        recordHistory("add(int, double)", a, b, result);
        return result;
    }

    // 4. Mixed Types: Double first, Integer second
    double add(double a, int b) {
        double result = a + b;
        recordHistory("add(double, int)", a, b, result);
        return result;
    }

    // 5. Different Parameter Count: Three Integers
    int add(int a, int b, int c) {
        int result = a + b + c;
        recordHistory("add(int, int, int)", a, b, c, result);
        return result;
    }

    // ---------------------------------------------------------
    // History Management
    // ---------------------------------------------------------

    // Method to sequentially process and display the stored outcomes
    void displayResults() const {
        cout << "\n=== Calculation History ===" << endl;
        if (history.empty()) {
            cout << "No calculations performed yet." << endl;
            return;
        }

        // Iterate through the vector and display each formatted string
        for (size_t i = 0; i < history.size(); ++i) {
            cout << "[" << i + 1 << "] " << history[i] << endl;
        }
        cout << "===========================\n" << endl;
    }
};

// ==========================================
// Main Function: Testing the Scenarios
// ==========================================
int main() {
    Calculator calc;

    cout << "Starting Calculator Overloading Tests...\n";

    // Test Case 1: Two integers
    int res1 = calc.add(10, 20);

    // Test Case 2: Two floating-point numbers
    double res2 = calc.add(15.5, 4.2);

    // Test Case 3: Mixed (int, double)
    double res3 = calc.add(5, 10.75);

    // Test Case 4: Mixed (double, int)
    double res4 = calc.add(99.9, 1);

    // Test Case 5: Three integers (testing parameter count change)
    int res5 = calc.add(5, 10, 15);

    // Displaying the results sequentially from the stored history
    calc.displayResults();

    return 0;
}
