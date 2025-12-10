#include <bits/stdc++.h>
using namespace std;

// 🧠 Problem : 
// Pascal's Triangle related queries:
// 1) Generate complete Pascal's Triangle up to n rows
// 2) Print nth row of Pascal's Triangle
// 3) Print element at row r and column c (1-indexed)
//
// Example :
// n = 5
// Pascal's Triangle:
// 1
// 1 1
// 1 2 1
// 1 3 3 1
// 1 4 6 4 1
//
// Constraint :
// 1 <= n, r, c <= 10^5
// Values fit in 64-bit, use long long


// 🔴 Approach 1 Brute Force : Generate Full Triangle (DP)
// TC : O(n^2), SC : O(n^2)
vector<vector<long long>> generateTriangle(int n) {

    vector<vector<long long>> tri(n);   // create vector with n rows

    for(int i = 0; i < n; i++) {

        tri[i].resize(i + 1);           // ith row has i+1 elements
        tri[i][0] = tri[i][i] = 1;      // first and last element are always 1

        // fill middle values using previous row formula
        for(int j = 1; j < i; j++) {
            tri[i][j] = tri[i - 1][j - 1] + tri[i - 1][j]; // nCk formula from above row
        }
    }
    return tri; // return full triangle
}


// 🔵 Approach 2 Better : Print nth Row Only (nCk Formula)
// TC : O(n), SC : O(1) extra
vector<long long> getRow(int n) {  // n is 1-indexed

    vector<long long> row;         // result row
    long long val = 1;             // first value is always 1
    row.push_back(1);

    // Using: C(n,k) = C(n,k−1) * (n−k)/k
    for (int k = 1; k < n; k++) {
        val = val * (n - k) / k;   // compute next binomial coefficient
        row.push_back(val);
    }
    return row;                   // return computed row
}


// 🟢 Approach 3 Optimal : Compute Single Element (nCr)
// TC : O(min(c, r-c)), SC : O(1)
long long getElement(int r, int c) {
    
    r--, c--;                      // convert from 1-index to 0-index

    if (c > r - c)                 // apply symmetry: C(n,k) == C(n, n-k)
        c = r - c;

    long long res = 1;            // start with C(r,0) = 1

    for (int i = 0; i < c; i++) {
        res *= (r - i);           // multiply numerator
        res /= (i + 1);           // divide denominator
    }
    return res;                   // return computed element
}


// ===================== main for testing =====================
int main() {

    int n = 5;

    // ===================== Approach 1: Full Triangle =====================
    cout << "Pascal Triangle (Brute DP Approach, n=" << n << "):" << endl;
    vector<vector<long long>> tri = generateTriangle(n);
    for (auto &row : tri) {
        for (auto &x : row) cout << x << " ";
        cout << endl;
    }

    // ===================== Approach 2: Get nth Row =====================
    cout << "\n" << n << "th Row (Better nCk formula): ";
    vector<long long> rowN = getRow(n);
    for (auto x : rowN) cout << x << " ";

    // ===================== Approach 3: Get Element at (r,c) =====================
    int r = 5, c = 3;
    cout << "\n\nElement at r=" << r << ", c=" << c 
         << " (Optimal nCr): " << getElement(r, c) << endl;

    return 0;
}



/*
===========================
Dry Run Example for getRow(5)
Row index uses 1-index.

k=0 → val = 1
k=1 → val = 1 * (5-1)/1 = 4
k=2 → val = 4 * (5-2)/2 = 6
k=3 → val = 6 * (5-3)/3 = 4
k=4 → val = 4 * (5-4)/4 = 1

Output: [1, 4, 6, 4, 1]


===========================
Additional Test Cases

Case 1:
n = 1
Output Triangle: [ [1] ]
getRow(1) → [1]
getElement(1,1) → 1

Case 2:
n = 4
Triangle:
1
1 1
1 2 1
1 3 3 1

Case 3:
getElement(r=6, c=2)
= C(5,1) = 5


===========================
Follow-Up Questions with Answers

Q1: Can we use modulo arithmetic (like 1e9+7)?
Yes. Use modular multiplication and modular inverse for division.

Q2: How to generate Pascal's Triangle in reverse?
Start from bottom row and move upward by reversing iteration.

Q3: Can Pascal's Triangle be extended to non-integer powers?
Yes. Generalized Binomial Theorem expands (x+y)^n for real/complex n.

Q4: Can we compute full nCr table faster?
Yes. Use factorial[] + inverseFactorial[] with Fermat's inverse for mod prime.

Q5: Can it be done using recursion?
Yes, using C(n,k) = C(n-1,k-1) + C(n-1,k), but it's slower without memoization.
*/
