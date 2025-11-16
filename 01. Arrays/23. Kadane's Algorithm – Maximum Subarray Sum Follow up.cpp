#include <bits/stdc++.h>
using namespace std;

// 🟢 Approach 3 Optimal (Kadane’s Algorithm + Print Subarray)
// Intuition :
// We maintain a running sum. If adding the next element drops sum below
// that element alone, we start a new subarray from that element.
// This version supports all-negative arrays correctly.
//
// Algo :
// 1. currSum = 0, maxSum = -inf
// 2. Maintain indices: start, end, tempStart
// 3. For i = 0 to n-1:
//        If currSum + arr[i] < arr[i]:
//              currSum = arr[i]      // restart subarray
//              tempStart = i
//        Else:
//              currSum += arr[i]     // continue subarray
//
//        If currSum > maxSum:
//              maxSum = currSum
//              start = tempStart
//              end = i
// 4. Extract subarray arr[start..end]
// 5. Return {maxSum, subarray}
//
// TC : O(n)
// SC : O(1)
//
// Edge cases :
// 1. All negatives → returns max single element
// 2. Single element array works
// 3. Works on mixed positive/negative values

pair<long long, vector<int>> kadaneWithSubarray(vector<int>& arr) {

    if(arr.empty()) return {0, {}}; // safety for empty input

    long long currSum = 0;
    long long maxSum = LLONG_MIN;

    int start = 0, end = 0, tempStart = 0;

    for (int i = 0; i < (int)arr.size(); i++) {

        // Check whether to extend or restart new subarray
        if (currSum + arr[i] < arr[i]) {
            currSum = arr[i];
            tempStart = i; // new potential start
        } else {
            currSum += arr[i]; // extend current subarray
        }

        // Update global max with best range found so far
        if (currSum > maxSum) {
            maxSum = currSum;
            start = tempStart;
            end = i;
        }
    }

    // Extract result subarray
    vector<int> result(arr.begin() + start, arr.begin() + end + 1);

    return {maxSum, result};
}

int main() {
    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    auto ans = kadaneWithSubarray(arr);

    cout << "Max Subarray Sum: " << ans.first << endl;
    cout << "Max Subarray: [ ";
    for(int x : ans.second) cout << x << " ";
    cout << "]" << endl;

    return 0;
}
