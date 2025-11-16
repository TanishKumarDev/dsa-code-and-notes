#include <bits/stdc++.h>
using namespace std;

/*
🧠 Problem : Sort an array consisting only of 0s, 1s, and 2s.
Example :
Input  : [2, 0, 2, 1, 1, 0]
Output : [0, 0, 1, 1, 2, 2]

Constraints :
1. Only elements allowed are 0, 1, and 2
2. Expected solution better than O(n log n)
3. Array size can be large, so O(n) preferred

Goal:
We must sort the array in-place without using extra space if possible.
*/



// 🔴 Approach 1 Brute Force (Using sort())==
// Intuition :
// Since values are only 0,1,2, direct sorting will automatically
// place them in correct order.
//
// Algo :
// 1. Use built-in sort(arr.begin(), arr.end())
//
// TC : O(n log n) due to sorting
// SC : O(1) in-place
//
// Edge cases :
// 1. Already sorted array works fine
// 2. All elements same works fine
// 3. Slow for very large n compared to O(n) solutions

void brute(vector<int>& arr) {
    sort(arr.begin(), arr.end());
}



// 🔵 Approach 2 Better (Counting / Frequency Sort)==
// Intuition :
// Count how many 0s, 1s, and 2s exist. Then rewrite the array.
// This avoids sorting overhead because values are fixed range.
//
// Algo :
// 1. cnt0, cnt1, cnt2 = 0
// 2. Count occurrences of 0, 1, 2
// 3. Rewrite the array based on the counts
//
// TC : O(n) + O(n) = O(n)
// SC : O(1)
//
// Edge cases :
// 1. Array may contain only one type (all 0s or all 1s or all 2s)
// 2. Works for n = 1 also
// 3. Already sorted or reversed both handled

void countSort(vector<int>& arr) {
    int cnt0 = 0, cnt1 = 0, cnt2 = 0;

    for(int num : arr) {
        if(num == 0) cnt0++;
        else if(num == 1) cnt1++;
        else cnt2++;
    }

    int i = 0;
    while(cnt0--) arr[i++] = 0;
    while(cnt1--) arr[i++] = 1;
    while(cnt2--) arr[i++] = 2;
}



// 🟢 Approach 3 Optimal (Dutch National Flag Algorithm)==
// Intuition :
// Maintain 3 sections in array.
// arr[0..low-1]     => 0s region
// arr[low..mid-1]   => 1s region
// arr[mid..high]    => unknown region
// arr[high+1..end]  => 2s region
//
// If arr[mid] == 0 : swap arr[low] & arr[mid], low++, mid++
// If arr[mid] == 1 : mid++
// If arr[mid] == 2 : swap arr[mid] & arr[high], high--
//
// Algo :
// 1. low=0, mid=0, high=n-1
// 2. While mid <= high:
//       if arr[mid] == 0 -> swap, low++, mid++
//       else if arr[mid] == 1 -> mid++
//       else -> swap, high--
//
// TC : O(n) single traversal
// SC : O(1)
//
// Edge cases :
// 1. All 0s or all 1s or all 2s
// 2. Single element array
// 3. Does not require sorting or extra array

void dutchFlag(vector<int>& arr) {
    int low = 0, mid = 0, high = arr.size() - 1;

    while (mid <= high) {
        if (arr[mid] == 0) {
            swap(arr[low++], arr[mid++]);
        }
        else if (arr[mid] == 1) {
            mid++;
        }
        else { // arr[mid] == 2
            swap(arr[mid], arr[high--]);
        }
    }
}

int main() {

    vector<int> arr = {2, 0, 2, 1, 1, 0};

    // Brute
    vector<int> a1 = arr;
    brute(a1);
    cout << "Brute Sorted     : ";
    for(int x : a1) cout << x << " ";
    cout << endl;

    // Count Sort
    vector<int> a2 = arr;
    countSort(a2);
    cout << "Counting Sorted  : ";
    for(int x : a2) cout << x << " ";
    cout << endl;

    // Dutch National Flag
    vector<int> a3 = arr;
    dutchFlag(a3);
    cout << "Dutch Flag Sorted: ";
    for(int x : a3) cout << x << " ";
    cout << endl;

    return 0;
}
/*
DRY RUNS FOR SORT 0s,1s,2s (All Approaches)

-------------------------------------------------------------
Example 1: Normal Case
Input  : [2, 0, 2, 1, 1, 0]
Output : [0, 0, 1, 1, 2, 2]

Brute:
sort() -> [0, 0, 1, 1, 2, 2]

Counting:
Count = 0s=2, 1s=2, 2s=2
Rewrite -> [0, 0, 1, 1, 2, 2]

Dutch Flag:
Initial: low=0, mid=0, high=5
arr = [2,0,2,1,1,0]

mid=0 → 2 → swap(mid,high) → [0,0,2,1,1,2], high=4
mid=0 → 0 → swap(low,mid) → [0,0,2,1,1,2], low=1, mid=1
mid=1 → 0 → swap(low,mid) → [0,0,2,1,1,2], low=2, mid=2
mid=2 → 2 → swap(mid,high) → [0,0,1,1,2,2], high=3
mid=2 → 1 → mid++
mid=3 → 1 → mid++
mid > high stop
Output → [0,0,1,1,2,2]

-------------------------------------------------------------
Example 2: Already Sorted
Input  : [0, 0, 1, 1, 2, 2]
Output : [0, 0, 1, 1, 2, 2]

Brute:
sort() -> same

Counting:
Count = 0s=2, 1s=2, 2s=2
Rewrite -> same

Dutch Flag:
low=0, mid=0, high=5
Walk through mid, all conditions already in place
No swaps needed
Output same

-------------------------------------------------------------
Example 3: Reverse Sorted
Input  : [2, 2, 1, 1, 0, 0]
Output : [0, 0, 1, 1, 2, 2]

Brute:
sort() -> [0, 0, 1, 1, 2, 2]

Counting:
Count = 0s=2, 1s=2, 2s=2
Rewrite

Dutch Flag:
mid=0: 2 → swap(mid,high) → [0,2,1,1,0,2], high--
mid=0: 0 → swap(low,mid) → [0,2,1,1,0,2], low=1 mid=1
mid=1: 2 → swap(mid,high) → [0,0,1,1,2,2], high--
mid=1: 0 → swap(low,mid) → [0,0,1,1,2,2], low=2 mid=2
mid=2,3 both 1 → mid moves
Done

-------------------------------------------------------------
Example 4: All Same
Input  : [1,1,1,1]
Output : [1,1,1,1]

Brute:
sort same

Counting:
Count = 0s=0, 1s=4, 2s=0 → rewrite

Dutch Flag:
mid loops through, only 1s → mid increments only → same result

-------------------------------------------------------------
Example 5: Single Element
Input  : [2]
Output : [2]

Brute:
sort same

Counting:
Count2 = 1 → rewrite same

Dutch Flag:
mid <= high? yes
arr[mid] == 2 → swap(mid,high) but same element
Done

-------------------------------------------------------------
Example 6: Mixed with imbalance
Input  : [0,2,2,2,1]
Output : [0,1,2,2,2]

Brute:
sort -> [0,1,2,2,2]

Counting:
Count0=1, Count1=1, Count2=3 → rewrite

Dutch Flag:
low=0, mid=0, high=4
mid=0: 0 → swap(low,mid), low=1 mid=1
mid=1: 2 → swap(mid,high) → new arrangement, high--
continue until sorted
*/
