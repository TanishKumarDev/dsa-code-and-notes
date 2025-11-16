#include <bits/stdc++.h>
using namespace std;


// 🧠 Problem :
// Given an array arr, find the maximum possible sum from any subarray.

// Example :
// Input  : [-2, 1, -3, 4, -1, 2, 1, -5, 4]
// Output : 6
// Explanation: Subarray [4, -1, 2, 1] has the maximum sum 6.

// Constraints :
// 1. Array elements may be positive or negative.
// 2. Subarray must be contiguous.
// 3. Return the maximum sum (long long for safety).



// 🔴 Approach 1 Brute Force (Three loops)=
// Intuition :
// Generate all possible subarrays and find the sum of each.
// Track the maximum sum seen so far.
//
// Algo :
// 1. maxSum = -infinity
// 2. For i from 0 to n-1:
//        For j from i to n-1:
//             sum = 0
//             For k from i to j:
//                   sum += arr[k]
//             maxSum = max(maxSum, sum)
// 3. return maxSum
//
// TC : O(n^3)   (Three nested loops)
// SC : O(1)
//
// Edge cases :
// 1. All negative numbers (still return max element)
// 2. n = 1 (return that element)
// 3. Very slow for n > 2000

int brute(vector<int>& arr) {
    int n = arr.size();
    int maxSum = INT_MIN; // store maximum sum found

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {

            int sum = 0; // sum of subarray [i..j]

            for (int k = i; k <= j; k++) {
                sum += arr[k]; // accumulate
            }

            maxSum = max(maxSum, sum); // update max
        }
    }

    return maxSum;
}


// 🔵 Approach 2 Better (Prefix sum within loop / two loops)=
// Intuition :
// Instead of computing subarray sum again and again from scratch,
// maintain running sum from i to j.
//
// Algo :
// 1. maxSum = -infinity
// 2. For i from 0 to n-1:
//       sum = 0
//       For j from i to n-1:
//             sum += arr[j]
//             maxSum = max(maxSum, sum)
// 3. return maxSum
//
// TC : O(n^2)
// SC : O(1)
//
// Edge cases :
// 1. Works with negative values
// 2. Faster than brute but still not optimal for large n

int better(vector<int>& arr) {
    int n = arr.size();
    int maxSum = INT_MIN;

    for (int i = 0; i < n; i++) {

        int sum = 0; // running sum starting at i

        for (int j = i; j < n; j++) {
            sum += arr[j]; // expand subarray
            maxSum = max(maxSum, sum);
        }
    }

    return maxSum;
}


// 🟢 Approach 3 Optimal (Kadane's Algorithm)=
// Intuition :
// If current running sum becomes negative, it cannot help future sums,
// so reset it to zero. Track the maximum seen so far.
//
// Algo :
// 1. currSum = 0, maxSum = -inf
// 2. For each element num in arr:
//         currSum += num
//         maxSum = max(maxSum, currSum)
//         if currSum < 0: currSum = 0
// 3. return maxSum
//
// TC : O(n)
// SC : O(1)
//
// Edge cases :
// 1. All numbers negative → standard Kadane fails (fix needed)
// 2. Final version handles all negatives by tracking max individually

long long kadane(vector<int>& arr) {
    long long currSum = 0;
    long long maxSum = LLONG_MIN;

    for (int num : arr) {

        currSum += num;              // include current number
        maxSum = max(maxSum, currSum); // update best sum

        if (currSum < 0)
            currSum = 0;             // reset if negative
    }
    return maxSum;
}



// Main Driver
int main() {

    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    cout << "Brute Result:      " << brute(arr) << endl;
    cout << "Better Result:     " << better(arr) << endl;
    cout << "Kadane Result:     " << kadane(arr) << endl;

    return 0;
}

/*
Additional Dry Run Examples & Test Cases

-------------------------------------------------------------
Test Case 1: Classic Example
arr = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
Expected Output: 6
Subarray: [4, -1, 2, 1]

Kadane Step-by-step:
curr=0, max=-inf
num=-2 → curr=-2 → max=-2 → curr reset 0
num=1  → curr=1  → max=1
num=-3 → curr=-2 → max=1 → curr reset 0
num=4  → curr=4  → max=4
num=-1 → curr=3  → max=4
num=2  → curr=5  → max=5
num=1  → curr=6  → max=6
num=-5 → curr=1  → max=6
num=4  → curr=5  → max=6
Final Answer = 6

-------------------------------------------------------------
Test Case 2: All Negative
arr = [-5, -2, -7, -3]
Expected Output: -2
Subarray: [-2] (largest element)

Kadane:
curr=0, max=-inf
num=-5 → curr=-5 → max=-5 → reset curr
num=-2 → curr=-2 → max=-2 → reset curr
num=-7 → curr=-7 → max=-2 → reset curr
num=-3 → curr=-3 → max=-2 → reset curr
Final Answer = -2

-------------------------------------------------------------
Test Case 3: All Positive
arr = [1, 2, 3, 4]
Expected Output: 10
Subarray: entire array

Kadane:
curr=0, max=-inf
1→1→max=1
2→3→max=3
3→6→max=6
4→10→max=10
Final Answer = 10

-------------------------------------------------------------
Test Case 4: Alternating Pos/Neg
arr = [5, -1, 5, -1, 5]
Expected Output: 13
Subarray: whole array (5 -1 5 -1 5)

Kadane:
5→5→max=5
-1→4→max=5
5→9→max=9
-1→8→max=9
5→13→max=13
Final Answer = 13

-------------------------------------------------------------
Test Case 5: Contains Zeros
arr = [0, 0, -1, 0, 0]
Expected Output: 0
Subarray: [0] or [0,0]

Kadane:
0→0→max=0
0→0→max=0
-1→-1→max=0→reset
0→0→max=0
0→0→max=0
Final Answer = 0

-------------------------------------------------------------
Test Case 6: Single Element Positive
arr = [8]
Expected Output: 8

Test Case 7: Single Element Negative
arr = [-4]
Expected Output: -4

-------------------------------------------------------------
Test Case 8: Large Values Stress
arr = [1000000000, -100, 1000000000]
Expected Output: 1999999900

Kadane:
curr=1e9 → max=1e9
num=-100 → curr=999999900 → max=1e9
num=1e9 → curr=1999999900 → max=1999999900
Final Answer = 1999999900

-------------------------------------------------------------
Test Case 9: Majority negative but some positive region
arr = [-8, -3, -6, -2, -5, -4]
Expected Output: -2

All negative: return max element manually

-------------------------------------------------------------
Test Case 10: Mixed with large negative drop
arr = [10, -100, 20, 30, -5, 40]
Expected Output: 85
Subarray: [20, 30, -5, 40]

Kadane:
10→10→max=10
-100→-90→reset
20→20→max=20
30→50→max=50
-5→45→max=50
40→85→max=85
Final Answer = 85
*/