#include <iostream>

using namespace std;

// =========================================================
// SCENARIO 1: The Problem (No Virtual Destructor)
// =========================================================
namespace FlawedDesign {

    class Base {
    public:
        Base() { cout << "  [Flawed] Base Constructor called." << endl; }

        // WARNING: No 'virtual' keyword here!
        ~Base() { cout << "  [Flawed] Base Destructor called." << endl; }
    };

    class Derived : public Base {
    private:
        int* dynamicData; // Raw pointer resource

    public:
        Derived() {
            cout << "  [Flawed] Derived Constructor called. Allocating memory." << endl;
            dynamicData = new int[100]; // Dynamic allocation
        }

        ~Derived() {
            // This will NOT execute, causing a memory leak!
            cout << "  [Flawed] Derived Destructor called. Freeing memory! (You won't see this)" << endl;
            delete[] dynamicData;
        }
    };
}

// =========================================================
// SCENARIO 2: The Solution (Using a Virtual Destructor)
// =========================================================
namespace CorrectDesign {

    class Base {
    public:
        Base() { cout << "  [Correct] Base Constructor called." << endl; }

        // FIX: Added the 'virtual' keyword
        virtual ~Base() { cout << "  [Correct] Base Destructor called." << endl; }
    };

    class Derived : public Base {
    private:
        int* dynamicData; // Raw pointer resource

    public:
        Derived() {
            cout << "  [Correct] Derived Constructor called. Allocating memory." << endl;
            dynamicData = new int[100]; // Dynamic allocation
        }

        // The 'override' keyword here is optional but excellent practice
        ~Derived() override {
            cout << "  [Correct] Derived Destructor called. Freeing memory!" << endl;
            delete[] dynamicData; // Safely releasing resources
        }
    };
}

// =========================================================
// Main Function: Executing Both Scenarios
// =========================================================
int main() {
    cout << "=== Part 1: Deletion WITHOUT Virtual Destructor ===" << endl;
    cout << "Creating object..." << endl;

    // Upcasting: Storing a Derived object inside a Base pointer
    FlawedDesign::Base* flawedPtr = new FlawedDesign::Derived();

    cout << "\nDeleting object..." << endl;
    delete flawedPtr;

    cout << "\n--> Notice above: The Derived destructor was skipped. The int array is leaked!\n";
    cout << "---------------------------------------------------\n\n";

    cout << "=== Part 2: Deletion WITH Virtual Destructor ===" << endl;
    cout << "Creating object..." << endl;

    // Upcasting: Storing a Derived object inside a Base pointer
    CorrectDesign::Base* correctPtr = new CorrectDesign::Derived();

    cout << "\nDeleting object..." << endl;
    delete correctPtr;

    cout << "\n--> Notice above: The virtual destructor forced the program to check the actual object type. Both destructors fired cleanly!\n";

    return 0;
}
