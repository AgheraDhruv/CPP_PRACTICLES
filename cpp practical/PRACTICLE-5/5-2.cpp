#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string filename;
    cout << "Enter the filename to process (e.g., sample.txt): ";
    getline(cin, filename);

    // Open the file using unformatted input stream
    ifstream file(filename);

    // Error handling: Check if the file exists and opened successfully
    if (!file.is_open()) {
        cerr << "Error: Could not open the file '" << filename << "'. Please check if it exists." << endl;
        return 1; // Exit with error code
    }

    int charCount = 0;
    int wordCount = 0;
    int lineCount = 0;
    string line;

    // Process the file line-by-line
    while (getline(file, line)) {
        lineCount++; // Increment line count for every successfully read line

        bool inWord = false; // State variable to track if we are inside a word

        // Scan characters manually
        for (int i = 0; i < line.length(); i++) {
            char c = line[i];
            charCount++; // Count every visible character and space in the line

            // Check for word boundaries (spaces or tabs)
            if (c == ' ' || c == '\t') {
                inWord = false;
            } else {
                // If it's a non-space character and we weren't already inside a word,
                // we have found the start of a new word.
                if (!inWord) {
                    wordCount++;
                    inWord = true;
                }
            }
        }
        // Note: getline() strips the newline ('\n') character.
        // If you need to count the newlines as characters too, uncomment the next line:
        // charCount++;
    }

    file.close(); // Always close the file when done

    // Output the final statistics
    cout << "\n--- File Statistics ---" << endl;
    cout << "Total Lines: " << lineCount << endl;
    cout << "Total Words: " << wordCount << endl;
    cout << "Total Characters (excluding newlines): " << charCount << endl;

    return 0;
}
