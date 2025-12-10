#include <bits/stdc++.h>
using namespace std;

/*
=====================================================================
🧠 Problem : First & Last Occurrence of a Number (Sorted Array)
=====================================================================
Given a SORTED array arr and a target value x, return the index of:

1) First Occurrence  (leftmost position of x)
2) Last Occurrence   (rightmost position of x)

If x is not present, return {-1, -1}.

This is a classic Binary Search problem, useful in:
- Counting occurrences
- Range queries
- Frequency calculations

---------------------------------------------------------------------
Example :
Input  : arr = [2, 4, 4, 4, 7, 10], x = 4
Output : First = 1, Last = 3

Input  : arr = [2, 4, 7, 10], x = 5
Output : First = -1, Last = -1

---------------------------------------------------------------------
Constraints :
1. Array must be sorted in non-decreasing order.
2. Works with duplicates, negative values, large values.
3. Return {-1, -1} if no occurrence exists.
=====================================================================
*/


// =================================================================
// 🔴 Approach 1 Brute Force
// =================================================================
//
// Intuition:
// Scan from left to get the first index, and from right to get the last.
//
// TC : O(n)
// SC : O(1)
//
// Not optimal, but easy starting point.
// =================================================================
pair<int,int> firstLastBrute(vector<int>& arr, int x){
    int n = arr.size();
    int first = -1, last = -1;

    // first
    for(int i = 0; i < n; i++){
        if(arr[i] == x){
            first = i;
            break;
        }
    }

    // last
    for(int i = n-1; i >= 0; i--){
        if(arr[i] == x){
            last = i;
            break;
        }
    }
    return {first, last};
}


// =================================================================
// 🔵 Approach 2 Optimal Binary Search
// =================================================================
//
// First occurrence:
// If arr[mid] == x → store answer & search LEFT half (high = mid - 1)
//
// Last occurrence:
// If arr[mid] == x → store answer & search RIGHT half (low = mid + 1)
//
// TC : O(log n)
// SC : O(1)
// =================================================================
int findFirst(vector<int>& arr, int x){
    int n = arr.size(), low = 0, high = n - 1, ans = -1;

    while(low <= high){
        int mid = low + (high - low)/2;

        if(arr[mid] == x){
            ans = mid;
            high = mid - 1; // continue searching on left
        }
        else if(arr[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return ans;
}

int findLast(vector<int>& arr, int x){
    int n = arr.size(), low = 0, high = n - 1, ans = -1;

    while(low <= high){
        int mid = low + (high - low)/2;

        if(arr[mid] == x){
            ans = mid;
            low = mid + 1; // continue searching on right
        }
        else if(arr[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return ans;
}

pair<int,int> firstLastBinary(vector<int>& arr, int x){
    return { findFirst(arr, x), findLast(arr, x) };
}


// =================================================================
// 🟢 Approach 3 Using STL (lower_bound + upper_bound)
// =================================================================
//
// lower_bound(x) → first index where value >= x
// upper_bound(x) → first index where value > x
//
// If lower_bound gives idx where arr[idx] == x,
// Last occurrence = upper_bound(x) - 1
//
// TC : O(log n)
// SC : O(1)
// =================================================================
pair<int,int> firstLastSTL(vector<int>& arr, int x){
    int n = arr.size();

    auto it1 = lower_bound(arr.begin(), arr.end(), x);
    if(it1 == arr.end() || *it1 != x) return {-1, -1};

    auto it2 = upper_bound(arr.begin(), arr.end(), x);
    return { (int)(it1 - arr.begin()), (int)(it2 - arr.begin()) - 1 };
}


// =================================================================
// MAIN TESTING
// =================================================================
int main(){
    vector<int> arr = {2, 4, 4, 4, 7, 10};
    int x = 4;

    auto brute  = firstLastBrute(arr, x);
    auto binary = firstLastBinary(arr, x);
    auto stl    = firstLastSTL(arr, x);

    cout << "Brute  First="  << brute.first  << " Last=" << brute.second  << endl;
    cout << "Binary First="  << binary.first << " Last=" << binary.second << endl;
    cout << "STL    First="  << stl.first    << " Last=" << stl.second    << endl;

    return 0;
}


/*
=====================================================================
DRY RUN (Binary Search)
=====================================================================
arr = [2, 4, 4, 4, 7, 10], x = 4

FIRST occurrence search:
low=0, high=5
mid=2 → arr[2]=4 match → ans=2, high=1
mid=0 → arr[0]=2 <4 → low=1
mid=1 → arr[1]=4 match → ans=1, high=0
first = 1

LAST occurrence search:
low=0, high=5
mid=2 → arr[2]=4 match → ans=2, low=3
mid=4 → arr[4]=7 >4 → high=3
mid=3 → arr[3]=4 match → ans=3, low=4
last = 3
=====================================================================

=====================================================================
EDGE CASES TESTING
=====================================================================
Case 1: x not present        arr=[2,3,5], x=4 → {-1,-1}
Case 2: all x                arr=[4,4,4], x=4 → {0,2}
Case 3: single element match arr=[7], x=7    → {0,0}
Case 4: single element diff  arr=[7], x=3    → {-1,-1}
Case 5: negatives            arr=[-5,-3,-3], x=-3 → {1,2}
=====================================================================

=====================================================================
FOLLOW-UP INTERVIEW QUESTIONS
=====================================================================
1. How to count occurrences using first & last index?
2. What is the relation with lower_bound & upper_bound?
3. Can this logic work on descending sorted arrays?
4. How to apply this in rotated sorted arrays?
5. What happens if array is not sorted?
6. Use cases in real applications?
7. Can this help in frequency queries?
=====================================================================

=====================================================================
FOLLOW-UP INTERVIEW ANSWERS
=====================================================================

1. How to count occurrences using first & last index?
count = lastIndex - firstIndex + 1 (if firstIndex != -1)

2. Relation with lower_bound & upper_bound?
firstOccurrence = lower_bound(x)
lastOccurrence  = upper_bound(x) - 1

3. Can this logic work on descending sorted arrays?
Yes, but conditions invert:
For first occurrence: arr[mid] == x → ans = mid, search RIGHT
For last  occurrence: arr[mid] == x → ans = mid, search LEFT

4. How to apply in rotated sorted arrays?
Find pivot, decide which half x belongs to, then apply search.

5. What happens if array is not sorted?
Binary search will FAIL. Must sort first or use hash/scan approaches.

6. Use cases in real applications?
Finding frequency, search logs time ranges, database index ranges,
autocomplete / prefix searching, version control change ranges.

7. Can this help in frequency queries?
Yes. Very frequently used in problems asking:
How many times does x appear? (range queries, prefix sums, fenwick tree)
=====================================================================
*/
