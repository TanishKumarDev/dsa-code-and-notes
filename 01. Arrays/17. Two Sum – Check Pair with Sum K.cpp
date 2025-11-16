#include <bits/stdc++.h>
using namespace std;

// 🧠 Problem : 
// Example : 
// Constraint : 

// 🔴 Approach 1 Brute Force (YES/NO)
// Intuition :
// Try all possible pairs using two nested loops. If any pair forms the target sum, return "YES".
// Otherwise, after checking all pairs, return "NO".

// Algo :
// 1. Loop i from 0 to n-1
// 2. Loop j from i+1 to n-1
// 3. If arr[i] + arr[j] == target -> return "YES"
// 4. After loops end -> return "NO"

// TC : O(n^2) due to nested loops
// SC : O(1)

// Edge cases :
// 1. Array of size < 2 => always "NO"
// 2. Negative numbers allowed
// 3. Large values sum should be handled with int safely (or long long if needed)

string twoSum_brute_yes_no(vector<int> &arr, int target) {
    int n = arr.size();
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(arr[i] + arr[j] == target) return "YES";
        }
    }
    return "NO";
}

// 🔴 Approach 1 Brute Force (Indices Version)
// Intuition :
// Same logic as previous brute force, but instead of "YES", return the pair of indices.

// Algo :
// 1. Loop i = 0..n-1
// 2. Loop j = i+1..n-1
// 3. If arr[i] + arr[j] == target, return {i, j}
// 4. If not found, return {-1, -1}

// TC : O(n^2)
// SC : O(1)

// Edge cases :
// 1. If no such pair exists, return {-1, -1}
// 2. Works with negative numbers
// 3. Returns first valid pair found

vector<int> twoSum_brute_indices(vector<int> &arr, int target) {
    int n = arr.size();
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(arr[i] + arr[j] == target) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

// 🔵 Approach 2 Better (Hash Map) YES/NO
// Intuition :
// Use a hash map to store numbers already seen. For every element x,
// we check if (target - x) is already present in map. If yes, pair exists.

// Algo :
// 1. Create unordered_map seen
// 2. For i in array:
//       need = target - arr[i]
//       if seen contains need -> return "YES"
//       else store seen[arr[i]] = i
// 3. End loop -> return "NO"

// TC : O(n) average due to hashing
// SC : O(n)

// Edge cases:
// 1. Duplicate values handled
// 2. Negative numbers also supported
// 3. If array is very large, hashing works efficiently

string twoSum_hash_yes_no(vector<int> &arr, int target) {
    unordered_map<int, int> seen;

    for(int i = 0; i < arr.size(); i++) {
        int need = target - arr[i];
        if(seen.count(need)) return "YES";
        seen[arr[i]] = i;
    }
    return "NO";
}

// 🔵 Approach 2 Better (Hash Map) Indices Version
// Intuition :
// Same hashing method, but return index of current element and index of previously seen element.

// Algo :
// 1. Loop through arr
// 2. Compute need = target - arr[i]
// 3. If seen[need] exists, return {seen[need], i}
// 4. Else store seen[arr[i]] = i
// 5. After loop, return {-1, -1}

// TC : O(n)
// SC : O(n)

// Edge cases:
// 1. Multiple answers possible; returns first valid pair
// 2. Handles negatives
// 3. Works without sorting

vector<int> twoSum_hash_indices(vector<int>& arr, int target) {
    unordered_map<int, int> seen;

    for(int i = 0; i < arr.size(); i++) {
        int need = target - arr[i];
        if(seen.count(need)) {
            return {seen[need], i};
        }
        seen[arr[i]] = i;
    }
    return {-1, -1};
}


// 🟢 Approach 3 Optimal (Two Pointers on Sorted Array) YES/NO
// Intuition :
// Sort array and use two pointers:
// If sum < target move left forward, else move right backward.

// Algo :
// 1. Sort array (copy of original if indices needed)
// 2. left = 0, right = n-1
// 3. While left < right:
//        sum = arr[left] + arr[right]
//        if sum == target -> return "YES"
//        else if sum < target -> left++
//        else -> right--
// 4. return "NO"

// TC : O(n log n) due to sort + O(n) search
// SC : O(1) (ignoring sorting in-place)

// Edge cases:
// 1. Must be sorted first
// 2. Does not return original indices (values get rearranged)

string twoSum_sorted_yes_no(vector<int> arr, int target) {
    sort(arr.begin(), arr.end());
    int left = 0, right = arr.size() - 1;

    while(left < right) {
        int sum = arr[left] + arr[right];

        if(sum == target) return "YES";
        else if(sum < target) left++;
        else right--;
    }
    return "NO";
}

// 🟢 Approach 3 Optimal (Two Pointers Sorted) Value Pair Version
// Note: This returns the VALUES not original indexes.

// Intuition :
// Same two pointer logic, but instead of YES/NO, return the pair found.

// Algo :
// 1. Sort array
// 2. left = 0, right = n - 1
// 3. If arr[left] + arr[right] == target -> return {arr[left], arr[right]}
// 4. Adjust pointers like before
// 5. If no match -> return {-1, -1}

// TC : O(n log n)
// SC : O(1)

// Edge cases:
// 1. Sorted array changes original order
// 2. If original indices needed, different approach must be used

vector<int> twoSum_sorted_values(vector<int> arr, int target) {
    sort(arr.begin(), arr.end());
    int left = 0, right = arr.size() - 1;

    while(left < right) {
        int sum = arr[left] + arr[right];

        if(sum == target)
            return {arr[left], arr[right]};
        else if(sum < target)
            left++;
        else
            right--;
    }
    return {-1, -1};
}


int main() {

    vector<int> arr = {2, 7, 11, 15};
    int target = 9;

    // -------------------------------------------
    // Brute Force YES/NO
    // -------------------------------------------
    cout << "Brute YES/NO: "
         << twoSum_brute_yes_no(arr, target) << endl;

    // -------------------------------------------
    // Brute Force Indices
    // -------------------------------------------
    vector<int> res1 = twoSum_brute_indices(arr, target);
    cout << "Brute Indices: [" << res1[0] << ", " << res1[1] << "]" << endl;

    // -------------------------------------------
    // Hash Map YES/NO
    // -------------------------------------------
    cout << "Hash YES/NO: "
         << twoSum_hash_yes_no(arr, target) << endl;

    // -------------------------------------------
    // Hash Map Indices
    // -------------------------------------------
    vector<int> res2 = twoSum_hash_indices(arr, target);
    cout << "Hash Indices: [" << res2[0] << ", " << res2[1] << "]" << endl;

    // -------------------------------------------
    // Two Pointer Sorted YES/NO
    // -------------------------------------------
    cout << "Two Pointer YES/NO: "
         << twoSum_sorted_yes_no(arr, target) << endl;

    // -------------------------------------------
    // Two Pointer Sorted Pair (values, not indices)
    // -------------------------------------------
    vector<int> res3 = twoSum_sorted_values(arr, target);
    cout << "Two Pointer Values: [" << res3[0] << ", " << res3[1] << "]" << endl;

    return 0;
}

// ======================================================
// DRY RUNS FOR ALL APPROACHES (Multiple Cases)
// ======================================================
//
// Example 1: Match exists
// arr = [2, 7, 11, 15], target = 9
//
// i = 0, j = 1 → 2 + 7 = 9 → return "YES"
// Answer = YES
//
// Example 2: No pair matches
// arr = [3, 4, 5], target = 20
//
// i = 0: j = 1 → 3+4 = 7, j = 2 → 3+5 = 8
// i = 1: j = 2 → 4+5 = 9
// End loops → return "NO"
// Answer = NO
//
// Example 3: Handles negative numbers
// arr = [-3, 1, 4, 2], target = 1
//
// i = 0, j = 3 → -3 + 2 = -1
// i = 1, j = 2 → 1 + 4 = 5
// i = 1, j = 3 → 1 + 2 = 3
// i = 2, j = 3 → 4 + 2 = 6
// No match → return "NO"
// Answer = NO
//
// Example 4: Duplicates present
// arr = [5, 5, 10], target = 10
//
// i = 0, j = 1 → 5 + 5 = 10 → return "YES"
// Answer = YES
//
// ======================================================
// Dry Run for Hashing YES/NO
// ======================================================
//
// arr = [2, 7, 11, 15], target = 9
//
// i=0: x=2, need=7, seen={}, store seen[2]=0
// i=1: x=7, need=2, seen has 2 → return "YES"
// Answer = YES
//
// arr = [3, 4, 5], target = 20
//
// i=0: seen={3}
// i=1: seen={3,4}
// i=2: seen={3,4,5}
// End → NO
//
// arr = [-3, 1, 4, 2], target = 1
//
// i=0: x=-3 need=4 store(-3:0)
// i=1: x=1 need=0 store(1:1)
// i=2: x=4 need=-3 found → return YES
// Answer = YES
//
// ======================================================
// Dry Run for Hashing INDICES
// ======================================================
//
// arr = [2, 7, 11, 15], target = 9
//
// i=0: x=2, need=7, map={2:0}
// i=1: x=7, need=2 found → return {0,1}
// Answer = [0, 1]
//
// arr = [5, 5, 10], target = 10
//
// i=0: x=5, need=5, map={5:0}
// i=1: x=5, need=5 found → return {0,1}
// Answer = [0, 1]
//
// ======================================================
// Dry Run for Two Pointer (YES/NO)
// ======================================================
//
// arr = [2, 7, 11, 15], sorted already
// left=0 right=3
// 2 + 15 = 17 > 9 → right--
// left=0 right=2
// 2 + 11 = 13 > 9 → right--
// left=0 right=1
// 2 + 7 = 9 == target → return "YES"
// Answer = YES
//
// arr = [3, 4, 5], target=20
// left=0 right=2
// 3+5=8 < 20 → left++
// left=1 right=2
// 4+5=9 < 20 → left++
// left == right → stop → NO
//
// ======================================================
// Dry Run for Two Pointer VALUE Return
// ======================================================
//
// arr = [2, 7, 11, 15], target = 9
// sorted = [2,7,11,15]
// left=0 right=3 → 2+15=17 > 9
// left=0 right=2 → 2+11=13 > 9
// left=0 right=1 → 2+7=9 → return {2,7}
// Answer = [2,7]
// 
// arr = [5, 1, 5], target=10
// sorted=[1,5,5]
// left=0 right=2 → 1+5=6 < 10 left++
// left=1 right=2 → 5+5=10 → return {5,5}
// Answer = [5, 5]
