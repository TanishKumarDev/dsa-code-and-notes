#include <bits/stdc++.h>
using namespace std;

// 🧠 Problem : 
// Example : 
// Constraint : 

// 🔴 Approach 1 Brute Force : 
// Intuition :

// - unordered_set (unordered + duplicates removed)
// - set (sorted order + duplicates removed)
// Algo :
// TC :
// SC :
// Edge cases :

int removeWithSet(vector<int>& arr) {
    // Using set ensures sorted order + unique elements
    set<int> s(arr.begin(), arr.end());
    
    int k = 0;
    for (int x : s) {
        arr[k++] = x;  // copy sorted unique elements back
    }
    return k;
}

// 🔵 Approach 2 Better : 

// Intuition :
// - works only if array is sorted

// Algo :
// TC :
// SC :
// Edge cases :

// WORKING
// Sorted array: 1 1 2 2 3 3 4
// i tracks "unique position"
// j scans to find new unique elements
// Final array (first k positions): 1 2 3 4

int removeDuplicatesBetter(vector<int>& arr) {
    int n = arr.size();

    // single element is already unique
    if(n <= 1 ) return n;
    
    // `i` → points to the place where next unique element will go
    int i = 0;

    // `j` → scans the array from left to right    
    for(int j = 1; j < n; j++){
        // Whenever a new unique element is found,
        // we move `i` forward and copy arr[j] into arr[i]
        if(arr[j] != arr[i]){
            i++;             // move write pointer
            arr[i] = arr[j]; // store unique element
        }
    }

    // New length of array with unique elements
    return i+1;
}
// 🟢 Approach 3 Optimal: 
// Intuition :
// Algo :
// TC :
// SC :
// Edge cases :

// Remove duplicates using STL `unique()`
// Note: Works correctly only if the array is SORTED.
int stlApproach(vector<int>& arr) {

    // `unique()` moves all unique elements to the front of the vector
    // and returns an iterator to the position AFTER the last unique element.
    //
    // IMPORTANT:
    // unique() removes only *consecutive* duplicates.
    // So the array MUST be sorted for correct results.
    auto it = unique(arr.begin(), arr.end());

    // Number of unique elements = distance from begin to new end
    int k = it - arr.begin();

    // If you want to shrink the vector to size k:
    // arr.resize(k);

    return k; // New length (count of unique elements)
}



int main() {

    // Approach 1: Using set
    vector<int> arr1 = {1, 2, 2, 3, 4, 4, 5};

    int k1 = removeWithSet(arr1);

    cout << "Approach 1 (Set) unique count: " << k1 << endl;
    cout << "Result: ";
    for (int i = 0; i < k1; i++) cout << arr1[i] << " ";
    cout << endl;


    // Approach 2: Two-pointer → requires fresh sorted array
    vector<int> arr2 = {1, 2, 2, 3, 4, 4, 5};

    int k2 = removeDuplicatesBetter(arr2);

    cout << "Approach 2 (Better) unique count: " << k2 << endl;
    cout << "Result: ";
    for (int i = 0; i < k2; i++) cout << arr2[i] << " ";
    cout << endl;


    // Approach 3: STL unique → requires fresh sorted array
    vector<int> arr3 = {1, 2, 2, 3, 4, 4, 5};

    int k3 = stlApproach(arr3);

    cout << "Approach 3 (STL) unique count: " << k3 << endl;
    cout << "Result: ";
    for (int i = 0; i < k3; i++) cout << arr3[i] << " ";
    cout << endl;

    return 0;
}
