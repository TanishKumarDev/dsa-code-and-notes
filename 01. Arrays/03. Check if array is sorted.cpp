#include <bits/stdc++.h>
using namespace std;

// 🧠 Problem : 
// Example : 
// Constraint : 

// 🔴 Approach 1 Brute Force : 
// Intuition :
// Algo :
// TC :
// SC :
// Edge cases :
bool brute(vector<int>& arr) {
    int n = arr.size();
    
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(arr[i] > arr[j]) return false;
        }
    }
    return true;
}

// 🔵 Approach 2 Better : 
// Intuition :
// Algo :
// TC :
// SC :
// Edge cases :
bool optimal(vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        if(arr[i] > arr[i+1]) return false;
    }
    return true;
}

// 🟢 Approach 3 Optimal: 
// Intuition :
// Algo :
// TC :
// SC :
// Edge cases :
bool stlApproach(vector<int>& arr) {
    return is_sorted(arr.begin(), arr.end());
}
int main()
{   

    vector<int> arr = {1, 2, 3, 4 };

    bool ans1 = brute(arr);
    cout << (ans1 ? "true" : "false") << endl;

    bool ans2 = optimal(arr);
    cout << (ans2 ? "true" : "false") << endl;

    bool arr3 = stlApproach(arr);
    cout << (arr3 ? "true" : "false") << endl;
    return 0;
}