#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Search target k in a rotated sorted array that may contain duplicates.
Return true if found, else false.
*/

/* ------------------------------------------------------------ */
// ⭐ Approach 1: Brute Force
// Time: O(n)
// Space: O(1)
bool searchBrute(vector<int> &arr, int k)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] == k)
            return true;
    }
    return false;
}

/* ------------------------------------------------------------ */
// ⭐ Approach 2: Binary Search with Duplicates
// Time: O(log n) average, O(n) worst case
// Space: O(1)

/*
Key idea:
- One half is usually sorted
- BUT duplicates can break the sorted check
- When arr[low] == arr[mid] == arr[high],
  we cannot decide → shrink boundaries
*/
bool searchBinary(vector<int> &arr, int k)
{
    int low = 0, high = arr.size() - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        // Case 1: found target
        if (arr[mid] == k)
            return true;

        // Case 2: duplicates on both ends → cannot decide
        if (arr[low] == arr[mid] && arr[mid] == arr[high])
        {
            low++;
            high--;
            continue;
        }

        // Case 3: left half is sorted
        if (arr[low] <= arr[mid])
        {
            // Target lies in left half
            if (arr[low] <= k && k < arr[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
        // Case 4: right half is sorted
        else
        {
            // Target lies in right half
            if (arr[mid] < k && k <= arr[high])
                low = mid + 1;
            else
                high = mid - 1;
        }
    }

    return false;
}

/* ------------------------------------------------------------ */
// ⭐ Approach 3: STL
// Time: O(n)
bool searchSTL(vector<int> &arr, int k)
{
    return find(arr.begin(), arr.end(), k) != arr.end();
}

/* ------------------------------------------------------------ */
int main()
{
    vector<int> arr = {2, 5, 6, 0, 0, 1, 2};
    int k = 0;

    cout << "Array: ";
    for (int x : arr)
        cout << x << " ";
    cout << endl;

    cout << "Target: " << k << endl;

    cout << "Found (Brute): "
         << searchBrute(arr, k) << endl;

    cout << "Found (Binary Search): "
         << searchBinary(arr, k) << endl;

    cout << "Found (STL): "
         << searchSTL(arr, k) << endl;

    return 0;
}
