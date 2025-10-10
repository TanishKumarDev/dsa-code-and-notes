## Problem: Detect Cycle in Directed Graph using BFS

* https://www.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1

**Problem Statement**:

Ek directed graph diya hai, jisme `V` vertices (0 to V-1) aur edges hain, represented as an adjacency list `adj[][]` ya edge list `edges`. Humein check karna hai ki graph mein cycle hai ya nahi. Cycle ka matlab ek path jo same node pe wapas aaye through directed edges.

**Breakdown**:

- **Input**:
  - `V`: Number of vertices (0 to V-1).
  - `edges`: Vector of pairs `[u, v]` representing a directed edge from `u` to `v`.
  - `adj[][]`: Adjacency list jisme `adj[i]` mein vertex `i` ke saare neighbors (outgoing edges) hain.
- **Output**:
  - `true` agar cycle hai, else `false`.
- **What We Need to Do**: BFS (Kahn’s Algorithm) use karke topological sort try karna hai. Agar saare nodes visit nahi hote, to cycle hai.
- **Why is This a Problem?**: Cycle detection in directed graphs important hai for problems like course scheduling, dependency resolution, aur deadlock detection.
- **Hinglish**: Bhai, ek directed graph hai jisme edges ek hi direction mein hain. BFS se check karenge ki koi loop (cycle) hai ya nahi.

**Constraints**:

- `1 <= V <= 10^4`
- `0 <= edges.length <= 10^5`
- Graph directed hai, aur cycle ho sakta hai.
- Graph can be disconnected.

**Examples**:

- Input: `V = 4`, `edges = [[0,1], [0,2], [1,2], [2,0], [2,3], [3,3]]`
  - Output: `true`
  - Explanation: Cycle exists (0 → 1 → 2 → 0 and 3 → 3).
- Input: `V = 4`, `edges = [[0,1], [0,2], [1,2], [2,3]]`
  - Output: `false`
  - Explanation: No cycle, it’s a Directed Acyclic Graph (DAG).
- Input: `V = 2`, `edges = [[0,1]]`
  - Output: `false`
  - Explanation: No cycle, simple directed edge.

**Key Definitions**:

- **Directed Graph**: Graph jisme edges ek direction mein hote hain (arrows).
- **Cycle**: Ek path jo shuru aur end same node pe kare through directed edges.
- **In-degree**: Har node pe kitne incoming edges hain.
- **BFS (Kahn’s Algorithm)**: Queue-based algorithm jo in-degree use karta hai topological sort aur cycle detection ke liye.
- **Hinglish**: Graph mein arrows hain, aur BFS se in-degree check karke cycle detect karenge.

**Why This is a Graph Question?**:

- Yeh problem directed graph ke structure pe based hai, jisme edges directional hain.
- Cycle detection ke liye BFS (Kahn’s Algorithm) perfect hai kyunki agar topological sort complete nahi hota, to cycle hai.
- **Hinglish**: Bhai, yeh graph ka sawal hai kyunki nodes aur directed edges hain, aur cycle check karna hai BFS se.

---

### Concept: What, Why, How

**What**:
- Humein ek directed graph mein check karna hai ki cycle exist karta hai ya nahi.
- Cycle tab hota hai jab ek node se shuru karke wapas usi node pe directed edges ke through aayein.

**Why**:
- Cycle detection ka use hota hai:
  - **Course Scheduling**: Agar prerequisites mein cycle hai, to courses complete nahi ho sakte.
  - **Dependency Resolution**: Software builds mein cyclic dependencies detect karna.
  - **Deadlock Detection**: Operating systems mein resource dependencies check karna.
- **Hinglish**: Bhai, cycle check karna zaroori hai kyunki cycle hone se dependencies stuck ho jati hain.

**How**:
- BFS (Kahn’s Algorithm) use karenge:
  - Ek adjacency list banao edges se.
  - Har node ka in-degree calculate karo.
  - Jinka in-degree 0 hai, unko queue mein daal do.
  - Queue se nodes pop karo, counter increment karo, aur neighbors ke in-degree kam karo.
  - Agar kisi neighbor ka in-degree 0 ho jaye, to queue mein daal do.
  - Agar counter `V` ke barabar hai, to no cycle (`false`). Else, cycle hai (`true`).
- **Hinglish**: Graph banao, in-degree nikalo, 0 wale nodes queue mein daalo. Pop karke counter badhao, neighbors ke in-degree ghatate jao. Agar counter `V` nahi hua, to cycle hai.

---

### Intuition

- Directed graph mein cycle tab banta hai jab ek node se shuru karke wapas usi node pe pohoch jayein through directed edges.
- Kahn’s Algorithm topological sort try karta hai. Agar saare nodes visit nahi hote (counter < V), to cycle hai kyunki kuch nodes ke in-degree kabhi 0 nahi honge.
- **Key Insight**: In-degree 0 wale nodes independent hote hain. Agar cycle hai, to kuch nodes ke in-degree 0 nahi banenge, aur topological sort incomplete rahega.
- **Hinglish**: Bhai, soch, cycle hone se kuch nodes ke in-degree 0 nahi honge, to queue mein nahi jayenge, aur counter chhota rahega.

---

### Algorithm

1. Edges se adjacency list banao (`u → v` ke liye `adj[u].push(v)`).
2. Ek `indegree` array banao aur har node ka in-degree calculate karo.
3. Ek queue banao aur saare nodes jinka in-degree 0 hai, unko queue mein daal do.
4. Ek counter banao visited nodes track karne ke liye.
5. Jab tak queue khali nahi hoti:
   - Queue se node pop karo, counter increment karo.
   - Uske saare neighbors ke in-degree ek se kam karo.
   - Agar kisi neighbor ka in-degree 0 ho jaye, to queue mein daal do.
6. Agar counter `V` ke barabar hai, to return `false` (no cycle). Else, return `true` (cycle exists).
7. **Hinglish**: Graph banao, in-degree nikalo, 0 wale nodes queue mein daalo. Pop karke counter badhao, neighbors ke in-degree ghatate jao. Agar counter `V` nahi hua, to cycle hai.

---

### Pseudocode (Provided)

The pseudocode you shared is perfect for Kahn’s Algorithm. I’m including it here for reference:

```cpp
function isCycle(V, adj):
    indegree = array of size V initialized with 0

    // Step 1: Compute indegree of every vertex
    for u in [0..V-1]:
        for neighbor in adj[u]:
            indegree[neighbor] += 1

    // Step 2: Push all nodes with indegree = 0 into queue
    queue = empty queue
    for i in [0..V-1]:
        if indegree[i] == 0:
            queue.push(i)

    count = 0   // to count visited nodes

    // Step 3: BFS / Topological sort
    while queue is not empty:
        node = queue.pop()
        count += 1

        for neighbor in adj[node]:
            indegree[neighbor] -= 1
            if indegree[neighbor] == 0:
                queue.push(neighbor)

    // Step 4: If count != V → some nodes were never processed → cycle exists
    if count == V:
        return false   // no cycle
    else:
        return true    // cycle exists
```

---

### Code (Using Teacher’s Style with Comments and Naming)

Tere teacher ke style mein code likh raha hu, with clear comments aur variable names jo unke lecture ke hisaab se samajh aayein. Main `edges` se adjacency list banaunga aur Kahn’s Algorithm implement karunga.

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to detect cycle in a directed graph using BFS
    bool isCyclic(int V, vector<vector<int>>& edges) {
        // Step 1: Create adjacency list from edges
        vector<vector<int>> adj(V);
        vector<int> indegree(V, 0);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v); // Directed edge u -> v
            indegree[v]++;       // Increment in-degree of v
        }

        // Step 2: Initialize queue with nodes having in-degree 0
        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        // Step 3: BFS to process nodes
        int count = 0; // Count of visited nodes
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            count++; // Increment count for processed node

            // Reduce in-degree of all neighbors
            for (int neighbor : adj[node]) {
                indegree[neighbor]--;
                // If in-degree becomes 0, add to queue
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        // Step 4: If count equals V, no cycle; else cycle exists
        return count != V;
    }
};

int main() {
    // Test Case 1: Cycle exists
    int V = 4;
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 2}, {2, 0}, {2, 3}, {3, 3}};
    Solution sol;
    cout << "Test Case 1: " << (sol.isCyclic(V, edges) ? "Cycle Detected" : "No Cycle") << endl;

    // Test Case 2: No cycle
    V = 4;
    edges = {{0, 1}, {0, 2}, {1, 2}, {2, 3}};
    cout << "Test Case 2: " << (sol.isCyclic(V, edges) ? "Cycle Detected" : "No Cycle") << endl;

    return 0;
}
```

**Improvements Suggested**:
- Code clean hai, aur teacher ke style mein `adj`, `indegree`, aur `count` use kiya.
- Comments detailed hain taaki har step samajh aaye.
- `vector<vector<int>>` for adjacency list aur `vector<int>` for in-degree to avoid issues.
- Main mein multiple test cases add kiye for practice.
- **Hinglish**: Bhai, code solid hai, edges se adj list banaya, BFS se cycle check kiya. Agar aur tweaks ya test cases chahiye to bolna.

---

### Dry Run (Tabular Format)

**Example Input (Cycle Case)**:
- `V = 4`, `edges = [[0,1], [0,2], [1,2], [2,0], [2,3], [3,3]]`
- Expected Output: `true` (cycle exists: 0 → 1 → 2 → 0 and 3 → 3).

| Step | Queue | In-Degree Array | Count | Action |
|------|-------|-----------------|-------|--------|
| 1    | []    | [0, 1, 2, 2]   | 0     | Build adj: adj[0]=[1,2], adj[1]=[2], adj[2]=[0,3], adj[3]=[3]. In-degrees: [0,1,2,2]. No node with in-degree 0, queue empty. |
| 2    | -     | -               | 0     | Queue empty, count=0 < V=4, return true (cycle exists). |

**Hinglish Explanation**:
- Step 1: Edges se adj list banaya: 0 → 1,2; 1 → 2; 2 → 0,3; 3 → 3. In-degrees: [0,1,2,2]. Koi node in-degree 0 nahi, queue khali.
- Step 2: Count=0 < 4, cycle hai, return true.

**Example Input (No Cycle)**:
- `V = 4`, `edges = [[0,1], [0,2], [1,2], [2,3]]`
- Expected Output: `false` (no cycle, DAG).

| Step | Queue | In-Degree Array | Count | Action |
|------|-------|-----------------|-------|--------|
| 1    | [0]   | [0, 1, 1, 1]   | 0     | Build adj: adj[0]=[1,2], adj[1]=[2], adj[2]=[3], adj[3]=[]. In-degrees: [0,1,1,1]. Push 0 to queue. |
| 2    | [1,2] | [0, 0, 0, 1]   | 1     | Pop 0, count=1. Reduce in-degree of 1,2 to 0, push 1,2 to queue. |
| 3    | [2]   | [0, 0, 0, 1]   | 2     | Pop 1, count=2. Reduce in-degree of 2 to 0 (already 0). |
| 4    | [3]   | [0, 0, 0, 0]   | 3     | Pop 2, count=3. Reduce in-degree of 3 to 0, push 3 to queue. |
| 5    | []    | [0, 0, 0, 0]   | 4     | Pop 3, count=4. No neighbors, queue empty. |
| 6    | -     | -               | -     | Count=4 = V, return false (no cycle). |

**Hinglish Explanation**:
- Step 1: Adj list banaya: 0 → 1,2; 1 → 2; 2 → 3. In-degrees: [0,1,1,1]. Node 0 in-degree 0, queue mein daala.
- Step 2: 0 pop, count=1. 1,2 ke in-degree 0 hue, queue mein daale.
- Step 3-4: 1,2 pop, 3 ka in-degree 0 hua, queue mein daala.
- Step 5: 3 pop, count=4. Queue khali, count=V, return false.

---

### Time Complexity (TC)

- **Graph Construction**: Har edge ke liye adjacency list aur in-degree update, `O(edges.length)`.
- **BFS**: Har node queue mein ek baar jata hai (`O(V)`), aur har edge ke liye in-degree kam hota hai (`O(edges.length)`).
- **Final TC**: `O(V + edges.length)`.
- **Hinglish**: Bhai, graph banane aur BFS ke liye nodes aur edges ek baar dekhe, to time V + edges hai.

### Space Complexity (SC)

- **Adjacency List**: `O(edges.length)` for edges.
- **In-degree Array**: `O(V)`
- **Queue**: Worst case mein saare nodes, `O(V)`.
- **Final SC**: `O(V + edges.length)` (ignoring input).
- **Hinglish**: Adj list, in-degree array, aur queue ke wajah se space V + edges ke around hai.

---

### Key Points for Interview

- **Why BFS (Kahn’s Algorithm)?**: In-degree ka use karke topological sort try karte hain, agar complete nahi hota to cycle hai.
- **Why Directed Graph?**: Edges directional hote hain, to in-degree se dependencies track karna easy hai.
- **Edge Cases**:
  - `V=1`, `edges=[[0,0]]`: Cycle (`true`).
  - Empty edges: No cycle (`false`).
  - Disconnected DAG: No cycle (`false`).
- **Hinglish**: Interview mein in-degree ka concept samjhao, Kahn’s algorithm ka flow clear karo, aur counter se cycle detection dikhana.

---

### Additional Notes for Beginners

- **Why This Works**: Kahn’s Algorithm topological sort try karta hai. Agar saare nodes visit nahi hote, to cycle hai kyunki kuch nodes ke in-degree 0 nahi banenge.
- **Hinglish**: Bhai, agar topological sort poora nahi hua, to cycle hai. In-degree 0 wale nodes hi queue mein jaate hain.
- **Practice Cases**:
  - `V=4`, `edges=[[0,1], [0,2], [1,2], [2,0], [2,3], [3,3]]` → `true`.
  - `V=4`, `edges=[[0,1], [0,2], [1,2], [2,3]]` → `false`.
- **DFS Alternative**: DFS se bhi cycle detection ho sakta hai (visited aur recursion stack use karke). Agar chahta hai, to DFS wala code de sakta hu.
- **Common Mistake**: In-degree update bhool jao ya counter check na karo, to galat answer aayega. Ensure counter `V` se compare karo.
