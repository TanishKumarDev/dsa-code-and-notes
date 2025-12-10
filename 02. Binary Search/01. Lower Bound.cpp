#include <bits/stdc++.h>
using namespace std;

/*
=====================================================================
🧠 Problem : Lower Bound in a Sorted Array
=====================================================================
Given a SORTED array arr and a value x, return the index of the first 
element which is NOT LESS THAN x (i.e., >= x). If no such element 
exists, return n (size of array).

This is known as the "Lower Bound" operation.

---------------------------------------------------------------------
Example :
Input  : arr = [2, 4, 7, 10, 15], x = 9
Output : 3   (10 is the first element >= 9)

Input  : arr = [2, 4, 7, 10, 15], x = 16
Output : 5   (no element >= 16 → return n)

---------------------------------------------------------------------
Constraints :
1. Array must be sorted in non-decreasing order.
2. Works with duplicates, negative values, large values.
3. Return n if lower bound does not exist.
=====================================================================
*/


// =================================================================
// 🔴 Approach 1 Brute Force
// =================================================================
//
// Intuition:
// Scan from left and return the first index where arr[i] >= x.
//
// Algo:
// for i from 0 to n-1:
//     if arr[i] >= x → return i
// return n
//
// TC : O(n)
// SC : O(1)
// Edge cases:
// 1. x smaller than first element → return 0
// 2. x greater than all elements → return n
// 3. duplicates are handled automatically
// =================================================================
int lowerBoundBrute(vector<int>& arr, int x) {
    int n = arr.size();
    for(int i = 0; i < n; i++){
        if(arr[i] >= x)
            return i;
    }
    return n;
}


// =================================================================
// 🔵 Approach 2 Better (Binary Search)
// =================================================================
//
// Intuition:
// Use Binary Search to find the first index where arr[mid] >= x.
// Maintain an answer variable initialized as n, and narrow search.
//
// Algo:
// low = 0, high = n-1
// ans = n
// while low <= high:
//     mid = low + (high-low)/2
//     if arr[mid] >= x:
//         ans = mid           (possible answer)
//         high = mid - 1      (search smaller index on left)
//     else:
//         low = mid + 1
// return ans
//
// TC : O(log n)
// SC : O(1)
// Edge cases:
// Same as brute, but faster.
// =================================================================
int lowerBoundBinary(vector<int>& arr, int x) {
    int n = arr.size();
    int low = 0, high = n - 1;
    int ans = n; // default if no element >= x

    while(low <= high){
        int mid = low + (high - low) / 2;

        if(arr[mid] >= x){
            ans = mid;       // candidate index
            high = mid - 1;  // try to find earlier index
        }
        else{
            low = mid + 1;   // go right
        }
    }
    return ans;
}


// =================================================================
// 🟢 Approach 3 Optimal (Using STL lower_bound)
// =================================================================
//
// Intuition:
// C++ provides lower_bound in <algorithm> which uses binary search.
//
// Algo:
// return lower_bound(arr.begin(), arr.end(), x) - arr.begin()
//
// TC : O(log n)
// SC : O(1)
// Edge cases:
// Same as above, built-in optimized implementation.
// =================================================================
int lowerBoundSTL(vector<int>& arr, int x){
    return lower_bound(arr.begin(), arr.end(), x) - arr.begin();
}


// =================================================================
// MAIN TESTING
// =================================================================
int main() {
    vector<int> arr = {2, 4, 7, 10, 15};
    int x = 9;

    cout << "Brute Force Lower Bound Index : " << lowerBoundBrute(arr, x) << endl;
    cout << "Binary Search Lower Bound Index : " << lowerBoundBinary(arr, x) << endl;
    cout << "STL Lower Bound Index : " << lowerBoundSTL(arr, x) << endl;

    return 0;
}


/*
=====================================================================
DRY RUN (Binary Search Example)
=====================================================================
arr = [2, 4, 7, 10, 15], x = 9
indexes: 0  1  2   3   4

low=0, high=4, ans=5
mid = 2 → arr[2]=7 < 9 → low = 3
mid = 3 → arr[3]=10 >= 9 → ans = 3, high = 2
loop ends → return ans = 3
=====================================================================

=====================================================================
EDGE CASES TESTING
=====================================================================
Case 1: arr = [3,5,8], x = 1 → return 0
Case 2: arr = [3,5,8], x = 6 → return 2
Case 3: arr = [3,5,8], x = 10 → return 3
Case 4: arr = [-5,-3,-1,4], x = -2 → return 2
Case 5: arr = [2,2,2,2], x = 2 → return 0 (first occurrence)
=====================================================================

=====================================================================
FOLLOW-UP INTERVIEW ANSWERS
=====================================================================

1. Difference between lower_bound and upper_bound?
lower_bound(arr.begin(), arr.end(), x)
→ returns the first index where value >= x

upper_bound(arr.begin(), arr.end(), x)
→ returns the first index where value > x

Example:
arr = [2, 4, 4, 4, 8]
lower_bound(x=4) → index 1
upper_bound(x=4) → index 4

2. Can lower bound be used to find the first occurrence of a number?
Yes. For sorted arrays, lower_bound(arr, x) gives the first index
where value >= x. If arr[index] == x, this is the first occurrence.

3. How do we modify binary search to find upper bound?
Instead of checking arr[mid] >= x, check arr[mid] > x.

Pseudo:
if arr[mid] > x:
    ans = mid
    high = mid - 1
else:
    low = mid + 1

4. Is lower bound still valid for descending sorted arrays?
No, not directly, because comparison logic depends on ascending order.
For descending arrays, comparisons must be reversed:
if arr[mid] <= x → search left
else → search right

5. Can lower bound be used in problems like "Insert position"?
Yes. lower_bound gives the exact position where x should be placed
while maintaining sorted order. Very common LeetCode pattern.

6. When does lower bound return n?
When no element in the array satisfies arr[i] >= x. Example:
arr = [3, 6, 10], x = 15 → return 3 (n)

7. How to handle lower bound in rotated sorted arrays?
Normal lower_bound does not work directly. We must first apply search
logic on rotated array using modified binary search, or find pivot and
apply lower_bound on correct half.
=====================================================================

*/
