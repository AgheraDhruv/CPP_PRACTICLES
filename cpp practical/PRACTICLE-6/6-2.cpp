#include <iostream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

// ==========================================
// 1. Base Level: Person Class
// ==========================================
class Person {
protected:
    string name;
    int age;

public:
    // Default constructor (needed for static array initialization)
    Person() : name("Unknown"), age(0) {}

    // Parameterized constructor
    Person(string n, int a) : name(n), age(a) {}

    // Display function for Person level
    void displayPerson() const {
        cout << left << setw(15) << name << " | Age: " << setw(3) << age;
    }
};

// ==========================================
// 2. Intermediate Level: Employee Class
// ==========================================
class Employee : public Person {
protected:
    int employeeID;

public:
    // Default constructor
    Employee() : Person(), employeeID(0) {}

    // Parameterized constructor with chaining to Person
    Employee(string n, int a, int id) : Person(n, a), employeeID(id) {}

    // Display function for Employee level
    void displayEmployee() const {
        displayPerson();
        cout << " | Emp ID: " << setw(5) << employeeID;
    }

    // Getter for ID (useful for retrieval strategy)
    int getEmployeeID() const {
        return employeeID;
    }
};

// ==========================================
// 3. Top Level: Manager Class
// ==========================================
class Manager : public Employee {
private:
    string department;

public:
    // Default constructor
    Manager() : Employee(), department("Unassigned") {}

    // Parameterized constructor with chaining to Employee
    Manager(string n, int a, int id, string dept) : Employee(n, a, id), department(dept) {}

    // Display function detailing the full hierarchy
    void displayManager() const {
        displayEmployee();
        cout << " | Department: " << department << endl;
    }
};

// ==========================================
// Main Function
// ==========================================
int main() {
    cout << "=== Multilevel Inheritance: Organizational Hierarchy ===" << endl << endl;

    // ---------------------------------------------------------
    // Strategy 1: Static Storage Method (Fixed-size Array)
    // Good for simple, predictable use cases.
    // ---------------------------------------------------------
    cout << "--- Strategy 1: Static Array Storage ---" << endl;
    const int MAX_MANAGERS = 3;
    Manager staticManagers[MAX_MANAGERS] = {
        Manager("Alice Smith", 45, 1001, "Human Resources"),
        Manager("Bob Johnson", 50, 1002, "Engineering"),
        Manager("Carol Davis", 38, 1003, "Marketing")
    };

    cout << "Listing all managers in static array:" << endl;
    for (int i = 0; i < MAX_MANAGERS; ++i) {
        staticManagers[i].displayManager();
    }
    cout << endl;

    // ---------------------------------------------------------
    // Strategy 2: Efficient Retrieval Method (std::map)
    // Uses Employee ID as the key for fast O(log n) lookups.
    // ---------------------------------------------------------
    cout << "--- Strategy 2: Efficient Retrieval (Map by ID) ---" << endl;
    map<int, Manager> managerDatabase;

    // Populating the map
    managerDatabase[2001] = Manager("David Lee", 42, 2001, "Finance");
    managerDatabase[2002] = Manager("Eve Carter", 36, 2002, "IT Support");
    managerDatabase[2003] = Manager("Frank Wright", 55, 2003, "Operations");

    // Simulating a retrieval query
    int searchID = 2002;
    cout << "Searching for Manager with Employee ID [" << searchID << "]:" << endl;

    // Using find() for safe and efficient retrieval
    auto it = managerDatabase.find(searchID);
    if (it != managerDatabase.end()) {
        cout << "Record Found: ";
        it->second.displayManager(); // ->second accesses the Manager object in the map
    } else {
        cout << "Error: Manager with ID " << searchID << " not found." << endl;
    }

    return 0;
}
