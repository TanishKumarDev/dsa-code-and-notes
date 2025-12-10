#include <bits/stdc++.h>
using namespace std;

/*
=====================================================================
🧠 Problem : Single Element in a Sorted Array
=====================================================================
You are given a SORTED array where:
Every element appears exactly TWICE, except ONE element which appears
only ONCE. Find and return that SINGLE element.

---------------------------------------------------------------------
Example :
Input  : arr = [1,1,2,3,3,4,4,8,8]
Output : 2

Input  : arr = [3,3,7,7,10,11,11]
Output : 10

---------------------------------------------------------------------
Constraints :
1. Array is sorted in non-decreasing order.
2. Exactly one element occurs once; all others occur twice.
3. Time target: O(log n), Space: O(1) expected.
=====================================================================
*/


// =================================================================
// 🔴 Approach 1 Brute Force (XOR Method)
// =================================================================
//
// Intuition:
// x XOR x = 0, and x XOR 0 = x
// XOR of all elements cancels pairs and leaves the single one.
//
// TC : O(n)
// SC : O(1)
//
// Works even if array is NOT sorted.
// =================================================================
int singleElementXOR(vector<int>& arr){
    int xr = 0;
    for(int num : arr){
        xr ^= num;
    }
    return xr;
}


// =================================================================
// 🔵 Approach 2 Optimal Binary Search (Index Pair Logic)
// =================================================================
//
// Intuition:
// Since elements appear in pairs, indexes follow a pattern:
//
// Pair index pattern (0-based):
// For pair elements: first index is even, second is odd
// Example: [1,1,2,2,3,3,...]
// index:   0 1 2 3 4 5 ...
//
// Before the single element: pattern holds
// After the single element: pattern breaks
//
// Check mid:
// If mid is even:
//     arr[mid] == arr[mid+1] -> single is on RIGHT
//     else                   -> single is on LEFT or at mid
// If mid is odd:
//     arr[mid] == arr[mid-1] -> single is on RIGHT
//     else                   -> single is on LEFT or at mid
//
// TC : O(log n)
// SC : O(1)
// =================================================================
int singleElementBinary(vector<int>& arr){
    int n = arr.size();
    int low = 0, high = n - 2; // stop before last index

    while(low <= high){
        int mid = low + (high - low) / 2;

        bool pairMatched = false;

        if(mid % 2 == 0){
            pairMatched = (arr[mid] == arr[mid + 1]);
        } else {
            pairMatched = (arr[mid] == arr[mid - 1]);
        }

        if(pairMatched){
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
    }

    return arr[low]; // low will point to single element
}


// =================================================================
// MAIN TESTING
// =================================================================
int main(){
    vector<int> arr = {1,1,2,3,3,4,4,8,8};

    cout << "XOR Method Result     : " << singleElementXOR(arr) << endl;
    cout << "Binary Search Result  : " << singleElementBinary(arr) << endl;

    return 0;
}


/*
=====================================================================
DRY RUN (Binary Search)
=====================================================================
arr = [1,1,2,3,3,4,4,8,8]
idx =  0 1 2 3 4 5 6 7 8

low=0, high=7
mid=3 → odd → arr[3] == arr[2]? (3 == 2? false)
=> single lies LEFT → high = 2

low=0, high=2
mid=1 → odd → arr[1] == arr[0]? (1 == 1? true)
=> go RIGHT → low = 2

low=2, high=2
mid=2 → even → arr[2] == arr[3]? (2 == 3? false)
=> go LEFT → high = 1

Loop ends, low = 2 → arr[2] = 2
=====================================================================

=====================================================================
EDGE CASES
=====================================================================
Case 1: smallest element single
arr=[2,3,3,4,4] → ans=2

Case 2: last element single
arr=[1,1,2,2,7] → ans=7

Case 3: only one element
arr=[10] → ans=10

Case 4: negative numbers
arr=[-5,-5,-2,-2,9] → ans=9

Case 5: large size works efficiently (log n)
=====================================================================

=====================================================================
FOLLOW-UP INTERVIEW QUESTIONS
=====================================================================
1. Why does binary search stop at n-2?
2. Why do we check parity (even/odd) of mid index?
3. Can we solve this on an unsorted array?
4. Can the XOR approach fail in any scenario?
5. Can this be extended if every element appears K times except one?
6. What if exactly two single values exist?
7. Can this be solved in a streaming data environment?
=====================================================================

=====================================================================
FOLLOW-UP INTERVIEW ANSWERS
=====================================================================

1. Why does binary search stop at n-2?
Because we check arr[mid] with its next/previous pair element, so mid+1
must be valid. Final result will be at index low.

2. Why check parity (even/odd) of mid?
Before the single element: pair starts at even index.
After the single element: pattern breaks and pairs shift.

3. Can we solve this on an unsorted array?
Binary search method cannot. XOR method works in unsorted array.

4. Can XOR approach fail?
Yes, if constraint breaks (not exactly two occurrences for others).
Binary approach assumes sorted + exact pair structure.

5. What if every element appears K times except one?
General solution uses bitwise counting per bit position.

6. What if two single values exist?
Both approaches fail. Need XOR grouping or hashing.

7. Can this be done for streaming data?
Yes, XOR approach is perfect for streaming continuous numbers.
=====================================================================
*/
