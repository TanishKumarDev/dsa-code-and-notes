#include <bits/stdc++.h>
using namespace std;

// 🧠 Problem :
// Given an integer array, return all elements that appear more than floor(n/3) times.
// At most 2 elements can satisfy this condition.
//
// Example:
// Input : [1,2,1,3,1,2,2]
// Output: [1,2]
//
// Constraint:
// 1 <= arr.size() <= 1e5
// Elements can be negative or large. Use O(1) extra space optimal solution.


// ============================================================================
// 🔴 Approach 1 Brute Force (O(N^2) time, O(N) space)
// ============================================================================
vector<int> majorityElementBrute(vector<int>& arr) {
    int n = arr.size();
    vector<int> ans;
    vector<bool> visited(n, false); // marks elements already counted

    for(int i = 0; i < n; i++) {
        if (visited[i]) continue; // skip if already processed

        int count = 0; // count freq of arr[i]

        for(int j = 0; j < n; j++) { // check entire array
            if(arr[j] == arr[i]) {
                count++;           // frequency++
                visited[j] = true; // mark visited
            }
        }

        if(count > n/3) {          // check majorityThreshold
            ans.push_back(arr[i]);
        }
    }

    return ans;
}


// ============================================================================
// 🔵 Approach 2 Better - HashMap (O(N) time, O(N) space)
// ============================================================================
vector<int> majorityElementBetter(vector<int>& arr) {
    int n = arr.size();
    unordered_map<int,int> freq; // stores frequencies
    vector<int> ans;

    for(int num : arr) {
        freq[num]++; // count occurrences
    }

    for(auto &p : freq) {
        if(p.second > n/3) { // check majorityThreshold
            ans.push_back(p.first);
        }
    }

    return ans;
}


// ============================================================================
// 🟢 Approach 3 Optimal: Extended Boyer-Moore Voting Algorithm
// O(N) time, O(1) space
// ============================================================================
vector<int> majorityElementOptimal(vector<int>& arr) {
    int n = arr.size();

    // Candidate values + vote counts
    int candidate1 = INT_MIN, candidate2 = INT_MIN; // two candidates possible
    int freq1 = 0, freq2 = 0;           // vote counters

    // -------------------- PHASE 1: Find potential candidates --------------------
    for(int value : arr) {
        if(value == candidate1) {            // matches candidate 1
            freq1++;               // vote++
        }
        else if(value == candidate2) {       // matches candidate 2
            freq2++;               // vote++
        }
        else if(freq1 == 0) {      // candidate 1 empty
            candidate1 = value;              // new candidate
            freq1 = 1;             // init vote
        }
        else if(freq2 == 0) {      // candidate 2 empty
            candidate2 = value;              // new candidate
            freq2 = 1;             // init vote
        }
        else {
            freq1--;               // reduce votes
            freq2--;
        }
    }

    // -------------------- PHASE 2: Verify candidates --------------------
    int count1 = 0, count2 = 0;
    for(int value : arr) {
        if(value == candidate1) count1++;     // count frequency of candidate 1
        if(value == candidate2) count2++;     // count frequency of candidate 2
    }

    vector<int> ans;
    int majorityThreshold = n/3;           // majority condition

    if(count1 > majorityThreshold) ans.push_back(candidate1); // valid candidate
    if(count2 > majorityThreshold && candidate2 != candidate1) ans.push_back(candidate2); // valid, avoid duplicate

    return ans;
}


// ============================================================================
// main() to test all approaches
// ============================================================================
int main() {

    vector<int> arr = {1, 2, 1, 3, 1, 2, 2};

    cout << "Brute:   ";
    for(int x : majorityElementBrute(arr)) cout << x << " ";
    cout << endl;

    cout << "Better:  ";
    for(int x : majorityElementBetter(arr)) cout << x << " ";
    cout << endl;

    cout << "Optimal: ";
    for(int x : majorityElementOptimal(arr)) cout << x << " ";
    cout << endl;

    return 0;
}


/*
======================== Dry Run (Optimal) ========================

arr = [1,2,1,3,1,2,2], n=7, majorityThreshold = 2

Phase 1 tracking:
x=1 → candidate1=1,freq1=1
x=2 → candidate2=2,freq2=1
x=1 → freq1=2
x=3 → both candidates diff → freq1=1,freq2=0
x=1 → freq1=2
x=2 → candidate2=2,freq2=1
x=2 → freq2=2

Phase 2 verify:
count(1)=3 > 2 → include
count(2)=3 > 2 → include

Result: [1,2]

=================================================================
Additional Test Cases
arr=[3,3,4] → [3]
arr=[1,1,1,2,3,4] → [1]
arr=[0,0,0] → [0]
arr=[2,2,9,3,9,3,9] → [9]

=================================================================
Follow-Up Questions with Answers

Q1) Can we extend Boyer-Moore to > N/K majority?
Yes. Maintain K-1 candidates and similar logic.

Q2) Why max 2 majority elements for n/3?
Because having 3 distinct > n/3 would exceed n.

Q3) Does this work with negative numbers?
Yes, values do not matter, only frequency.

Q4) Can we solve streaming input?
Yes, Boyer-Moore works on streams.

Q5) How to return element > n/2?
Use classical Boyer-Moore with 1 candidate.
*/
/*
======================== Dry Run (Optimal Approach) ========================

Goal: Find all elements occurring more than ⌊ n/3 ⌋ times
Array: arr = [1, 2, 1, 3, 1, 2, 2]
n = 7
majorityThreshold = ⌊7/3⌋ = 2

-----------------------------------
PHASE 1: Candidate Selection
-----------------------------------
Initial:
candidate1 = ∅, candidate2 = ∅
freq1 = 0, freq2 = 0

Traverse array:

i  x   Action                                         candidate1,freq1      candidate2,freq2
------------------------------------------------------------------------------
0  1   freq1 == 0 → candidate1 = 1, freq1 = 1                  1,1           ∅,0
1  2   freq2 == 0 → candidate2 = 2, freq2 = 1                  1,1           2,1
2  1   x == candidate1 → freq1++                             1,2           2,1
3  3   x != candidate1 && x != candidate2 → freq1--,freq2--           1,1           2,0
4  1   x == candidate1 → freq1++                             1,2           2,0
5  2   freq2 == 0 → candidate2 = 2, freq2 = 1                  1,2           2,1
6  2   x == candidate2 → freq2++                             1,2           2,2

Final candidates after Phase 1:
Candidate 1 = 1
Candidate 2 = 2

-----------------------------------
PHASE 2: Verification
-----------------------------------
Count actual occurrences:

count(1) = 3  > 2 ✔ include
count(2) = 3  > 2 ✔ include

Final Result: [1, 2]


======================== Additional Dry Runs ========================

Case 1:
arr = [3,3,4]
n=3, majorityThreshold=1
Candidates: 3,4
Verify: count(3)=2 >1 → [3]

Case 2:
arr = [1,1,1,2,3,4]
n=6, majorityThreshold=2
Candidates found: 1,2 (but verify)
count(1)=3 >2 → include
count(2)=1 <=2 → discard
Output: [1]

Case 3:
arr = [0,0,0]
n=3, majorityThreshold=1
Candidates found: 0
count(0)=3 >1 → [0]

Case 4:
arr = [2,2,9,3,9,3,9]
n=7, majorityThreshold=2
Candidates after Phase 1 likely: 9,2 or 9,3 depending on sequence.
Actual freq: 9 appears 3 times → [9]

Case 5 (No majority > n/3 exists):
arr = [1,2,3,4,5,6]
n=6, majorityThreshold=2
No element appears >2 times
Output: []

Case 6 (All elements same):
arr = [7,7,7,7,7]
Output: [7]

Case 7 (Two valid majority elements):
arr = [1,1,2,2,1,2,3,3,1,2]
n=10, majorityThreshold=3
count(1)=4, count(2)=4 → Output: [1,2]


======================== Follow-Up Questions (Expanded) ========================

Q1) Why can there be at most 2 majority elements when majorityThreshold is n/3?
Because if 3 distinct elements were each > n/3, total occurrences > n, impossible.

Q2) Can Boyer–Moore be extended to majority elements > n/k?
Yes. Maintain k-1 candidates and frequency counters.

Q3) Does order of elements matter?
No. Only frequency matters, not order.

Q4) Does this work with negative values or large integers?
Yes. Values do not matter, only matches and counts.

Q5) Can this handle streaming data?
Yes. Boyer–Moore is perfect for streaming since only counters are stored.

Q6) Can the optimal approach return false positives in Phase 1?
Yes. That is why Phase 2 verification is required.

Q7) Can this be done using sorting?
Yes. After sorting, candidates are near center indices, but sorting takes O(n log n).

Q8) What if we need the element > n/2 instead of > n/3?
Use classical Boyer–Moore Voting with only one candidate.

Q9) What happens if array is empty?
Return empty result.

Q10) Can we adapt this for frequencies in sliding window?
Yes, but would need frequency structure like hashmap or freq queue (not Boyer-Moore).


======================== Time & Space Summary ========================
Approach                     Time        Space
------------------------------------------------
Brute Force                 O(N²)       O(N)
Better (HashMap)            O(N)        O(N)
Optimal Boyer-Moore         O(N)        O(1)


=====================================================================
*/
