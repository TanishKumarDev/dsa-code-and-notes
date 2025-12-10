#include <bits/stdc++.h>
using namespace std;

/*
🧠 Problem:
Given an array a[] of size N containing numbers from 1 to N.
One number occurs twice (repeating), and one number is missing.
Find both numbers.

Example:
Input  : a = [1, 2, 3, 3, 5]
Output : repeating = 3, missing = 4

Constraints:
1 <= N <= 10^5
1 <= a[i] <= N
Array contains exactly one repeating and one missing value.
*/


// ============================================================================
// 🔴 Approach 1: Brute Force (Nested loops)
// Intuition:
// Count frequency of each number from 1 to N using two loops.
//
// Algo:
// For i from 1 to N:
//    count occurrences of i by scanning whole array
//    if count == 2 → repeating
//    if count == 0 → missing
//
// TC: O(N^2)
// SC: O(1)
// ============================================================================
vector<int> brute(vector<int>& a) {
    int n = a.size();
    int repeating = -1, missing = -1;

    for (int num = 1; num <= n; num++) {
        int cnt = 0;

        for (int j = 0; j < n; j++) {    // count frequency of num
            if (a[j] == num) cnt++;
        }

        if (cnt == 2) repeating = num;  // number appears twice
        if (cnt == 0) missing = num;    // number does not appear
    }
    return {repeating, missing};
}


// ============================================================================
// 🔵 Approach 2: Better (Using Hash/Frequency Array)
// Intuition:
// Maintain frequency array freq[1..N].
// freq[i] == 2 → repeating
// freq[i] == 0 → missing
//
// Algo:
// Create freq array of size N+1 initialized to 0
// Count frequencies
// Loop again to find repeating and missing
//
// TC: O(N)
// SC: O(N)
// ============================================================================
vector<int> better(vector<int>& a) {
    int n = a.size();
    vector<int> freq(n + 1, 0);

    for (int x : a) {
        freq[x]++;         // increment count of element
    }

    int repeating = -1, missing = -1;
    for (int i = 1; i <= n; i++) {
        if (freq[i] == 2) repeating = i;
        if (freq[i] == 0) missing = i;
    }
    return {repeating, missing};
}


// ============================================================================
// 🟢 Approach 3: Optimal (Math / Sum formulas)
// Intuition:
// Let repeating = X, missing = Y
//
// Sum formula:
// S  = 1 + 2 + ... + N = N(N+1)/2
// S2 = 1² + 2² + ... + N² = N(N+1)(2N+1)/6
//
// From array we get:
// S'  = sum(arr)
// S2' = sum(arr²)
//
// We have:
// S' - S = X - Y   ...(1)
// S2' - S2 = X² - Y² = (X - Y)(X + Y)  ...(2)
//
// From (2) / (1):
// X + Y = (S2'-S2)/(S'-S)
//
// Solve equations to find X and Y
//
// TC: O(N)
// SC: O(1)
// ============================================================================
vector<int> mathApproach(vector<int>& a) {
    long long n = a.size();
    long long Sn  = n * (n + 1) / 2;
    long long S2n = n * (n + 1) * (2 * n + 1) / 6;

    long long S = 0, S2 = 0;
    for (int x : a) {
        S  += x;           // sum of elements
        S2 += 1LL * x * x; // sum of squares
    }

    long long val1 = S - Sn;   // X - Y
    long long val2 = S2 - S2n; // X² - Y²

    val2 = val2 / val1;        // (X + Y)

    long long X = (val1 + val2) / 2; // repeating
    long long Y = X - val1;          // missing

    return {(int)X, (int)Y};
}


// ============================================================================
// 🟢 Approach 4: Optimal (XOR Bit Manipulation)
// Intuition:
// XOR of arr and [1..N] gives xr = X ^ Y
// Partition numbers by rightmost set bit to separate repeating and missing.
//
// Steps:
// 1) xr = XOR of all a[i] and XOR of 1..N
// 2) find a set bit that differs
// 3) XOR partition into two buckets → produces candidate numbers
// 4) check which occurs twice
//
// TC: O(N)
// SC: O(1)
// ============================================================================
vector<int> xorApproach(vector<int>& a) {
    int n = a.size();
    int xr = 0;

    for (int i = 0; i < n; i++) {
        xr ^= a[i];        // XOR array values
        xr ^= (i + 1);     // XOR numbers 1..N
    }

    int bit = xr & ~(xr - 1); // isolate rightmost set bit

    int zero = 0, one = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] & bit) one ^= a[i];
        else zero ^= a[i];

        if ((i + 1) & bit) one ^= (i + 1);
        else zero ^= (i + 1);
    }

    int cnt = 0;
    for (int x : a) if (x == zero) cnt++;

    if (cnt == 2) return {zero, one};  // zero is repeating
    return {one, zero};                // one is repeating
}


// ============================================================================
// main() to test all approaches
// ============================================================================
int main() {

    vector<int> a = {1, 2, 3, 3, 5};

    auto r1 = brute(a);
    auto r2 = better(a);
    auto r3 = mathApproach(a);
    auto r4 = xorApproach(a);

    cout << "Brute:         repeating=" << r1[0] << " missing=" << r1[1] << endl;
    cout << "Better:        repeating=" << r2[0] << " missing=" << r2[1] << endl;
    cout << "Math Optimal:  repeating=" << r3[0] << " missing=" << r3[1] << endl;
    cout << "XOR Optimal:   repeating=" << r4[0] << " missing=" << r4[1] << endl;

    return 0;
}


/*
========================= Dry Run (Math Approach) =========================
a = [1,2,3,3,5], n = 5

Sn  = 5*6/2 = 15
S2n = 5*6*11/6 = 55

Array sums:
S  = 1+2+3+3+5 = 14
S2 = 1+4+9+9+25 = 48

val1 = S - Sn  = 14 - 15 = -1   = X - Y
val2 = S2 - S2n = 48 - 55 = -7  = X² - Y²
X + Y = val2 / val1 = (-7)/(-1) = 7

Solve:
X - Y = -1
X + Y = 7
Add → 2X = 6 → X = 3
Y = X - (-1) = 3 + 1 = 4

Repeating = 3, Missing = 4


========================= Additional Test Cases =========================
Input:  [2,2]        → repeating=2, missing=1
Input:  [1,1,3,4,5]  → repeating=1, missing=2
Input:  [4,3,6,2,1,1]→ repeating=1, missing=5


========================= Follow-Up Questions =========================
Q1) Can we handle multiple repeating numbers?
Use frequency hashmap or bucket list of missing/repeating.

Q2) Can we solve for very large N (1e7+)?
Use XOR approach (O(1) memory) or Math approach (64-bit).

Q3) What if array contains zero or negative values?
This logic applies only when values are from 1 to N.

Q4) Can this be extended to find 2 missing numbers?
Yes, use XOR 2-missing approach.

Q5) Why XOR approach is optimal?
Constant space, bit-level separation avoids overflow issues.
*/
