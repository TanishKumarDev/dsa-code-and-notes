#include <bits/stdc++.h>
using namespace std;

/*
🧠 Problem:
Given an integer array nums and an integer target, return all unique quadruplets
[nums[a], nums[b], nums[c], nums[d]] such that:
a != b != c != d and nums[a] + nums[b] + nums[c] + nums[d] == target.

Return answer without duplicates.

Example:
Input  : nums = [1, 0, -1, 0, -2, 2], target = 0
Output : [[-2, -1, 1, 2], [-2, 0, 0, 2], [-1, 0, 0, 1]]

Constraints:
1 <= nums.size() <= 200
-10^9 <= nums[i] <= 10^9
-10^9 <= target <= 10^9
*/



// ============================================================================
// 🔴 Approach 1 Brute Force (O(N^4) Time)
// Intuition:
// Try every combination of 4 different indices (i, j, k, l).
// Check if sum == target. Store in set to avoid duplicates.
//
// Why works:
// Simple exhaustive checking, but very slow for large input.
//
// TC: O(N^4 log M)
// SC: O(M) for storing unique quadruplets
// ============================================================================
vector<vector<int>> fourSumBrute(vector<int>& nums, int target) {

    int n = nums.size();
    set<vector<int>> uniqueSet; // to avoid duplicates automatically

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            for(int k = j + 1; k < n; k++) {
                for(int l = k + 1; l < n; l++) {

                    long long sum = (long long)nums[i] + nums[j] + nums[k] + nums[l];

                    if(sum == target) {
                        vector<int> quad = {nums[i], nums[j], nums[k], nums[l]};
                        sort(quad.begin(), quad.end()); // sort to maintain order
                        uniqueSet.insert(quad);         // auto remove duplicates
                    }
                }
            }
        }
    }

    return vector<vector<int>>(uniqueSet.begin(), uniqueSet.end());
}



// ============================================================================
// 🔵 Approach 2 Better (O(N^3) Time + Hashing)
// Intuition:
// Fix first 2 numbers i, j. Remaining sum we need is (target - nums[i] - nums[j]).
// Now same idea as 2-sum using hashset for the remaining part.
//
// TC: O(N^3)
// SC: O(N)
// ============================================================================
vector<vector<int>> fourSumBetter(vector<int>& nums, int target) {

    int n = nums.size();
    set<vector<int>> uniqueSet;

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {

            unordered_set<long long> seen; // stores numbers seen after j

            for(int k = j + 1; k < n; k++) {

                long long required = (long long)target - nums[i] - nums[j] - nums[k];

                if(seen.count(required)) {
                    vector<int> quad = {nums[i], nums[j], nums[k], (int)required};
                    sort(quad.begin(), quad.end()); // sorted for uniqueness
                    uniqueSet.insert(quad);
                }

                seen.insert(nums[k]); // mark k-th element seen
            }
        }
    }

    return vector<vector<int>>(uniqueSet.begin(), uniqueSet.end());
}



// ============================================================================
// 🟢 Approach 3 Optimal (Two-Pointer) — O(N^3) Time, O(1) Extra Space
// Intuition (Important):
// Sort array → allows two-pointer logic & duplicate skipping.
// Fix two numbers nums[i], nums[j] and use two-pointer (k,l) for remaining sum:
// sum = nums[i] + nums[j] + nums[k] + nums[l]
//
// If sum < target → need bigger value → k++
// If sum > target → need smaller value → l--
// If sum == target → record quadruplet & skip duplicates.
//
// Why optimal?
// Reduces 1 loop compared to brute force and avoids hashing overhead.
//
// TC: O(N^3)
// SC: O(1) + result
// ============================================================================
vector<vector<int>> fourSumOptimal(vector<int>& nums, int target) {

    int n = nums.size();
    vector<vector<int>> result;

    sort(nums.begin(), nums.end()); // important for two-pointer and duplicate skip

    for(int i = 0; i < n; i++) {

        if(i > 0 && nums[i] == nums[i - 1]) continue; // skip duplicate i

        for(int j = i + 1; j < n; j++) {

            if(j > i + 1 && nums[j] == nums[j - 1]) continue; // skip duplicate j

            int left = j + 1, right = n - 1;

            while(left < right) {

                long long sum = (long long)nums[i] + nums[j] + nums[left] + nums[right];

                if(sum == target) {

                    result.push_back({nums[i], nums[j], nums[left], nums[right]});

                    // skip duplicates for left
                    while(left < right && nums[left] == nums[left + 1]) left++;
                    // skip duplicates for right
                    while(left < right && nums[right] == nums[right - 1]) right--;

                    left++;
                    right--;
                }
                else if(sum < target) {
                    left++;    // need bigger value
                }
                else {
                    right--;   // need smaller value
                }
            }
        }
    }

    return result;
}



// ============================================================================
// main() for testing
// ============================================================================
int main() {

    vector<int> nums = {1, 0, -1, 0, -2, 2};
    int target = 0;

    // Brute Force Result
    cout << "Brute Result: ";
    for (auto &quad : fourSumBrute(nums, target)) {
        cout << "[ ";
        for (int x : quad) cout << x << " ";
        cout << "] ";
    }
    cout << endl;

    // Better (Hashing) Result
    cout << "Better Result: ";
    for (auto &quad : fourSumBetter(nums, target)) {
        cout << "[ ";
        for (int x : quad) cout << x << " ";
        cout << "] ";
    }
    cout << endl;

    // Optimal (Two Pointer) Result
    cout << "Optimal Result: ";
    for (auto &quad : fourSumOptimal(nums, target)) {
        cout << "[ ";
        for (int x : quad) cout << x << " ";
        cout << "] ";
    }
    cout << endl;

    return 0;
}




/*
======================== Dry Run (Optimal) ========================

Input: nums = [1, 0, -1, 0, -2, 2], target = 0
Sorted: [-2, -1, 0, 0, 1, 2]

i=0 → -2
  j=1 → -1
    left=2 (0), right=5 (2)
    sum = -2 + -1 + 0 + 2 = -1 < 0 → left++

    left=3 (0), right=5 (2)
    sum = -2 + -1 + 0 + 2 = -1 < 0 → left++

    left=4 (1), right=5 (2)
    sum = -2 + -1 + 1 + 2 = 0 → store [-2, -1, 1, 2]

i=0 → -2
  j=2 → 0
    left=3 (0), right=5 (2)
    sum = 0 → store [-2, 0, 0, 2]

i=1 → -1
  j=3 → 0
    left=4 (1), right=5 (2)
    sum = 2 > 0 → right--

    left=4 (1), right=4 stop


Final Output:
[-2, -1, 1, 2]
[-2, 0, 0, 2]


======================== Edge Cases ========================
Case 1: nums length < 4 → return []
Case 2: nums = [0,0,0,0] target=0 → [[0,0,0,0]]
Case 3: no valid quadruplet → return []

======================== Follow-Up Questions ========================
Q1) Can we generalize this to k-Sum?
Yes, using recursion + 2-pointer method for final 2-sum stage.

Q2) Can we solve without sorting?
Yes, but duplicate handling becomes complex.

Q3) Can this be modified for closest sum?
Yes, similar logic used in 3Sum-closest.

Q4) Can we handle extremely large integers safely?
Use long long for sum and required values.

Q5) Can we return count instead of combinations?
Yes, maintain total count rather than storing quadruplets.

=====================================================================
*/
