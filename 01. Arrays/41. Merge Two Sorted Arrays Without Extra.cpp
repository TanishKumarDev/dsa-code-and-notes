#include <bits/stdc++.h>
using namespace std;

/*
🧠 Problem:
You are given two sorted arrays nums1 and nums2.
nums1 has extra space at the end to store all numbers from nums2.
Merge nums2 into nums1 so that nums1 becomes one sorted array.

Example:
Input:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],      n = 3

Output:
nums1 = [1,2,2,3,5,6]

Constraints:
1 ≤ m,n ≤ 10^5
Arrays are sorted in non-decreasing order.
Must modify nums1 in-place.
*/


// ============================================================================
// 🔴 Approach 1: Brute Force (Insert & Sort Again)
// Intuition:
// Simply copy nums2 elements into nums1, then sort nums1 again.
// Very slow for big input.
//
// Algo:
// for i from 0 to n-1:
//     nums1[m+i] = nums2[i]
// sort(nums1)
//
// TC: O((m+n) log (m+n))
// SC: O(1)
// ============================================================================
void mergeBrute(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    for (int i = 0; i < n; i++) {
        nums1[m + i] = nums2[i];    // copy nums2 elements
    }
    sort(nums1.begin(), nums1.end()); // re-sort full array
}


// ============================================================================
// 🔵 Approach 2: Better (Two Pointers + Extra Array)
// Intuition:
// Merge like merge step of merge sort, but use extra buffer and copy back.
//
// Algo:
// i = 0, j = 0
// while i < m && j < n:
//     choose smaller and push into temp
// append remaining
// copy temp array back into nums1
//
// TC: O(m+n)
// SC: O(m+n)
// ============================================================================
void mergeBetter(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    vector<int> temp;
    int i = 0, j = 0;

    while (i < m && j < n) {
        if (nums1[i] < nums2[j]) temp.push_back(nums1[i++]);
        else temp.push_back(nums2[j++]);
    }
    while (i < m) temp.push_back(nums1[i++]);
    while (j < n) temp.push_back(nums2[j++]);

    // Copy back
    for (int k = 0; k < m + n; k++) {
        nums1[k] = temp[k];
    }
}


// ============================================================================
// 🟢 Approach 3 (Optimal): Merge From The End (Three Pointers)
// Intuition:
// Instead of shifting elements, start filling from the END of nums1.
//
// Why from end?
// nums1 has empty positions at end; large values should be placed at back.
//
// Algo:
// i = m-1, j = n-1, k = m+n-1
// while i >= 0 and j >= 0:
//     if nums1[i] > nums2[j] → nums1[k] = nums1[i], i--, k--
//     else nums1[k] = nums2[j], j--, k--
//
// if remaining nums2, copy leftover into nums1
//
// TC: O(m+n)
// SC: O(1)  (best possible)
// ============================================================================
void mergeOptimal(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1;      // last valid from nums1
    int j = n - 1;      // last from nums2
    int k = m + n - 1;  // last space in nums1

    // Compare from end
    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) nums1[k--] = nums1[i--];
        else nums1[k--] = nums2[j--];
    }

    // Only nums2 might have leftovers
    while (j >= 0) {
        nums1[k--] = nums2[j--];
    }
}


// ============================================================================
// main() to test all merging approaches
// ============================================================================
int main() {

    vector<int> A1 = {1,2,3,0,0,0};
    vector<int> B1 = {2,5,6};
    int m = 3, n = 3;

    vector<int> nums1_brute = A1;
    vector<int> nums1_better = A1;
    vector<int> nums1_optimal = A1;

    mergeBrute(nums1_brute, m, B1, n);
    mergeBetter(nums1_better, m, B1, n);
    mergeOptimal(nums1_optimal, m, B1, n);

    cout << "Brute Merge Result:   ";
    for(int x : nums1_brute) cout << x << " ";
    cout << endl;

    cout << "Better Merge Result:  ";
    for(int x : nums1_better) cout << x << " ";
    cout << endl;

    cout << "Optimal Merge Result: ";
    for(int x : nums1_optimal) cout << x << " ";
    cout << endl;

    return 0;
}


/*
====================== Dry Run (Optimal) ======================
nums1 = [1,2,3,0,0,0], m=3
nums2 = [2,5,6],      n=3

i = 2 (3), j = 2 (6), k = 5

Step 1:
3 < 6 -> nums1[5] = 6
nums1 = [1,2,3,0,0,6]
j--, k--

Step 2:
3 < 5 -> nums1[4] = 5
nums1 = [1,2,3,0,5,6]
j--, k--

Step 3:
3 >= 2 -> nums1[3] = 3
nums1 = [1,2,3,3,5,6]
i--, k--

Step 4:
2 >= 2 -> nums1[2] = 2
nums1 = [1,2,2,3,5,6]
j--, k--

Remaining nums2 exhausted.

Final = [1,2,2,3,5,6]


====================== Edge Cases ======================
Case 1:
nums1 = [0], m=0
nums2 = [5], n=1 → result = [5]

Case 2:
nums2 empty → nums1 remains same

Case 3:
All nums2 smaller:
nums1=[5,6,7,0,0,0], nums2=[1,2,3]
result=[1,2,3,5,6,7]

Case 4:
Duplicates allowed and handled


====================== Follow-Up Questions ======================
Q1: Can we merge in decreasing order?  
Yes, just reverse comparison logic or reverse final array.

Q2: Can this work for linked lists?  
Same logic using merge-sorted-lists technique.

Q3: What if arrays are not sorted?  
Sort first → O((m+n) log (m+n))

Q4: Can we merge k sorted arrays?  
Use min-heap (priority queue) → O(N log k)

Q5: Can we do this in streaming input form?  
Yes, use external merging or heap-based merge.
*/
