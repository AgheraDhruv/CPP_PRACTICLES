#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

// Helper function to clean a word (convert to lowercase and remove trailing punctuation)
string cleanWord(string word) {
    // Convert all characters to lowercase
    transform(word.begin(), word.end(), word.begin(), ::tolower);

    // Remove basic trailing punctuation (like periods or commas)
    while (!word.empty() && ispunct(word.back())) {
        word.pop_back();
    }

    // Remove basic leading punctuation
    while (!word.empty() && ispunct(word.front())) {
        word.erase(0, 1);
    }

    return word;
}

int main() {
    cout << "=== Word Frequency Counter ===\n";

    string sentence;
    cout << "Enter a sentence: ";
    // Use getline to read the entire sentence, including spaces
    getline(cin, sentence);

    // Create a map to store the word (string) and its frequency (int)
    // std::map automatically keeps the keys sorted alphabetically
    map<string, int> wordFrequency;

    // Use stringstream to easily split the sentence into individual words
    stringstream ss(sentence);
    string word;

    // Extract words one by one separated by spaces
    while (ss >> word) {
        // Clean the word (lowercase and strip punctuation)
        string cleaned = cleanWord(word);

        // Skip empty strings that might occur if a "word" was just punctuation
        if (!cleaned.empty()) {
            // If the word isn't in the map, this adds it with a value of 0, then increments to 1.
            // If it is in the map, it simply increments the existing value.
            wordFrequency[cleaned]++;
        }
    }

    // Display the results
    cout << "\n--- Word Frequencies ---\n";
    if (wordFrequency.empty()) {
        cout << "No valid words found." << endl;
    } else {
        // Iterate through the map and print each key-value pair
        for (map<string, int>::const_iterator it = wordFrequency.begin(); it != wordFrequency.end(); ++it) {
            cout << it->first << " : " << it->second << endl;
        }
    }
    cout << "------------------------\n";

    return 0;
}
