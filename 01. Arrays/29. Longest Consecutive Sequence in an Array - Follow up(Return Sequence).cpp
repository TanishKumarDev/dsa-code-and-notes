#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Return the actual longest consecutive sequence from the array.

Example:
Input:  [100, 4, 200, 1, 3, 2]
Output: [1, 2, 3, 4]

Approach:
Use unordered_set for O(1) lookups.
Find sequence starting points (x where x-1 does not exist).
Track best sequence start and length.
Reconstruct result vector and return.
*/

vector<int> longestConsecutiveSequence(vector<int>& arr) {

    int n = arr.size();
    if (n == 0) return {};   // Empty input

    // Insert all elements in a hash set for quick existence check
    unordered_set<int> st(arr.begin(), arr.end());

    int bestStart = 0;         // Starting number of best sequence
    int bestLength = 1;        // Length of best sequence found

    for (int x : st) {

        // Check if x can be start of a new sequence
        // x is start only if x-1 doesn't exist
        if (st.find(x - 1) == st.end()) {

            int currStart = x;     // Start of current sequence
            int currLen = 1;       // Current length counter

            int nextVal = x + 1;   // Try to find next consecutive values

            // Keep increasing nextVal while it exists
            while (st.find(nextVal) != st.end()) {
                currLen++;
                nextVal++;
            }

            // Update best result if this sequence is longer
            // If same length, choose smaller starting number
            if (currLen > bestLength ||
               (currLen == bestLength && currStart < bestStart)) {
                bestLength = currLen;
                bestStart = currStart;
            }
        }
    }

    // Build final result from bestStart and bestLength
    vector<int> result;
    for (int i = 0; i < bestLength; i++) {
        result.push_back(bestStart + i);
    }
    return result;
}


// ====================== TEST MAIN ======================
int main() {

    vector<int> arr = {100, 4, 200, 1, 3, 2};

    vector<int> ans = longestConsecutiveSequence(arr);

    cout << "Longest Consecutive Sequence: ";
    for (int x : ans) cout << x << " ";
    cout << endl;

    return 0;
}
