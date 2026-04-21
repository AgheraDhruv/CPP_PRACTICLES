#include <iostream>
#include <string>
#include <queue>
#include <iomanip>

using namespace std;

// ==========================================
// 1. Base Class 1: Fuel
// ==========================================
class Fuel {
protected:
    string fuelType;

public:
    // Default constructor
    Fuel() : fuelType("Unspecified") {}

    // Parameterized constructor
    Fuel(string type) : fuelType(type) {}

    string getFuelType() const {
        return fuelType;
    }
};

// ==========================================
// 2. Base Class 2: Brand
// ==========================================
class Brand {
protected:
    string brandName;

public:
    // Default constructor
    Brand() : brandName("Unspecified") {}

    // Parameterized constructor
    Brand(string name) : brandName(name) {}

    string getBrandName() const {
        return brandName;
    }
};

// ==========================================
// 3. Derived Class: Car (Multiple Inheritance)
// ==========================================
class Car : public Brand, public Fuel {
public:
    // Default constructor
    Car() : Brand(), Fuel() {}

    // Parameterized constructor chaining to both base classes
    Car(string brand, string fuel) : Brand(brand), Fuel(fuel) {}

    // Method to display complete car details
    void displayCarDetails() const {
        cout << left << "Brand: " << setw(15) << brandName
             << "| Fuel Type: " << fuelType << endl;
    }
};

// ==========================================
// Main Function
// ==========================================
int main() {
    cout << "=== Vehicle Manufacturing Management System ===" << endl << endl;

    // ---------------------------------------------------------
    // Method 1: Direct Static Method (Fixed-size Array)
    // Useful for a fixed, predetermined batch of vehicles.
    // ---------------------------------------------------------
    cout << "--- Method 1: Static Array Processing ---" << endl;
    const int BATCH_SIZE = 3;

    // Initializing an array of Car objects using the parameterized constructor
    Car staticBatch[BATCH_SIZE] = {
        Car("Toyota Camry", "Petrol"),
        Car("Ford F-150", "Diesel"),
        Car("Tesla Model 3", "Electric")
    };

    cout << "Processing static vehicle batch:" << endl;
    for (int i = 0; i < BATCH_SIZE; ++i) {
        cout << "[" << i + 1 << "] ";
        staticBatch[i].displayCarDetails();
    }
    cout << endl;

    // ---------------------------------------------------------
    // Method 2: Efficient Structured Approach (std::queue)
    // Simulates a real-world service queue (First-In-First-Out)
    // ---------------------------------------------------------
    cout << "--- Method 2: Dynamic Service Queue (FIFO) ---" << endl;
    queue<Car> serviceQueue;

    // Enqueueing cars into the service line
    serviceQueue.push(Car("Honda Civic", "Petrol"));
    serviceQueue.push(Car("Nissan Leaf", "Electric"));
    serviceQueue.push(Car("Volvo XC90", "Hybrid"));

    cout << "Processing vehicles in the service queue:" << endl;
    int position = 1;

    // Process cars until the queue is empty
    while (!serviceQueue.empty()) {
        cout << "Servicing Car #" << position++ << " -> ";

        // Access the front car, display it, then remove it from the queue
        Car currentCar = serviceQueue.front();
        currentCar.displayCarDetails();
        serviceQueue.pop();
    }

    return 0;
}

