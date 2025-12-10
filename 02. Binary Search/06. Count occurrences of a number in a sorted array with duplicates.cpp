#include <bits/stdc++.h>
using namespace std;

/*
=====================================================================
🧠 Problem : Count occurrences of a number in a sorted array
=====================================================================
Given a SORTED array arr and a value x, return how many times x appears.
If x does not appear, return 0.

This problem is a direct extension of "First & Last Occurrence".

---------------------------------------------------------------------
Example :
Input  : arr = [2, 4, 4, 4, 7, 10], x = 4
Output : 3

Input  : arr = [2, 4, 7, 10], x = 5
Output : 0

---------------------------------------------------------------------
Constraints :
1. Array must be sorted in non-decreasing order.
2. Includes duplicates, negative numbers, large values.
3. Return 0 if no occurrence exists.
=====================================================================
*/


// =================================================================
// 🔴 Approach 1 Brute Force (Linear Counting)
// =================================================================
//
// Intuition:
// Scan array, count how many elements equal x.
//
// TC : O(n)
// SC : O(1)
// =================================================================
int countBrute(vector<int>& arr, int x){
    int cnt = 0;
    for(int num : arr){
        if(num == x) cnt++;
    }
    return cnt;
}


// =================================================================
// 🔵 Approach 2 Optimal Binary Search using First + Last Occurrence
// =================================================================
//
// Intuition:
// count = lastIndex - firstIndex + 1
// If firstIndex = -1 → x not present → count = 0
//
// TC : O(log n)
// SC : O(1)
// =================================================================
int findFirst(vector<int>& arr, int x){
    int low = 0, high = arr.size() - 1, ans = -1;
    while(low <= high){
        int mid = low + (high - low)/2;
        if(arr[mid] == x){
            ans = mid;
            high = mid - 1; // search left half
        }
        else if(arr[mid] < x) low = mid + 1;
        else high = mid - 1;
    }
    return ans;
}

int findLast(vector<int>& arr, int x){
    int low = 0, high = arr.size() - 1, ans = -1;
    while(low <= high){
        int mid = low + (high - low)/2;
        if(arr[mid] == x){
            ans = mid;
            low = mid + 1; // search right half
        }
        else if(arr[mid] < x) low = mid + 1;
        else high = mid - 1;
    }
    return ans;
}

int countBinary(vector<int>& arr, int x){
    int first = findFirst(arr, x);
    if(first == -1) return 0; // not found
    int last = findLast(arr, x);
    return last - first + 1;
}


// =================================================================
// 🟢 Approach 3 Using STL (lower_bound + upper_bound)
// =================================================================
//
// lower_bound gives first index >= x
// upper_bound gives first index > x
// count = upper_bound(x) - lower_bound(x)
//
// TC : O(log n)
// SC : O(1)
// =================================================================
int countSTL(vector<int>& arr, int x){
    auto first = lower_bound(arr.begin(), arr.end(), x);
    if(first == arr.end() || *first != x)
        return 0;
    auto last = upper_bound(arr.begin(), arr.end(), x);
    return last - first;
}


// =================================================================
// MAIN TESTING
// =================================================================
int main(){
    vector<int> arr = {2, 4, 4, 4, 7, 10};
    int x = 4;

    cout << "Brute Force Count          : " << countBrute(arr, x) << endl;
    cout << "Binary Search Count        : " << countBinary(arr, x) << endl;
    cout << "STL Count                  : " << countSTL(arr, x) << endl;

    return 0;
}


/*
=====================================================================
DRY RUN (Binary Search Approach)
=====================================================================
arr = [2, 4, 4, 4, 7, 10], x = 4

FIRST occurrence:
mid=2 → arr[2]=4 match → ans=2, high=1
mid=0 → arr[0]=2 <4 → low=1
mid=1 → arr[1]=4 match → ans=1, high=0
first = 1

LAST occurrence:
mid=2 → arr[2]=4 match → ans=2, low=3
mid=4 → arr[4]=7 >4 → high=3
mid=3 → arr[3]=4 match → ans=3, low=4
last = 3

count = last - first + 1 = 3
=====================================================================

=====================================================================
EDGE CASES TESTING
=====================================================================
Case 1: x not present
arr=[1,3,5], x=2 → count=0

Case 2: single element match
arr=[7], x=7 → count=1

Case 3: all elements equal
arr=[4,4,4,4], x=4 → count=4

Case 4: negatives
arr=[-5,-3,-3,-3,1], x=-3 → count=3

Case 5: large range
arr=[1,2,3,4,5,6], x=10 → count=0
=====================================================================

=====================================================================
FOLLOW-UP INTERVIEW QUESTIONS
=====================================================================
1. Relationship with first/last occurrence problem?
2. Can this method work on descending sorted arrays?
3. How to count occurrences in rotated sorted arrays?
4. Can we do this in unsorted arrays efficiently?
5. Can we apply two-pointer or hash method here?
6. Are STL functions inclusive or exclusive for boundaries?
7. How useful is this in frequency queries?
=====================================================================

=====================================================================
FOLLOW-UP INTERVIEW ANSWERS
=====================================================================

1. Relationship with first/last occurrence problem?
Direct extension. count = last - first + 1.

2. Can this method work on descending sorted arrays?
Yes, but binary search conditions reverse.

3. How to count occurrences in rotated sorted arrays?
Find pivot, then check both sorted halves.

4. Can we do this in unsorted arrays efficiently?
Yes, using hash map. TC O(n), SC O(n).
Binary search won't work without sorting.

5. Can we apply two-pointer or hash method here?
Yes. Hashing useful for multiple queries. Two-pointer useful when
counting frequencies in sorted streaming windows.

6. Are STL boundaries inclusive?
lower_bound  → first index where value >= x
upper_bound  → first index where value > x (exclusive)

7. How useful is this in frequency queries?
Very useful for range counting, searching logs,
database indexing, autocomplete prefix ranges.
=====================================================================
*/
