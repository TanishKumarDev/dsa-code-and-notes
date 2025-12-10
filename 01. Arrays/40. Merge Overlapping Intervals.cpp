#include <bits/stdc++.h>
using namespace std;

/*
🧠 Problem:
Given a list of intervals, merge all overlapping intervals and return the result.
Intervals are in form [start, end]. Two intervals overlap when:
next.start <= current.end

Example:
Input  : [[1,3], [2,6], [8,10], [15,18]]
Output : [[1,6], [8,10], [15,18]]

Explanation:
[1,3] and [2,6] overlap and merge into [1,6]

Constraints:
1 <= intervals.size() <= 10^5
interval[i] = [start, end] where -10^9 <= start <= end <= 10^9
*/


// ============================================================================
// 🔴 Approach 1: Brute Force (O(N log N + N) → practically same as optimal)
// Intuition:
// 1) Sort intervals by starting time.
// 2) Traverse and merge any interval that overlaps with previous.
//
// Why overlap?
// If next.start <= end, means intervals overlap.
//
// Algo:
// sort(intervals)
// ans = empty
// for each interval:
//    if ans empty → push interval
//    else compare with last merged interval:
//        if overlap → update end = max(end, curr.end)
//        else push new interval
//
// TC: O(N log N) due to sorting
// SC: O(N) for result
//
// Edge cases:
// 1) Nested intervals → [1,10],[2,3] => [1,10]
// 2) Disjoint intervals → return as is
// 3) Single interval → return same
// ============================================================================
vector<vector<int>> mergeBrute(vector<vector<int>>& intervals) {

    sort(intervals.begin(), intervals.end()); // sort by start time
    vector<vector<int>> result;

    int n = intervals.size();
    for(int i = 0; i < n; ) {

        int start = intervals[i][0]; // starting of merged segment
        int end   = intervals[i][1]; // ending of merged segment

        int j = i + 1;
        // expand merge area while overlap exists
        while(j < n && intervals[j][0] <= end) {
            end = max(end, intervals[j][1]);
            j++;
        }

        result.push_back({start, end}); // merged interval stored
        i = j; // skip all used intervals
    }

    return result;
}


// ============================================================================
// 🟢 Approach 2: Optimal (Two-pointer/Line-sweep style)
// Same logic as brute, but implemented in cleaner form.
// TC: O(N log N), SC: O(N)
//
// Why optimal?
// Sorting is required; after sorting we only do a single scan O(N).
// ============================================================================
vector<vector<int>> merge(vector<vector<int>>& intervals) {

    if(intervals.empty()) return {};

    sort(intervals.begin(), intervals.end()); // sort by start value

    vector<vector<int>> merged;
    merged.push_back(intervals[0]); // initialize with first interval

    for(int i = 1; i < intervals.size(); i++) {

        vector<int>& last = merged.back();  // last stored interval
        vector<int>& curr = intervals[i];   // current interval

        if(curr[0] <= last[1]) {
            // overlap detected, merge
            last[1] = max(last[1], curr[1]);
        } else {
            // no overlap, simply push
            merged.push_back(curr);
        }
    }
    return merged;
}


// ============================================================================
// main() for testing
// ============================================================================
int main() {

    vector<vector<int>> intervals = {{1,3},{2,6},{8,10},{15,18}};

    cout << "Brute Merge: ";
    for(auto &v : mergeBrute(intervals)) {
        cout << "[" << v[0] << "," << v[1] << "] ";
    }
    cout << endl;

    cout << "Optimal Merge: ";
    for(auto &v : merge(intervals)) {
        cout << "[" << v[0] << "," << v[1] << "] ";
    }
    cout << endl;

    return 0;
}



/*
======================== Dry Run (Optimal) ========================

Input intervals (unsorted):
[[1,3], [2,6], [8,10], [15,18]]

After sorting:
[[1,3], [2,6], [8,10], [15,18]]

Initialize merged = [[1,3]]

i = 1 → [2,6]
last = [1,3]
2 <= 3 overlap true → new last = [1, max(3,6)] = [1,6]
merged = [[1,6]]

i = 2 → [8,10]
last = [1,6]
8 <= 6 false → no overlap → add new interval
merged = [[1,6], [8,10]]

i = 3 → [15,18] → no overlap
merged = [[1,6], [8,10], [15,18]]

Final Output: [[1,6], [8,10], [15,18]]


============================ Edge Cases ============================
1) intervals = [] → return []
2) intervals = [[5,5]] → return same
3) intervals = [[1,4],[4,5]] → [1,5] (touching counts as overlap)
4) intervals = [[1,10],[2,3],[4,8]] → [1,10]
5) intervals with negatives → works fine


========================== Follow-Up Questions ==========================
Q1) Can this be extended to merging K sorted interval lists?
Yes → Use min-heap to merge like Merge K sorted lists.

Q2) How to count total merged length?
Sum of (end-start+1) of final merged intervals.

Q3) Can we insert a new interval and merge efficiently?
Yes → use Insert Interval technique (binary search + merge).

Q4) What if instead of merging, we want intersection of intervals?
Use interval intersection approach (two pointers).

Q5) Can we solve without sorting?
Only if input is already sorted, otherwise sorting is necessary.

=================================================================
*/
