#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Given a sorted array where every element appears twice
except one element which appears exactly once.
Find that single element.

Constraints:
- Array is sorted
- Exactly one single element exists
*/

/* ------------------------------------------------------------ */
// ⭐ Approach 1: Brute Force
// Time: O(n)
// Space: O(1)
int singleNonDuplicateBrute(vector<int> &arr)
{
    int n = arr.size();

    // If only one element exists
    if (n == 1)
        return arr[0];

    for (int i = 0; i < n; i++)
    {
        // First element
        if (i == 0)
        {
            if (arr[i] != arr[i + 1])
                return arr[i];
        }
        // Last element
        else if (i == n - 1)
        {
            if (arr[i] != arr[i - 1])
                return arr[i];
        }
        // Middle elements
        else
        {
            if (arr[i] != arr[i - 1] && arr[i] != arr[i + 1])
                return arr[i];
        }
    }

    return -1; // should never reach here
}

/* ------------------------------------------------------------ */
// ⭐ Approach 2 & 3: Binary Search (Optimal)
// Time: O(log n)
// Space: O(1)

/*
Key observation:
- Before the single element, pairs start at even index
- After the single element, pairs start at odd index
*/
int singleNonDuplicateBinary(vector<int> &arr)
{
    int n = arr.size();

    // Edge cases
    if (n == 1)
        return arr[0];
    if (arr[0] != arr[1])
        return arr[0];
    if (arr[n - 1] != arr[n - 2])
        return arr[n - 1];

    int low = 1, high = n - 2;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        // Check if mid is the single element
        if (arr[mid] != arr[mid - 1] && arr[mid] != arr[mid + 1])
            return arr[mid];

        /*
        If mid is even and equals next
        OR mid is odd and equals previous
        → single element is on right side
        */
        if ((mid % 2 == 0 && arr[mid] == arr[mid + 1]) ||
            (mid % 2 == 1 && arr[mid] == arr[mid - 1]))
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1; // should never reach here
}

/* ------------------------------------------------------------ */
int main()
{
    vector<int> arr = {1, 1, 2, 3, 3, 4, 4, 8, 8};

    cout << "Array: ";
    for (int x : arr)
        cout << x << " ";
    cout << endl;

    cout << "Single element (Brute): "
         << singleNonDuplicateBrute(arr) << endl;

    cout << "Single element (Binary Search): "
         << singleNonDuplicateBinary(arr) << endl;

    return 0;
}
