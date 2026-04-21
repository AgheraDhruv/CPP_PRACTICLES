#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// ==========================================
// Complex Number Class Definition
// ==========================================
class Complex {
private:
    double real;
    double imag;

public:
    // Constructor with default arguments
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // ---------------------------------------------------------
    // Operator Overloads
    // ---------------------------------------------------------

    // Overload the + operator to add two complex numbers
    Complex operator+(const Complex& other) const {
        return Complex(this->real + other.real, this->imag + other.imag);
    }

    // Overload the - operator to subtract two complex numbers
    Complex operator-(const Complex& other) const {
        return Complex(this->real - other.real, this->imag - other.imag);
    }

    // Overload the << operator for intuitive and clean printing
    friend ostream& operator<<(ostream& os, const Complex& c) {
        os << c.real << (c.imag >= 0 ? " + " : " - ") << abs(c.imag) << "i";
        return os;
    }

    // Getters (optional, but good for data extraction if needed)
    double getReal() const { return real; }
    double getImag() const { return imag; }
};

// ==========================================
// Main Function: Testing & Batch Operations
// ==========================================
int main() {
    cout << "=== Complex Number Computational Model ===" << endl << endl;

    // ---------------------------------------------------------
    // 1. Basic Operator Testing
    // ---------------------------------------------------------
    cout << "--- Standard Operations ---" << endl;
    Complex c1(4.5, 2.0);
    Complex c2(1.5, -3.5);

    // Using the overloaded + and - operators just like standard primitives
    Complex sum = c1 + c2;
    Complex diff = c1 - c2;

    cout << "C1:   " << c1 << endl;
    cout << "C2:   " << c2 << endl;
    cout << "Sum:  " << sum << "  (C1 + C2)" << endl;
    cout << "Diff: " << diff << "  (C1 - C2)" << endl << endl;

    // ---------------------------------------------------------
    // 2. Batch Operations (Collection Management)
    // ---------------------------------------------------------
    cout << "--- Batch Operations (Summing a Collection) ---" << endl;

    // Storing multiple complex objects in a flexible vector
    vector<Complex> complexBatch = {
        Complex(1.0, 2.0),
        Complex(3.0, 4.0),
        Complex(-2.0, 1.0),
        Complex(0.0, -5.0)
    };

    // Initializing a variable to hold the running total
    Complex totalSum(0.0, 0.0);

    cout << "Processing Batch:" << endl;
    for (size_t i = 0; i < complexBatch.size(); ++i) {
        cout << "  Value " << i + 1 << ": " << complexBatch[i] << endl;

        // Leveraging the overloaded + operator to sum the entire array
        totalSum = totalSum + complexBatch[i];
    }

    cout << "\nTotal Batch Sum: " << totalSum << endl;

    return 0;
}
