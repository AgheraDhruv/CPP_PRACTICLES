#include <iostream>

using namespace std;

class Point {
private:
    int x;
    int y;

public:
    // Constructor with default arguments
    Point(int startX = 0, int startY = 0) {
        x = startX;
        y = startY;
    }

    // Chainable move function using the 'this' pointer
    // It returns a reference to the current Point object (Point&)
    Point& move(int dx, int dy) {
        this->x += dx;
        this->y += dy;

        // *this dereferences the pointer to return the actual object
        return *this;
    }

    // Setters for the pointer demonstration
    void setX(int newX) { this->x = newX; }
    void setY(int newY) { this->y = newY; }

    // Method to display the coordinates
    void display() const {
        cout << "Current Position: (" << x << ", " << y << ")\n";
    }
};

// Global function demonstrating pass-by-reference using pointers
// This allows the function to directly modify the original object in memory
void updatePointViaPointer(Point* ptr, int newX, int newY) {
    if (ptr != nullptr) {
        // The arrow operator (->) is used to access members of an object through a pointer
        ptr->setX(newX);
        ptr->setY(newY);
        cout << "\n[Pointer Update] Point updated directly in memory to (" << newX << ", " << newY << ").\n";
    }
}

int main() {
    cout << "=== Graphical Point Tracker ===\n\n";

    // 1. Initialize the point
    Point p(0, 0);
    cout << "Starting Point:\n";
    p.display();

    // 2. Demonstrate Method Chaining using the 'this' pointer
    cout << "\nExecuting chained moves: p.move(2, 3).move(-1, 4).move(5, -2);\n";
    p.move(2, 3).move(-1, 4).move(5, -2);
    p.display();

    // 3. Demonstrate pass-by-reference using pointers
    // We pass the memory address of 'p' using the address-of operator (&)
    updatePointViaPointer(&p, 100, 200);
    p.display();

    return 0;
}
