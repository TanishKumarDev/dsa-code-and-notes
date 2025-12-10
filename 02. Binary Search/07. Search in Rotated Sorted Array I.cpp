#include <bits/stdc++.h>
using namespace std;

/*
=====================================================================
🧠 Problem : Search in Rotated Sorted Array (Part-I)
=====================================================================
You are given a SORTED array that has been ROTATED at some pivot
unknown to you. Search for a given target and return its index.
If not found, return -1.

Array contains DISTINCT integers. (No duplicates in this Part-I)

---------------------------------------------------------------------
Example :
Input  : arr = [4, 5, 6, 7, 0, 1, 2], x = 0
Output : 4

Input  : arr = [4, 5, 6, 7, 0, 1, 2], x = 3
Output : -1

---------------------------------------------------------------------
Why is this challenging?
Normal Binary Search fails because although the array was sorted,
it is rotated, meaning there is a "break" / "pivot":

Original sorted:   [0, 1, 2, 4, 5, 6, 7]
Rotated version:   [4, 5, 6, 7, 0, 1, 2]
                                 ^ pivot

The array is not globally sorted anymore, but it **is sorted in two halves**.

---------------------------------------------------------------------
Key Insight to handle rotation (Important for future):
At any mid position, at least ONE of the two halves is always sorted.

We check:
    If arr[left] <= arr[mid]  => LEFT half is sorted
    Else                      => RIGHT half is sorted

Then decide:
    If target lies inside sorted half → move there
    Else → move to the other half

This idea generalizes to almost all rotated-array problems.
---------------------------------------------------------------------
Constraints :
1. Array contains DISTINCT numbers.
2. Time Complexity must be O(log n).
3. Return -1 if element not found.
=====================================================================
*/


// =================================================================
// 🔴 Approach 1 Brute Force
// =================================================================
//
// Intuition:
// Check each element.
//
// TC : O(n)
// SC : O(1)
// =================================================================
int searchBrute(vector<int>& arr, int x){
    for(int i = 0; i < arr.size(); i++){
        if(arr[i] == x) return i;
    }
    return -1;
}


// =================================================================
// 🔵 Approach 2 Binary Search on Rotated Array (Optimal)
// =================================================================
//
// Intuition:
// Use the "one half is sorted" rule.
//
// Algo:
//
// low = 0, high = n-1
// while low <= high:
//     mid = (low + high)/2
//     if arr[mid] == x → return mid
//
//     If left half sorted (arr[low] <= arr[mid]):
//         if x is in [arr[low], arr[mid]] → high = mid - 1
//         else → low = mid + 1
//     Else right half sorted:
//         if x is in [arr[mid], arr[high]] → low = mid + 1
//         else → high = mid - 1
//
// return -1
//
// TC : O(log n)
// SC : O(1)
// =================================================================
int searchRotatedBinary(vector<int>& arr, int x){
    int low = 0, high = arr.size() - 1;

    while(low <= high){
        int mid = low + (high - low)/2;

        if(arr[mid] == x) return mid;

        // LEFT HALF sorted?
        if(arr[low] <= arr[mid]){
            if(arr[low] <= x && x < arr[mid])
                high = mid - 1; // search in left half
            else
                low = mid + 1;  // search in right half
        }
        else{ // RIGHT HALF sorted
            if(arr[mid] < x && x <= arr[high])
                low = mid + 1;  // search in right half
            else
                high = mid - 1; // search in left half
        }
    }
    return -1;
}


// =================================================================
// MAIN TESTING
// =================================================================
int main(){
    vector<int> arr = {4, 5, 6, 7, 0, 1, 2};
    int x = 0;

    cout << "Brute Force Result  : " << searchBrute(arr, x) << endl;
    cout << "Binary Search Result: " << searchRotatedBinary(arr, x) << endl;

    return 0;
}


/*
=====================================================================
DRY RUN (Search x = 0)
=====================================================================
arr = [4, 5, 6, 7, 0, 1, 2]
idx =  0  1  2  3  4  5  6
low=0, high=6
mid=3 → arr[3]=7 ≠ 0

Left half sorted? arr[0]=4 <= arr[3]=7 → YES
Is 0 in [4..7]? No → search right half
low = mid + 1 = 4

low=4, high=6
mid=5 → arr[5]=1 ≠ 0

Left half sorted? arr[4]=0 <= arr[5]=1 → YES
Is 0 in [0..1]? YES → search left half
high = mid - 1 = 4

low=4, high=4
mid=4 → arr[4] = 0 FOUND → return 4
=====================================================================

=====================================================================
EDGE CASES TESTING
=====================================================================
Case 1: No rotation       arr=[1,2,3,4], x=3 → index=2
Case 2: x not present     arr=[4,5,6,7,0,1], x=8 → -1
Case 3: single element    arr=[5], x=5 → 0
Case 4: pivot at start    arr=[7,0,1,2], x=7 → 0
Case 5: pivot at end      arr=[1,2,3,7], x=7 → 3
=====================================================================

=====================================================================
FOLLOW-UP INTERVIEW QUESTIONS
=====================================================================
1. How do we find pivot index (smallest element) in rotated array?
2. What changes if array contains duplicates?
3. How to search in rotated array containing duplicates?
4. How to return both position and pivot?
5. Can this logic be used for rotated strings, timestamps, circular arrays?
6. Can we apply this idea to find minimum element?
7. How can we search range [l, r] inside rotated array?
=====================================================================

=====================================================================
FOLLOW-UP INTERVIEW ANSWERS
=====================================================================

1. Find pivot index?
Use binary search:
if arr[mid] > arr[high] → pivot right
else pivot left

2. What if duplicates exist?
Sorted-half check may fail. Requires modified logic.

3. Search with duplicates?
If arr[mid] == arr[low] == arr[high] → shrink edges: low++, high--

4. Return pivot + search?
Find pivot first, then normal binary search in correct half.

5. Circular/clock-wise data?
Same logic works for circular buffers, timestamps, rotation problems.

6. Find minimum element?
Same pivot detection approach : smallest element = pivot.

7. Search within range [l, r]?
Check which segment is sorted and apply standard binary search rules.
=====================================================================
*/
