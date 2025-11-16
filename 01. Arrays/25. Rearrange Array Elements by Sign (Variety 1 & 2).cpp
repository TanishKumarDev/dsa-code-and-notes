#include <bits/stdc++.h>
using namespace std;

// 🧠 Problem: Rearrange array to alternate positive and negative numbers
//
// Variety 1: Equal number of +ve and -ve values
//    - Pattern must be: + - + - + - ... (start positive)
//    - Relative order of positives and negatives must remain same
//
// Variety 2: Unequal number of +ve and -ve values
//    - Same alternating behavior
//    - Leftover elements appended at end in same relative order
//
// Example:
// Input : [3,1,-2,-5,2,-4]
// Output: [3,-2,1,-5,2,-4]
//
// Input : [3, 1, -2, -5, -6]
// Output: [3,-2,1,-5,-6] (extra negative placed at end)
//
// Constraints:
// 1 <= N <= 10^5
// Must try for O(n) time and O(1) or O(n) extra space depending on approach


// 🔴 Approach 1 Brute Force (Using two separate arrays)
// Intuition:
// Separate positive and negative numbers into two vectors.
// Then merge them alternately. Leftovers will automatically go at end.
//
// Time Complexity  : O(n)
// Space Complexity : O(n) additional (pos + neg arrays)
//
// Edge cases:
// 1. If positives and negatives not equal, leftover stays at end.
// 2. Order within positives and negatives is preserved.
//
vector<int> rearrangeBrute(vector<int>& A) {
    vector<int> pos, neg;

    for (int num : A) {
        if (num > 0) pos.push_back(num);
        else neg.push_back(num);
    }

    int i = 0, p = 0, n = 0;
    while (p < pos.size() && n < neg.size()) {
        A[i++] = pos[p++];
        A[i++] = neg[n++];
    }
    while (p < pos.size()) A[i++] = pos[p++];
    while (n < neg.size()) A[i++] = neg[n++];
    return A;
}


// 🔵 Approach 2 Better for Variety 1 (Equal +ve and -ve)
// Intuition:
// If number of positives and negatives is equal, we know exact positions:
// All positives placed at even indices 0,2,4,... and negatives at 1,3,5,...
//
// Time Complexity  : O(n)
// Space Complexity : O(n)
//
// Edge cases:
// Must be used only when pos.size() == neg.size()
//
vector<int> rearrangeEqual(vector<int>& A) {
    int n = A.size();
    vector<int> ans(n, 0);

    int pos = 0, neg = 1;
    for (int num : A) {
        if (num > 0) {
            ans[pos] = num;
            pos += 2;
        } else {
            ans[neg] = num;
            neg += 2;
        }
    }
    return ans;
}


// 🟢 Approach 3 Optimal (In-place using index correction, Variety 2)
// Intuition:
// Use a pointer for the index that violates the rule (wrong sign).
// If a mismatch found, search forward for an element with opposite sign,
// then right-rotate subarray to maintain order.
//
// Time Complexity  : O(n^2) worst case due to shifting rotation,
//                    but usually behaves closer to O(n).
// Space Complexity : O(1)
//
// Edge cases:
// Suitable when positives and negatives not equal.
// Preserves original order.
//
void rightRotate(vector<int>& A, int wrong, int correct) {
    int temp = A[correct];
    for (int i = correct; i > wrong; i--) {
        A[i] = A[i - 1];
    }
    A[wrong] = temp;
}

vector<int> rearrangeInPlace(vector<int>& A) {
    int n = A.size();
    int wrong = -1;

    for (int i = 0; i < n; i++) {

        // When current element violates alternation rule
        if (wrong != -1) {
            // Check whether we found opposite sign to fix violation
            if ((A[wrong] > 0 && A[i] < 0) ||
                (A[wrong] < 0 && A[i] > 0)) {

                rightRotate(A, wrong, i);

                if (i - wrong >= 2) wrong += 2;
                else wrong = -1;
            }
        } else {
            if (((i % 2 == 0) && A[i] < 0) ||
                ((i % 2 == 1) && A[i] > 0)) {
                wrong = i;
            }
        }
    }
    return A;
}


// main function for testing
int main() {

    vector<int> v1 = {3, 1, -2, -5, 2, -4};
    vector<int> v2 = {3, 1, -2, -5, -6};

    cout << "Input 1: ";
    for (int x : v1) cout << x << " ";
    cout << "\nBrute Result: ";
    rearrangeBrute(v1);
    for (int x : v1) cout << x << " ";
    cout << endl;

    vector<int> v3 = {3, 1, -2, -5, 2, -4};
    cout << "\nEqual Case Result: ";
    vector<int> resEq = rearrangeEqual(v3);
    for (int x : resEq) cout << x << " ";
    cout << endl;

    cout << "\nInput 2: ";
    for (int x : v2) cout << x << " ";
    cout << "\nIn-Place Optimal: ";
    rearrangeInPlace(v2);
    for (int x : v2) cout << x << " ";
    cout << endl;

    return 0;
}


/*
Dry Run Example Variety 1 (Equal +ve and -ve)
A = [3,1,-2,-5,2,-4]
pos = [3,1,2]
neg = [-2,-5,-4]
Result = [3,-2,1,-5,2,-4]

Dry Run Example Variety 2 (Unequal)
A = [3,1,-2,-5,-6]
pos = [3,1]
neg = [-2,-5,-6]
Result = [3,-2,1,-5,-6]

*/
