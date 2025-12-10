#include <bits/stdc++.h>
using namespace std;

// 🧠 Problem :
// Given a 2D matrix (N x M), return all elements in spiral order
// (clockwise spiral traversal).
//
// Example :
// Input :
// 1 2 3
// 4 5 6
// 7 8 9
// Output : [1,2,3,6,9,8,7,4,5]
//
// Constraint :
// 1 <= N, M <= 10^5 (total elements N*M fits in memory)


// 🔴 Approach 1 Brute Force : Recursive Spiral Traversal
// Intuition :
// We maintain 4 boundaries: top, bottom, left, right.
// Print top row → right col → bottom row → left col
// Then recursively shrink boundaries and repeat.
//
// Algo :
// spiralRec(mat, ans, top=0, bottom=n-1, left=0, right=m-1)
// Inside function:
//   1. Traverse left → right (top row), top++
//   2. Traverse top → bottom (right col), right--
//   3. Traverse right → left (bottom row), bottom-- (if valid)
//   4. Traverse bottom → top (left col), left++ (if valid)
//   5. Recursively call again while boundaries valid
//
// TC : O(N*M)
// SC : O(N*M) recursion + output
// Edge cases :
// Single row / Single column / Empty matrix
void spiralRec(vector<vector<int>>& mat, vector<int>& ans,
               int top, int bottom, int left, int right) {
    if (top > bottom || left > right) return;

    for (int i = left; i <= right; i++) ans.push_back(mat[top][i]);
    top++;

    for (int i = top; i <= bottom; i++) ans.push_back(mat[i][right]);
    right--;

    if (top <= bottom) {
        for (int i = right; i >= left; i--) ans.push_back(mat[bottom][i]);
        bottom--;
    }

    if (left <= right) {
        for (int i = bottom; i >= top; i--) ans.push_back(mat[i][left]);
        left++;
    }

    spiralRec(mat, ans, top, bottom, left, right);
}


// 🔵 Approach 2 Better : Iterative 4-Pointer Method (Recommended for Interviews)
// Intuition :
// Use four boundaries: top, bottom, left, right
// Traversal order:
// 1. left → right  (top row)
// 2. top → bottom  (right col)
// 3. right → left  (bottom row) [if top <= bottom]
// 4. bottom → top  (left col)   [if left <= right]
//
// Algo :
// while boundaries valid:
//    traverse top row, top++
//    traverse right col, right--
//    traverse bottom row, bottom--
//    traverse left col, left++
//
// TC : O(N*M)
// SC : O(1) extra space
// Edge cases :
// Works for 1xN, Nx1, empty matrix
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& mat) {
        vector<int> ans;
        if (mat.empty()) return ans;

        int n = mat.size(), m = mat[0].size();
        int top = 0, bottom = n - 1;
        int left = 0, right = m - 1;

        while (top <= bottom && left <= right) {

            for (int i = left; i <= right; i++)
                ans.push_back(mat[top][i]);
            top++;

            for (int i = top; i <= bottom; i++)
                ans.push_back(mat[i][right]);
            right--;

            if (top <= bottom) {
                for (int i = right; i >= left; i--)
                    ans.push_back(mat[bottom][i]);
                bottom--;
            }

            if (left <= right) {
                for (int i = bottom; i >= top; i--)
                    ans.push_back(mat[i][left]);
                left++;
            }
        }
        return ans;
    }
};


// 🟢 Approach 3 Optimal : Direction Array Method
// Intuition :
// Use directions: Right, Down, Left, Up
// Track visited cells and change direction when hitting boundaries.
//
// Algo :
// dir = 0 (right)
// directions = [(0,1),(1,0),(0,-1),(-1,0)]
// while count < n*m:
//     ans.push(mat[i][j])
//     move in directions[dir]
//     if out of bounds or visited:
//         revert step, change dir = (dir+1)%4, move again
//
// TC : O(N*M)
// SC : O(N*M) visited array
// Edge cases :
// Handles all size matrices
vector<int> spiralOrderDir(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();
    vector<int> ans;
    vector<vector<int>> vis(n, vector<int>(m, 0));

    int i = 0, j = 0, dir = 0;
    vector<pair<int,int>> d = {{0,1},{1,0},{0,-1},{-1,0}}; // R,D,L,U

    for (int k = 0; k < n*m; k++) {
        ans.push_back(mat[i][j]);
        vis[i][j] = 1;

        int ni = i + d[dir].first;
        int nj = j + d[dir].second;

        if (ni<0 || nj<0 || ni>=n || nj>=m || vis[ni][nj]) {
            dir = (dir + 1) % 4;
            ni = i + d[dir].first;
            nj = j + d[dir].second;
        }
        i = ni; j = nj;
    }
    return ans;
}


int main() {
    vector<vector<int>> mat = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    Solution obj;
    vector<int> result = obj.spiralOrder(mat);

    for (int x : result) cout << x << " ";
    return 0;
}


/*
===========================
Dry Run Example
Input:
1 2 3
4 5 6
7 8 9

top=0, bottom=2, left=0, right=2

1st row → [1,2,3], top=1
right col → [6,9], right=1
bottom row → [8,7], bottom=1
left col → [4], left=1

Matrix done.

Output:
[1,2,3,6,9,8,7,4,5]


===========================
Additional Test Cases
Case 1:
[1 2 3 4]
Output: [1,2,3,4]

Case 2:
1
2
3
Output: [1,2,3]

Case 3:
[1 2]
[3 4]
Output: [1,2,4,3]

*/

/*
===========================
Follow-Up Questions with Answers
===========================

Q1: How to print spiral in anti-clockwise direction?
Answer:
Reverse the movement order:
Instead of → Down → ← Up
Use ↓ Right ↑ Left.
Boundaries logic remains the same, just change traversal order:
1) Traverse top → bottom (left column)
2) Traverse left → right (bottom row)
3) Traverse bottom → top (right column)
4) Traverse right → left (top row)

-----------------------------------

Q2: Can we print reverse spiral (spiral from inside to outside)?
Answer:
Yes. You can:
Option A:
  First extract the normal spiral in a list, then reverse the list.
Option B:
  Start boundaries from the center layer and expand outwards layer-by-layer.

-----------------------------------

Q3: Can we return spiral order layer-by-layer (list of lists)?
Answer:
Yes. Instead of pushing values directly into one array,
push each layer’s traversal into a separate temporary list
and add that list to the final result (vector<vector<int>>).  
This is helpful for ring-by-ring visualizations.

-----------------------------------

Q4: Can we do spiral traversal on a linked matrix (each cell has 4 pointers)?
Answer:
Yes, logic remains same but pointer movement changes:
Instead of index movement i++, j-- etc., use:
node = node->right, node->down, node->left, node->up
You still need visited tracking or boundary control.

-----------------------------------

Q5: Can we modify matrix while traversing in spiral?
Answer:
Yes, but only if modifications do not affect boundary conditions.
Safe modifications:
  - Replace values
  - Mark visited cells
Not safe:
  - Changing matrix dimensions
  - Reordering rows/columns during traversal

-----------------------------------

Q6: How to handle very large matrix where recursion may overflow?
Answer:
Use the iterative 4-pointer method (Better/Optimal approach).
It avoids stack depth issues and is interview recommended.

-----------------------------------

Q7: What if the matrix is not rectangular or contains jagged rows?
Answer:
Spiral traversal requires well-defined boundaries.
For jagged arrays:
  - Normalize by padding missing values, or
  - Use visited[][] check + direction array based traversal.

-----------------------------------

Q8: How to convert spiral traversal into anti-spiral (outer to inner, reversed)?
Answer:
Perform normal spiral traversal, store result in a list,
then reverse the list, OR
start boundaries from outermost and push while shrinking inwards,
but append to a stack to reverse order.

-----------------------------------
*/
