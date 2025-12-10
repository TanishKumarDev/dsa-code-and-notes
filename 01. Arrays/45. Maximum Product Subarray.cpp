#include <bits/stdc++.h>
using namespace std;

/*
🧠 Problem:
Given an integer array nums[], find the maximum product of a contiguous subarray.

Example:
Input  : [2,3,-2,4]
Output : 6   (subarray: [2,3])

Input  : [-2,0,-1]
Output : 0   (subarray: [0])

Constraints:
1 <= n <= 10^5
-10^9 <= nums[i] <= 10^9
*/


// ============================================================================
// 🔴 Approach 1: Brute Force (O(N²))
// ----------------------------------------------------------------------------
// Intuition:
// Check product of every possible subarray. Maintain maximum product found.
//
// Very slow for large arrays but easiest to understand.
//
// Algo:
// ans = nums[0]
// for i from 0 to n-1:
//    prod = 1
//    for j from i to n-1:
//         prod *= nums[j]
//         ans = max(ans, prod)
// return ans
//
// TC: O(N^2)
// SC: O(1)
// ============================================================================
int brute(vector<int>& nums) {
    int ans = nums[0];  // stores maximum product seen so far

    for (int i = 0; i < nums.size(); i++) {

        long long prod = 1;  // product starting from index i

        for (int j = i; j < nums.size(); j++) {
            prod *= nums[j];         // multiplying current element
            ans = max(ans, (int)prod); // update global maximum
        }
    }
    return ans;
}


// ============================================================================
// 🔵 Approach 2: Better (Kadane Variation for Products)
// ----------------------------------------------------------------------------
// Intuition:
// Unlike sum, product changes sign when multiplying by negatives.
// A very negative product can become very positive when multiplied by another negative.
//
// Therefore track:
// maxProd = maximum product ending at current index
// minProd = minimum product ending at current index
//
// If nums[i] is negative, swapping maxProd & minProd helps because
// a small negative multiplied by negative could become maximum.
//
// Algo:
// maxProd = nums[0], minProd = nums[0], result = nums[0]
// Iterate from i=1 to n-1:
//    If nums[i] < 0: swap(maxProd, minProd)
//    maxProd = max(nums[i], maxProd*nums[i])
//    minProd = min(nums[i], minProd*nums[i])
//    result = max(result, maxProd)
//
// TC: O(N)
// SC: O(1)
// ============================================================================
class SolutionDP {
public:
    int maxProduct(vector<int>& nums) {
        int res = nums[0];     // final answer (max product)
        int maxProd = nums[0]; // max product ending at current index
        int minProd = nums[0]; // min product ending at current index

        for (int i = 1; i < nums.size(); i++) {

            // If current number is negative, product sign flips
            if (nums[i] < 0)
                swap(maxProd, minProd); // swap roles

            // Either start new subarray from nums[i]
            // or continue previous by multiplying.
            maxProd = max(nums[i], maxProd * nums[i]);
            minProd = min(nums[i], minProd * nums[i]);

            // Update global best
            res = max(res, maxProd);
        }
        return res;
    }
};


// ============================================================================
// 🟢 Approach 3: Optimal Prefix-Suffix Product
// ----------------------------------------------------------------------------
// Intuition:
// Product subarray might be best from prefix OR suffix. Example:
//
// nums = [-1, -2, -3]
// total product = -6 but best is 6 from [-1,-2,-3] OR [ -2, -3 ]
//
// Scan from left and right simultaneously:
// Keep prefix product & suffix product
//
// If product becomes zero, reset to 1 (zero breaks subarray)
//
// Algo:
// pre = 1, suff = 1, ans = -inf
// for i in 0..n-1:
//    if pre == 0: pre = 1
//    if suff == 0: suff = 1
//    pre  *= nums[i]
//    suff *= nums[n-i-1]
//    ans = max(ans, max(pre, suff))
//
// TC: O(N)
// SC: O(1)
// ============================================================================
int maxProductPrefixSuffix(vector<int>& nums) {
    int n = nums.size();
    long long pre = 1, suff = 1; // prefix & suffix product trackers
    long long ans = LLONG_MIN;  // global maximum

    for (int i = 0; i < n; i++) {

        if (pre == 0) pre = 1;           // reset if zero breaks prefix product
        if (suff == 0) suff = 1;         // reset for suffix as well

        pre  *= nums[i];                 // update prefix
        suff *= nums[n - 1 - i];         // update suffix

        ans = max({ans, pre, suff});     // update best
    }
    return (int)ans;
}


// ============================================================================
// main() to test all approaches
// ============================================================================
int main() {

    vector<int> nums = {2, 3, -2, 4};

    cout << "Brute Result: " << brute(nums) << endl;

    SolutionDP obj;
    cout << "Better DP Result: " << obj.maxProduct(nums) << endl;

    cout << "Optimal Prefix-Suffix Result: " << maxProductPrefixSuffix(nums) << endl;

    return 0;
}


/*
===========================================================
Dry Run (Better / DP Approach)
nums = [2, 3, -2, 4]

Start:
res = 2, maxProd = 2, minProd = 2

i = 1, x = 3
maxProd = max(3, 2*3) = 6
minProd = min(3, 2*3) = 6
res = 6

i = 2, x = -2 (negative → swap)
swap(maxProd, minProd) → both 6 so unchanged
maxProd = max(-2, 6 * -2) = -2
minProd = min(-2, 6 * -2) = -12
res = 6

i = 3, x = 4
maxProd = max(4, -2 * 4) = 4
minProd = min(4, -12 * 4) = -48
res = max(6, 4) = 6

Answer = 6
===========================================================

Extra Edge cases:
nums = [0,0,0]         → 0
nums = [-2]            → -2
nums = [-2,-3,-4]      → 24
nums = [-2,0,-3]       → 0
nums = [-1,-2,-9,-6]   → 108

===========================================================
Follow-Up Q & A:

Q1) How to return the actual subarray?
Track index when maxProd changes and store start-end indices.

Q2) Why minProd needed?
Negative * negative becomes positive, might maximize answer.

Q3) Why prefix-suffix helps?
Handles cases where max subarray is cut by zero or bounded by negatives.

Q4) Can we do divide & conquer?
Yes similar to max sum, but more complex.

Q5) How to handle overflow?
Use long long for products internally.
*/
