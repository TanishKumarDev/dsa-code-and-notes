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
void rotateRightBrute(vector<int>& arr, int k) {
    int n = arr.size();
    if (n == 0) return;

    k %= n;                 // k may be greater than n
    if (k == 0) return;     // no rotation needed

    vector<int> temp(k);    // store last k elements

    // Copy last k elements in temp
    for (int i = 0; i < k; i++) {
        temp[i] = arr[n - k + i];
    }

    // Shift remaining n-k elements to the right
    for (int i = n - 1; i >= k; i--) {
        arr[i] = arr[i - k];
    }

    // Move saved elements to front
    for (int i = 0; i < k; i++) {
        arr[i] = temp[i];
    }
}
void rotateLeftBrute(vector<int>& arr, int k) {
    int n = arr.size();
    if (n == 0) return;

    k %= n;  
    if (k == 0) return;

    vector<int> temp(k); // store first k elements

    // Save first k
    for (int i = 0; i < k; i++) {
        temp[i] = arr[i];
    }

    // Shift remaining n-k elements to the left
    for (int i = 0; i < n - k; i++) {
        arr[i] = arr[i + k];
    }

    // Move saved elements to the end
    for (int i = 0; i < k; i++) {
        arr[n - k + i] = temp[i];
    }
}
// 🔵 Approach 2 Better : 
// Intuition :
// Algo :
// TC :
// SC :
// Edge cases :
class SolutionRight {
public:
    void reverseArray(vector<int>& arr, int start, int end) {
        while (start < end) swap(arr[start++], arr[end--]);
    }

    void rotate(vector<int>& arr, int k) {
        int n = arr.size();
        if (n == 0) return;

        k %= n;
        if (k == 0) return;

        reverseArray(arr, n - k, n - 1);  // reverse last k
        reverseArray(arr, 0, n - k - 1);  // reverse first n-k
        reverseArray(arr, 0, n - 1);      // reverse all
    }
};
class SolutionLeft {
public:
    void reverseArray(vector<int>& arr, int start, int end) {
        while (start < end) swap(arr[start++], arr[end--]);
    }

    void rotateLeft(vector<int>& arr, int k) {
        int n = arr.size();
        if (n == 0) return;

        k %= n;
        if (k == 0) return;

        reverseArray(arr, 0, k - 1);      // reverse first k
        reverseArray(arr, k, n - 1);      // reverse last n-k
        reverseArray(arr, 0, n - 1);      // reverse all
    }
};

// 🟢 Approach 3 Optimal: ✔️ Best Alternative (No manual reverse function)

// Approach 3 ->  Same as Approach 2 just using Leetcode functions

// Intuition :
// Algo :
// TC :
// SC :
// Edge cases :

class SolutionRightLeetcode {
public:

    // Rotate array to the RIGHT by k steps
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0) return;     // Empty array check

        k %= n;                 // In case k > n
        if (k == 0) return;     // No rotation needed

        // Step 1: Reverse the last k elements
        reverse(nums.begin() + (n - k), nums.end());

        // Step 2: Reverse the first n-k elements
        reverse(nums.begin(), nums.begin() + (n - k));

        // Step 3: Reverse the entire array
        reverse(nums.begin(), nums.end());
    }
};
class SolutionLeftLeetcode {
public:

    // Rotate array to the LEFT by k steps
    void rotateLeft(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0) return;     // Empty array check

        k %= n;                 // Normalize k
        if (k == 0) return;     // Nothing to rotate

        // Step 1: Reverse the first k elements
        reverse(nums.begin(), nums.begin() + k);

        // Step 2: Reverse the remaining n-k elements
        reverse(nums.begin() + k, nums.end());

        // Step 3: Reverse the entire array
        reverse(nums.begin(), nums.end());
    }
};
int main() {

    vector<int> arr1 = {10, 20, 30, 40, 50};
    vector<int> arr2 = {10, 20, 30, 40, 50};
    vector<int> arr3 = {10, 20, 30, 40, 50};
    vector<int> arr4 = {10, 20, 30, 40, 50};
    vector<int> arr5 = {10, 20, 30, 40, 50};
    vector<int> arr6 = {10, 20, 30, 40, 50};

    int k = 2;

    cout << "Original Array: ";
    for (int x : arr1) cout << x << " ";
    cout << endl;

    // Approach 1
    // Brute Right Rotate
    rotateRightBrute(arr1, k);
    cout << "Right Rotation Brute: ";
    for (int x : arr1) cout << x << " ";
    cout << endl;
    
    // Brute Left Rotate
    rotateLeftBrute(arr2, k);
    cout << "Left Rotation Brute: ";
    for (int x : arr2) cout << x << " ";
    cout << endl;
    
    // Approach 2
    // Optimal Right Rotate
    SolutionRight s1;
    s1.rotate(arr3, k);
    cout << "Right Rotation Optimal: ";
    for (int x : arr3) cout << x << " ";
    cout << endl;
    
    // Optimal Left Rotate
    SolutionLeft s2;
    s2.rotateLeft(arr4, k);
    cout << "Left Rotation Optimal: ";
    for (int x : arr4) cout << x << " ";
    cout << endl;
    
    // Approach 3 ->  Same as Approach 2 just using Leetcode functions
    // Leetcode Right Rotate
    SolutionRightLeetcode s3;
    s3.rotate(arr5, k);
    cout << "Right Rotation Leetcode: ";
    for (int x : arr5) cout << x << " ";
    cout << endl;

    // Leetcode Left Rotate
    SolutionLeftLeetcode s4;
    s4.rotateLeft(arr6, k);
    cout << "Left Rotation Leetcode: ";
    for (int x : arr6) cout << x << " ";
    cout << endl;
    return 0;
}