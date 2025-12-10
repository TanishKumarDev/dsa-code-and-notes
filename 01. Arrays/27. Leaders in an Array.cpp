#include <bits/stdc++.h>
using namespace std;

/*
🧠 Problem :
A Leader in an array is an element that is strictly greater than
all the elements to its right.

Example:
Input  : arr = [10, 22, 12, 3, 0, 6]
Output : [22, 12, 6]
Explanation:
22 > all right elements
12 > all right elements
6 > all right elements (last element is always a leader)

Constraints:
1 <= N <= 10^6
Array may contain positive/negative values
Return leaders in the same order as they appear in array
*/


// ============================================================================
// 🔴 Approach 1 Brute Force
// ============================================================================
// Intuition:
// For each element arr[i], check if any element on the right arr[j] is greater.
// If no such element exists, arr[i] is a leader.
//
// Algo:
// for i from 0 to n-1:
//     isLeader = true
//     for j from i+1 to n-1:
//         if arr[j] > arr[i]:
//             isLeader = false, break
//     if isLeader: push arr[i] to ans
//
// TC : O(n^2) Nested loops
// SC : O(n) result storage only
//
// Edge cases:
// ✔ Last element always a leader
// ✔ Works with negative numbers
// ✔ Works with duplicates

vector<int> bruteLeaders(vector<int>& arr) {

    int n = arr.size();     // Store the size of array
    vector<int> ans;        // Vector to store leader elements

    // Outer loop: pick each element one by one
    for (int i = 0; i < n; i++) {

        bool isLeader = true;  // Assume arr[i] is leader initially

        // Inner loop: compare arr[i] with every element to its right
        for (int j = i + 1; j < n; j++) {

            // If any element arr[j] is greater than arr[i], it's not a leader
            if (arr[j] > arr[i]) {
                isLeader = false;
                break;         // No need to check further
            }
        }

        // If no bigger element found, add arr[i] to leaders list
        if (isLeader) ans.push_back(arr[i]);
    }

    return ans;  // Return final list of leaders
}
// ============================================================================
// 🔵 Approach 2 Better (Optimal O(n) from right)
// ============================================================================
// Intuition:
// Traverse from right side. Maintain the maximum seen so far (maxSoFar).
// If current element > maxSoFar, it's a leader.
//
// Algo:
// maxSoFar = arr[n-1]
// push arr[n-1] to answer
// for i from n-2 down to 0:
//      if arr[i] > maxSoFar:
//          push arr[i]
//          maxSoFar = arr[i]
// reverse(ans)
//
// TC : O(n) Single traversal + reverse
// SC : O(n) result vector
//
// Edge cases:
// ✔ Last element always leader
// ✔ Handles duplicates
// ✔ Works with negatives

vector<int> optimalLeaders(vector<int>& arr) {

    int n = arr.size();          // Size of array
    if (n == 0) return {};       // If empty array, return empty result

    vector<int> ans;             // Stores leader elements
    int maxSoFar = arr[n - 1];   // Last element is always a leader

    ans.push_back(maxSoFar);     // Add last element to result

    // Traverse array from second last to first
    for (int i = n - 2; i >= 0; i--) {

        // If current element is greater than maxSoFar, it is leader
        if (arr[i] > maxSoFar) {
            ans.push_back(arr[i]);  // Add to answer
            maxSoFar = arr[i];      // Update max element seen so far
        }
    }

    reverse(ans.begin(), ans.end()); // Reverse to maintain original order
    return ans;                       // Return final list
}


// ============================================================================
// main() to test both approaches
// ============================================================================
int main() {

    vector<int> arr = {10, 22, 12, 3, 0, 6};

    cout << "Input Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    // Brute Force
    vector<int> res1 = bruteLeaders(arr);
    cout << "Brute Leaders: ";
    for (int x : res1) cout << x << " ";
    cout << endl;

    // Optimal
    vector<int> res2 = optimalLeaders(arr);
    cout << "Optimal Leaders: ";
    for (int x : res2) cout << x << " ";
    cout << endl;

    return 0;
}


/*
// ============================================================================
Dry Run for Approach 1 (Brute Force)
// ============================================================================
Test Case:
arr = [10, 22, 12, 3, 0, 6]
n = 6

i = 0 → arr[i] = 10
Compare with right side: [22, 12, 3, 0, 6]
22 > 10 → Not a leader

i = 1 → arr[i] = 22
Compare with right: [12, 3, 0, 6]
No element > 22 → Leader → add 22

i = 2 → arr[i] = 12
Compare with right: [3, 0, 6]
No element > 12 → Leader → add 12

i = 3 → arr[i] = 3
Compare with right: [0, 6]
6 > 3 → Not a leader

i = 4 → arr[i] = 0
Compare with right: [6]
6 > 0 → Not a leader

i = 5 → arr[i] = 6
Right side empty → always leader → add 6

Output (Brute): [22, 12, 6]

---
// ============================================================================
Dry Run for Approach 2 (Optimal O(n))
// ============================================================================
Test Case:
arr = [10, 22, 12, 3, 0, 6]
n = 6

Start from right:
maxSoFar = arr[5] = 6
ans = [6]

i = 4 → arr[4] = 0
0 > 6 → false → skip

i = 3 → arr[3] = 3
3 > 6 → false → skip

i = 2 → arr[2] = 12
12 > 6 → true → add 12
maxSoFar = 12
ans = [6, 12]

i = 1 → arr[1] = 22
22 > 12 → true → add 22
maxSoFar = 22
ans = [6, 12, 22]

i = 0 → arr[0] = 10
10 > 22 → false → skip

Reverse ans → [22, 12, 6]

Output (Optimal): [22, 12, 6]

---

// ============================================================================
Additional Test Case Dry Runs
// ============================================================================
Case 2:
arr = [5, 4, 3, 2, 1]

Right is always smaller.

Leaders (Brute and Optimal): [5, 4, 3, 2, 1]

Case 3:
arr = [1, 2, 3, 4, 5]

Only the last one is strictly greater than all right elements.

Leaders (Brute and Optimal): [5]

Case 4:
arr = [7, 7, 7, 7]

No element is strictly greater than the right (only last qualifies).

Leaders: [7]

Case 5:
arr = [-1, -5, -3, -10]

Evaluate:
-1 > right values? No, because -1 > -5, -3, -10 → Yes, so leader
-5 > right [-3, -10]? No
-3 > right [-10]? Yes, so leader
-10 last → leader

Leaders: [-1, -3, -10]


*/