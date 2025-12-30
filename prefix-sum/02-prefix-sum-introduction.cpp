#include <bits/stdc++.h>
using namespace std;

/*
    Function: prefSum
    Purpose:
    --------
    Given an input array, this function builds and returns
    a prefix sum array.

    Prefix Sum Definition:
    ----------------------
    prefixSum[i] = sum of elements from index 0 to index i
                 = arr[0] + arr[1] + ... + arr[i]

    Why Prefix Sum?
    ---------------
    - Helps answer range sum queries in O(1) time
    - Preprocessing takes O(n)
*/
vector<int> prefSum(vector<int> &arr)
{
    // Number of elements in input array
    int n = arr.size();

    /*
        prefixSum array will store cumulative sums.
        Size is same as input array.
    */
    vector<int> prefixSum(n);

    /*
        Base case:
        prefixSum[0] stores sum till index 0,
        which is just the first element itself.
    */
    prefixSum[0] = arr[0];

    /*
        Build prefix sum array:
        At each index i,
        prefixSum[i] = sum till previous index + current element
                     = prefixSum[i-1] + arr[i]
    */
    for (int i = 1; i < n; i++)
    {
        prefixSum[i] = prefixSum[i - 1] + arr[i];
    }

    // Return the fully built prefix sum array
    return prefixSum;
}

int main()
{
    // Input array
    vector<int> arr = {10, 20, 10, 5, 15};

    // Generate prefix sum array
    vector<int> prefixSum = prefSum(arr);

    // Print prefix sum array
    for (auto value : prefixSum)
    {
        cout << value << " ";
    }

    return 0;
}

/*
    Time Complexity:
    ----------------
    O(n) → single loop over the array

    Space Complexity:
    -----------------
    O(n) → extra prefixSum array
*/
