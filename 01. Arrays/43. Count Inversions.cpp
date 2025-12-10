#include <bits/stdc++.h>
using namespace std;

/*
🧠 Problem:
Given an array arr[], count how many inversion pairs (i, j) exist such that:
i < j AND arr[i] > arr[j]

Example:
Input  : arr = [5, 3, 2, 4, 1]
Output : 8
Explanation inversion pairs:
(5,3), (5,2), (5,4), (5,1)
(3,2), (3,1)
(2,1)
(4,1)

Constraints:
1 ≤ n ≤ 10^6
-10^9 ≤ arr[i] ≤ 10^9
Answer fits in 64-bit (long long).
*/


// ============================================================================
// 🔴 Approach 1 Brute Force
// Intuition:
// Compare every element with every later element.
// If arr[i] > arr[j], inversion++.
//
// Algo:
// for i in [0..n-1]:
//    for j in [i+1..n-1]:
//       if arr[i] > arr[j]: cnt++
//
// TC: O(N^2)  (too slow for n > 10^5)
// SC: O(1)
// ============================================================================
long long brute(vector<int>& arr) {
    int n = arr.size();
    long long cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) cnt++;
        }
    }
    return cnt;
}


// ============================================================================
// 🔵 Approach 2 Optimal using Merge Sort (Divide & Conquer)
// Intuition (very important!):
//
// Think about how merge sort merges two sorted halves:
// Left part:  sorted L
// Right part: sorted R
//
// When merging, suppose L[left] > R[right]:
// Because both halves are sorted, EVERY element from L[left] to L[mid]
// is greater than R[right].
// Therefore, we can count inversions in bulk instead of comparing one by one.
//
// Why merge sort?
// 1) It divides array into sorted parts
// 2) During merge step, we detect how many elements from left-half
//    are greater than elements in right-half.
// 3) This gives inversion counts efficiently.
//
// TC: O(N log N)
// SC: O(N)
// ============================================================================
class Solution {
private:
    long long mergeAndCount(vector<int>& arr, int low, int mid, int high) {
        vector<int> temp;       // temporary sorted array
        int left = low;         // pointer for left half
        int right = mid + 1;    // pointer for right half
        long long invCount = 0;

        while (left <= mid && right <= high) {

            if (arr[left] <= arr[right]) {
                temp.push_back(arr[left]);
                left++;
            } else {
                temp.push_back(arr[right]);
                // Key logic:
                // arr[left] > arr[right]
                // Since left..mid is sorted,
                // all elements from left..mid are > arr[right]
                invCount += (mid - left + 1);
                right++;
            }
        }

        // remaining elements
        while (left <= mid) temp.push_back(arr[left++]);
        while (right <= high) temp.push_back(arr[right++]);

        // copy back sorted part
        for (int i = low; i <= high; i++) {
            arr[i] = temp[i - low];
        }
        return invCount;
    }

    long long mergeSort(vector<int>& arr, int low, int high) {
        if (low >= high) return 0;
        int mid = (low + high) / 2;

        long long inv = 0;
        inv += mergeSort(arr, low, mid);        // left inversions
        inv += mergeSort(arr, mid + 1, high);   // right inversions
        inv += mergeAndCount(arr, low, mid, high); // merge inversion count
        return inv;
    }

public:
    long long countInversions(vector<int>& arr) {
        return mergeSort(arr, 0, arr.size() - 1);
    }
};


// ============================================================================
// main() for testing
// ============================================================================
int main() {

    vector<int> arr = {5, 3, 2, 4, 1};

    Solution obj;
    cout << "Brute Inversions:  " << brute(arr) << endl;

    vector<int> temp = arr;
    cout << "Optimal Inversions: " << obj.countInversions(temp) << endl;

    return 0;
}


/*
========================= DRY RUN (Core Idea) =========================
arr = [5, 3, 2, 4, 1]

Sorted with merge steps:

Left: [5, 3, 2]      Right: [4, 1]

While merging left=[2,3,5], right=[1,4]

Compare 2 and 1:
2 > 1 → inversion count += (mid-left+1) = 3 values (2,3,5)
count = 3

Compare 2 and 4 → ok
Compare 3 and 4 → ok
Compare 5 and 4:
5 > 4 → inversion count += 1
count = 4

Final output: 8 total inversions

========================= EDGE CASES =========================
Case 1: Already sorted ascending → inversions = 0
Case 2: Sorted descending → inversions = n*(n-1)/2
Case 3: Contains duplicates → allowed, inversions counted only if arr[i] > arr[j]
Case 4: Large values or negatives → no problem, comparison only.

========================= FOLLOW-UP QUESTIONS =========================
Q1) Can this be solved using Fenwick Tree / BIT?
Yes, O(N log N) using coordinate compression.

Q2) Can this be solved using Balanced BST / Ordered Set?
Yes, also O(N log N).

Q3) What if we need inversion count mod 1e9+7? 
Just apply modulo to result.

Q4) Can we count reverse pairs (arr[i] > 2*arr[j])?
Yes, similar merge sort logic (LeetCode Hard problem).

Q5) Why not use QuickSort?
QuickSort does not guarantee sorted halves during recursion,
so it cannot count inversions efficiently.
*/
