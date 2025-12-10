#include <bits/stdc++.h>
using namespace std;

// 🧠 Problem : 
// Rotate a given N x N square matrix by 90 degrees clockwise.
// The rotation must be done in-place for the better/optimal approaches.
//
// Example : 
// Input :
// 1 2 3
// 4 5 6
// 7 8 9
//
// Output :
// 7 4 1
// 8 5 2
// 9 6 3
//
// Constraint :
// 1 <= N <= 10^3
// Matrix values may be any integer values.


// 🔴 Approach 1 Brute Force : 
// Intuition :
// Create a new matrix and directly place elements such that:
// rotated[j][n-1-i] = original[i][j]
// This formula rotates the element positions clockwise.
//
// Algo :
// Create new matrix result[N][N]
// for i = 0 to n-1:
//     for j = 0 to n-1:
//         result[j][n-i-1] = mat[i][j]
// return result
//
// TC : O(n^2)
// SC : O(n^2) extra space (because new matrix is created)
// Edge cases :
// Works for all matrix sizes including n=1
// Does not modify original matrix
vector<vector<int>> rotateBrute(vector<vector<int>>& mat) {
    int n = mat.size();
    vector<vector<int>> rotate(n, vector<int>(n));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            rotate[j][n - i - 1] = mat[i][j];
        }
    }
    return rotate;
}


// 🔵 Approach 2 Better : 
// Intuition :
// A 90-degree rotation can be achieved by:
// Step 1: Transpose the matrix  (swap mat[i][j] with mat[j][i])
// Step 2: Reverse each row
//
// Why it works?
// Transpose rearranges rows to columns,
// and reversing each row forms the 90-degree clockwise rotation.
//
// Algo :
// transpose the matrix
// for each row: reverse it
//
// TC : O(n^2)
// SC : O(1) (in-place)
// Edge cases :
// Matrix must be square (N x N)
// Works for negative values, zero, duplicates
void rotate(vector<vector<int>>& mat) {
    int n = mat.size();

    // Step 1: Transpose
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(mat[i][j], mat[j][i]);
        }
    }

    // Step 2: Reverse each row
    for (int i = 0; i < n; i++) {
        reverse(mat[i].begin(), mat[i].end());
    }
}


int main() {

    vector<vector<int>> mat = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

// 🧠 Problem : 
// Rotate a given N x N square matrix by 90 degrees clockwise.
// The rotation must be done in-place for the better/optimal approaches.
//
// Example : 
// Input :
// 1 2 3
// 4 5 6
// 7 8 9
//
// Output :
// 7 4 1
// 8 5 2
// 9 6 3
//
// Constraint :
// 1 <= N <= 10^3
// Matrix values may be any integer values.


// 🔴 Approach 1 Brute Force : 
// Intuition :
// Create a new matrix and directly place elements such that:
// rotated[j][n-1-i] = mat[i][j]
// This formula rotates the element positions clockwise.
//
// Algo :
// Create new matrix result[N][N]
// for i = 0 to n-1:
//     for j = 0 to n-1:
//         result[j][n-i-1] = mat[i][j]
// return result
//
// TC : O(n^2)
// SC : O(n^2) extra space (because new matrix is created)
// Edge cases :
// Works for all matrix sizes including n=1
// Does not modify original matrix
vector<vector<int>> rotateBrute(vector<vector<int>>& mat) {
    int n = mat.size();
    vector<vector<int>> rotate(n, vector<int>(n));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            rotate[j][n - i - 1] = mat[i][j];
        }
    }
    return rotate;
}


// 🔵 Approach 2 Better : 
// Intuition :
// A 90-degree rotation can be achieved by:
// Step 1: Transpose the matrix  (swap mat[i][j] with mat[j][i])
// Step 2: Reverse each row
//
// Why it works?
// Transpose rearranges rows to columns,
// and reversing each row forms the 90-degree clockwise rotation.
//
// Algo :
// transpose the matrix
// for each row: reverse it
//
// TC : O(n^2)
// SC : O(1) (in-place)
// Edge cases :
// Matrix must be square (N x N)
// Works for negative values, zero, duplicates
void rotate(vector<vector<int>>& mat) {
    int n = mat.size();

    // Step 1: Transpose
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(mat[i][j], mat[j][i]);
        }
    }

    // Step 2: Reverse each row
    for (int i = 0; i < n; i++) {
        reverse(mat[i].begin(), mat[i].end());
    }
}


// 🟢 Approach 3 Optimal: 
// Intuition :
// Same as Better approach (transpose + reverse rows).
// There is no faster approach in terms of time and space than O(n^2) and O(1)
// but this is considered optimal since it modifies in-place.
//
// Algo :
// Same as Approach 2
//
// TC : O(n^2)
// SC : O(1)
// Edge cases :
// If matrix is 1x1, output remains same.
// No extra memory is used.
void rotateOptimal(vector<vector<int>>& mat) {
    int n = mat.size();

    // Transpose
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(mat[i][j], mat[j][i]);
        }
    }

    // Reverse rows
    for (int i = 0; i < n; i++) {
        reverse(mat[i].begin(), mat[i].end());
    }
}


int main() {

    vector<vector<int>> mat = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    rotateOptimal(mat);

    for (auto &row : mat) {
        for (auto &x : row) cout << x << " ";
        cout << endl;
    }

    return 0;
}


/*
===========================
Dry Run for Approach 3 (Optimal)
===========================

Input matrix:
1 2 3
4 5 6
7 8 9

Step 1: Transpose (swap mat[i][j] with mat[j][i]):
i=0,j=1 swap → 2 and 4
i=0,j=2 swap → 3 and 7
i=1,j=2 swap → 6 and 8

Matrix becomes:
1 4 7
2 5 8
3 6 9

Step 2: Reverse each row:
Row 1: [1 4 7] → [7 4 1]
Row 2: [2 5 8] → [8 5 2]
Row 3: [3 6 9] → [9 6 3]

Final Rotated Matrix:
7 4 1
8 5 2
9 6 3

===========================
Additional Test Cases
===========================

Case 1:
Input:
[5]
Output:
[5]

Case 2:
Input:
1 2
3 4
Output:
3 1
4 2

Case 3:
Input:
1 2 3 4
5 6 7 8
9 1 2 3
4 5 6 7

Output:
4 9 5 1
5 1 6 2
6 2 7 3
7 3 8 4
*/

/*
===========================
Follow-Up Questions
===========================

Q1: Can we rotate the matrix by 90 degrees anti-clockwise?
Answer:
Yes. Two common methods:
Method A:
    Step 1: Transpose
    Step 2: Reverse each COLUMN
Method B:
    Use formula: rotated[n-j-1][i] = mat[i][j]

-----------------------------------

Q2: How to rotate matrix by 180 degrees?
Answer:
Option A: Apply 90-degree rotation twice.
Option B (Direct transformation):
    rotated[n-i-1][n-j-1] = mat[i][j]

-----------------------------------

Q3: How to rotate by 270 degrees (or 90 degrees counter-clockwise)?
Answer:
Rotate 90 degrees three times, OR use formula:
    rotated[n-j-1][i] = mat[i][j]

-----------------------------------

Q4: Can this rotation work for non-square matrix (MxN instead of NxN)?
Answer:
The in-place method requires a square matrix.
For non-square matrix, we must use extra space.

-----------------------------------

Q5: What is the space complexity difference between brute and optimal approaches?
Answer:
Brute  : O(n^2) extra space
Better/Optimal: O(1) extra space (in-place)

-----------------------------------

Q6: Can we do rotation without modifying the original matrix?
Answer:
Yes. Use the Brute Force approach that creates a new matrix
instead of modifying the input matrix.

-----------------------------------

Q7: What if the matrix contains extremely large numbers?
Answer:
Rotation logic does not depend on values, only positions.
Works fine for any integer range.

-----------------------------------

Q8: Is there a way to rotate using STL functions only?
Answer:
Yes, for optimal:
    Step 1: Transpose with swap
    Step 2: For each row: reverse(mat[i].begin(), mat[i].end())

-----------------------------------

Q9: What if asked to rotate k times?
Answer:
k = k % 4 (since 4 rotations = original matrix)
If k == 1 → 90 degrees
If k == 2 → 180 degrees
If k == 3 → 270 degrees

-----------------------------------

Q10: Can we rotate matrix in anti-clockwise direction in-place?
Answer:
Yes. Steps:
    Step 1: Transpose
    Step 2: Reverse each COLUMN instead of row
*/
