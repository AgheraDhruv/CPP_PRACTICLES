#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

// User-defined stream manipulator to prepend a currency symbol
// Note: Using '$' here for universal terminal compatibility,
// but you can replace it with "₹" if your console supports UTF-8.
ostream& currency(ostream& os) {
    os << "$";
    return os;
}

// Structure to hold student data
struct Student {
    string name;
    double marks;
    double fees;
};

int main() {
    // Sample data for demonstration
    vector<Student> students = {
        {"Alice Smith", 89.456, 1500.50},
        {"Bob Johnson", 76.12, 1200.75},
        {"Charlie Brown", 92.8, 1650.00},
        {"Diana Prince", 85.0, 1400.20}
    };

    cout << "Student Database Listing" << endl;
    cout << "========================" << endl << endl;

    // Table Header Formatting
    // Using left alignment and setw() to create fixed-width columns
    cout << left
         << setw(20) << "Student Name"
         << setw(15) << "Marks (%)"
         << setw(15) << "Fees Paid"
         << endl;

    // Using setfill to create a solid separator line
    cout << setfill('-') << setw(50) << "-" << endl;

    // Resetting setfill back to empty space for the data rows
    cout << setfill(' ');

    // Setting floating-point precision for the entire output
    // fixed ensures trailing zeros are shown, setprecision(2) limits to 2 decimal places
    cout << fixed << setprecision(2);

    // Iterating through the student list and displaying formatted data
    for (const auto& student : students) {
        cout << left << setw(20) << student.name
             << setw(15) << student.marks
             // Using our user-defined 'currency' manipulator right before the fees
             << currency << student.fees
             << endl;
    }

    cout << endl;
    return 0;
}
