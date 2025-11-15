#include <bits/stdc++.h>
using namespace std;

// 🧠 Problem : 
// Example : 
// Constraint : 

// 🔴 Approach 1 Brute Force :

// Intuition:
// Har element ke liye pura array traverse karke count nikal lo.
// Jiska count exactly 1 mile -> wahi single non-duplicate number hai.

// Algo:
// 1. For loop i = 0 to n-1:
//        - count = 0
//        - for loop j = 0 to n-1:
//              agar arr[i] == arr[j] -> count++
//        - agar count == 1 -> return arr[i]
// 2. Agar koi answer nahi mila -> return -1

// TC: O(n^2)  because nested loops
// SC: O(1)

// Edge cases:
// 1. Array empty -> return -1
// 2. Single element array -> wahi answer hoga
// 3. All elements appear twice except one

int brute(vector<int>& arr) {

    // Outer loop: pick each number
    for (int i = 0; i < arr.size(); i++) {

        int count = 0;   // Count occurrences of arr[i]

        // Inner loop: count how many times arr[i] appears
        for (int j = 0; j < arr.size(); j++) {
            if (arr[i] == arr[j])
                count++;
        }

        // If count == 1 -> unique element found
        if (count == 1)
            return arr[i];
    }

    return -1;   // If no unique element found
}


// 🔵 Approach 2 Better : Hashign

// Intuition:
// Ek frequency map banao: har element ka count store ho jayega.
// Fir map ko iterate karke jiska freq == 1 ho -> wahi answer.

// Algo:
// 1. unordered_map<int,int> freq banao.
// 2. Entire array traverse kar ke freq[x]++.
// 3. Map iterate kar ke jis key ki value 1 ho -> return key.

// TC: O(n) average case
// SC: O(n) for hash map

// Edge cases:
// 1. All elements except one appear twice
// 2. Unique element at beginning or end
// 3. If no single element -> return -1

int hashing(vector<int>& arr) {

    unordered_map<int, int> freq;   // Stores frequency of each element

    // Build frequency table
    for (int x : arr)
        freq[x]++;

    // Find element with frequency 1
    for (auto &p : freq) {
        if (p.second == 1)
            return p.first;
    }

    return -1;   // If no element with freq 1 found
}

// 🟢 Approach 3 Optimal:  XOR 

// Intuition:
// XOR ki properties:
// 1) x ^ x = 0          -> same numbers cancel out
// 2) x ^ 0 = x          -> XOR with zero gives same number
// 3) XOR is associative and commutative

// Array me sab elements twice aate hain except one element.
// Repeated elements XOR hone par cancel ho jayenge.
// Sirf unique element bachega.

// Example:
// arr = [4, 1, 2, 1, 2]
// XOR flow:
// ans = 0
// ans ^= 4 -> 4
// ans ^= 1 -> 5
// ans ^= 2 -> 7
// ans ^= 1 -> 6
// ans ^= 2 -> 4   (final answer)

// Algo:
// 1. ans = 0
// 2. For each x in array: ans ^= x
// 3. Return ans

// TC: O(n)
// SC: O(1)

// Edge cases:
// 1. Single-element array -> same element return
// 2. All elements appear exactly twice except one
// 3. Array ordering does not matter

class Solution {
public:
    int singleNumber(vector<int>& nums) {

        int ans = 0;   // XOR accumulator

        // XOR all elements
        for (int x : nums)
            ans ^= x;

        return ans;    // This is the unique number
    }
};

int main()
{
    // Example input: every element appears twice except one
    vector<int> arr = {4, 1, 2, 1, 2};

    // ---------------------------------------------
    // Approach 1 : Brute Force (O(n^2))
    // ---------------------------------------------
    int ans1 = brute(arr);
    cout << "Single Number using Brute Force: " << ans1 << endl;

    // ---------------------------------------------
    // Approach 2 : Hashing (O(n))
    // ---------------------------------------------
    int ans2 = hashing(arr);
    cout << "Single Number using Hashing: " << ans2 << endl;

    // ---------------------------------------------
    // Approach 3 : XOR (Optimal, O(n))
    // ---------------------------------------------
    Solution s;
    int ans3 = s.singleNumber(arr);
    cout << "Single Number using XOR: " << ans3 << endl;

    return 0;
}
