#include <bits/stdc++.h>
using namespace std;

// 🧠 Problem : 
// Given an integer array, count the number of subarrays whose sum is equal to k.
// A subarray is a contiguous part of the array.
//
// Example : 
// Input : arr = [1, 2, 3], k = 3
// Subarrays with sum 3 are: [1,2], [3]
// Output : 2
//
// Constraint :
// 1 <= arr.size() <= 10^5
// -10^9 <= arr[i] <= 10^9
// Sum can overflow for large values, so use long long if needed.


// 🔴 Approach 1 Brute Force : 
// Intuition :
// Generate all subarrays using 3 nested loops and compute the sum of each.
// If sum == k, increment count.
//
// Algo :
// for i in range 0 to n-1:
//     for j in range i to n-1:
//         sum = 0
//         for l in range i to j:
//             sum += arr[l]
//         if sum == k: count++
//
// TC : O(n^3) due to three nested loops
// SC : O(1)
// Edge cases :
// Works with negative numbers, zero, and all types of integers.
int brute(vector<int>& arr, int k) {
    int n = arr.size(), cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int sum = 0;
            for (int l = i; l <= j; l++){
                sum += arr[l];
            }
            if (sum == k) cnt++;
        }
    }
    return cnt;
}


// 🔵 Approach 2 Better :
// Intuition :
// Instead of summing again for each subarray, build running sum from i to j.
// This reduces one loop.
//
// Algo :
// for i from 0 to n-1:
//     sum = 0
//     for j from i to n-1:
//         sum += arr[j]
//         if sum == k: count++
//
// TC : O(n^2)
// SC : O(1)
// Edge cases :
// Still slow for n close to 10^5. Works for negative numbers too.
int better(vector<int>& arr, int k) {
    int n = arr.size(), cnt = 0;
    for (int i = 0; i < n; i++) {
        long long sum = 0;
        for (int j = i; j < n; j++) {
            sum += arr[j];
            if (sum == k) cnt++;
        }
    }
    return cnt;
}


// 🟢 Approach 3 Optimal: Prefix Sum + HashMap (Best)
// Intuition :
// Use prefix sum and store frequency in hashmap.
// If prefixSum - k exists in map, it means a subarray ending here has sum=k.
//
// Algo :
// prefixSum = 0
// map[prefixSum]++   // store 0 sum initially
// for each element x in arr:
//     prefixSum += x
//     if map contains (prefixSum - k):
//         cnt += map[prefixSum - k]
//     map[prefixSum]++
//
// TC : O(n)
// SC : O(n)
// Edge cases :
// Handles negative numbers, zeros, large values.
// Works efficiently for large n.
int optimal(vector<int>& arr, int k) {
    unordered_map<long long, int> mp;  
    long long prefixSum = 0;
    int cnt = 0;

    mp[0] = 1; // prefix sum zero before starting

    for (int x : arr) {
        prefixSum += x;

        long long need = prefixSum - k;
        if (mp.count(need)) {
            cnt += mp[need];
        }

        mp[prefixSum]++;  // increase freq
    }
    return cnt;
}


int main() {

    vector<int> arr = {1, 2, 3};
    int k = 3;

    cout << "Brute: " << brute(arr, k) << endl;
    cout << "Better: " << better(arr, k) << endl;
    cout << "Optimal: " << optimal(arr, k) << endl;

    return 0;
}


/*
===========================
Dry Run (Optimal Approach)
arr = [1, 2, 3], k = 3

prefixSum map initially: {0:1}

Step 1:
x=1 → prefixSum = 1
need = prefixSum - k = 1 - 3 = -2 (not found)
mp = {0:1, 1:1}

Step 2:
x=2 → prefixSum = 3
need = 3 - 3 = 0 (found in map)
cnt += mp[0] → cnt = 1
mp = {0:1, 1:1, 3:1}

Step 3:
x=3 → prefixSum = 6
need = 6 - 3 = 3 (found)
cnt += mp[3] → cnt = 2
mp = {0:1, 1:1, 3:1, 6:1}

Answer = 2


===========================
Additional Test Cases
Case 1:
arr = [1,1,1], k=2
Subarrays: [1,1], [1,1] → Output: 2

Case 2:
arr = [1, -1, 1], k=1
Subarrays: [1], [1,-1,1], [1] → Output: 3

Case 3:
arr = [3,4,7,2,-3,1,4,2], k=7
Output: 4

Case 4:
arr = [0,0,0], k=0
All subarrays valid
Count = 6
*/

/*
===========================
Follow-Up Questions with Answers
===========================

Q1: How to find the longest subarray with sum = k?
Answer:
Use prefix sum + hashmap, but instead of counting, store the first index of each prefixSum.
For each prefixSum, check if (prefixSum - k) exists:
    length = currentIndex - indexOf(prefixSum - k)
Keep track of maximum length.
Time: O(n), Space: O(n)

-----------------------------------

Q2: How to print all subarrays with sum = k?
Answer:
Still use prefix sum + hashmap, but store all indices where each prefixSum occurs.
Whenever prefixSum - k found, print subarray from index+1 to current index.
This may return many subarrays.
Time: O(n + total_subarrays), Space: O(n)

-----------------------------------

Q3: What changes when array contains only positive numbers?
Answer:
We can use a Sliding Window (Two Pointers) approach because:
If currentSum > k → move left pointer
If currentSum < k → move right pointer
If equal → count and move pointers
Time: O(n), Space: O(1)
Works only for non-negative numbers.

-----------------------------------

Q4: How to count subarrays with sum divisible by k?
Answer:
Use modulo-based prefix sum:
prefixSum % k = remainder
If the same remainder repeats, subarray between them has sum divisible by k.
Use hashmap of remainder frequencies.
Formula:
count += freq[remainder]
Then freq[remainder]++
Time: O(n), Space: O(k)

-----------------------------------

Q5: Can we solve similar logic for 2D matrix subarray sum = k?
Answer:
Yes. Fix left and right column boundaries and compress columns into a 1D array of row sums.
Then apply the same 1D subarray-sum-k logic.
Time: O(cols^2 * rows), Space: O(rows)

-----------------------------------

Q6: What changes if we want subarray sum closest to k, not exactly k?
Answer:
We can use prefix sum + balanced BST or std::set.
Check prefixSum and nearest prefixSum - k for closest difference.
This is a harder variant.

-----------------------------------

Q7: What if integers are extremely large and prefix sum overflows?
Answer:
Use long long (C++), BigInteger (Java), or Python int.
Or use modulo arithmetic if sum divisible-by-k variation is required.

-----------------------------------

Q8: Can the optimal approach be extended for k range queries?
Answer:
Yes, Fenwick Tree (Binary Indexed Tree) or Segment Tree can be used for prefix sum frequency range queries.
But HashMap remains simpler for exact equality.
*/
