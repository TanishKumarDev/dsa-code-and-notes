#include <bits/stdc++.h>
using namespace std;

/*
Problem:
A peak element is an element that is strictly greater than its neighbors.
Return the index of ANY peak element.

Note:
- nums[-1] and nums[n] are considered -∞
- Multiple peaks may exist
*/

/* ------------------------------------------------------------ */
// ⭐ Better Brute Approach
// Time: O(n)
// Space: O(1)
//
// Intuition:
// A peak element is greater than its immediate neighbors.
// The problem guarantees virtual neighbors as -∞ at both ends.
// So:
// - First element needs to be checked only with its right neighbor
// - Last element needs to be checked only with its left neighbor
// - Middle elements need to be checked with both neighbors
//
// Logic:
// 1. If the array has only one element, it is always a peak.
// 2. Check if the first element is greater than the second.
// 3. Check if the last element is greater than the second last.
// 4. Linearly scan the middle elements and return the index
//    where nums[i] is greater than both neighbors.
//
// Since at least one peak always exists, the loop will return a result.

int findPeakBrute(vector<int> &nums)
{
    int n = nums.size();

    // Single element is always a peak
    if (n == 1)
        return 0;

    // Check first element
    if (nums[0] > nums[1])
        return 0;

    // Check last element
    if (nums[n - 1] > nums[n - 2])
        return n - 1;

    // Check middle elements
    for (int i = 1; i <= n - 2; i++)
    {
        if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1])
            return i;
    }

    return -1; // logically unreachable
}

/* ------------------------------------------------------------ */
// ⭐ Approach 2: Binary Search (Optimal)
// Time: O(log n)
// Space: O(1)
//
// Intuition:
// Think of the array as a mountain range.
// - If nums[mid] > nums[mid+1], we are on a descending slope,
//   so a peak must exist on the LEFT side (including mid).
// - If nums[mid] < nums[mid+1], we are on an ascending slope,
//   so a peak must exist on the RIGHT side.
//
// Logic:
// 1. Use binary search on indices.
// 2. Compare nums[mid] with nums[mid+1].
// 3. If nums[mid] > nums[mid+1], move high = mid.
// 4. Else, move low = mid + 1.
// 5. When low == high, it points to a peak element.
//
// A peak is guaranteed to exist, so the search always converges.
int findPeakBinary(vector<int> &nums)
{
    int low = 0;
    int high = nums.size() - 1;

    while (low < high)
    {
        int mid = low + (high - low) / 2;

        if (nums[mid] > nums[mid + 1])
        {
            // Descending slope → peak is on left
            high = mid;
        }
        else
        {
            // Ascending slope → peak is on right
            low = mid + 1;
        }
    }

    // low == high → peak index
    return low;
}

/* ------------------------------------------------------------ */
// ⭐ Approach 3: STL (for completeness)
// Time: O(n)
int findPeakSTL(vector<int> &nums)
{
    int n = nums.size();

    for (int i = 0; i < n; i++)
    {
        if ((i == 0 || nums[i] > nums[i - 1]) &&
            (i == n - 1 || nums[i] > nums[i + 1]))
            return i;
    }
    return -1;
}

/* ------------------------------------------------------------ */
int main()
{
    vector<int> nums = {1, 2, 1, 3, 5, 6, 4};

    cout << "Array: ";
    for (int x : nums)
        cout << x << " ";
    cout << endl;

    cout << "Peak index (Brute): "
         << findPeakBrute(nums) << endl;

    cout << "Peak index (Binary Search): "
         << findPeakBinary(nums) << endl;

    cout << "Peak index (STL): "
         << findPeakSTL(nums) << endl;

    return 0;
}
