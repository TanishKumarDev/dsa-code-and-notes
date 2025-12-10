#include <bits/stdc++.h>
using namespace std;

// 🧠 Problem :
// Find the length of the longest sequence where numbers
// come one after another (consecutive).

// Example:
// Input:  [100, 4, 200, 1, 3, 2]
// Output: 4
// Because the longest consecutive numbers are [1,2,3,4]

// Constraints:
// 1 <= N <= 10^6
// Numbers may be positive, negative, duplicates

// 🔴 Approach 1 Brute Force : Check every number's next number repeatedly
// Intuition:
// For each number arr[i], keep checking if (arr[i] + 1), (arr[i] + 2) ... exist.
// Count length of this chain.
//
// Algo:
// For i from 0 to n-1:
//     count = 1
//     nextNum = arr[i] + 1
//     while nextNum exists in array:
//         count++, nextNum++
//     longest = max(longest, count)
//
// To check existence, we use find() which is O(n).
// So worst case = n * n → O(n^2)
//
// TC: O(n^2)
// SC: O(1) besides input
// Edge cases handled: duplicates, negative, single element
int bruteLongestConsecutive(vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) return n;

    int longest = 1;

    for (int i = 0; i < n; i++) {
        int count = 1;
        int nextVal = arr[i] + 1;

        // keep searching next consecutive value
        while (find(arr.begin(), arr.end(), nextVal) != arr.end()) {
            count++;
            nextVal++;
        }
        longest = max(longest, count);
    }

    return longest;
}
// 🔵 Approach 2 Better :
// Intuition:
// If array is sorted, consecutive numbers come together.
// Just count continuous increasing by +1 elements.
//
// Sort arr.
// If arr[i] == arr[i-1] + 1 → increment count
// Else if arr[i] != arr[i-1] → reset count to 1
// Track max count.
//
// TC: O(n log n) due to sorting
// SC: O(1) ignoring sort space
int sortedLongestConsecutive(vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) return n;

    sort(arr.begin(), arr.end());

    int longest = 1, count = 1;

    for (int i = 1; i < n; i++) {

        if (arr[i] == arr[i-1] + 1) {
            count++;                        // continues sequence
        }
        else if (arr[i] != arr[i-1]) {
            count = 1;                      // reset only if not duplicate
        }

        longest = max(longest, count);
    }

    return longest;
}
// 🟢 Approach 3 Optimal:
// Intuition:
// Put all numbers into an unordered_set for O(1) lookup.
// A number x can be start of a sequence only if (x-1) does NOT exist.
//
// Example set: {100,4,200,1,3,2}
// Start points: 100 (yes), 4(no), 200(yes), 1(yes), 3(no), 2(no)
// Then count forward x+1, x+2...
//
// TC: O(n)
// SC: O(n)
int optimalLongestConsecutive(vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return 0;

    unordered_set<int> st(arr.begin(), arr.end());
    int longest = 1;

    for (int x : st) {

        // If x-1 not present, x is start of sequence
        if (st.find(x - 1) == st.end()) {
            int count = 1;
            int val = x;

            // keep checking next consecutive numbers
            while (st.find(val + 1) != st.end()) {
                count++;
                val++;
            }

            longest = max(longest, count);
        }
    }
    return longest;
}

int main() {
    vector<int> arr = {100, 4, 200, 1, 3, 2};

    cout << "Brute Force:  " << bruteLongestConsecutive(arr) << endl;
    cout << "Sorting Way:  " << sortedLongestConsecutive(arr) << endl;
    cout << "Optimal Set:  " << optimalLongestConsecutive(arr) << endl;

    return 0;
}
/*==============================
🤔 Follow-Up Questions and Answers
==============================

1. Q: Can we solve it in **O(n)** time without using extra O(n) space?

A:
Not generally, because to achieve O(n) lookup operations we need a HashSet which itself costs O(n) space.
Without extra space, only sorting O(n log n) is possible.

Some interviewers allow "space complexity doesn't matter if input storage counts", then you can say sorting solution is acceptable.

2. Q: What if the array is **already sorted**?
   A:
   Then simply count longest continuous increasing by 1 sequence in **O(n)** without extra space.

3. Q: What if numbers are extremely large (like up to 10^18)?
   A:
   HashSet still works, but memory usage becomes high.
   We might need to use ordered sets, compressed mapping, or bitmaps if range is small.

4. Q: How to handle when array contains **duplicates**?
   A:
   HashSet automatically handles duplicates (ignores them).
   In sorting approach, duplicates should not reset the counter.

5. Q: Can we return the **actual sequence**, not just the length?

Answer (Optimal Strategy):

Instead of storing just `count`, store the start and end of sequence:

Example modification in optimal approach:

```
bestStart = x
bestEnd = val
```

Finally return the list: `[bestStart, bestStart+1, ..., bestEnd]`

6. Q: Space optimization?
   A:
   You can attempt to reuse the same array if sorting is allowed.
   Sorting: O(1) extra space if language supports in-place sort.

7. Q: Can this be extended to 2D grid (matrix consecutive numbers problem)?
   A:
   Yes, but then we need DFS/Union-Find or Graph traversal concepts.

---

*/

/*
==============================
🧠 Dry Run (Best Test Case)
arr = [100, 4, 200, 1, 3, 2]

Sorted:
[1, 2, 3, 4, 100, 200]
Longest run = 4

Set = {100,4,200,1,3,2}

Start points:
100 → run=1
200 → run=1
1 → run=1,2,3,4 → longest=4

==============================
More Test Cases
Case 1:
arr = [5,4,3,2,1]
Longest = 5 (5,4,3,2,1)

Case 2:
arr = [1,2,3,10,11,15]
Longest = 3 (1,2,3)

Case 3:
arr = [7,7,7,7]
Longest = 1

Case 4:
arr = [-1,0,1,2]
Longest = 4 (-1,0,1,2)

Case 5:
arr = []
Longest = 0
*/
