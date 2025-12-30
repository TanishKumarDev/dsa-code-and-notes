#include <bits/stdc++.h>
using namespace std;

// ⭐ Approach 1:
int findEquilibriumBruteForce(vector<int> &arr)
{
    // Check for indexes one by one until
    // an equilibrium index is found
    for (int i = 0; i < arr.size(); ++i)
    {

        // Get left sum
        int leftSum = 0;
        for (int j = 0; j < i; j++)
            leftSum += arr[j];

        // Get right sum
        int rightSum = 0;
        for (int j = i + 1; j < arr.size(); j++)
            rightSum += arr[j];

        // If leftsum and rightsum are same, then
        // index i is an equilibrium index
        if (leftSum == rightSum)
            return i;
    }

    // If equilibrium index doesn't exist
    return -1;
}

// ⭐ Approach 2:
int findEquilibriumBetter(vector<int> &arr)
{
    int n = arr.size();

    vector<int> pref(n, 0);
    vector<int> suff(n, 0);

    // Initialize the ends of prefix and suffix array
    pref[0] = arr[0];
    suff[n - 1] = arr[n - 1];

    // Calculate prefix sum for all indices
    for (int i = 1; i < n; i++)
        pref[i] = pref[i - 1] + arr[i];

    // Calculating suffix sum for all indices
    for (int i = n - 2; i >= 0; i--)
        suff[i] = suff[i + 1] + arr[i];

    // Checking if prefix sum is equal to suffix sum
    for (int i = 0; i < n; i++)
    {
        if (pref[i] == suff[i])
            return i;
    }

    // if equilibrium index doesn't exist
    return -1;
}
// ⭐ Approach 3:
int findEquilibriumOptimal(vector<int> &arr)
{
    int prefSum = 0, total = 0;

    // Calculate the array sum
    for (int ele : arr)
    {
        total += ele;
    }

    // Iterate pivot over all the elements of the array and
    // till left != right
    for (int pivot = 0; pivot < arr.size(); pivot++)
    {
        int suffSum = total - prefSum - arr[pivot];
        if (prefSum == suffSum)
        {
            return pivot;
        }
        prefSum += arr[pivot];
    }

    // there is no equilibrium point
    return -1;
}
int main()
{
    vector<int> arr = {-7, 1, 5, 2, -4, 3, 0};
    cout << findEquilibriumBruteForce(arr) << endl;
    cout << findEquilibriumBetter(arr) << endl;
    cout << findEquilibriumOptimal(arr) << endl;
    return 0;
}