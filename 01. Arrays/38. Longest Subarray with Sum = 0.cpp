#include <bits/stdc++.h>
using namespace std;

/*
🧠 Problem:
Given an integer array arr, find the length of the longest subarray whose sum is 0.

Example:
Input  : arr = [1, -1, 3, 2, -2, -3, 3]
Output : 6
Explanation:
Subarray [ -1, 3, 2, -2, -3, 3 ] has sum = 0 and length = 6

Constraints:
1 <= n <= 10^6
-10^9 <= arr[i] <= 10^9
*/


// ============================================================================
// 🔴 Approach 1: Brute Force (O(N^2) Time)
// Intuition:
// Check all possible subarrays (i to j) and compute sum.
// If sum becomes zero, update max length.
//
// Algo:
// maxLen = 0
// for i from 0 to n-1:
//    sum = 0
//    for j from i to n-1:
//        sum += arr[j]
//        if sum == 0: update maxLen
//
// TC: O(N^2)
// SC: O(1)
// Edge cases:
// Works with negative numbers, zeros, duplicates.
// ============================================================================
int bruteLongestZeroSum(vector<int>& arr) {
    int n = arr.size();
    int maxLen = 0;

    for (int i = 0; i < n; i++) {
        int sum = 0; 
        for (int j = i; j < n; j++) {
            sum += arr[j]; // accumulate sum
            if (sum == 0) {
                maxLen = max(maxLen, j - i + 1); // update longest
            }
        }
    }
    return maxLen;
}


// ============================================================================
// 🔵 Approach 2: Better (Prefix Sum + HashMap) O(N) Time
// Intuition:
// Maintain prefix sum. If prefixSum repeats, subarray between
// previous index + 1 and current index has sum = 0.
//
// Example: prefix sums
// arr:  [1, -1, 3, 2, -2, -3, 3]
// pSum: [1,  0, 3, 5,  3,  0, 3]
// Whenever prefixSum repeats → zero-sum subarray.
//
// Algo:
// prefixMap stores: (prefixSum → first index)
// sum = 0
// for each i:
//   sum += arr[i]
//   if sum == 0 → maxLen = i+1
//   else if sum exists in map → maxLen = max(maxLen, i - map[sum])
//   else store map[sum] = i
//
// TC: O(N)
// SC: O(N)
// Edge Cases:
// All zeros, no zero sum, large values, negative values
// ============================================================================
int longestZeroSumSubarray(vector<int>& arr) {
    int n = arr.size();
    unordered_map<long long, int> prefixIndex; // prefixSum → first index
    long long prefixSum = 0;
    int maxLen = 0;

    for (int i = 0; i < n; i++) {
        prefixSum += arr[i]; // running sum

        if (prefixSum == 0) {
            maxLen = i + 1; // entire array till i has sum zero
        }
        else if (prefixIndex.count(prefixSum)) {
            maxLen = max(maxLen, i - prefixIndex[prefixSum]);
        }
        else {
            prefixIndex[prefixSum] = i; // store first occurrence
        }
    }
    return maxLen;
}


// ============================================================================
// 🟢 Approach 3: Optimal same as Better (Prefix Sum + HashMap)
// In zero-sum subarray problem, Better approach is already optimal.
// No further optimization in time complexity possible.
//
// TC: O(N)
// SC: O(N)
// ============================================================================
int longestZeroSumSubarrayOptimal(vector<int>& arr) {
    return longestZeroSumSubarray(arr);
}


// ============================================================================
// main()
// ============================================================================
int main() {
    vector<int> arr = {1, -1, 3, 2, -2, -3, 3};

    cout << "Brute:   " << bruteLongestZeroSum(arr) << endl;
    cout << "Better:  " << longestZeroSumSubarray(arr) << endl;
    cout << "Optimal: " << longestZeroSumSubarrayOptimal(arr) << endl;

    return 0;
}


/*
======================= Dry Run (Better / Optimal) =======================

arr = [1, -1, 3, 2, -2, -3, 3]
prefixSum and map tracking:

i   arr[i]  prefixSum   Action                     maxLen
----------------------------------------------------------
0     1        1        store (1→0)
1    -1        0        sum==0 → maxLen = 2
2     3        3        store (3→2)
3     2        5        store (5→3)
4    -2        3        found 3 at index 2 → len = 4-2 = 2
5    -3        0        sum==0 → maxLen = 6
6     3        3        found 3 at index 2 → len = 6-2 = 4

Final maxLen = 6


============================ Edge Cases ============================
Case 1: arr = [0, 0, 0, 0] → longest = 4
Case 2: arr = [1, 2, 3] → longest = 0 (no zero sum)
Case 3: arr = [1, -1] → longest = 2
Case 4: arr = [-3, 1, 2] → longest = 3
Case 5: arr = [1000000000, -1000000000] → longest = 2


============================ Follow-Up Questions ============================
Q1: Can we return the actual subarray instead of length?
Yes. Store startIndex = prefixIndex[prefixSum] + 1 and endIndex = i.

Q2: How to count total zero-sum subarrays?
Increase count every time prefixSum repeats.

Q3: Will two-pointer sliding window work?
No, because array has negative numbers.

Q4: Can prefix sum overflow?
Use long long to prevent overflow.

Q5: How to solve zero-sum submatrix (2D grid)?
Fix left & right columns, compress rows, apply same logic.

=================================================================
*/
