#include <bits/stdc++.h>
using namespace std;

/*
=====================================================================
🧠 Problem : Search in Rotated Sorted Array II (With Duplicates)
=====================================================================
Given a SORTED array that is ROTATED and may contain DUPLICATES,
search for a target value x. If found return true, else false.

This is LeetCode #81 (medium), extension of Rotated Sorted Array I.

---------------------------------------------------------------------
Example :
Input  : arr = [2, 5, 6, 0, 0, 1, 2], x = 0
Output : true

Input  : arr = [2, 5, 6, 0, 0, 1, 2], x = 3
Output : false

---------------------------------------------------------------------
Why is this version harder?
Duplicates break the logic of identifying the sorted half.

Example:
arr = [3, 1, 3, 3, 3]
Here arr[low] == arr[mid] == arr[high], so we cannot decide
which half is sorted.

Key FIX:
If arr[low] == arr[mid] == arr[high], SHRINK search space:
    low++, high--

This reduces ambiguous cases until we find a clear sorted half.

---------------------------------------------------------------------
Constraints :
1. Sorted + rotated array.
2. Contains duplicates.
3. Must do better than O(n) in average, but worst case may degrade.
=====================================================================
*/


// =================================================================
// 🔴 Approach 1 Brute Force
// =================================================================
//
// Simply linear scan. Works always, but O(n).
//
// TC : O(n)
// SC : O(1)
// =================================================================
bool searchBrute(vector<int>& arr, int x){
    for(int v : arr) if(v == x) return true;
    return false;
}


// =================================================================
// 🔵 Approach 2 Modified Binary Search (Handles Duplicates)
// =================================================================
//
// Intuition summary:
// - Works same as Part-I, but duplicates may prevent knowing sorted half.
// - If arr[low] == arr[mid] == arr[high], shrink boundaries.
//
// Algo:
// low = 0, high = n-1
// while low <= high:
//     mid = (low + high)/2
//     if arr[mid] == x → return true
//
//     if arr[low] == arr[mid] && arr[mid] == arr[high]:
//         low++, high--
//         continue
//
//     if left half sorted (arr[low] <= arr[mid]):
//         if x in [arr[low], arr[mid]] → high = mid - 1
//         else → low = mid + 1
//     else (right half sorted):
//         if x in [arr[mid], arr[high]] → low = mid + 1
//         else → high = mid - 1
//
// return false
//
// TC : Average O(log n), Worst O(n) (when many duplicates)
// SC : O(1)
// =================================================================
bool searchRotatedDuplicate(vector<int>& arr, int x){
    int low = 0, high = arr.size() - 1;

    while(low <= high){
        int mid = low + (high - low)/2;

        if(arr[mid] == x) return true;

        // Ambiguous case due to duplicates
        if(arr[low] == arr[mid] && arr[mid] == arr[high]){
            low++, high--;
            continue;
        }

        // LEFT half sorted?
        if(arr[low] <= arr[mid]){
            if(arr[low] <= x && x < arr[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
        // RIGHT half sorted
        else{
            if(arr[mid] < x && x <= arr[high])
                low = mid + 1;
            else
                high = mid - 1;
        }
    }
    return false;
}


// =================================================================
// MAIN TESTING
// =================================================================
int main(){
    vector<int> arr = {2, 5, 6, 0, 0, 1, 2};
    int x = 0;

    cout << "Brute Force Result       : " << (searchBrute(arr, x) ? "Found" : "Not Found") << endl;
    cout << "Binary Search Result     : " << (searchRotatedDuplicate(arr, x) ? "Found" : "Not Found") << endl;

    return 0;
}


/*
=====================================================================
DRY RUN (Example)
=====================================================================
arr = [2, 5, 6, 0, 0, 1, 2], x = 0
low=0, high=6
mid=3 -> arr[3]=0 → FOUND → return true
=====================================================================

When does worst case happen?
arr = [3,3,3,3,3,3,3], x = 3
Shrinking one-by-one → O(n)
=====================================================================

=====================================================================
EDGE CASES TESTING
=====================================================================
Case 1: No rotation
arr=[1,2,3,4], x=3 → true

Case 2: All duplicates
arr=[2,2,2,2], x=2 → true
arr=[2,2,2,2], x=3 → false

Case 3: Single element
arr=[5], x=5 → true
arr=[5], x=3 → false

Case 4: Rotation at index 0 (no real rotation)
arr=[1,2,2,3], x=2 → true

Case 5: x not exist
arr=[2,5,6,0,0,1,2], x=7 → false
=====================================================================

=====================================================================
FOLLOW-UP INTERVIEW QUESTIONS
=====================================================================
1. Why does worst-case time become O(n) for duplicates?
2. How to find pivot in rotated array with duplicates?
3. Can this approach be extended to return index instead of boolean?
4. Difference between this and Rotated Array without duplicates?
5. Can this logic be used for strings / circular buffers / timestamps?
6. How to handle multiple search queries efficiently?
7. Can we still use first/last occurrence idea in rotated arrays?
=====================================================================

=====================================================================
FOLLOW-UP INTERVIEW ANSWERS
=====================================================================

1. Why worst-case O(n)?
Because duplicates cause low++, high-- shrinking, losing the binary search reduction guarantee.

2. Find pivot with duplicates?
Same ambiguity: if arr[mid] == arr[high], reduce high-- and repeat.

3. Return index instead of boolean?
Yes. Replace "return true" with "return mid" and propagate -1 otherwise.

4. Difference vs no-duplicate version?
Decision of sorted side is ALWAYS reliable without duplicates.

5. Strings / timestamps / circular buffer?
Yes, same logic works for any rotated monotonic structure.

6. Multiple search queries?
Use modified binary search per query, or preprocess with segment tree / binary searchable un-rotated mapping.

7. First/last occurrence in rotated?
Need pivot detection first, then search in correct half applying LB/UB logic.
=====================================================================
*/
