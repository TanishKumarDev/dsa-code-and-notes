#include <bits/stdc++.h>
using namespace std;

/*
=====================================================================
🧠 Problem : Find Minimum in Rotated Sorted Array
=====================================================================
You are given a SORTED array that has been ROTATED at some pivot.
Find the MINIMUM element in the array.

NOTE: This version assumes DISTINCT elements (no duplicates).
(Duplicate version comes later if needed.)

---------------------------------------------------------------------
Example:
arr = [4, 5, 6, 7, 0, 1, 2]
Minimum = 0

arr = [3, 4, 5, 1, 2]
Minimum = 1

arr = [1, 2, 3, 4]
Minimum = 1  (not rotated)

---------------------------------------------------------------------
Why does rotation create difficulty?
Normally, minimum is always at index 0 in sorted array.

But rotation generates a "break" (pivot):
Sorted original:   [0, 1, 2, 4, 5, 6, 7]
Rotated version:   [4, 5, 6, 7, 0, 1, 2]
                                 ^
                           pivot / minimum

The array is NOT globally sorted anymore, but it consists of:
- One sorted left segment
- One sorted right segment
- Minimum lies at the boundary between segments (pivot)

---------------------------------------------------------------------
Key Insight (VERY IMPORTANT for future problems):
If arr[mid] > arr[high] ⇒ minimum lies to the RIGHT of mid.
If arr[mid] < arr[high] ⇒ minimum lies to the LEFT of mid (including mid).

This works because right segment always contains the pivot.
---------------------------------------------------------------------

Constraints:
1. Distinct values
2. O(log n) required
3. If array NOT rotated → answer = arr[0]
=====================================================================
*/


// =================================================================
// 🔴 Approach 1 Brute Force
// =================================================================
//
// Scan entire array and return the smallest element.
//
// TC : O(n)
// SC : O(1)
//
// Works but does not use binary search benefits.
// =================================================================
int findMinBrute(vector<int>& arr){
    int mn = INT_MAX;
    for(int x : arr) mn = min(mn, x);
    return mn;
}


// =================================================================
// 🔵 Approach 2 Binary Search (Optimal)
// =================================================================
//
// Intuition:
// Use relationship:
//     If arr[mid] > arr[high]  → pivot/minimum is right side
//     Else                    → pivot/minimum is left side (including mid)
//
// Algo:
// low = 0, high = n-1
// while low < high:
//     mid = (low + high) / 2
//     if arr[mid] > arr[high] → low = mid + 1
//     else → high = mid
// return arr[low]
//
// TC : O(log n)
// SC : O(1)
// =================================================================
int findMinBinary(vector<int>& arr){
    int low = 0, high = arr.size() - 1;

    while(low < high){
        int mid = low + (high - low)/2;

        if(arr[mid] > arr[high]) 
            low = mid + 1;   // minimum in right half
        else
            high = mid;      // minimum in left (possibly mid)
    }
    return arr[low];
}


// =================================================================
// MAIN TESTING
// =================================================================
int main(){
    vector<int> arr = {4, 5, 6, 7, 0, 1, 2};

    cout << "Brute Force Minimum  : " << findMinBrute(arr) << endl;
    cout << "Binary Search Minimum: " << findMinBinary(arr) << endl;

    return 0;
}


/*
=====================================================================
DRY RUN (Find min in: [4,5,6,7,0,1,2])
=====================================================================
low=0, high=6
mid = 3 → arr[3]=7 > arr[6]=2 → minimum in RIGHT half → low = 4

low=4, high=6
mid = 5 → arr[5]=1 <= arr[6]=2 → minimum in LEFT (including mid) → high = 5

low=4, high=5
mid = 4 → arr[4]=0 <= arr[5]=1 → high = 4

low=4, high=4 → stop → minimum = arr[4] = 0
=====================================================================

=====================================================================
EDGE CASES TESTING
=====================================================================
Case 1: Already sorted (no rotation)
arr=[1,2,3,4] → min = 1

Case 2: Single element
arr=[7] → min = 7

Case 3: Rotated at index 1
arr=[5,1,2,3,4] → min = 1

Case 4: Rotated at last
arr=[2,3,4,5,1] → min = 1

Case 5: Rotation near middle
arr=[30,40,50,10,20] → min = 10
=====================================================================

=====================================================================
FOLLOW-UP INTERVIEW QUESTIONS
=====================================================================
1. Why are we comparing arr[mid] with arr[high], not arr[low]?
2. How to find rotation count using this logic?
3. What changes if duplicates exist?
4. How to return pivot index instead of value?
5. How to apply same logic to find maximum?
6. How to search within this rotated array after finding pivot?
7. Why is worst-case still O(log n) (distinct case)?
=====================================================================

=====================================================================
FOLLOW-UP INTERVIEW ANSWERS
=====================================================================

1. Why compare with arr[high]?
Because right side always contains pivot (minimum). Comparing mid-to-high
tells if pivot lies to left or right.

2. Rotation count?
Index of minimum = number of rotations.
Example: [4,5,6,7,0,1,2] → min at index 4 → rotated 4 times.

3. Duplicates version?
Condition changes:
if arr[mid] == arr[high] → high--
Worst case: O(n)

4. Pivot index version?
Same logic, return index instead of value:
return low at the end.

5. Maximum?
Max = element just before min (or (minIndex - 1 + n) % n)

6. Search any element?
Find pivot first, then binary search in correct half.

7. Why guaranteed O(log n)?
Distinct elements ensure strictly sorted halves without ambiguity.
=====================================================================
*/
