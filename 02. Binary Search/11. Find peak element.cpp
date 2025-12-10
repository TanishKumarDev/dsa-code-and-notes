#include <bits/stdc++.h>
using namespace std;

/*
=====================================================================
🧠 Problem : Find Peak Element in a Mountain/Unimodal Array
=====================================================================
You are given an array arr where a peak element is defined as an element
that is STRICTLY greater than its neighbors.

Return ANY one peak element’s index. Multiple peaks may exist.

For boundaries:
- arr[0] is a peak if arr[0] > arr[1]
- arr[n-1] is a peak if arr[n-1] > arr[n-2]

---------------------------------------------------------------------
Example :
Input  : arr = [1, 3, 5, 4, 2]
Output : index 2 (peak = 5)

Input  : arr = [5, 10, 20, 15]
Output : index 2 (peak = 20)

Input  : arr = [10, 5]
Output : index 0 (peak = 10)

---------------------------------------------------------------------
Constraints :
1. Array may have multiple peaks.
2. Array is not necessarily strictly mountain-shaped, only need one peak.
3. Return any valid peak.
=====================================================================
*/


// =================================================================
// 🔴 Approach 1 Brute Force
// =================================================================
//
// Intuition:
// Check each element and compare with neighbors.
//
// TC : O(n)
// SC : O(1)
// =================================================================
int findPeakBrute(vector<int>& arr){
    int n = arr.size();
    if(n == 1) return 0;
    if(arr[0] > arr[1]) return 0;
    if(arr[n-1] > arr[n-2]) return n-1;

    for(int i = 1; i < n-1; i++){
        if(arr[i] > arr[i-1] && arr[i] > arr[i+1])
            return i;
    }
    return -1; // theoretically never happens if a peak always exists
}


// =================================================================
// 🔵 Approach 2 Optimal Binary Search
// =================================================================
//
// Intuition:
// Use binary search. At mid:
// - If arr[mid] < arr[mid+1], peak lies on RIGHT side (increasing slope).
// - Else peak lies on LEFT side (including mid).
//
// This works because at least one peak must exist in any array.
//
// TC : O(log n)
// SC : O(1)
// =================================================================
int findPeakBinary(vector<int>& arr){
    int n = arr.size();
    int low = 0, high = n - 1;

    while(low < high){
        int mid = low + (high - low) / 2;

        if(arr[mid] < arr[mid + 1])
            low = mid + 1;  // go right
        else
            high = mid;     // go left or stay
    }
    return low; // low = high = peak index
}


// =================================================================
// MAIN TESTING
// =================================================================
int main(){
    vector<int> arr = {1, 3, 5, 4, 2};

    cout << "Brute Force Peak index : " << findPeakBrute(arr) << endl;
    cout << "Binary Search Peak index : " << findPeakBinary(arr) << endl;

    return 0;
}


/*
=====================================================================
DRY RUN (Binary Search)
=====================================================================
arr = [1, 3, 5, 4, 2]
idx =  0  1  2  3  4

low=0, high=4
mid=2 → arr[2]=5, arr[3]=4 → arr[mid] > arr[mid+1]
=> high = mid = 2

low=0, high=2
mid=1 → arr[1]=3, arr[2]=5 => arr[mid] < arr[mid+1]
=> low = mid + 1 = 2

low=2, high=2 → stop
Peak index = 2, value=5
=====================================================================

=====================================================================
EDGE CASES TESTING
=====================================================================
Case 1: Single element
arr=[7] → peak index=0

Case 2: Strict descending
arr=[9,7,5,3] → peak index=0

Case 3: Strict ascending
arr=[1,2,3,4,5] → peak index=4

Case 4: Multiple peaks
arr=[1,3,2,4,1] → Binary search may return index 1 or 3

Case 5: Plateau (not allowed in strict peak definition)
arr=[2,2,2] → no peak (must handle separately if needed)
=====================================================================

=====================================================================
FOLLOW-UP INTERVIEW QUESTIONS
=====================================================================
1. Why does binary search work for peak finding?
2. What if equal neighbors exist (plateau)? Does logic change?
3. Can we use this for continuous functions or floating values?
4. Relation to "Find Peak Element" LeetCode problem?
5. Does a peak always exist in any array?
6. How to find ALL peak elements?
7. Can it be used to find peak in rotated sorted arrays?
=====================================================================

=====================================================================
FOLLOW-UP INTERVIEW ANSWERS
=====================================================================

1. Why does binary search work for peak finding?
Because if arr[mid] < arr[mid+1], ascending slope guarantees a peak on
the right. Otherwise peak is on left half including mid.

2. What if equal neighbors exist (plateau)?
Need modified logic or fallback to O(n). Strict peak requires >, not ≥.

3. Can we use this for continuous functions or floating values?
Yes. Binary search is used for unimodal function optimization.

4. Relation to LeetCode problem?
Identical. LeetCode #162: Find Peak Element.

5. Does a peak always exist?
Yes. In any array, at least one peak always exists.

6. How to find ALL peak elements?
Linear scan in O(n). Binary search only guarantees one peak.

7. Can it be used in rotated sorted arrays?
Yes, peak often corresponds to rotation pivot.
=====================================================================
*/
