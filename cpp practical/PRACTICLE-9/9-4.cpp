#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

// Function to display the menu
void showMenu() {
    cout << "\n=== Directory Management System ===" << endl;
    cout << "1. Add a new folder" << endl;
    cout << "2. Add a file to a folder" << endl;
    cout << "3. Display directory structure" << endl;
    cout << "4. Exit" << endl;
    cout << "Select an option (1-4): ";
}

int main() {
    // Map storing folder names as keys and a vector of file names as values
    map<string, vector<string>> fileSystem;
    int choice;

    do {
        showMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = 0;
        }

        switch (choice) {
            case 1: {
                string folderName;
                cout << "Enter the name of the new folder: ";
                cin >> ws; // Clear leading whitespace
                getline(cin, folderName);

                // Check if folder already exists
                if (fileSystem.find(folderName) != fileSystem.end()) {
                    cout << "[Notice] Folder '" << folderName << "' already exists." << endl;
                } else {
                    // Create an empty folder by assigning an empty vector
                    fileSystem[folderName] = vector<string>();
                    cout << "[Success] Folder '" << folderName << "' created." << endl;
                }
                break;
            }
            case 2: {
                string folderName, fileName;
                cout << "Enter the name of the destination folder: ";
                cin >> ws;
                getline(cin, folderName);

                // Check if folder exists before adding a file
                // We use find() so we don't accidentally create the folder if it doesn't exist
                map<string, vector<string>>::iterator it = fileSystem.find(folderName);

                if (it != fileSystem.end()) {
                    cout << "Enter the name of the file to add: ";
                    getline(cin, fileName);

                    // Add the file to the vector associated with this folder
                    it->second.push_back(fileName);
                    cout << "[Success] File '" << fileName << "' added to '" << folderName << "'." << endl;
                } else {
                    cout << "[Error] Folder '" << folderName << "' does not exist. Please create it first." << endl;
                }
                break;
            }
            case 3: {
                cout << "\n--- Directory Structure ---" << endl;
                if (fileSystem.empty()) {
                    cout << "The file system is currently empty." << endl;
                } else {
                    // Iterating through the map.
                    // std::map automatically sorts its keys, so folders will appear alphabetically.
                    for (map<string, vector<string>>::const_iterator mapIt = fileSystem.begin();
                         mapIt != fileSystem.end(); ++mapIt) {

                        // mapIt->first gives us the Key (Folder Name)
                        cout << "[Folder] " << mapIt->first << endl;

                        // mapIt->second gives us the Value (Vector of Files)
                        const vector<string>& files = mapIt->second;

                        if (files.empty()) {
                            cout << "    (Empty folder)" << endl;
                        } else {
                            // Iterating through the vector to print files
                            for (vector<string>::const_iterator vecIt = files.begin();
                                 vecIt != files.end(); ++vecIt) {
                                cout << "    |-- " << *vecIt << endl;
                            }
                        }
                    }
                }
                cout << "---------------------------" << endl;
                break;
            }
            case 4:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "[Error] Invalid choice. Please enter a number between 1 and 4." << endl;
        }
    } while (choice != 4);

    return 0;
}
