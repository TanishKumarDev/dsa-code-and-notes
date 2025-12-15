#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Find the minimum element in a rotated sorted array.
Assume NO duplicates.
*/

/* ------------------------------------------------------------ */
// ⭐ Approach 1: Brute Force
// Time: O(n)
// Space: O(1)
int findMinBrute(vector<int> &nums)
{
    int minVal = INT_MAX;

    for (int i = 0; i < nums.size(); i++)
    {
        minVal = min(minVal, nums[i]);
    }

    return minVal;
}

/* ------------------------------------------------------------ */
// ⭐ Approach 2: Binary Search (Optimal)
// Time: O(log n)
// Space: O(1)

/*
Key idea:
- Minimum element is the only element whose previous is greater
- Compare mid with high to decide direction
*/
int findMinBinary(vector<int> &nums)
{
    int low = 0, high = nums.size() - 1;

    while (low < high)
    {
        int mid = low + (high - low) / 2;

        // If mid element is greater than high,
        // minimum lies in right half
        if (nums[mid] > nums[high])
            low = mid + 1;
        else
            // Minimum lies in left half including mid
            high = mid;
    }

    // low == high → pointing to minimum element
    return nums[low];
}

/* ------------------------------------------------------------ */
// ⭐ Approach 3: STL
// Time: O(n)
int findMinSTL(vector<int> &nums)
{
    return *min_element(nums.begin(), nums.end());
}

/* ------------------------------------------------------------ */
int main()
{
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};

    cout << "Array: ";
    for (int x : nums)
        cout << x << " ";
    cout << endl;

    cout << "Minimum (Brute): "
         << findMinBrute(nums) << endl;

    cout << "Minimum (Binary Search): "
         << findMinBinary(nums) << endl;

    cout << "Minimum (STL): "
         << findMinSTL(nums) << endl;

    return 0;
}
