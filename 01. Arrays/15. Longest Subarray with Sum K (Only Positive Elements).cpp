#include <bits/stdc++.h>
using namespace std;

// 🧠 Problem : 
// Example : 
// Constraint : 

// 🔴 Approach 1 Brute Force : 

// Intuition:
// Har possible subarray banake uska sum check karo.
// Jo subarray ka sum k ke equal ho, uski length update kar do.
// Ye 3 loops use karta hai: i, j, aur ek loop sum calculate karne ke liye.

// Algo:
// 1. i = 0..n-1 start index
// 2. j = i..n-1 end index
// 3. For each (i, j) range, ek aur loop se sum calculate karo
// 4. If sum == k -> maxLen update
// 5. Return maxLen

// TC: O(n^3)  (Worst possible approach)
// SC: O(1)

// Edge cases:
// 1. k = 0
// 2. All elements zero
// 3. No subarray matches sum

int brute(vector<int>& arr, long long k) {

    int n = arr.size();
    int maxLen = 0;

    // Pick all starting points
    for (int i = 0; i < n; i++) {

        // Pick all ending points
        for (int j = i; j < n; j++) {

            long long sum = 0;

            // Calculate sum of subarray arr[i..j]
            for (int l = i; l <= j; l++)
                sum += arr[l];

            // Check sum
            if (sum == k)
                maxLen = max(maxLen, j - i + 1);
        }
    }

    return maxLen;
}

// 🔵 Approach 2 Better : 

// Intuition:
// Ye pehle approach se better hai kyunki inner-most loop nahi hai.
// Har i se start karke sum ko j loop me hi accumulate karte jao.
// Means j loop chalate waqt sum increment hota rahega.
// Agar sum == k ho jaye to length update.

// Algo:
// 1. For i = 0..n-1:
//        sum = 0
//        For j = i..n-1:
//             sum += arr[j]
//             if sum == k -> update maxLen
// 2. Return maxLen

// TC: O(n^2)
// SC: O(1)

// Edge cases:
// 1. Negative numbers (Still works)
// 2. k = 0
// 3. No valid subarray

int better(vector<int>& arr, long long k) {

    int n = arr.size();
    int maxLen = 0;

    // Fix start
    for (int i = 0; i < n; i++) {

        long long sum = 0;    // fresh sum

        // Expand end
        for (int j = i; j < n; j++) {

            sum += arr[j];    // accumulate

            if (sum == k)
                maxLen = max(maxLen, j - i + 1);
        }
    }

    return maxLen;
}

// 🟢 Approach 3 Optimal: Sliding Window

// Intuition:
// Array non-negative ho to sliding window perfect kaam karta hai.
// Right pointer sum badhata hai.
// Agar sum > k ho jaaye -> left pointer se window shrink.
// Jab sum == k -> window length update.

// Algo:
// 1. left = 0, right = 0, sum = 0
// 2. Right pointer move:
//        sum += arr[right]
//        While sum > k: shrink from left (sum -= arr[left], left++)
//        If sum == k: update maxLen
// 3. Continue until right reaches end.

// TC: O(n)     (Each element left/right pointer se ek hi baar pass hota hai)
// SC: O(1)

// Edge cases:
// 1. Elements negative ho to sliding window fail hota hai
// 2. k = 0 case
// 3. Entire array sum == k

int getLongestSubarray(vector<int>& arr, long long k) {

    int n = arr.size();
    int left = 0, right = 0;
    long long sum = 0;
    int maxLen = 0;

    while (right < n) {

        // Expand window
        sum += arr[right];

        // Shrink window if sum exceeds k
        while (sum > k && left <= right) {
            sum -= arr[left];
            left++;
        }

        // Exact match
        if (sum == k)
            maxLen = max(maxLen, right - left + 1);

        right++;
    }

    return maxLen;
}
int main()
{
    // Example input array
    vector<int> arr = {1, 2, 1, 1, 1, 3, 2};
    long long k = 5;

    // -------------------------------------------------
    // Approach 1 : Brute Force (O(n^3))
    // -------------------------------------------------
    int ans1 = brute(arr, k);
    cout << "Longest Subarray Length using Brute Force: " << ans1 << endl;

    // -------------------------------------------------
    // Approach 2 : Better (O(n^2))
    // -------------------------------------------------
    int ans2 = better(arr, k);
    cout << "Longest Subarray Length using Better Approach: " << ans2 << endl;

    // -------------------------------------------------
    // Approach 3 : Optimal Sliding Window (O(n))
    // -------------------------------------------------
    int ans3 = getLongestSubarray(arr, k);
    cout << "Longest Subarray Length using Sliding Window: " << ans3 << endl;

    return 0;
}
