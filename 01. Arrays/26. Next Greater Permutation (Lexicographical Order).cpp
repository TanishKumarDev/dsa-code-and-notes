#include <bits/stdc++.h>
using namespace std;


// 🧠 Problem :
// Given an array arr, rearrange it into the lexicographically next greater permutation.
// If such arrangement is not possible, return the smallest permutation (sorted ascending).

// Example :
// Input  : [1, 2, 3]
// Output : [1, 3, 2]

// Input  : [3, 2, 1]
// Output : [1, 2, 3]

// Constraints :
// 1 <= N <= 10^5
// Values may contain duplicates
// Must return next lexicographical permutation


// 🔴 Approach 1 Brute Force (Generate all permutations)
vector<int> brute(vector<int> arr) {

    // Step A: Make a sorted version → first permutation in lexicographical order
    vector<int> sortedArr = arr;
    sort(sortedArr.begin(), sortedArr.end());

    // Store all permutations
    vector<vector<int>> all;
    do {
        all.push_back(sortedArr);
        // keep generating next permutations
    } while (next_permutation(sortedArr.begin(), sortedArr.end()));

    // Step B: Find given array in all permutations and return next
    for (int i = 0; i < all.size(); i++) {

        if (all[i] == arr) { // found current arrangement
            if (i == all.size() - 1)
                return all[0]; // if last, return first (smallest)
            return all[i + 1]; // else return next one
        }
    }

    return arr; // fallback
}

// 🔵 Approach 2 Better (Manual Next Permutation)
void nextPermutation(vector<int>& arr) {
    int n = arr.size();

    // Step 1: Find rightmost index i such that arr[i] < arr[i+1]
    // That means arr[i] is the "dip" where we can make a larger permutation
    int i = n - 2;
    while (i >= 0 && arr[i] >= arr[i + 1]) {
        i--; // move left until dip found
    }

    // Case: No dip found → array is the largest permutation
    if (i < 0) {
        reverse(arr.begin(), arr.end()); // return smallest arrangement
        return;
    }

    // Step 2: From right, find element just greater than arr[i]
    int j = n - 1;
    while (arr[j] <= arr[i]) {
        j--; // find swap candidate
    }

    // Step 3: Swap them
    swap(arr[i], arr[j]);

    // Step 4: Reverse suffix starting at i+1 so we get the next smallest form
    reverse(arr.begin() + i + 1, arr.end());
}

// 🟢 Approach 3 Optimal (Using STL next_permutation)
bool nextPermutationSTL(vector<int>& arr) {
    // STL handles all logic internally
    // Returns false if it was the last permutation (and arr becomes first)
    return next_permutation(arr.begin(), arr.end());
}

// main function to test all approaches
int main() {

    vector<int> a1 = {1, 2, 3};
    vector<int> a2 = {3, 2, 1};
    vector<int> a3 = {1, 1, 5};
    vector<int> a4 = {1, 3, 2};

    cout << "Brute Result for {1,2,3} : ";
    vector<int> b = brute(a1);
    for (int x : b) cout << x << " ";
    cout << endl;

    cout << "Manual Next Permutation for {3,2,1} : ";
    nextPermutation(a2);
    for (int x : a2) cout << x << " ";
    cout << endl;

    cout << "Manual Next Permutation for {1,1,5} : ";
    nextPermutation(a3);
    for (int x : a3) cout << x << " ";
    cout << endl;

    cout << "STL next_permutation for {1,3,2} : ";
    nextPermutationSTL(a4);
    for (int x : a4) cout << x << " ";
    cout << endl;

    return 0;
}

/*
=============================================================
DRY RUN EXAMPLES FOR NEXT PERMUTATION
=============================================================

-------------------------------------------------------------
Example 1:
Input  : [1, 2, 3]
Output : [1, 3, 2]   (next lexicographical)

Manual Steps:
i starts at n-2 = 1
Check arr[1] = 2, arr[2] = 3 → 2 < 3, dip found at i = 1
From right find j where arr[j] > arr[i] → j = 2 (3 > 2)
Swap arr[i], arr[j] → [1, 3, 2]
Reverse suffix from i+1 (already in order)
Final: [1, 3, 2]

-------------------------------------------------------------
Example 2 (strictly decreasing):
Input  : [3, 2, 1]
Output : [1, 2, 3]  (wraps to smallest)

Steps:
i starts at 1 → arr[1]=2, arr[2]=1 → 2 >= 1, continue
i=0 → arr[0]=3, arr[1]=2 → 3 >= 2, continue
i becomes -1 → no dip
Reverse whole array → [1, 2, 3]

-------------------------------------------------------------
Example 3 (repeating elements):
Input  : [1, 1, 5]
Output : [1, 5, 1]

Steps:
i = 1 → arr[1]=1, arr[2]=5 → dip at i=1
From right find j s.t arr[j] > arr[i] → j = 2 (5)
Swap → [1,5,1]
Suffix reverse does not change order
Final: [1, 5, 1]

-------------------------------------------------------------
Example 4 (middle case):
Input  : [1, 3, 2]
Output : [2, 1, 3]

Steps:
i=1: arr[1]=3, arr[2]=2 → 3 >= 2 continue
i=0: arr[0]=1, arr[1]=3 → dip at i=0
Find j from right: arr[2]=2 > 1 → j=2
Swap → [2, 3, 1]
Reverse suffix from 1 → [2, 1, 3]

-------------------------------------------------------------
Example 5 (two elements):
Input  : [2, 1]
Output : [1, 2]

Steps:
i = 0 → arr[0] = 2 >= arr[1] = 1 → i = -1
Reverse entire → [1, 2]

-------------------------------------------------------------
Example 6 (one element):
Input  : [7]
Output : [7]

Steps:
No dip possible, result same.

-------------------------------------------------------------
Example 7 (bigger random example)
Input  : [1, 4, 3, 2]
Output : [2, 1, 3, 4]

Steps:
i=2: arr[2]=3, arr[3]=2 → 3 >= 2 continue
i=1: arr[1]=4, arr[2]=3 → 4 >= 3 continue
i=0: arr[0]=1, arr[1]=4 → dip at i=0
From right, j=3: arr[3]=2 > 1 → j found
Swap arr[0] and arr[3] → [2, 4, 3, 1]
Reverse suffix from index 1: [4, 3, 1] → [1, 3, 4]
Final: [2, 1, 3, 4]

=============================================================
Quick Reference Expected Results:
Input              → Output
[1,2,3]            → [1,3,2]
[3,2,1]            → [1,2,3]
[1,1,5]            → [1,5,1]
[1,3,2]            → [2,1,3]
[2,1]              → [1,2]
[7]                → [7]
[1,4,3,2]          → [2,1,3,4]
=============================================================
*/

