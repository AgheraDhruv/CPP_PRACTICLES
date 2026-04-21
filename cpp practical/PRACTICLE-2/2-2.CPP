#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    int roll;
    string name;
    float m1, m2, m3;

public:
    // Default Constructor (for default values)
    Student() {
        roll = 0;
        name = "Test Student";
        m1 = 50;
        m2 = 50;
        m3 = 50;
    }

    // Parameterized Constructor (for user input values)
    Student(int r, string n, float a, float b, float c) {
        roll = r;
        name = n;
        m1 = a;
        m2 = b;
        m3 = c;
    }

    float average() {
        return (m1 + m2 + m3) / 3;
    }

    void display() {
        cout << "\nRoll No : " << roll;
        cout << "\nName    : " << name;
        cout << "\nMarks   : " << m1 << ", " << m2 << ", " << m3;
        cout << "\nAverage : " << average() << "\n";
    }
};

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    // Default student (testing)
    cout << "\n--- Default Student Record ---";
    Student s_default;
    s_default.display();

    // User input students
    cout << "\n--- Enter Student Details ---";
    for (int i = 0; i < n; i++) {
        int roll;
        string name;
        float m1, m2, m3;

        cout << "\nEnter Roll No: ";
        cin >> roll;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Marks in 3 subjects: ";
        cin >> m1 >> m2 >> m3;

        Student s(roll, name, m1, m2, m3);
        s.display();
    }

    return 0;
}
