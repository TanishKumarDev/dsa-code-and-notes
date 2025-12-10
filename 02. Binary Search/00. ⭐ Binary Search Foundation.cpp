#include <bits/stdc++.h>
using namespace std;

/*
=====================================================================
🧠 Problem : Binary Search (Iterative + Recursive)
=====================================================================
Given a SORTED array arr and a target value, find the index of the
target using Binary Search. If the target does not exist, return -1.

Key Rule: Binary Search works ONLY on sorted arrays.

---------------------------------------------------------------------
Example :
Input  : arr = [2, 4, 7, 10, 15, 20, 30], target = 15
Output : 3   (0-based indexing)
---------------------------------------------------------------------
Constraints :
1. Array must be sorted in non-decreasing order.
2. Works on positive, negative, duplicate or large numbers.
3. If not found, return -1.
=====================================================================
*/


// =================================================================
// 🔴 Approach 1: Iterative Binary Search (Most used in interviews)
// =================================================================
//
// Intuition:
// Instead of scanning every element, we repeatedly divide the search
// space in half. Compare target with middle element and eliminate
// half of the array.
//
// Algo:
// 1. Initialize left = 0, right = n-1
// 2. While left <= right:
//       mid = left + (right-left)/2   (avoids overflow)
//       if arr[mid] == target -> return mid
//       else if arr[mid] < target  -> search right half
//       else -> search left half
// 3. If loop ends, target not found → return -1
//
// TC : O(log n)
// SC : O(1)
// Edge cases:
// 1. Empty array  -> return -1
// 2. Single element array
// 3. Target smaller than first or greater than last element
// 4. Duplicate values (returns any valid index)
// =================================================================
int binarySearchIterative(vector<int>& arr, int target) {
    int left = 0;                       // start pointer
    int right = arr.size() - 1;         // end pointer

    while (left <= right) {             // search space is valid
        int mid = left + (right - left) / 2;
        // safer than (left + right)/2 to avoid overflow

        if (arr[mid] == target) {
            return mid;                 // target found
        } 
        else if (arr[mid] < target) {
            left = mid + 1;             // search right half
        } 
        else {
            right = mid - 1;            // search left half
        }
    }
    return -1; // target not found
}


// =================================================================
// 🔵 Approach 2: Recursive Binary Search
// =================================================================
//
// Intuition:
// Problem is naturally recursive. Each recursive call eliminates
// half of current search space.
//
// Algo:
// base case: if left > right → return -1
// mid = left + (right-left)/2
// if arr[mid] == target -> return mid
// else if arr[mid] < target -> search right side
// else -> search left side
//
// TC : O(log n)
// SC : O(log n) due to recursion stack
// Edge cases:
// Same as iterative + stack overflow for extremely large arrays.
// =================================================================
int binarySearchRecursive(vector<int>& arr, int left, int right, int target) {
    if (left > right) return -1;        // no range left

    int mid = left + (right - left) / 2;

    if (arr[mid] == target) return mid;
    if (arr[mid] < target)
        return binarySearchRecursive(arr, mid + 1, right, target);
    else
        return binarySearchRecursive(arr, left, mid - 1, target);
}

// Wrapper function for recursion
int searchRecursive(vector<int>& arr, int target) {
    return binarySearchRecursive(arr, 0, arr.size() - 1, target);
}


// =================================================================
// 🟢 MAIN FUNCTION (Test Cases)
// =================================================================
int main() {
    vector<int> arr = {2, 4, 7, 10, 15, 20, 30};
    int target = 15;

    int idxIter = binarySearchIterative(arr, target);
    int idxRec  = searchRecursive(arr, target);

    cout << "Iterative result index: " << idxIter << endl;
    cout << "Recursive result index: " << idxRec  << endl;

    return 0;
}


/*
=====================================================================
DRY RUN (Iterative)
=====================================================================
arr = [2, 4, 7, 10, 15, 20, 30], target = 15
Indexes: 0  1  2  3   4   5   6

left = 0, right = 6
mid = 0 + (6-0)/2 = 3
arr[3] = 10 < target, so left = mid + 1 = 4

left = 4, right = 6
mid = 4 + (6-4)/2 = 5
arr[5] = 20 > target, so right = mid - 1 = 4

left = 4, right = 4
mid = 4
arr[4] = 15 == target → return 4
=====================================================================

=====================================================================
EDGE CASES TESTING
=====================================================================
Case 1: arr = [], target = 10 → return -1
Case 2: arr = [5], target = 5 → return 0
Case 3: arr = [5], target = 7 → return -1
Case 4: arr = [1,2,3,4,5], target = 0 → return -1
Case 5: arr = [1,2,3,4,5], target = 6 → return -1
Case 6: arr = [-5, -2, 0, 8], target = -2 → return 1
Case 7: duplicates: arr = [2,2,2,2], target=2 → return any valid index
=====================================================================

=====================================================================
INTERVIEW FOLLOW-UP ANSWERS
=====================================================================

1. Why does binary search require a sorted array?
Because binary search eliminates half of the search space in every step.
This is only possible when elements follow a sorted order so comparisons
(mid < target or mid > target) can help decide the correct half.

2. Why use mid = left + (right-left)/2 instead of (left+right)/2?
(left + right) may overflow when values are large (e.g., indices ~1e9).
Using left + (right-left)/2 prevents integer overflow and is safer.

3. What is the TC difference between binary search and linear search?
Linear Search   → O(n)
Binary Search   → O(log n)
Binary Search is exponentially faster for large n.

4. How to find first or last occurrence of an element using binary search?
Modify comparison logic:
- When arr[mid] == target, store mid as potential answer.
- For FIRST occurrence → search on left side → right = mid - 1
- For LAST occurrence  → search on right side → left  = mid + 1

5. How to use binary search on a decreasing (reverse sorted) array?
Just reverse the comparison:
if(arr[mid] == target) return mid;
if(arr[mid] > target) left = mid + 1;
else right = mid - 1;

6. Can binary search be applied on floating values?
Yes. Binary Search can be used for doubles/floats when searching for a
value or computing square roots, cube roots, etc. Stop when precision
difference becomes sufficiently small (epsilon comparison).

7. What is Binary Search on answer (BS on space)?
Binary Search is used when search space is not an array but an
"answer range". Common pattern in hard DSA:
- Minimum days to complete tasks
- Allocate books / Painter's partition problem
- Min speed / capacity to finish work
We guess an answer mid, check feasibility, and shrink range.

8. Modify binary search to count number of occurrences of a target.
Count = lastOccurrenceIndex - firstOccurrenceIndex + 1,
If first occurrence = -1, count = 0.
Technique uses two binary searches.

*/
