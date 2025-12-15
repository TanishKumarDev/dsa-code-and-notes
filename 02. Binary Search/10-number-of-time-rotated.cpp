#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Find how many times a sorted array has been rotated.
Key fact:
Rotation count = index of the minimum element.
Assume NO duplicates.
*/

/* ------------------------------------------------------------ */
// ⭐ Approach 1: Brute Force (find min index)
// Time: O(n)
// Space: O(1)
// Scan the whole array and find the minimum element.

// Why brute?
// Checks every element
// Does no optimization
// Works for all cases

// When to use:
// Small input
// Just need correctness
// First approach in interviews

int findRotationsBrute(vector<int> &arr)
{
    int n = arr.size();

    int minVal = arr[0];
    int minIndex = 0;

    // Find index of minimum element
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < minVal)
        {
            minVal = arr[i];
            minIndex = i;
        }
    }

    // Index of minimum = rotation count
    return minIndex;
}

/* ------------------------------------------------------------ */
// ⭐ Approach 2: Linear scan (break point)
// Time: O(n)
// Space: O(1)
// Find the point where sorted order breaks.

// Why better than brute?
// May stop early
// Does less work on average
// Still linear time

// When to use:
// Array is rotated
// Want cleaner logic than brute
// Before jumping to binary search

int findRotationCountLinear(vector<int> &arr)
{
    int n = arr.size();

    // Rotation happens where order breaks
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            // Next index is the minimum element
            return i + 1;
        }
    }

    // Array is not rotated
    return 0;
}

/* ------------------------------------------------------------ */
// ⭐ Approach 3: Binary Search (Optimal)
// Time: O(log n)
// Space: O(1)
int findRotationsBinary(vector<int> &arr)
{
    int low = 0;
    int high = arr.size() - 1;

    while (low < high)
    {
        int mid = low + (high - low) / 2;

        // Minimum lies in right half
        if (arr[mid] > arr[high])
            low = mid + 1;
        else
            // Minimum lies in left half including mid
            high = mid;
    }

    // low points to minimum element
    return low;
}

/* ------------------------------------------------------------ */
int main()
{
    vector<int> arr = {4, 5, 6, 7, 0, 1, 2};

    cout << "Array: ";
    for (int x : arr)
        cout << x << " ";
    cout << endl;

    cout << "Rotation count (Brute): "
         << findRotationsBrute(arr) << endl;

    cout << "Rotation count (Linear): "
         << findRotationCountLinear(arr) << endl;

    cout << "Rotation count (Binary Search): "
         << findRotationsBinary(arr) << endl;

    return 0;
}
