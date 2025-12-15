#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Find the LAST occurrence of a target element in a SORTED array.
If not present, return -1.
*/

/* ------------------------------------------------------------ */
// ⭐ Approach 1: Brute Force
// Time Complexity: O(n)
// Space Complexity: O(1)
/*
Idea:
Scan the array from the right side.
The first match we find is the LAST occurrence.
*/
int lastOccurrenceBrute(vector<int> &arr, int target)
{
    int n = arr.size();

    // Start scanning from the last index
    for (int i = n - 1; i >= 0; i--)
    {
        if (arr[i] == target)
            return i;
    }

    // Target not found
    return -1;
}

/* ------------------------------------------------------------ */
// ⭐ Approach 2: Binary Search (Optimal)
// Time Complexity: O(log n)
// Space Complexity: O(1)
/*
Why Binary Search works here:
- Array is sorted
- Even if we find target at mid, we don't stop
- We move RIGHT to check if target appears later
*/
int lastOccurrenceBinary(vector<int> &arr, int target)
{
    int low = 0, high = arr.size() - 1;
    int ans = -1; // stores last found index

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target)
        {
            ans = mid;     // possible answer
            low = mid + 1; // move right to find later occurrence
        }
        else if (arr[mid] > target)
        {
            high = mid - 1; // move left
        }
        else
        {
            low = mid + 1; // move right
        }
    }

    return ans;
}

/* ------------------------------------------------------------ */
// ⭐ Approach 3:
// Using STL (upper_bound)
// upper_bound returns first index > target
// so last occurrence = index - 1
// Time Complexity: O(log n)
int lastOccurrenceSTL(vector<int> &arr, int target)
{
    int idx = upper_bound(arr.begin(), arr.end(), target) - arr.begin();

    // Check boundary and value
    if (idx > 0 && arr[idx - 1] == target)
        return idx - 1;

    return -1;
}

/* ------------------------------------------------------------ */
int main()
{
    vector<int> arr = {1, 2, 2, 2, 3, 4, 5};
    int target = 2;

    cout << "Array: ";
    for (int x : arr)
        cout << x << " ";
    cout << endl;

    cout << "Target: " << target << endl;

    cout << "Last Occurrence (Brute): "
         << lastOccurrenceBrute(arr, target) << endl;

    cout << "Last Occurrence (Binary Search): "
         << lastOccurrenceBinary(arr, target) << endl;

    cout << "Last Occurrence (STL): "
         << lastOccurrenceSTL(arr, target) << endl;

    return 0;
}
