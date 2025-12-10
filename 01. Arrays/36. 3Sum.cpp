#include <bits/stdc++.h>
using namespace std;

// 🧠 Problem :
// Given an integer array nums, return all unique triplets [nums[i], nums[j], nums[k]]
// such that i != j != k and their sum is zero.
//
// Example:
// Input  : nums = [-1, 0, 1, 2, -1, -4]
// Output : [[-1, -1, 1], [-1, 0, 1]]
//
// Explanation:
// Triplets whose sum is 0:
// -1 + -1 + 2 = 0  (but 2 is not there, correct list is below)
// -1 + 0 + 1 = 0
// -1 + -1 + 2 = 0 (Not in example, corrected: true combinations are list given)
//
// Constraint :
// 1 <= nums.size() <= 10^4
// -10^9 <= nums[i] <= 10^9
// Must avoid duplicate triplets in output.


// 🔴 Approach 1 Brute Force : O(N^3) Time, O(M log M) Space
// Intuition:
// Try every triplet combination i, j, k. If sum == 0, add triplet.
// But same triplet may appear multiple times. Use a set to remove duplicates.
//
// Why it works:
// Checks ALL possible triplets → 100% correct, but too slow for big n.
//
// TC: O(N^3 log M) because we sort every found triplet and insert into a set.
// SC: O(M) storing unique triplets
vector<vector<int>> threeSumBrute(vector<int>& nums) {

    int n = nums.size();
    set<vector<int>> uniqueTriplets; // ensures result uniqueness

    // Triple nested loops = O(N^3)
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {

                // Check if sum is zero
                if (nums[i] + nums[j] + nums[k] == 0) {

                    vector<int> triplet = {nums[i], nums[j], nums[k]};
                    sort(triplet.begin(), triplet.end()); // ensure sorted order
                    uniqueTriplets.insert(triplet); // duplicates removed
                }
            }
        }
    }

    // convert set to vector
    return vector<vector<int>>(uniqueTriplets.begin(), uniqueTriplets.end());
}


// 🔵 Approach 2 Better : Hashing - O(N^2) Time, O(N) Space
// Intuition:
// Fix nums[i], and use a hashset to find (target - nums[j]).
// Similar to 2Sum idea inside loop for each i.
//
// Why faster?
// Reduces 1 loop: N^3 → N^2
//
// TC: O(N^2)
// SC: O(N)
vector<vector<int>> threeSumBetter(vector<int>& nums) {

    int n = nums.size();
    set<vector<int>> st; // to keep unique sorted triplets

    for (int i = 0; i < n; i++) {
        unordered_set<int> seen; // stores values to form required target

        for (int j = i + 1; j < n; j++) {
            int third = -(nums[i] + nums[j]); // third number needed

            if (seen.count(third)) {
                vector<int> triplet = {nums[i], nums[j], third};
                sort(triplet.begin(), triplet.end());
                st.insert(triplet); // auto removes duplicates
            }

            seen.insert(nums[j]); // add current value for future
        }
    }

    return vector<vector<int>>(st.begin(), st.end());
}


// 🟢 Approach 3 Optimal : Two Pointer Technique - O(N^2) Time, O(1) Extra Space
// Intuition (EXPLAINED PROPERLY):
// Sorting array helps us:
// If we fix nums[i], we want nums[j] + nums[k] = -nums[i].
// Use 2 pointers (j starts right of i, k starts at end).
// If sum < 0 → need bigger value → j++
// If sum > 0 → need smaller value → k--
// If equals 0 → record triplet and skip duplicates.
//
// Why avoid duplicates?
// Because sorted array groups identical values together, so we skip them.
//
// Why it's optimal?
// Only O(N^2) and constant extra space excluding result.
//
// TC: O(N^2)
// SC: O(1) extra (ignoring result vector)
vector<vector<int>> threeSumOptimal(vector<int>& nums) {

    int n = nums.size();
    vector<vector<int>> result;

    sort(nums.begin(), nums.end()); // required for two-pointer duplicate skipping

    for (int i = 0; i < n; i++) {

        // Skip duplicate i values to avoid repeated triplets
        if (i > 0 && nums[i] == nums[i-1]) continue;

        int left = i + 1;
        int right = n - 1;

        while (left < right) {

            long long sum = (long long)nums[i] + nums[left] + nums[right];

            if (sum == 0) {

                result.push_back({nums[i], nums[left], nums[right]});

                // Skip duplicates on left
                while (left < right && nums[left] == nums[left + 1]) left++;
                // Skip duplicates on right
                while (left < right && nums[right] == nums[right - 1]) right--;

                left++;
                right--;
            }
            else if (sum < 0) {
                left++;  // need a larger sum
            }
            else {
                right--; // need a smaller sum
            }
        }
    }

    return result;
}


// ============================== main() ==============================
int main() {

    vector<int> nums = {-1, 0, 1, 2, -1, -4};

    cout << "Brute: ";
    for (auto& t : threeSumBrute(nums)) {
        for (int x : t) cout << x << " ";
        cout << " | ";
    }

    cout << "\nBetter: ";
    for (auto& t : threeSumBetter(nums)) {
        for (int x : t) cout << x << " ";
        cout << " | ";
    }

    cout << "\nOptimal: ";
    for (auto& t : threeSumOptimal(nums)) {
        for (int x : t) cout << x << " ";
        cout << " | ";
    }

    cout << endl;
    return 0;
}


/*
======================== Dry Run (Optimal) ========================

Input: nums = [-4, -1, -1, 0, 1, 2]
Sorted

i=0 → nums[i]=-4
left=1, right=5
sum = -4 + -1 + 2 = -3 < 0 → left++
sum = -4 + -1 + 2 = -3 < 0 → left++ (zero possible? no)

i=1 → nums[i]=-1
left=2, right=5
sum = -1 + -1 + 2 = 0 → store [-1,-1,2]
skip duplicates → left moves
left=3, right=4
sum = -1 + 0 + 1 = 0 → store [-1,0,1]

i=2 → nums[i] = -1 (skip duplicate)

i=3 → nums[i] = 0
left=4, right=5, no match

Final Output:
[-1,-1,2], [-1,0,1]


======================== Edge Cases ========================
Case 1: nums = [] → output []
Case 2: nums = [0] → []
Case 3: nums = [0,0,0] → [[0,0,0]]
Case 4: nums = [1,2,-2,-1] → []
Case 5: nums has large values → use long long for sum


======================== Follow-Up Questions ========================
Q1) Can 3Sum be extended to 4Sum, kSum?
Yes, using recursion + two-pointer.

Q2) Why sort first in optimal?
To efficiently skip duplicates and apply two-pointer logic.

Q3) What if we need count instead of list?
Return count++ each time sum==0.

Q4) Can we solve without sorting?
Yes, with hashing but duplicate handling becomes harder.

Q5) Can this solve 3Sum closest problem?
Yes, similar two-pointer approach with tracking min difference.

====================================================================
*/
