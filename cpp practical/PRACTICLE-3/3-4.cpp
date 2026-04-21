#include <iostream>

using namespace std;

// 1. Template function to display the array
template <typename T>
void displayArray(T arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

// 2. Template function to find the maximum value
template <typename T>
T findMax(T arr[], int size) {
    if (size <= 0) return T(); // Return default value if array is empty

    T maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

// 3. Template function to reverse the array
template <typename T>
void reverseArray(T arr[], int size) {
    int start = 0;
    int end = size - 1;
    while (start < end) {
        // Swap elements
        T temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        start++;
        end--;
    }
}

// 4. Template function to find and print leader elements (Competitive Programming Task)
template <typename T>
void findLeaders(T arr[], int size) {
    if (size <= 0) return;

    // Temporary array to store leaders so we can print them left-to-right
    T* leaders = new T[size];
    int count = 0;

    // The rightmost element is always a leader
    T maxFromRight = arr[size - 1];
    leaders[count++] = maxFromRight;

    // Scan the array from right to left
    for (int i = size - 2; i >= 0; i--) {
        if (arr[i] > maxFromRight) {
            maxFromRight = arr[i];
            leaders[count++] = arr[i];
        }
    }

    // Print leaders in left-to-right order (reverse of how we found them)
    for (int i = count - 1; i >= 0; i--) {
        cout << leaders[i] << " ";
    }
    cout << "\n";

    // Clean up dynamically allocated memory
    delete[] leaders;
}

int main() {
    cout << "=== Template-Based Array Operations ===\n\n";

    // --- 1. Integer Array Operations ---
    cout << "--- Integer Array ---\n";
    int intArr[] = {16, 17, 4, 3, 5, 2}; // Example from the prompt
    int intSize = sizeof(intArr) / sizeof(intArr[0]);

    cout << "Original: ";
    displayArray(intArr, intSize);

    cout << "Maximum Value: " << findMax(intArr, intSize) << "\n";

    cout << "Leader Elements: ";
    findLeaders(intArr, intSize); // Expected: 17 5 2

    reverseArray(intArr, intSize);
    cout << "Reversed: ";
    displayArray(intArr, intSize);
    cout << "\n";

    // --- 2. Float Array Operations ---
    cout << "--- Float Array ---\n";
    float floatArr[] = {5.5, 9.2, 4.1, 7.8, 3.3};
    int floatSize = sizeof(floatArr) / sizeof(floatArr[0]);

    cout << "Original: ";
    displayArray(floatArr, floatSize);

    cout << "Maximum Value: " << findMax(floatArr, floatSize) << "\n";

    cout << "Leader Elements: ";
    findLeaders(floatArr, floatSize); // Expected: 9.2 7.8 3.3

    reverseArray(floatArr, floatSize);
    cout << "Reversed: ";
    displayArray(floatArr, floatSize);
    cout << "\n";

    // --- 3. Character Array Operations ---
    cout << "--- Character Array ---\n";
    char charArr[] = {'z', 'b', 'y', 'a', 'x'};
    int charSize = sizeof(charArr) / sizeof(charArr[0]);

    cout << "Original: ";
    displayArray(charArr, charSize);

    cout << "Maximum Value: " << findMax(charArr, charSize) << " (ASCII: " << (int)findMax(charArr, charSize) << ")\n";

    cout << "Leader Elements: ";
    findLeaders(charArr, charSize); // Expected: z y x

    reverseArray(charArr, charSize);
    cout << "Reversed: ";
    displayArray(charArr, charSize);
    cout << "\n";

    return 0;
}
