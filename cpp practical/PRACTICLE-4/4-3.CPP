#include <iostream>

using namespace std;

// Function to merge two sorted arrays into a third dynamically allocated array
void mergeSortedArrays(const int* arr1, int n, const int* arr2, int m, int* mergedArr) {
    int i = 0; // Pointer for arr1
    int j = 0; // Pointer for arr2
    int k = 0; // Pointer for mergedArr

    // Traverse both arrays and copy the smaller element into the merged array
    while (i < n && j < m) {
        if (arr1[i] <= arr2[j]) {
            mergedArr[k] = arr1[i];
            i++;
        } else {
            mergedArr[k] = arr2[j];
            j++;
        }
        k++;
    }

    // If there are remaining elements in arr1, copy them over
    while (i < n) {
        mergedArr[k] = arr1[i];
        i++;
        k++;
    }

    // If there are remaining elements in arr2, copy them over
    while (j < m) {
        mergedArr[k] = arr2[j];
        j++;
        k++;
    }
}

int main() {
    int n, m;

    cout << "=== Sorted Dataset Merger ===\n\n";

    // 1. Read size and elements for the first dataset
    cout << "Enter the size of the first sorted dataset (n): ";
    cin >> n;

    if (n < 0) {
        cout << "Size cannot be negative.\n";
        return 1;
    }

    // Dynamically allocate the first array
    int* arr1 = new int[n];
    if (n > 0) {
        cout << "Enter " << n << " sorted integers for the first dataset:\n";
        for (int i = 0; i < n; i++) {
            cin >> arr1[i];
        }
    }

    // 2. Read size and elements for the second dataset
    cout << "\nEnter the size of the second sorted dataset (m): ";
    cin >> m;

    if (m < 0) {
        cout << "Size cannot be negative.\n";
        delete[] arr1; // Prevent memory leak before exiting
        return 1;
    }

    // Dynamically allocate the second array
    int* arr2 = new int[m];
    if (m > 0) {
        cout << "Enter " << m << " sorted integers for the second dataset:\n";
        for (int i = 0; i < m; i++) {
            cin >> arr2[i];
        }
    }

    // 3. Dynamically allocate the merged array of size n + m
    int* mergedArr = new int[n + m];

    // Perform the merge
    mergeSortedArrays(arr1, n, arr2, m, mergedArr);

    // 4. Display the merged sorted array
    cout << "\n--- Merged Sorted Dataset ---\n";
    cout << "Elements: [ ";
    for (int i = 0; i < (n + m); i++) {
        cout << mergedArr[i] << " ";
    }
    cout << "]\n";
    cout << "Total Size: " << (n + m) << "\n";

    // 5. CRITICAL: Free dynamically allocated memory to prevent memory leaks
    delete[] arr1;
    delete[] arr2;
    delete[] mergedArr;

    return 0;
}
