#include <bits/stdc++.h>
using namespace std;

/*
🧠 Problem:
Given an integer array arr[], count pairs (i, j) such that:
i < j AND arr[i] > 2 * arr[j]

Example:
Input  : arr = [1, 3, 2, 3, 1]
Output : 2
Explanation:
Pairs are: (3,1) at indices (1,4) and (3,1) at indices (3,4)

Constraints:
1 ≤ n ≤ 10^5
-10^9 ≤ arr[i] ≤ 10^9
The answer fits in 64-bit (long long).
*/


// ============================================================================
// 🔴 Approach 1: Brute Force
// Intuition:
// Directly check all pairs (i,j)
// If arr[i] > 2 * arr[j], count++
//
// Algo:
// for i in [0..n-1]:
//     for j in [i+1..n-1]:
//         if arr[i] > 2*arr[j]: count++
//
// TC: O(N^2)  (too slow for N > 10^4)
// SC: O(1)
// ============================================================================
long long brute(vector<int>& arr) {
    long long cnt = 0;
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((long long)arr[i] > 2LL * arr[j]) cnt++;
        }
    }
    return cnt;
}


// ============================================================================
// 🟢 Approach 2: Optimal using Merge Sort (Divide & Conquer)
// WHY MERGE SORT WORKS? (Very important)
// After dividing, left[] and right[] are individually sorted.
// For each element in left part, we want to count how many elements in right
// satisfy:
// left[i] > 2 * right[j]
//
// Because right[] is sorted, once a right[j] satisfies the condition,
// ALL elements after j will also satisfy it
// → so we can count them in O(1) bulk instead of scanning.
//
// TC: O(N log N)
// SC: O(N)
// ============================================================================
class Solution {
private:

    // ------------------------------------------------------------
    // countPairs():
    // Counts reverse pairs across two sorted halves of array:
    // Condition: arr[left] > 2 * arr[right]
    //
    // Left half : arr[low ... mid]
    // Right half: arr[mid+1 ... high]
    //
    // Because both halves are sorted, we can use two pointers.
    // ------------------------------------------------------------
    long long countPairs(vector<int>& arr, int low, int mid, int high) {

        long long cnt = 0;
        int right = mid + 1;  // pointer for right half

        // Iterate over left half elements
        for (int left = low; left <= mid; left++) {

            // Move right pointer forward while condition holds
            while (right <= high && (long long)arr[left] > 2LL * arr[right]) {
                right++;
            }

            // All elements from (mid+1) to (right-1) satisfy reverse pair
            // So we add the count in one shot
            cnt += (right - (mid + 1));
        }
        return cnt;
    }


    // ------------------------------------------------------------
    // mergeAndSort():
    // Standard merge step of merge sort to sort subarray arr[low..high]
    // After countPairs() is done, we must re-sort the subarray
    // to maintain sorted property for upper recursion levels.
    // ------------------------------------------------------------
    long long mergeAndSort(vector<int>& arr, int low, int mid, int high) {

        vector<int> temp;           // temporary sorted output
        int left = low;             // pointer to left sorted block
        int right = mid + 1;        // pointer to right sorted block

        // Merge two sorted halves
        while (left <= mid && right <= high) {
            if (arr[left] <= arr[right]) {
                temp.push_back(arr[left++]);
            } else {
                temp.push_back(arr[right++]);
            }
        }

        // Copy remaining left half elements
        while (left <= mid) temp.push_back(arr[left++]);

        // Copy remaining right half elements
        while (right <= high) temp.push_back(arr[right++]);

        // Write back sorted result into original array segment
        for (int i = low; i <= high; i++) {
            arr[i] = temp[i - low];
        }

        return 0;   // return value unused, just keeping structure consistent
    }


    // ------------------------------------------------------------
    // mergeSort():
    // Recursively splits array and counts reverse pairs using
    // countPairs() during merge step.
    // ------------------------------------------------------------
    long long mergeSort(vector<int>& arr, int low, int high) {

        if (low >= high) return 0;     // base case: single element

        int mid = (low + high) / 2;
        long long cnt = 0;

        // Count in left half
        cnt += mergeSort(arr, low, mid);

        // Count in right half
        cnt += mergeSort(arr, mid + 1, high);

        // Count cross-half reverse pairs
        cnt += countPairs(arr, low, mid, high);

        // Sort this segment for future use
        mergeAndSort(arr, low, mid, high);

        return cnt;
    }

public:
    // ------------------------------------------------------------
    // reversePairs():
    // Wrapper function to trigger merge sort counting
    // ------------------------------------------------------------
    long long reversePairs(vector<int>& arr) {
        return mergeSort(arr, 0, arr.size() - 1);
    }
};


// ============================================================================
// main() for testing
// ============================================================================
int main() {

    vector<int> arr = {1, 3, 2, 3, 1};

    cout << "Brute Output:   " << brute(arr) << endl;

    Solution obj;
    vector<int> temp = arr;
    cout << "Optimal Output: " << obj.reversePairs(temp) << endl;

    return 0;
}


/*
===================== Dry Run (Optimal with explanation) =====================

arr = [1, 3, 2, 3, 1]

Divide using merge sort:

Left=[1,3,2], Right=[3,1]

Sort left recursively -> [1,2,3]
Sort right recursively -> [1,3]

Now count pairs across segments:

Left=[1,2,3], Right=[1,3]

For left[i]=1: no right elems satisfy 1 > 2*right[j]
For left[i]=2: no right elems satisfy 2 > 2*right[j]
For left[i]=3: check:
   3 > 2*1 → yes (1 pair)
   3 > 2*3 → no

So far count = 1

Final sorted: [1,1,2,3,3]

Then earlier recursive stage also counts one more pair.

Total reverse pairs = 2


===================== Edge Cases =====================
Case 1: arr sorted ascending → count = 0
Case 2: arr sorted descending → count = max ~ n*(n-1)/2
Case 3: negative values still work because comparison uses > 2*x
Case 4: duplicates allowed and handled successfully


===================== Follow-up Questions =====================
Q1) Can we use Fenwick Tree / BIT for this?
Yes, using coordinate compression, O(N log N).

Q2) Why not QuickSort based approach?
QuickSort does not ensure sorted subarrays during recursion,
so cannot count pairs efficiently.

Q3) What if we want pairs arr[i] >= 3 * arr[j]?
Same logic, change comparison to > 3*arr[j].

Q4) Can this be extended for 2D points inversion?
Yes, using advanced merge counting or range trees.

Q5) Can it be solved in streaming (online)?
Use ordered set / BIT / balanced BST.
*/

// Quick Concept Recap
// | Step              | Key Insight                                                |
// | ----------------- | ---------------------------------------------------------- |
// | Divide            | Split into two sorted halves using merge sort              |
// | Count Cross Pairs | Since halves are sorted, use two pointers to count in bulk |
// | Merge             | Re-sort merged region to maintain sorted property          |
// | Result            | O(N log N) time, handles large constraints                 |
