#include <iostream>
#include <queue>
#include <cmath>
#include <iomanip>

using namespace std;

// Forward declaration of Fahrenheit so Celsius can reference it
class Fahrenheit;

// ==========================================
// 1. Celsius Class
// ==========================================
class Celsius {
private:
    double temperature;

public:
    Celsius(double t = 0.0) : temperature(t) {}

    double getTemp() const { return temperature; }

    void display() const {
        cout << fixed << setprecision(2) << temperature << " °C";
    }

    // Declaration of type-conversion operator to Fahrenheit
    operator Fahrenheit() const;

    // Declaration of equality operator comparing Celsius to Fahrenheit
    bool operator==(const Fahrenheit& f) const;
};

// ==========================================
// 2. Fahrenheit Class
// ==========================================
class Fahrenheit {
private:
    double temperature;

public:
    Fahrenheit(double t = 0.0) : temperature(t) {}

    double getTemp() const { return temperature; }

    void display() const {
        cout << fixed << setprecision(2) << temperature << " °F";
    }

    // Declaration of type-conversion operator to Celsius
    operator Celsius() const;

    // Declaration of equality operator comparing Fahrenheit to Celsius
    bool operator==(const Celsius& c) const;
};

// ==========================================
// Method Implementations
// ==========================================

// Celsius to Fahrenheit Conversion logic: (C * 9/5) + 32
Celsius::operator Fahrenheit() const {
    return Fahrenheit((temperature * 9.0 / 5.0) + 32.0);
}

// Fahrenheit to Celsius Conversion logic: (F - 32) * 5/9
Fahrenheit::operator Celsius() const {
    return Celsius((temperature - 32.0) * 5.0 / 9.0);
}

// Equality Operator: Celsius == Fahrenheit
bool Celsius::operator==(const Fahrenheit& f) const {
    Fahrenheit converted = *this; // Implicitly uses the conversion operator
    // Using a small epsilon (0.001) for safe floating-point comparison
    return abs(converted.getTemp() - f.getTemp()) < 0.001;
}

// Equality Operator: Fahrenheit == Celsius
bool Fahrenheit::operator==(const Celsius& c) const {
    Celsius converted = *this; // Implicitly uses the conversion operator
    return abs(converted.getTemp() - c.getTemp()) < 0.001;
}

// ==========================================
// Main Function
// ==========================================
int main() {
    cout << "=== Weather App: Temperature Conversion System ===" << endl << endl;

    // ---------------------------------------------------------
    // 1. Basic Conversion & Equality Testing
    // ---------------------------------------------------------
    cout << "--- Standard Conversions ---" << endl;
    Celsius c1(0.0);       // Freezing point in Celsius
    Fahrenheit f1(32.0);   // Freezing point in Fahrenheit

    Celsius c2(100.0);     // Boiling point in Celsius

    // Implicit Type Conversion working here
    Fahrenheit convertedF = c2;
    Celsius convertedC = f1;

    cout << "Converted "; c2.display(); cout << " to "; convertedF.display(); cout << endl;
    cout << "Converted "; f1.display(); cout << " to "; convertedC.display(); cout << endl;

    // Testing the Overloaded Equality Operator
    cout << "\n--- Equality Operator Testing ---" << endl;
    if (c1 == f1) {
        c1.display(); cout << " is perfectly equal to "; f1.display(); cout << endl;
    } else {
        cout << "Temperatures are not equal." << endl;
    }

    // ---------------------------------------------------------
    // 2. Storage Approach 1: Static Array Storage
    // ---------------------------------------------------------
    cout << "\n--- Storage Method 1: Fixed Array (Celsius to Fahrenheit) ---" << endl;
    const int BATCH_SIZE = 3;
    Celsius myCelsiusReadings[BATCH_SIZE] = { Celsius(10.0), Celsius(25.5), Celsius(30.0) };
    Fahrenheit myFahrenheitStorage[BATCH_SIZE];

    cout << "Processing Static Array..." << endl;
    for (int i = 0; i < BATCH_SIZE; ++i) {
        // Automatically converts Celsius objects to Fahrenheit and stores them
        myFahrenheitStorage[i] = myCelsiusReadings[i];

        cout << "Index [" << i << "]: ";
        myCelsiusReadings[i].display(); cout << " -> ";
        myFahrenheitStorage[i].display(); cout << endl;
    }

    // ---------------------------------------------------------
    // 3. Storage Approach 2: Dynamic Queue (FIFO)
    // ---------------------------------------------------------
    cout << "\n--- Storage Method 2: Dynamic Queue (Fahrenheit to Celsius) ---" << endl;
    queue<Fahrenheit> fQueue;

    // Enqueue incoming sensor data
    fQueue.push(Fahrenheit(68.0));
    fQueue.push(Fahrenheit(85.5));
    fQueue.push(Fahrenheit(104.0));

    cout << "Processing Dynamic Queue (FIFO)..." << endl;
    int popCount = 1;
    while (!fQueue.empty()) {
        Fahrenheit currentF = fQueue.front();
        Celsius convertedC = currentF; // Convert to Celsius as it leaves the queue

        cout << "Pop #" << popCount++ << ": ";
        currentF.display(); cout << " -> ";
        convertedC.display(); cout << endl;

        fQueue.pop(); // Remove processed item
    }

    return 0;
}
