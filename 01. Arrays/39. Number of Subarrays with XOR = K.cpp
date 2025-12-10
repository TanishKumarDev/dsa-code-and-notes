#include <bits/stdc++.h>
using namespace std;

/*
🧠 Problem:
Given an integer array arr[] and a value k, count total number of subarrays
whose XOR is equal to k.

Example:
Input  : arr = [4, 2, 2, 6, 4], k = 6
Output : 4

Explanation:
Subarrays with XOR = 6 are:
[4, 2]       -> 4 ^ 2 = 6
[2, 2, 6]    -> 2 ^ 2 ^ 6 = 6
[6]          -> 6 = 6
[2, 6, 4]    -> 2 ^ 6 ^ 4 = 6

Constraints:
1 <= n <= 10^6
-10^9 <= arr[i] <= 10^9
Use O(N) or O(N log N) ideally.
*/


// ============================================================================
// 🔴 Approach 1: Brute Force (O(N^3) time, O(1) space)
// Intuition:
// Try all subarrays (i..j). Compute XOR by iterating inside.
// Extremely slow for large arrays.
// ============================================================================
int bruteXorCount(vector<int>& arr, int k) {
    int n = arr.size();
    int count = 0;

    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {

            int xorVal = 0; // calculate XOR from scratch
            for(int l = i; l <= j; l++) {
                xorVal ^= arr[l];
            }

            if(xorVal == k) count++;
        }
    }
    return count;
}


// ============================================================================
// 🔵 Approach 2: Better (O(N^2) time, O(1) space)
// Intuition:
// While expanding j from i to n, XOR can be updated incrementally
// XOR property: a ^ b ^ c = (a ^ b) ^ c  (no need to recompute from scratch)
// ============================================================================
int betterXorCount(vector<int>& arr, int k) {
    int n = arr.size();
    int count = 0;

    for(int i = 0; i < n; i++) {
        int xorVal = 0; // resets for each i
        for(int j = i; j < n; j++) {
            xorVal ^= arr[j]; // update using previous XOR

            if(xorVal == k) count++;
        }
    }
    return count;
}


// ============================================================================
// 🟢 Approach 3: Optimal (Prefix XOR + HashMap)
// Intuition:
// Let prefixXOR[i] = XOR of subarray arr[0..i]
//
// XOR rule:
// If XOR(i..j) should equal k, then:
// prefixXOR[j] ^ prefixXOR[i-1] = k
// => prefixXOR[i-1] = prefixXOR[j] ^ k
//
// So at index j, we just need to find how many prefix XORs previously existed
// equal to (prefixXor ^ k).
//
// Hashmap: freq[prefixXorValue] = count so far
//
// Handles cases where subarray starts from index 0 by storing freq[0] = 1.
//
// TC: O(N)
// SC: O(N)
// ============================================================================
int optimalXorCount(vector<int>& arr, int k) {

    unordered_map<int,int> freq;  // prefixXOR → count of occurrences
    freq[0] = 1; // base case allows subarrays starting index 0

    int prefixXor = 0;
    int count = 0;

    for(int x : arr) {
        prefixXor ^= x; // update running XOR

        int required = prefixXor ^ k; // XOR needed to form k

        if(freq.count(required)) {
            count += freq[required]; // add all matching previous prefixes
        }

        freq[prefixXor]++; // store the current prefixXOR
    }

    return count;
}


// ============================================================================
// main() to test all approaches
// ============================================================================
int main() {

    vector<int> arr = {4, 2, 2, 6, 4};
    int k = 6;

    cout << "Brute:   " << bruteXorCount(arr, k) << endl;
    cout << "Better:  " << betterXorCount(arr, k) << endl;
    cout << "Optimal: " << optimalXorCount(arr, k) << endl;

    return 0;
}


/*
======================== Dry Run (Optimal) ========================

arr = [4, 2, 2, 6, 4], k = 6

Index  Value   prefixXor   required(prefixXor^k)   freq map hit?   count
-----------------------------------------------------------------------
      freq = {0:1}

0      4        4           4^6 = 2                no              0
       freq = {0:1, 4:1}

1      2        4^2 = 6     6^6 = 0                yes(1 hit)      1
       freq = {0:1, 4:1, 6:1}

2      2        6^2 = 4     4^6 = 2                no              1
       freq = {0:1, 4:2, 6:1}

3      6        4^6 = 2     2^6 = 4                yes(2 hits)     1+2 = 3
       freq = {0:1, 4:2, 6:2, 2:1}

4      4        2^4 = 6     6^6 = 0                yes(1 hit)      3+1 = 4

Final Answer = 4


========================== Edge Cases ==========================
Case: [0,0,0,0], k=0  => result = 10 (all subarrays zero)
Case: [1,2,3], k=4    => result = 1 ([1,2,3])
Case: all negatives or large values — works fine due to XOR property


========================== Follow-Up Questions ==================
Q1) Why prefix XOR instead of prefix sum?
Because XOR is reversible: a^b^b = a (similar to subtraction in sum).

Q2) Can two-pointer sliding window work?
No, XOR is not monotonic like sum, so window shrinking doesn’t work.

Q3) How to print all subarrays instead of just count?
Store indices in hashmap vector, not just count.

Q4) Can this be extended to 2D matrix XOR?
Yes, reduce to 1D XOR using row compression technique.

Q5) What if we need longest XOR = k?
Similar prefix map approach but store first index instead of count.


=================================================================
*/
