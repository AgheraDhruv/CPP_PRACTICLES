#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Iterative approach to compute the sum
long long iterativeSum(const vector<int>& arr) {
    long long sum = 0;
    for (int num : arr) {
        sum += num;
    }
    return sum;
}

// Recursive approach to compute the sum
// We pass the vector by reference to avoid heavy memory copying, and use 'n' as the current size constraint
long long recursiveSum(const vector<int>& arr, int n) {
    // Base case: if array size is 0, sum is 0
    if (n <= 0) {
        return 0;
    }
    // Recursive step: last element + sum of the rest of the array
    return arr[n - 1] + recursiveSum(arr, n - 1);
}

int main() {
    int size;

    cout << "=== Array Sum Performance Evaluator ===\n";
    cout << "Enter the number of elements in the array: ";
    cin >> size;

    if (size <= 0) {
        cout << "Array size must be greater than 0.\n";
        return 1;
    }

    // Dynamically allocate array based on user input
    vector<int> arr(size);

    cout << "Enter the " << size << " elements (separated by spaces or newlines):\n";
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }

    cout << "\n--- Computing Sums ---\n";

    // 1. Evaluate Iterative Approach
    auto startIterative = high_resolution_clock::now();
    long long sumIterative = iterativeSum(arr);
    auto stopIterative = high_resolution_clock::now();
    auto durationIterative = duration_cast<nanoseconds>(stopIterative - startIterative);

    cout << "Iterative Sum : " << sumIterative << "\n";
    cout << "Iterative Time: " << durationIterative.count() << " nanoseconds\n\n";

    // 2. Evaluate Recursive Approach
    auto startRecursive = high_resolution_clock::now();
    long long sumRecursive = recursiveSum(arr, size);
    auto stopRecursive = high_resolution_clock::now();
    auto durationRecursive = duration_cast<nanoseconds>(stopRecursive - startRecursive);

    cout << "Recursive Sum : " << sumRecursive << "\n";
    cout << "Recursive Time: " << durationRecursive.count() << " nanoseconds\n\n";

    return 0;
}
