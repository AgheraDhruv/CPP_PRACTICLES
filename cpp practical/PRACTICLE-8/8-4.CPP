#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

int main() {
    cout << "=== Streamlined Data Processing System ===\n";
    cout << "Expected file format per line: [Name] [Score1] [Score2]\n\n";

    string filename;
    ifstream file;

    // =========================================================
    // 1. Retry Mechanism for File Opening
    // =========================================================
    while (true) {
        cout << "Enter the path to the data file (or type 'exit' to quit): ";
        getline(cin, filename);

        if (filename == "exit") {
            cout << "Exiting program. Goodbye!" << endl;
            return 0;
        }

        file.open(filename);

        // If file opens successfully, break out of the retry loop
        if (file.is_open()) {
            cout << "\n[System] Successfully opened '" << filename << "'. Beginning processing...\n\n";
            break;
        }

        // If opening fails, clear the stream error flags and prompt again
        cout << "[Error] File not found or cannot be opened. Please verify the path and try again.\n\n";
        file.clear();
    }

    // =========================================================
    // 2. Line-by-Line Processing & Validation
    // =========================================================
    string line;
    int lineNumber = 0;
    int validCount = 0;
    int corruptCount = 0;
    double classTotalScore = 0.0;

    // Table Header formatting
    cout << left << setw(10) << "Line #" << setw(15) << "Student" << "Calculated Average" << endl;
    cout << "---------------------------------------------------" << endl;

    // Read directly from the file stream one line at a time
    while (getline(file, line)) {
        lineNumber++;

        // Skip completely empty lines to avoid false corruption flags
        if (line.empty()) continue;

        // Bind the current line to a string stream for isolated parsing
        istringstream iss(line);
        string name;
        double score1, score2;

        // Try to extract exactly one string and two doubles
        if (!(iss >> name >> score1 >> score2)) {
            // Extraction failed (e.g., user put letters instead of numbers for the scores)
            cout << left << setw(10) << lineNumber << setw(15) << "---"
                 << "[Error] Corrupted data: '" << line << "'. Skipping." << endl;
            corruptCount++;
            continue;
        }

        // Optional Validation: Check for unwanted extra garbage at the end of the line
        string extraData;
        if (iss >> extraData) {
            cout << left << setw(10) << lineNumber << setw(15) << "---"
                 << "[Error] Extra data found: '" << line << "'. Skipping." << endl;
            corruptCount++;
            continue;
        }

        // =========================================================
        // 3. Numeric Processing for Valid Data
        // =========================================================
        double average = (score1 + score2) / 2.0;
        classTotalScore += average;
        validCount++;

        // Display the successfully processed data
        cout << left << setw(10) << lineNumber << setw(15) << name
             << fixed << setprecision(2) << average << endl;
    }

    // Close the file immediately after finishing the read loop
    file.close();

    // =========================================================
    // 4. Final Processing Summary
    // =========================================================
    cout << "---------------------------------------------------" << endl;
    cout << "\n=== Processing Summary ===" << endl;
    cout << "Total Lines Read:     " << lineNumber << endl;
    cout << "Valid Records:        " << validCount << endl;
    cout << "Corrupted/Skipped:    " << corruptCount << endl;

    if (validCount > 0) {
        cout << "Overall Class Target: " << fixed << setprecision(2)
             << (classTotalScore / validCount) << endl;
    } else {
        cout << "Overall Class Target: N/A (No valid data processed)" << endl;
    }

    return 0;
}
