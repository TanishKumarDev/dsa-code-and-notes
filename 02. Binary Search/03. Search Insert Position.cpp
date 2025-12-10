#include <bits/stdc++.h>
using namespace std;

/*
=====================================================================
🧠 Problem : Search Insert Position (Binary Search)
=====================================================================
Given a SORTED array arr and a target value x, return the index where
x is found. If x is not present, return the index where it should be
INSERTED to keep the array sorted.

This is a classic Binary Search problem (LeetCode #35).

---------------------------------------------------------------------
Example :
Input  : arr = [2, 4, 7, 10, 15], x = 7
Output : 2  (7 exists at index 2)

Input  : arr = [2, 4, 7, 10, 15], x = 9
Output : 3  (9 should be inserted before 10)

Input  : arr = [2, 4, 7, 10, 15], x = 1
Output : 0  (insert at beginning)

Input  : arr = [2, 4, 7, 10, 15], x = 20
Output : 5  (insert at end)

---------------------------------------------------------------------
Constraints :
1. Array must be sorted in non-decreasing order.
2. Works with duplicates, negative and large values.
3. Return index in range [0, n].
=====================================================================
*/


// =================================================================
// 🔴 Approach 1 Brute Force (Linear Scan)
// =================================================================
//
// Intuition:
// Scan from left and return the first index where arr[i] >= x.
// If x > all elements, return n.
//
// Algo:
// for i in [0..n-1]:
//     if arr[i] >= x → return i
// return n
//
// TC : O(n)
// SC : O(1)
// =================================================================
int searchInsertBrute(vector<int>& arr, int x) {
    int n = arr.size();
    for(int i = 0; i < n; i++){
        if(arr[i] >= x)
            return i;
    }
    return n;
}


// =================================================================
// 🔵 Approach 2 Binary Search (Optimal)
// =================================================================
//
// Intuition:
// Binary Search for first index where arr[mid] >= x.
// If x exists, this gives correct index.
// If x does not exist, gives correct insert position.
//
// Algo:
// low = 0, high = n-1, ans = n
// while low <= high:
//     mid = low + (high-low)/2
//     if arr[mid] >= x:
//         ans = mid
//         high = mid - 1
//     else:
//         low = mid + 1
// return ans
//
// TC : O(log n)
// SC : O(1)
// =================================================================
int searchInsertBinary(vector<int>& arr, int x) {
    int n = arr.size();
    int low = 0, high = n - 1;
    int ans = n;

    while(low <= high){
        int mid = low + (high - low)/2;

        if(arr[mid] >= x){
            ans = mid;
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
    }
    return ans;
}


// =================================================================
// 🟢 Approach 3 Using STL lower_bound()
// =================================================================
//
// Intuition:
// C++ lower_bound gives first index where value >= x
//
// Algo:
// return lower_bound(arr.begin(), arr.end(), x) - arr.begin()
//
// TC : O(log n)
// SC : O(1)
// =================================================================
int searchInsertSTL(vector<int>& arr, int x){
    return lower_bound(arr.begin(), arr.end(), x) - arr.begin();
}


// =================================================================
// MAIN TESTING
// =================================================================
int main() {
    vector<int> arr = {2, 4, 7, 10, 15};
    int x = 9;

    cout << "Brute Force Insert Position : " << searchInsertBrute(arr, x) << endl;
    cout << "Binary Search Insert Position : " << searchInsertBinary(arr, x) << endl;
    cout << "STL Insert Position : " << searchInsertSTL(arr, x) << endl;

    return 0;
}


/*
=====================================================================
DRY RUN (Binary Search Example)
=====================================================================
arr = [2, 4, 7, 10, 15], x = 9
indexes: 0  1  2   3   4
low = 0, high = 4, ans = 5

mid = 2 → arr[2] = 7 < 9 → low = 3
mid = 3 → arr[3] = 10 >= 9 → ans = 3, high = 2
loop ends → return ans = 3
=====================================================================

=====================================================================
EDGE CASES TESTING
=====================================================================
Case 1: x smaller than all         arr=[5,10], x=1  → return 0
Case 2: x larger than all          arr=[5,10], x=20 → return 2
Case 3: x exists in array          arr=[2,4,7], x=7 → return 2
Case 4: duplicates                 arr=[2,4,4,4,9], x=4 → return 1
Case 5: negative numbers           arr=[-8,-3,0,3], x=-2 → return 2
=====================================================================

=====================================================================
FOLLOW-UP INTERVIEW QUESTIONS
=====================================================================
1. Relationship between Search Insert Position and lower_bound?
2. Can this be used in dynamic sorted array insertion?
3. How to handle insert position in descending sorted arrays?
4. Difference vs binary search that returns exact match only?
5. Can we use this logic in linked lists?
6. Can it be applied to rotated sorted arrays?
7. How to modify this to return insertion position + maintain count?
=====================================================================

=====================================================================
FOLLOW-UP INTERVIEW ANSWERS
=====================================================================

1. Relationship between Search Insert Position and lower_bound?
Search Insert Position is exactly lower_bound(arr, x) for sorted array.

2. Can this be used in dynamic sorted array insertion?
Yes. After finding pos = insertIndex, we can do insert(arr.begin()+pos, x).

3. How to handle insert position in descending sorted arrays?
Reverse comparisons:
if arr[mid] <= x → ans = mid, high = mid - 1
else low = mid + 1

4. Difference vs standard binary search returning match only?
Standard binary search returns -1 when not found.
Search Insert always returns valid position ∈ [0, n].

5. Can we use this logic in linked lists?
Not efficiently. Linked lists do not support random mid access; time becomes O(n).

6. Can it be applied to rotated sorted arrays?
Not directly. Need pivot logic first, then apply binary search on the correct half.

7. How to modify this to return insertion position + maintain count?
Use: pos = lower_bound(arr, x)
Then count duplicates using: upper_bound(arr, x) - lower_bound(arr, x)
=====================================================================
*/
