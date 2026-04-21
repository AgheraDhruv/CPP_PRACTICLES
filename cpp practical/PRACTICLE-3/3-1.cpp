
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

class Employee {
private:
    string name;
    double basicSalary;
    double bonus;

public:
    // Constructor with a default argument for the bonus.
    // If the caller doesn't provide a bonus, it defaults to $500.00.
    Employee(string empName, double salary, double empBonus = 500.0) {
        name = empName;
        basicSalary = salary;
        bonus = empBonus;
    }

    // Inline function: Suggests the compiler replace the function call
    // with the actual code to reduce overhead and enable instant computation.
    inline double calculateTotalSalary() const {
        return basicSalary + bonus;
    }

    // Function to display employee records clearly
    void display() const {
        cout << left << setw(20) << name
             << "$" << setw(14) << fixed << setprecision(2) << basicSalary
             << "$" << setw(14) << fixed << setprecision(2) << bonus
             << "$" << fixed << setprecision(2) << calculateTotalSalary() << "\n";
    }
};

int main() {
    // Dynamic storage: vector automatically resizes as records are added
    vector<Employee> payrollSystem;
    int choice;

    cout << "=== Automated Payroll System ===\n";

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Employee with Default Bonus\n";
        cout << "2. Add Employee with Custom Bonus (Exceptional Performer)\n";
        cout << "3. Display All Payroll Records\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        // Input validation
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                string name;
                double salary;

                cout << "Enter Employee Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Basic Salary: $";
                cin >> salary;

                // Constructor uses the default bonus ($500)
                payrollSystem.push_back(Employee(name, salary));
                cout << "Employee added successfully with default bonus!\n";
                break;
            }
            case 2: {
                string name;
                double salary, bonus;

                cout << "Enter Employee Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Basic Salary: $";
                cin >> salary;
                cout << "Enter Custom Bonus Amount: $";
                cin >> bonus;

                // Constructor uses the custom provided bonus
                payrollSystem.push_back(Employee(name, salary, bonus));
                cout << "Employee added successfully with custom bonus!\n";
                break;
            }
            case 3: {
                if (payrollSystem.empty()) {
                    cout << "No employee records found in the system.\n";
                } else {
                    cout << "\n--- Organization Payroll Records ---\n";
                    cout << left << setw(20) << "Employee Name"
                         << setw(15) << "Basic Salary"
                         << setw(15) << "Bonus"
                         << "Total Salary\n";
                    cout << "--------------------------------------------------------------\n";

                    for (const auto& emp : payrollSystem) {
                        emp.display();
                    }
                    cout << "--------------------------------------------------------------\n";
                }
                break;
            }
            case 4:
                cout << "Exiting Payroll System. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please select an option from 1 to 4.\n";
        }
    } while (choice != 4);

    return 0;
}
