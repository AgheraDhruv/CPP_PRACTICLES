#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Define PI for area calculation
const double PI = 3.14159265358979323846;

// 1. Base Class: Shape
class Shape {
private:
    double radius; // Encapsulated data member

public:
    // Default constructor
    Shape() : radius(0.0) {}

    // Setter: Ensures controlled access and validation
    void setRadius(double r) {
        if (r >= 0) {
            radius = r;
        } else {
            cout << "Warning: Radius cannot be negative. Setting to 0." << endl;
            radius = 0;
        }
    }

    // Getter: Allows derived classes and external functions to read the radius
    double getRadius() const {
        return radius;
    }
};

// 2. Derived Class: Circle
class Circle : public Shape {
public:
    // Method to compute the area of the circle
    double calculateArea() const {
        // Accessing radius via the public getter method from the base class
        return PI * getRadius() * getRadius();
    }
};

// Helper function to cleanly display results
void displayCircleData(const string& methodType, int index, double radius, double area) {
    cout << left << setw(15) << methodType
         << "Circle " << index + 1 << " | "
         << "Radius: " << setw(10) << radius
         << "Area: " << area << endl;
}

int main() {
    cout << "=== Engineering Circle Area Calculator ===" << endl;
    cout << fixed << setprecision(4); // Format floating-point output

    // ==========================================
    // APPROACH 1: Static Method (Fixed-size Array)
    // ==========================================
    cout << "\n--- Static Approach (Fixed Array of size 3) ---" << endl;
    const int STATIC_SIZE = 3;
    Circle staticCircles[STATIC_SIZE];
    double tempRadius;

    for (int i = 0; i < STATIC_SIZE; ++i) {
        cout << "Enter radius for static Circle " << (i + 1) << ": ";
        cin >> tempRadius;
        staticCircles[i].setRadius(tempRadius);
    }

    cout << "\n[Static Array Results]" << endl;
    for (int i = 0; i < STATIC_SIZE; ++i) {
        displayCircleData("Static", i, staticCircles[i].getRadius(), staticCircles[i].calculateArea());
    }

    // ==========================================
    // APPROACH 2: Dynamic Method (std::vector)
    // ==========================================
    cout << "\n--- Dynamic Approach (Flexible Vector) ---" << endl;
    int dynamicCount;
    cout << "How many circles do you want to process dynamically? ";
    cin >> dynamicCount;

    // std::vector handles dynamic memory allocation automatically
    vector<Circle> dynamicCircles(dynamicCount);

    for (int i = 0; i < dynamicCount; ++i) {
        cout << "Enter radius for dynamic Circle " << (i + 1) << ": ";
        cin >> tempRadius;
        dynamicCircles[i].setRadius(tempRadius);
    }

    cout << "\n[Dynamic Vector Results]" << endl;
    for (int i = 0; i < dynamicCount; ++i) {
        displayCircleData("Dynamic", i, dynamicCircles[i].getRadius(), dynamicCircles[i].calculateArea());
    }

    return 0;
}
