#include <iostream>
#include <string>

using namespace std;

// Helper function to convert an uppercase character to lowercase manually
char toLowercase(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A'); // Shift ASCII value
    }
    return c;
}

// Helper function to check if a character is a letter or number
bool isAlphaNumeric(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9');
}

int main() {
    // Basic fixed-size arrays to hold our data
    const int MAX_WORDS = 1000;
    string uniqueWords[MAX_WORDS];
    int wordCounts[MAX_WORDS] = {0}; // Initialize counts to 0
    int uniqueCount = 0;

    string paragraph;
    cout << "=== Manual Word Frequency Counter ===\n";
    cout << "Enter a paragraph of text:\n";

    // 1. Read the complete paragraph using unformatted input
    getline(cin, paragraph);

    string currentWord = "";

    // 2. Parse the string manually
    for (int i = 0; i <= paragraph.length(); i++) {
        char c = paragraph[i];

        // If it's a valid character (not end of string) and alphanumeric
        if (i < paragraph.length() && isAlphaNumeric(c)) {
            // Build the word character by character, converting to lowercase
            currentWord += toLowercase(c);
        }
        else {
            // We hit a space, punctuation, or the end of the string
            if (currentWord != "") {
                bool found = false;

                // 3. Search for the word in our array
                for (int j = 0; j < uniqueCount; j++) {
                    if (uniqueWords[j] == currentWord) {
                        wordCounts[j]++; // Increment frequency
                        found = true;
                        break;
                    }
                }

                // 4. If it's a new word, add it to the array
                if (!found) {
                    if (uniqueCount < MAX_WORDS) {
                        uniqueWords[uniqueCount] = currentWord;
                        wordCounts[uniqueCount] = 1;
                        uniqueCount++;
                    } else {
                        cout << "\nWarning: Maximum word limit reached (" << MAX_WORDS << ")." << endl;
                        break; // Stop processing if array is full
                    }
                }

                // Reset the temporary word builder for the next iteration
                currentWord = "";
            }
        }
    }

    // 5. Display the results
    cout << "\n--- Word Frequencies ---\n";
    if (uniqueCount == 0) {
        cout << "No words found in the input.\n";
    } else {
        for (int i = 0; i < uniqueCount; i++) {
            cout << uniqueWords[i] << " : " << wordCounts[i] << "\n";
        }
    }
    cout << "------------------------\n";

    return 0;
}
