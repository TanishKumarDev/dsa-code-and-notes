#include <bits/stdc++.h>
using namespace std;

// 🧠 Problem :
// Example :
// Constraint :

// 🔴 Approach 1 Brute Force :
// Intuition :
// Algo :
// TC :
// SC :
// Edge cases :
class Solution
{
public:
    pair<int, int> sortApproach(vector<int> &arr)
    {

        // If array has fewer than 2 elements → second smallest/largest don't exist
        if (arr.size() < 2)
            return {-1, -1};

        // Sort the array in ascending order
        // After sorting: [smallest, 2nd_smallest, ..., 2nd_largest, largest]
        sort(arr.begin(), arr.end());

        // Using arr[1] and arr[n-2] works ONLY if
        // all elements are distinct.
        //
        // Example:
        // arr = [1, 1, 1, 2]
        // Sorted = [1, 1, 1, 2]
        // arr[1] = 1  → this is NOT second smallest (correct is 2)
        // arr[n-2] = 1 → this is NOT second largest (no valid 2nd largest)
        //
        // Meaning:
        // This approach breaks when duplicates exist.

        int secondSmallest = arr[1];
        int secondLargest = arr[arr.size() - 2];

        return {secondSmallest, secondLargest};
    }
};
// 🔵 Approach 2 Better :
// Intuition :
// Algo :
// TC :
// SC :
// Edge cases :
pair<int, int> twoPass(vector<int> &arr)
{

    int n = arr.size();

    // If array has less than 2 elements, second smallest and second largest don't exist
    if (n < 2)
        return {-1, -1};

    // ------------------------------------------------------------
    // Pass 1: Find the smallest and the largest element in the array
    // ------------------------------------------------------------

    int small = INT_MAX; // will store smallest element
    int large = INT_MIN; // will store largest element

    for (int x : arr)
    {

        // Update the smallest element
        small = min(x, small);

        // Update the largest element
        large = max(x, large);
    }

    // ------------------------------------------------------------
    // Pass 2: Find second smallest and second largest
    // (We skip elements that are equal to smallest/largest)
    // ------------------------------------------------------------

    int secSmall = INT_MAX; // second smallest candidate
    int secLarge = INT_MIN; // second largest candidate

    for (int x : arr)
    {

        // For second smallest:
        // It should be greater than 'small' but smallest among others
        if (x > small)
        {
            secSmall = min(x, secSmall);
        }

        // For second largest:
        // It should be smaller than 'large' but largest among others
        if (x < large)
        {
            secLarge = max(x, secLarge);
        }
    }

    // ------------------------------------------------------------
    // Handle cases where second smallest or second largest
    // did not get updated (e.g., all values equal)
    // ------------------------------------------------------------

    if (secSmall == INT_MAX)
        secSmall = -1;
    if (secLarge == INT_MIN)
        secLarge = -1;

    // Return pair: {second smallest, second largest}
    return {secSmall, secLarge};
}
// 🟢 Approach 3 Optimal:
// Intuition :
// Algo :
// TC :
// SC :
// Edge cases :
pair<int, int> optimal(vector<int> &arr)
{

    int n = arr.size();

    // If array has fewer than 2 elements, second smallest/largest can't exist
    if (n < 2)
        return {-1, -1};

    // 'small'  = smallest element
    // 'second_small' = second smallest element
    int small = INT_MAX, second_small = INT_MAX;

    // 'large'  = largest element
    // 'second_large' = second largest element
    int large = INT_MIN, second_large = INT_MIN;

    // Traverse the array only once → O(N)
    for (int x : arr)
    {

        // -----------------------------------
        // Handle Smallest + Second Smallest
        // -----------------------------------

        // Case 1: Found new smallest
        // Move old smallest to second_small
        if (x < small)
        {
            second_small = small;
            small = x;
        }
        // Case 2: x is between small and second_small
        // It must be greater than 'small' but smaller than existing second_small
        else if (x < second_small && x != small)
        {
            second_small = x;
        }

        // -----------------------------------
        // Handle Largest + Second Largest
        // -----------------------------------

        // Case 1: Found new largest
        // Move old largest to second_large
        if (x > large)
        {
            second_large = large;
            large = x;
        }
        // Case 2: x is between large and second_large
        // It must be smaller than 'large' but greater than existing second_large
        else if (x > second_large && x != large)
        {
            second_large = x;
        }
    }

    // If second smallest never got updated → return -1
    if (second_small == INT_MAX)
        second_small = -1;

    // If second largest never got updated → return -1
    if (second_large == INT_MIN)
        second_large = -1;

    // Return pair {second smallest, second largest}
    return {second_small, second_large};
}

int main()
{
    Solution s;

    vector<int> arr = {-2, -1, 1, 2, 3, 4, 5, 6, 8, 9};

    // Brute approach result
    auto p1 = s.sortApproach(arr);
    cout << p1.first << " " << p1.second << endl;

    // Better approach result
    auto p2 = twoPass(arr);
    cout << p2.first << " " << p2.second << endl;

    // Optimal approach result
    auto p3 = optimal(arr);
    cout << p3.first << " " << p3.second << endl;

    return 0;
}