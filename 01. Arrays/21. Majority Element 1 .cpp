#include <bits/stdc++.h>
using namespace std;

// 🧠 Problem : Given an array arr, find the element that occurs more than n/2 times. If no such element exists, return -1.

// Example : 
// Input  : [2, 2, 1, 1, 1, 2, 2]
// Output : 2

// Constraint : 
// 1. Majority element appears strictly more than n/2 times.
// 2. Return -1 if no majority exists.

// 🔴 Approach 1 Brute Force : 
// Intuition:
// For each element, count how many times it appears. If count > n/2,
// that element is the majority.

// Algo:
// 1. For i from 0 to n-1:
//      - cnt = 0
//      - For j from 0 to n-1:
//            if arr[j] == arr[i], cnt++
//      - If cnt > n/2 -> return arr[i]
// 2. If none found, return -1.
//
// TC : O(n^2) due to two nested loops
// SC : O(1)

// Edge cases:
// 1. If n == 1, that single element is majority.
// 2. If no element frequency > n/2, return -1.
int brute(vector<int>& arr) {
    int n = arr.size();

    for(int i = 0; i < n; i++) {
        int cnt = 0;

        // Count frequency of arr[i]
        for(int j = 0; j < n; j++) {
            if(arr[i] == arr[j]) cnt++;
        }

        // Check if majority
        if(cnt > n / 2) return arr[i];
    }

    return -1;
}

// 🔵 Approach 2 Better : 
// Intuition:
// Use a hash map to store frequency of each number.
// As soon as any count > n/2, return it.
//
// Algo:
// 1. freq = empty map
// 2. For each num in arr:
//       freq[num]++
//       if freq[num] > n/2 -> return num
// 3. If none exceeds, return -1.
//
// TC : O(n) average (hash operations)
// SC : O(n)
//
// Edge cases:
// 1. Works with negative and large integers.
// 2. Handles multiple candidates, returns first majority found.
int hashMap(vector<int>& arr) {
    unordered_map<int, int> freq;
    int n = arr.size();

    for(int num : arr) {
        freq[num]++; // increase frequency

        if(freq[num] > n/2) return num; // majority found
    }

    return -1;
}

// 🟢 Approach 3 Optimal: 
// Intuition:
// Majority element appears more than half. If we pair each occurrence
// with a different number, the majority will remain unpaired at end.
//
// Algo:
// 1. count = 0, candidate = any
// 2. For each num:
//       if count == 0: candidate = num
//       if num == candidate: count++
//       else: count--
// 3. Candidate now holds potential answer
// 4. Verify by counting again if needed.
//
// TC : O(n)
// SC : O(1)
//
// Edge cases:
// 1. Must reverify if problem allows no-majority case.
// 2. For guaranteed majority (LeetCode majority element), no verification needed.

int boyerMoore(vector<int>& arr) {

    int count = 0, candidate = 0;

    // Phase 1: Find candidate
    for(int num : arr) {

        if(count == 0) 
            candidate = num;

        if(num == candidate)
            count++;
        else
            count--;
    }

    // Phase 2: Verify candidate
    int cnt = 0;
    for(int x : arr) {
        if(x == candidate) cnt++;
    }

    if(cnt > arr.size()/2) return candidate;
    return -1;
}
int main() {

    vector<int> arr = {2, 2, 1, 1, 1, 2, 2};

    cout << "Brute Force Majority:       " << brute(arr) << endl;
    cout << "Hash Map Majority:          " << hashMap(arr) << endl;
    cout << "Boyer-Moore Majority:       " << boyerMoore(arr) << endl;

    return 0;
}

/*
================================================================
DRY RUNS FOR ALL POSSIBLE CASES
================================================================

---------------------------------------------------------------
Case 1: Standard Majority Exists
arr = [2, 2, 1, 1, 1, 2, 2], n=7, n/2=3
Majority = 2

Brute:
count(2)=4 > 3 → return 2

HashMap:
freq[2] → 1,2
freq[1] → 1,2,3
freq[2] → 3,4 → return 2

Boyer Moore:
count=1 (2)
count=2 (2)
count=1 (1 cancels)
count=0 (1 cancels)
count=1 candidate=1
count=0 when 2 comes
count=1 candidate=2
Verify freq(2)=4 > 3, return 2

---------------------------------------------------------------
Case 2: Already Majority is first element
arr = [7, 7, 7, 2, 3], n=5, n/2=2
Majority = 7

Brute: count(7)=3 > 2 → return 7
Hash: freq[7] exceeds 2 → return 7
Boyer Moore:
candidate=7 keeps majority

---------------------------------------------------------------
Case 3: Single Element
arr = [10]
Majority = 10

All approaches return 10.

---------------------------------------------------------------
Case 4: No Majority Exists
arr = [1, 2, 3, 4], n=4, n/2=2
None occurs >2 times.

Brute → return -1
Hash → return -1
Boyer Moore:
candidate found but verify fails → -1

---------------------------------------------------------------
Case 5: Negative numbers
arr = [-1, -1, -1, 2, 3], n=5, n/2=2
Majority = -1

---------------------------------------------------------------
Case 6: Alternating values (no majority)
arr = [5, 6, 5, 6, 5, 6], n=6, n/2=3
each freq = 3, not >3 → return -1

---------------------------------------------------------------
Case 7: Edge tricky cancellation pattern
arr = [3, 3, 4, 2, 4, 4, 2, 4, 4], n=9, n/2=4
Majority = 4
Boyer Moore must still find candidate correctly.
*/