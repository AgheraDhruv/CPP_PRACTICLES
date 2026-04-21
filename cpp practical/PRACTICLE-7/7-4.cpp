#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

// Define PI for the Circle calculations
const double PI = 3.14159265358979323846;

// ==========================================
// 1. Base Class: Shape
// ==========================================
class Shape {
public:
    // Pure virtual function makes Shape an Abstract Base Class
    virtual double Area() const = 0;

    // Virtual helper for clean console output
    virtual string getName() const = 0;

    // Virtual destructor is CRITICAL in polymorphism to prevent memory leaks
    // when deleting derived objects through a base class pointer.
    virtual ~Shape() {
        // Optional debug message to show destruction
        // cout << "[System] Shape destroyed." << endl;
    }
};

// ==========================================
// 2. Derived Class: Rectangle
// ==========================================
class Rectangle : public Shape {
private:
    double length;
    double width;

public:
    Rectangle(double l, double w) : length(l), width(w) {}

    // Overriding the base class Area function
    double Area() const override {
        return length * width;
    }

    string getName() const override {
        return "Rectangle (" + to_string((int)length) + "x" + to_string((int)width) + ")";
    }

    ~Rectangle() override {}
};

// ==========================================
// 3. Derived Class: Circle
// ==========================================
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    // Overriding the base class Area function
    double Area() const override {
        return PI * radius * radius;
    }

    string getName() const override {
        return "Circle (r=" + to_string((int)radius) + ")";
    }

    ~Circle() override {}
};

// ==========================================
// Helper Function to Process Shapes
// ==========================================
// This function demonstrates Polymorphism. It accepts a base pointer (Shape*)
// but dynamically resolves the correct Area() method based on the actual object.
void displayShapeDetails(const Shape* shape) {
    cout << left << setw(20) << shape->getName()
         << " | Computed Area: " << shape->Area() << endl;
}

// ==========================================
// Main Function
// ==========================================
int main() {
    cout << "=== Polymorphic Geometric Area System ===" << endl;
    cout << fixed << setprecision(2); // Set precision for all floating-point output

    // ---------------------------------------------------------
    // Strategy 1: Static Storage (Fixed-size Array)
    // ---------------------------------------------------------
    cout << "\n--- Strategy 1: Static Array Storage ---" << endl;
    const int STATIC_SIZE = 3;

    // Array of base class pointers pointing to derived objects
    Shape* staticShapes[STATIC_SIZE];
    staticShapes[0] = new Rectangle(10.0, 5.0);
    staticShapes[1] = new Circle(7.0);
    staticShapes[2] = new Rectangle(8.0, 8.0); // A square is just a specific rectangle

    cout << "Processing fixed shape collection:" << endl;
    for (int i = 0; i < STATIC_SIZE; ++i) {
        displayShapeDetails(staticShapes[i]);
    }

    // Memory Cleanup for Static Array
    for (int i = 0; i < STATIC_SIZE; ++i) {
        delete staticShapes[i];
    }

    // ---------------------------------------------------------
    // Strategy 2: Dynamic Storage (std::vector)
    // ---------------------------------------------------------
    cout << "\n--- Strategy 2: Dynamic Vector Storage ---" << endl;

    // Vector of base class pointers allows flexible resizing at runtime
    vector<Shape*> dynamicShapes;

    // Pushing newly allocated objects into the vector
    dynamicShapes.push_back(new Circle(10.0));
    dynamicShapes.push_back(new Rectangle(12.0, 4.0));
    dynamicShapes.push_back(new Circle(4.5));

    // Demonstrating extensibility: easily adding another shape later
    dynamicShapes.push_back(new Rectangle(15.0, 2.0));

    cout << "Processing dynamic shape collection (Size: " << dynamicShapes.size() << "):" << endl;
    for (const auto& shapePtr : dynamicShapes) {
        displayShapeDetails(shapePtr);
    }

    // Memory Cleanup for Dynamic Vector
    for (auto& shapePtr : dynamicShapes) {
        delete shapePtr;
    }
    dynamicShapes.clear();

    cout << "\n[System] All dynamically allocated memory successfully cleaned up." << endl;

    return 0;
}
