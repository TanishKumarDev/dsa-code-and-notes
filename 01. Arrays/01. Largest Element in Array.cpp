#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 1. Sorting (Brute)
    int sortApproach(vector<int>& arr) {
        if (arr.empty()) return -1;
        sort(arr.begin(), arr.end());
        return arr.back();
    }

    // 2. Linear Scan (Optimal)
    int linearScan(vector<int>& arr) {
        if (arr.empty()) return -1;
        int maxVal = arr[0];
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] > maxVal) maxVal = arr[i];
        }
        return maxVal;
    }

    // 3. STL (Production)
    int stlApproach(vector<int>& arr) {
        if (arr.empty()) return -1;
        return *max_element(arr.begin(), arr.end());
    }
};

int main() {
    Solution s;
    vector<int> arr = {1, 2, 3, 4, 5};
    cout << s.sortApproach(arr) << endl;
    cout << s.linearScan(arr) << endl;
    cout << s.stlApproach(arr) << endl;
    return 0;
}