#include <bits/stdc++.h>
using namespace std;

/*
=====================================================================
🧠 Problem : Upper Bound in a Sorted Array
=====================================================================
Given a SORTED array arr and a value x, return the index of the first
element that is STRICTLY GREATER THAN x. If no such element exists,
return n (size of array).

This operation is known as "Upper Bound".

---------------------------------------------------------------------
Example :
Input  : arr = [2, 4, 7, 10, 15], x = 7
Output : 3   (10 is the first element > 7)

Input  : arr = [2, 4, 7, 10, 15], x = 16
Output : 5   (no element > 16 → return n)

---------------------------------------------------------------------
Constraints :
1. Array must be sorted in non-decreasing order.
2. Works with duplicates, negative values, large values.
3. Return n if upper bound does not exist.
=====================================================================
*/


// =================================================================
// 🔴 Approach 1 Brute Force
// =================================================================
//
// Intuition:
// Scan from left and return the first index where arr[i] > x.
//
// Algo:
// for i from 0 to n-1:
//     if arr[i] > x → return i
// return n
//
// TC : O(n)
// SC : O(1)
//
// Edge cases:
// 1. x < first element → return 0
// 2. x >= all elements → return n
// 3. duplicates handled automatically
// =================================================================
int upperBoundBrute(vector<int>& arr, int x) {
    int n = arr.size();
    for(int i = 0; i < n; i++){
        if(arr[i] > x)
            return i;
    }
    return n;
}


// =================================================================
// 🔵 Approach 2 Binary Search (Better / Optimal)
// =================================================================
//
// Intuition:
// Similar to lower bound, but condition becomes arr[mid] > x.
//
// Algo:
// low = 0, high = n-1, ans = n
// while low <= high:
//     mid = low + (high-low)/2
//     if arr[mid] > x:
//         ans = mid
//         high = mid - 1
//     else:
//         low = mid + 1
// return ans
//
// TC : O(log n)
// SC : O(1)
// =================================================================
int upperBoundBinary(vector<int>& arr, int x) {
    int n = arr.size();
    int low = 0, high = n - 1;
    int ans = n;

    while(low <= high){
        int mid = low + (high - low) / 2;

        if(arr[mid] > x){
            ans = mid;       // candidate
            high = mid - 1;  // search left side for smaller index
        } else {
            low = mid + 1;   // move right
        }
    }
    return ans;
}


// =================================================================
// 🟢 Approach 3 Using STL upper_bound()
// =================================================================
//
// Intuition:
// C++ provides upper_bound in <algorithm> which returns iterator to
// first element > x.
//
// Algo:
// return upper_bound(arr.begin(), arr.end(), x) - arr.begin()
//
// TC : O(log n)
// SC : O(1)
// =================================================================
int upperBoundSTL(vector<int>& arr, int x){
    return upper_bound(arr.begin(), arr.end(), x) - arr.begin();
}


// =================================================================
// MAIN TESTING
// =================================================================
int main() {
    vector<int> arr = {2, 4, 7, 10, 15};
    int x = 7;

    cout << "Brute Force Upper Bound Index : " << upperBoundBrute(arr, x) << endl;
    cout << "Binary Search Upper Bound Index : " << upperBoundBinary(arr, x) << endl;
    cout << "STL Upper Bound Index : " << upperBoundSTL(arr, x) << endl;

    return 0;
}


/*
=====================================================================
DRY RUN (Binary Upper Bound)
=====================================================================
arr = [2, 4, 7, 10, 15], x = 7
indexes: 0  1  2   3   4
low = 0, high = 4, ans = 5

mid = 2 → arr[2] = 7  NOT > 7 → low = 3
mid = 3 → arr[3] = 10 > 7 → ans = 3, high = 2

Loop ends → return 3
=====================================================================

=====================================================================
EDGE CASES TESTING
=====================================================================
Case 1: arr = [3,5,8], x = 1  → return 0
Case 2: arr = [3,5,8], x = 6  → return 2
Case 3: arr = [3,5,8], x = 10 → return 3
Case 4: arr = [-5,-3,-1,4], x = -2 → return 2
Case 5: arr = [2,2,2,2], x = 2 → return 4 (all equal → none > 2)
=====================================================================

=====================================================================
FOLLOW-UP INTERVIEW QUESTIONS
=====================================================================
1. Difference between lower_bound and upper_bound?
2. Can upper bound be used to find last occurrence of a number?
3. How to derive upper bound using lower bound logic?
4. Does upper bound work for descending sorted arrays?
5. Can upper bound solve "Insert position" problems?
6. When does upper bound return n?
7. How to find count of occurrences using upper bound?
=====================================================================

=====================================================================
FOLLOW-UP INTERVIEW ANSWERS
=====================================================================

1. Difference between lower_bound and upper_bound?
lower_bound → first index where value >= x
upper_bound → first index where value > x

2. Can upper bound be used to find last occurrence of a number?
Yes. If we have:
lastOccurrence = upper_bound(x) - 1
but must ensure arr[lastOccurrence] == x.

3. How to derive upper bound using lower bound logic?
Change condition:
instead of (arr[mid] >= x), use (arr[mid] > x).

4. Does upper bound work for descending sorted arrays?
Not directly. Comparisons must be reversed for descending order.

5. Can upper bound solve "Insert position" problems?
Yes. For placing elements strictly after existing duplicates.

6. When does upper bound return n?
When no element is strictly greater than x.

7. How to find count of occurrences using upper bound?
count = upper_bound(x) - lower_bound(x)
=====================================================================
*/
