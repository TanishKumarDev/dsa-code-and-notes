#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Given a matrix, if any element is 0, set its entire row and column to 0.

Example:
Input:
1 1 1
1 0 1
1 1 1

Output:
1 0 1
0 0 0
1 0 1

Constraints:
1 <= n, m <= 2000
Matrix may contain any integer values
We need to modify matrix in-place.
*/


// ============================================================================
// Approach 1: Brute Force (Mark rows and columns immediately)
// ============================================================================
// Intuition (Hinglish):
// Jab bhi kisi element mat[i][j] me 0 mile, turant us row aur column ko
// mark kar do, lekin directly 0 mat daalo warna chain reaction ho jayega
// aur galat results aayenge.
// Isliye hum non-zero values ko temporary -1 se mark karte hain, aur end me
// jitne bhi -1 hain unhe 0 bana dete hain.
//
// Algo:
// For every cell (i,j):
//   If mat[i][j] == 0:
//      mark entire row i (replace non-zero with -1)
//      mark entire col j (replace non-zero with -1)
// After loops, convert -1 → 0
//
// TC: O(n*m*(n+m))  worst approx O(n^3)
// SC: O(1) extra
//
// Edge cases:
// Works with negative numbers
// Matrix of size 1x1
// Multiple zeros
void markRow(vector<vector<int>>& mat, int r, int m) {
    for (int j = 0; j < m; j++)
        if (mat[r][j] != 0) mat[r][j] = -1;
}
void markCol(vector<vector<int>>& mat, int c, int n) {
    for (int i = 0; i < n; i++)
        if (mat[i][c] != 0) mat[i][c] = -1;
}
void bruteSetZeroes(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();

    // First marking
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == 0) {
                markRow(mat, i, m);
                markCol(mat, j, n);
            }
        }
    }

    // Replace all -1 with 0
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mat[i][j] == -1) mat[i][j] = 0;
}


// ============================================================================
// Approach 2: Better (Use row[] and col[] arrays)
// ============================================================================
// Intuition:
// First pass: record which row/col contains zero.
// Second pass: set cell = 0 if row[i] or col[j] is marked.
//
// TC: O(n*m)
// SC: O(n + m)
//
// Edge cases handled:
// Duplicate zeros
// Works for large matrices
void betterSetZeroes(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();
    vector<int> row(n, 0), col(m, 0);

    // Scan matrix and mark rows and columns that need zeroing
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mat[i][j] == 0) {
                row[i] = 1;
                col[j] = 1;
            }

    // Set zeroes accordingly
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (row[i] == 1 || col[j] == 1)
                mat[i][j] = 0;
}


// ============================================================================
// Approach 3: Optimal (Use 1st row and 1st column as markers)
// ============================================================================
// Intuition:
// Use matrix itself to store which row and col should be zero.
// mat[i][0] -> tells if row i should be zero
// mat[0][j] -> tells if col j should be zero
//
// col0 flag tracks if first column should become zero.
//
// Steps:
// 1) Mark rows/cols using first row and col
// 2) Fill inner submatrix
// 3) Handle first row if mat[0][0] == 0
// 4) Handle first column if col0 == 0
//
// TC: O(n*m)
// SC: O(1)
//
// Edge cases:
// When first row or first column originally has zero
void optimalSetZeroes(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();
    int col0 = 1;  // tracks if first col needs to be zero

    // Step 1: mark first row & col
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == 0) {
                mat[i][0] = 0;
                if (j != 0)
                    mat[0][j] = 0;
                else
                    col0 = 0;
            }
        }
    }

    // Step 2: fill internal matrix
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++)
            if (mat[i][0] == 0 || mat[0][j] == 0)
                mat[i][j] = 0;

    // Step 3: handle first row
    if (mat[0][0] == 0)
        for (int j = 0; j < m; j++) mat[0][j] = 0;

    // Step 4: handle first column
    if (col0 == 0)
        for (int i = 0; i < n; i++) mat[i][0] = 0;
}


// ====================== UTILITY: PRINT MATRIX ======================
void printMatrix(const vector<vector<int>>& mat) {
    for (auto &row : mat) {
        for (auto &x : row) cout << x << " ";
        cout << endl;
    }
}


// ============================================================================
// main() for testing
// ============================================================================
int main() {

    vector<vector<int>> arr = {
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
    };

    cout << "Original Matrix:" << endl;
    printMatrix(arr);

    vector<vector<int>> a1 = arr, a2 = arr, a3 = arr;

    bruteSetZeroes(a1);
    cout << "\nBrute Set Zeroes:" << endl;
    printMatrix(a1);

    betterSetZeroes(a2);
    cout << "\nBetter Set Zeroes:" << endl;
    printMatrix(a2);

    optimalSetZeroes(a3);
    cout << "\nOptimal Set Zeroes:" << endl;
    printMatrix(a3);

    return 0;
}


/*
==========================
Dry Run Example
Input:
1 1 1
1 0 1
1 1 1

Brute output:
1 0 1
0 0 0
1 0 1

Better output:
1 0 1
0 0 0
1 0 1

Optimal output:
1 0 1
0 0 0
1 0 1

==========================
Additional Test Cases
Case 1:
1-row matrix:
[1 0 3 4]
Output:
[0 0 0 0]

Case 2:
1-col matrix:
[5]
[0]
[7]
Output:
[0]
[0]
[0]

Case 3:
Multiple zeros:
[1 2 3]
[4 0 6]
[0 8 9]
Output:
[0 0 3]
[0 0 0]
[0 0 0]

Case 4:
All zeros:
Output remains all zeros.
*/
