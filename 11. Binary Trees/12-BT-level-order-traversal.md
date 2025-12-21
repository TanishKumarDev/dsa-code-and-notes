# BINARY TREE — LEVEL ORDER TRAVERSAL (BFS)

---

## What We Covered Here

1. What level order traversal means
2. Difference between DFS and BFS
3. Why queue is mandatory for level order traversal
4. Core BFS idea: process tree level by level
5. Algorithm for level order traversal
6. Why we use `queue.size()` for each level
7. Step-by-step dry run (very detailed)
8. C++ implementation (clean + deeply commented)
9. JavaScript implementation (clean + deeply commented)
10. Time & space complexity (why O(N))
11. Common mistakes and interview traps
12. Interview-level Q&A synthesis

---

## 1. What Is Level Order Traversal? (Mindset First)

**Level Order Traversal** means:

> Visit nodes **level by level**, from **left to right**

Example:

```
        1
       / \
      2   3
     / \
    4   5
```

Output:

```
[
  [1],
  [2, 3],
  [4, 5]
]
```

This traversal is also called:

> **Breadth First Search (BFS)**

---

## 2. DFS vs BFS (Must Be Clear)

| Traversal   | Strategy      | Tool Used         |
| ----------- | ------------- | ----------------- |
| Pre/In/Post | Depth first   | Recursion / Stack |
| Level Order | Breadth first | Queue             |

Key difference:

* DFS goes **deep**
* BFS goes **wide**

---

## 3. Why Queue Is Mandatory (Important Insight)

Queue follows **FIFO**:

```
First In → First Out
```

This perfectly matches **level-by-level processing**.

> Nodes discovered earlier (upper levels)
> must be processed before deeper nodes.

---

## 4. Core BFS Idea (One-Line)

> Put root in queue →
> process nodes level-wise →
> push children into queue

---

## 5. Algorithm (Clear and Structured)

1. If tree is empty → return empty result
2. Push root into queue
3. While queue is not empty:

   * Find number of nodes at current level (`size = queue.size()`)
   * Process exactly `size` nodes:

     * Pop node
     * Store its value
     * Push its children (if any)
   * Store current level result

---

## 6. Why `queue.size()` Is CRITICAL (Interview Trap)

At the start of each level:

```
queue contains ONLY nodes of that level
```

So:

* `queue.size()` = number of nodes in current level
* Looping `size` times ensures:

  * You don’t mix levels
  * Children go to **next level**

Without this, level separation breaks.

---

## 7. Example Tree (We Will Dry Run This)

```
            1
          /   \
         2     3
        / \
       4   5
```

Expected Output:

```
[
  [1],
  [2, 3],
  [4, 5]
]
```

---

## 8. Dry Run — Step by Step (Very Deep)

### Initial State

```
queue = [1]
answer = []
```

---

### Level 1

* `queue.size() = 1`
* Process 1 node

| Action    | Queue  | Level |
| --------- | ------ | ----- |
| Pop 1     | []     | [1]   |
| Push 2, 3 | [2, 3] | [1]   |

Add level:

```
answer = [[1]]
```

---

### Level 2

* `queue.size() = 2`
* Process 2 nodes

| Action   | Queue   | Level |
| -------- | ------- | ----- |
| Pop 2    | [3]     | [2]   |
| Push 4,5 | [3,4,5] | [2]   |
| Pop 3    | [4,5]   | [2,3] |

Add level:

```
answer = [[1], [2,3]]
```

---

### Level 3

* `queue.size() = 2`

| Action | Queue | Level |
| ------ | ----- | ----- |
| Pop 4  | [5]   | [4]   |
| Pop 5  | []    | [4,5] |

Add level:

```
answer = [[1], [2,3], [4,5]]
```

Queue empty → stop.

---

## 9. C++ — Level Order Traversal (Core Logic)

### Version 1 — Only Required Function

```cpp
vector<vector<int>> levelOrder(TreeNode* root) {

    vector<vector<int>> ans;
    if (root == nullptr) return ans;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();
        vector<int> level;

        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();

            level.push_back(node->data);

            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        ans.push_back(level);
    }
    return ans;
}
```

---

## 10. C++ — Full Program (Deep Commented)

```cpp
#include <bits/stdc++.h>
using namespace std;

// Tree node structure
struct TreeNode {
    int data;             // Value stored
    TreeNode* left;       // Left child
    TreeNode* right;      // Right child

    TreeNode(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {

        vector<vector<int>> ans;

        // Edge case: empty tree
        if (root == nullptr) {
            return ans;
        }

        // Queue for BFS
        queue<TreeNode*> q;
        q.push(root);

        // BFS traversal
        while (!q.empty()) {

            // Number of nodes at current level
            int size = q.size();
            vector<int> level;

            // Process one full level
            for (int i = 0; i < size; i++) {

                TreeNode* node = q.front();
                q.pop();

                // Store node value
                level.push_back(node->data);

                // Push children for next level
                if (node->left != nullptr) {
                    q.push(node->left);
                }
                if (node->right != nullptr) {
                    q.push(node->right);
                }
            }

            // Store current level
            ans.push_back(level);
        }

        return ans;
    }
};

int main() {

    /*
            Tree:
                1
              /   \
             2     3
            / \
           4   5
    */

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    Solution sol;
    vector<vector<int>> result = sol.levelOrder(root);

    for (auto level : result) {
        for (int val : level) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
```

---

## 11. JavaScript — Level Order Traversal

```javascript
function levelOrder(root) {
    let result = [];
    if (root === null) return result;

    let queue = [];
    queue.push(root);

    while (queue.length > 0) {
        let size = queue.length;
        let level = [];

        for (let i = 0; i < size; i++) {
            let node = queue.shift();
            level.push(node.data);

            if (node.left !== null) queue.push(node.left);
            if (node.right !== null) queue.push(node.right);
        }

        result.push(level);
    }

    return result;
}
```

---

## 12. Time & Space Complexity (Deep Explanation)

### Time Complexity — **O(N)**

Why?

* Each node is:

  * Enqueued once
  * Dequeued once
* Constant work per node

So total = **O(N)**

---

### Space Complexity — **O(N)**

Why?

* Queue can hold up to:

  * All nodes at widest level
* Worst case: last level contains N/2 nodes

Hence:

```
Space = O(N)
```

---

## 13. Common Mistakes (Interview Traps)

1. Forgetting `queue.size()` → levels mix
2. Using recursion instead of queue
3. Printing flat array instead of 2D vector
4. Assuming space is O(log N) always (wrong)

---

## 14. Interview-Level Q&A Synthesis

### Q1. Why BFS for level order?

Because BFS naturally processes nodes level-wise.

---

### Q2. Can we do level order using recursion?

Yes (height-based), but inefficient.

---

### Q3. What if tree is skewed?

Queue size stays small, but still O(N) space overall.

---

### Q4. Difference between BFS and DFS?

BFS uses queue, DFS uses stack/recursion.

---

### Q5. Where is level order used?

* Tree views (left/right/top)
* Shortest path problems
* Serialization/deserialization

---

## Key Takeaway (Lock This)

> **Level Order = BFS = Queue**
> `queue.size()` separates levels — never skip it.
