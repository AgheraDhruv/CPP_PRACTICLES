#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// ==========================================
// 1. Abstract Base Class
// ==========================================
class GradingFramework {
protected:
    string studentName;
    double marks;

public:
    // Constructor to initialize base attributes
    GradingFramework(string name, double m) : studentName(name), marks(m) {}

    // Pure virtual function makes this class Abstract
    virtual string computeGrade() const = 0;

    // Virtual destructor ensures proper cleanup of derived objects
    virtual ~GradingFramework() {}

    // Virtual display method that can be extended by derived classes
    virtual void displayRecord() const {
        cout << left << setw(20) << studentName
             << " | Marks: " << setw(6) << fixed << setprecision(2) << marks
             << " | Grade: " << computeGrade() << endl;
    }
};

// ==========================================
// 2. Derived Class: Undergraduate
// ==========================================
class Undergraduate : public GradingFramework {
public:
    Undergraduate(string name, double m) : GradingFramework(name, m) {}

    // Standard grading logic for undergraduates
    string computeGrade() const override {
        if (marks >= 90.0) return "A";
        else if (marks >= 80.0) return "B";
        else if (marks >= 70.0) return "C";
        else if (marks >= 60.0) return "D";
        else return "F";
    }

    void displayRecord() const override {
        cout << "[UG] ";
        GradingFramework::displayRecord();
    }
};

// ==========================================
// 3. Derived Class: Postgraduate
// ==========================================
class Postgraduate : public GradingFramework {
public:
    Postgraduate(string name, double m) : GradingFramework(name, m) {}

    // More rigorous grading logic for postgraduates
    string computeGrade() const override {
        if (marks >= 90.0) return "A (Distinction)";
        else if (marks >= 85.0) return "B+ (High Merit)";
        else if (marks >= 80.0) return "B (Merit)";
        else if (marks >= 75.0) return "C (Pass)";
        else return "F (Fail)";
    }

    void displayRecord() const override {
        cout << "[PG] ";
        GradingFramework::displayRecord();
    }
};

// ==========================================
// Main Function: Collection Management
// ==========================================
int main() {
    cout << "=== University Advanced Grading System ===" << endl << endl;

    // A collection of base class pointers to manage different student types uniformly
    vector<GradingFramework*> studentRecords;

    int choice;
    do {
        cout << "\n--- Add New Student Record ---" << endl;
        cout << "1. Add Undergraduate Student" << endl;
        cout << "2. Add Postgraduate Student" << endl;
        cout << "3. View All Grades and Exit" << endl;
        cout << "Select an option (1-3): ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            string name;
            double marks;

            cout << "Enter Student Name (single word/no spaces): ";
            cin >> name;
            cout << "Enter Marks (0-100): ";
            cin >> marks;

            if (choice == 1) {
                // Dynamically allocate an Undergraduate object
                studentRecords.push_back(new Undergraduate(name, marks));
                cout << "Undergraduate record added." << endl;
            } else {
                // Dynamically allocate a Postgraduate object
                studentRecords.push_back(new Postgraduate(name, marks));
                cout << "Postgraduate record added." << endl;
            }
        }
    } while (choice != 3);

    // ---------------------------------------------------------
    // Processing the Collection using Polymorphism
    // ---------------------------------------------------------
    cout << "\n=== Final Grade Report ===" << endl;
    if (studentRecords.empty()) {
        cout << "No records to display." << endl;
    } else {
        // Iterate through the pointers. The program dynamically calls the correct
        // computeGrade() and displayRecord() method based on the object's actual type.
        for (const auto& student : studentRecords) {
            student->displayRecord();
        }
    }

    // ---------------------------------------------------------
    // Memory Cleanup
    // ---------------------------------------------------------
    for (auto& student : studentRecords) {
        delete student; // Invokes the virtual destructor
    }
    studentRecords.clear();

    cout << "\n[System] Memory safely cleared. Exiting program." << endl;

    return 0;
}
