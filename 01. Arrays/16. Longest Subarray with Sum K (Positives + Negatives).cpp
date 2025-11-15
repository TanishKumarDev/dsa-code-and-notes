#include <bits/stdc++.h>
using namespace std;

// 🧠 Problem : 
// Example : 
// Constraint : 

// 🔴 Approach 1 Brute Force : 

// Intuition:
// Har possible subarray ko check karo.
// i = start index, j = end index, aur ek third loop sum calculate karne ke liye.
// Jahan sum == k mile, wahan maxLen update.

// Algo:
// 1. i = 0..n-1
// 2. j = i..n-1
// 3. Har (i..j) ke liye sum calculate karo
// 4. If sum == k, length update karo
// 5. maxLen return

// TC: O(n^3)
// SC: O(1)

// Edge cases:
// 1. k = 0
// 2. No subarray sums to k
// 3. All elements zero

int brute(vector<int>& arr, int k) {
    int n = arr.size(), maxLen = 0;

    for (int i = 0; i < n; i++) {

        for (int j = i; j < n; j++) {

            int sum = 0;

            // Calculate sum of arr[i..j]
            for (int l = i; l <= j; l++)
                sum += arr[l];

            // Check if equals k
            if (sum == k)
                maxLen = max(maxLen, j - i + 1);
        }
    }
    return maxLen;
}

// 🔵 Approach 2 Better :  Two Loops

// Intuition:
// Third loop ki zaroorat nahi. Sum ko j loop me hi accumulate karte jao.
// Har bar sum += arr[j]
// Agar sum == k ho jaye -> maxLen update.

// Algo:
// 1. Loop i = 0..n-1
//      sum = 0
//      Loop j = i..n-1
//          sum += arr[j]
//          If sum == k -> update maxLen

// TC: O(n^2)
// SC: O(1)

// Edge cases:
// 1. Negative values allowed
// 2. k = 0
// 3. Whole array sum == k

int better(vector<int>& arr, int k) {
    int n = arr.size(), maxLen = 0;

    for (int i = 0; i < n; i++) {

        int sum = 0;   // fresh sum for new start index

        for (int j = i; j < n; j++) {

            sum += arr[j];

            if (sum == k)
                maxLen = max(maxLen, j - i + 1);
        }
    }

    return maxLen;
}

// 🟢 Approach 3 Optimal: Prefix Sum + Hash Map (Optimal)
// Intuition:
// Prefix sum concept:
// prefix[i] = arr[0] + arr[1] + ... + arr[i]
// Agar kisi index i par:
//    prefix[i] == k -> subarray length = i+1
//
// Agar prefix[i] - k = previous_prefix j par mil jaye,
//    matlab arr[j+1 .. i] ka sum k ke barabar hai.
//
// Hash map me har prefix sum ka earliest index store karte hain.
// Jisse max possible length mil sake.

// Algo:
// 1. sum = 0
// 2. Har index i par:
//        sum += arr[i]
//        Case 1: sum == k -> update maxLen
//        Case 2: sum-k map me ho -> update maxLen
//        Map me sum insert karo only if not exists (earliest index needed)
// 3. maxLen return

// TC: O(n)
// SC: O(n)

// Edge cases:
// 1. Negative values allowed
// 2. Longest subarray may start from index 0
// 3. k = 0 handled automatically

int getLongestSubarray(vector<int>& arr, int k) {

    int n = arr.size();
    unordered_map<int, int> prefixMap;  // prefixSum -> earliest index
    int sum = 0, maxLen = 0;

    for (int i = 0; i < n; i++) {

        sum += arr[i];

        // Case 1: prefix itself equals k
        if (sum == k)
            maxLen = max(maxLen, i + 1);

        // Case 2: check if (sum - k) seen before
        int rem = sum - k;
        if (prefixMap.count(rem))
            maxLen = max(maxLen, i - prefixMap[rem]);

        // Insert prefix sum if first time seen
        if (prefixMap.find(sum) == prefixMap.end())
            prefixMap[sum] = i;
    }

    return maxLen;
}

int main()
{
    // Example array (can contain positive + negative values)
    vector<int> arr = {1, 2, -1, 2, 3, -2, 4};
    int k = 4;

    // ---------------------------------------------
    // Approach 1 : Brute Force (O(n^3))
    // ---------------------------------------------
    int ans1 = brute(arr, k);
    cout << "Longest Subarray Length using Brute Force: " << ans1 << endl;

    // ---------------------------------------------
    // Approach 2 : Better (O(n^2))
    // ---------------------------------------------
    int ans2 = better(arr, k);
    cout << "Longest Subarray Length using Better: " << ans2 << endl;

    // ---------------------------------------------
    // Approach 3 : Optimal Prefix Sum + Hash Map (O(n))
    // ---------------------------------------------
    int ans3 = getLongestSubarray(arr, k);
    cout << "Longest Subarray Length using Optimal Prefix Sum: " << ans3 << endl;

    return 0;
}
