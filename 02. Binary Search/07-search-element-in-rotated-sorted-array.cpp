#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Search for target in a rotated sorted array.
Return index if found, else return -1.
Assume NO duplicates.
*/

/* ------------------------------------------------------------ */
// ⭐ Approach 1: Brute Force
// Time: O(n)
// Space: O(1)
int searchBrute(vector<int> &nums, int target)
{
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] == target)
            return i;
    }
    return -1;
}

/* ------------------------------------------------------------ */
// ⭐ Approach 2: Optimal Binary Search
// Time: O(log n)
// Space: O(1)

/*
Idea:
At least one half (left or right) is always sorted.
- Identify sorted half
- Check if target lies in that half
- Eliminate the other half
*/
int searchBinary(vector<int> &nums, int target)
{
    int low = 0, high = nums.size() - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        // Case 1: Found
        if (nums[mid] == target)
            return mid;

        // Case 2: Left half is sorted
        if (nums[low] <= nums[mid])
        {
            // Target lies in left half
            if (nums[low] <= target && target < nums[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
        // Case 3: Right half is sorted
        else
        {
            // Target lies in right half
            if (nums[mid] < target && target <= nums[high])
                low = mid + 1;
            else
                high = mid - 1;
        }
    }

    return -1;
}

/* ------------------------------------------------------------ */
// ⭐ Approach 3: STL (not optimal but simple)
// Time: O(n)
int searchSTL(vector<int> &nums, int target)
{
    auto it = find(nums.begin(), nums.end(), target);

    if (it == nums.end())
        return -1;

    return it - nums.begin();
}

/* ------------------------------------------------------------ */
int main()
{
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    int target = 0;

    cout << "Array: ";
    for (int x : nums)
        cout << x << " ";
    cout << endl;

    cout << "Target: " << target << endl;

    cout << "Index (Brute): "
         << searchBrute(nums, target) << endl;

    cout << "Index (Binary Search): "
         << searchBinary(nums, target) << endl;

    cout << "Index (STL): "
         << searchSTL(nums, target) << endl;

    return 0;
}
