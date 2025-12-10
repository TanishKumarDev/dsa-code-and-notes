#include <bits/stdc++.h>
using namespace std;

/*
=====================================================================
🧠 Problem : Floor & Ceil in a Sorted Array
=====================================================================
Given a SORTED array arr and a value x:

Floor of x = largest element <= x  
Ceil  of x = smallest element >= x  

If floor does not exist → return some sentinel (e.g., INT_MIN or -1 as per use case)  
If ceil does not exist  → return some sentinel (e.g., INT_MAX or -1)

---------------------------------------------------------------------
Example :
arr = [2, 4, 7, 10, 15], x = 9
Floor = 7  (largest <= 9)
Ceil  = 10 (smallest >= 9)

arr = [2, 4, 7, 10, 15], x = 1
Floor = NONE, Ceil = 2

arr = [2, 4, 7, 10, 15], x = 20
Floor = 15, Ceil = NONE

---------------------------------------------------------------------
Constraints :
1. Array must be sorted in non-decreasing order.
2. Works with duplicates, negative and large numbers.
3. Result may represent "no existence" situations.
=====================================================================
*/


// =================================================================
// 🔴 Approach 1 Brute Force (Linear Scan)
// =================================================================
//
// Intuition:
// Floor: scan elements <= x and track maximum.
// Ceil : scan elements >= x and track minimum.
//
// TC : O(n)
// SC : O(1)
// Not optimal, but easy understanding.
// =================================================================
pair<int,int> floorCeilBrute(vector<int>& arr, int x){
    int n = arr.size();
    int floorVal = INT_MIN;
    int ceilVal  = INT_MAX;

    for(int i = 0; i < n; i++){
        if(arr[i] <= x) floorVal = max(floorVal, arr[i]);
        if(arr[i] >= x) ceilVal  = min(ceilVal, arr[i]);
    }
    if(floorVal == INT_MIN) floorVal = -1; // not found
    if(ceilVal  == INT_MAX) ceilVal  = -1; // not found

    return {floorVal, ceilVal};
}


// =================================================================
// 🔵 Approach 2 Optimal (Binary Search)
// =================================================================
//
// Intuition:
// Very similar to lower/upper bound.
// Floor: last index where arr[mid] <= x
// Ceil : first index where arr[mid] >= x
//
// TC : O(log n)
// SC : O(1)
// =================================================================
pair<int,int> floorCeilBinary(vector<int>& arr, int x){
    int n = arr.size();

    int low = 0, high = n - 1;
    int floorVal = -1;

    // find floor
    while(low <= high){
        int mid = low + (high - low)/2;

        if(arr[mid] <= x){
            floorVal = arr[mid];
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    low = 0, high = n - 1;
    int ceilVal = -1;

    // find ceil
    while(low <= high){
        int mid = low + (high - low)/2;

        if(arr[mid] >= x){
            ceilVal = arr[mid];
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return {floorVal, ceilVal};
}


// =================================================================
// 🟢 Approach 3 Using STL (lower_bound + upper_bound)
// =================================================================
//
// Ceil  = *lower_bound(arr.begin(), arr.end(), x)
// Floor = element just before lower_bound(x) if exists.
//
// TC : O(log n)
// SC : O(1)
// =================================================================
pair<int,int> floorCeilSTL(vector<int>& arr, int x){
    int n = arr.size();

    auto it = lower_bound(arr.begin(), arr.end(), x);

    int ceilVal = (it == arr.end() ? -1 : *it);

    int floorVal;
    if(it == arr.begin())
        floorVal = (*it == x ? x : -1);
    else {
        if(it != arr.end() && *it == x) floorVal = x;
        else floorVal = *(it - 1);
    }

    return {floorVal, ceilVal};
}


// =================================================================
// MAIN TESTING
// =================================================================
int main(){
    vector<int> arr = {2, 4, 7, 10, 15};
    int x = 9;

    auto brute  = floorCeilBrute(arr, x);
    auto binary = floorCeilBinary(arr, x);
    auto stl    = floorCeilSTL(arr, x);

    cout << "Brute  Floor = " << brute.first  << ", Ceil = " << brute.second  << endl;
    cout << "Binary Floor = " << binary.first << ", Ceil = " << binary.second << endl;
    cout << "STL    Floor = " << stl.first    << ", Ceil = " << stl.second    << endl;

    return 0;
}


/*
=====================================================================
DRY RUN (Binary Search Example)
=====================================================================
arr = [2, 4, 7, 10, 15], x = 9

FLOOR:
low=0, high=4
mid=2 → arr[2]=7 <= 9 → floor=7, low=3
mid=3 → arr[3]=10 > 9 → high=2
floor result = 7

CEIL:
low=0, high=4
mid=2 → arr[2]=7 < 9 → low=3
mid=3 → arr[3]=10 >= 9 → ceil=10, high=2
ceil result = 10
=====================================================================

=====================================================================
EDGE CASES TESTING
=====================================================================
Case 1: arr=[2,5,9], x=1   → floor=-1, ceil=2
Case 2: arr=[2,5,9], x=2   → floor=2, ceil=2
Case 3: arr=[2,5,9], x=8   → floor=5, ceil=9
Case 4: arr=[2,5,9], x=20  → floor=9, ceil=-1
Case 5: duplicates arr=[2,4,4,4,9], x=4 → floor=4, ceil=4
Case 6: negatives arr=[-8,-3,0,3], x=-5 → floor=-8, ceil=-3
=====================================================================

=====================================================================
FOLLOW-UP INTERVIEW QUESTIONS
=====================================================================
1. Relationship of floor & ceil with lower_bound / upper_bound?
2. Can this be applied on descending sorted arrays?
3. How to compute floor/ceil for floating precision values?
4. How to find floor/ceil in rotated sorted arrays?
5. Can floor and ceil be used in range searching?
6. What if array is not sorted? Any approach?
7. How to use this in real problems like room booking or scheduling?
=====================================================================

=====================================================================
FOLLOW-UP INTERVIEW ANSWERS
=====================================================================

1. Relationship of floor & ceil with lower_bound / upper_bound?
Floor = element just before lower_bound(x), unless exact match.
Ceil  = lower_bound(x).

2. Can this be applied on descending sorted arrays?
Yes, but comparisons must reverse:
arr[mid] >= x → floor
arr[mid] <= x → ceil

3. How to compute floor/ceil for floating precision values?
Use binary search with precision control (epsilon). Very useful in
square root, cube root, trigonometric monotonic functions.

4. How to find floor/ceil in rotated sorted arrays?
First find pivot (rotation index), then apply binary search on
appropriate segment.

5. Can floor and ceil be used in range searching?
Yes, often used to find valid element ranges, bookings, timestamps.

6. What if array is not sorted? Any approach?
Then binary search cannot be used. Need linear scan or sort first
(O(n log n)) before applying logic.

7. How to use this in real problems like room booking or scheduling?
Finding nearest available start time, next meeting slot, etc. Ceil gives
next available time, floor gives last finished event.
=====================================================================
*/
