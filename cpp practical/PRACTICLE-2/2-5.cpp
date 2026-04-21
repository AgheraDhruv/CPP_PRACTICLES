#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Account {
private:
    double p;
    double annualRate;
    int t;
    int loan_id;
    string applicant_name;

public:
    void input() {
        cout << "Enter Loan ID: ";
        cin >> loan_id;

        cout << "Enter Applicant Name: ";
        getline(cin >> ws, applicant_name);

        cout << "Enter Principal Amount: ";
        cin >> p;

        cout << "Enter Annual Interest Rate (%): ";
        cin >> annualRate;

        cout << "Enter Time (in months): ";
        cin >> t;
    }

    double calculate_emi() {
        double r = annualRate / 12.0 / 100.0;


        if (r == 0) {
            return p / t;
        }

        return (p * r * pow(1 + r, t)) / (pow(1 + r, t) - 1);
    }

    void display() {
        cout << "\nLoan ID: " << loan_id << endl;
        cout << "Applicant Name: " << applicant_name << endl;
        cout << "Monthly EMI: " << calculate_emi() << endl;
    }
};

int main() {
    Account acc1, acc2;

    acc1.input();
    acc2.input();

    acc1.display();
    acc2.display();

    return 0;
}
