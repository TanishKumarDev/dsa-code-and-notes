## Problem: BFS of Graph

* https://www.geeksforgeeks.org/problems/bfs-traversal-of-graph/1

**Problem Statement**:

Ek connected undirected graph diya hai, jisme `V` vertices hain, represented as an adjacency list `adj[][]`, jahan `adj[i]` vertex `i` ke neighbors ka list hai. Humein vertex `0` se shuru karke **Breadth-First Search (BFS)** traversal karna hai, aur vertices ko left-to-right order mein visit karna hai, jaise `adj` list mein diye hain. Final output mein BFS traversal ka list return karna hai.

**Breakdown**:

- **Input**:
  - `V`: Number of vertices (0 to V-1).
  - `adj[][]`: Adjacency list jisme `adj[i]` vertex `i` ke neighbors ka list hai.
- **Output**:
  - `vector<int>`: BFS traversal ka result, starting from vertex 0, in the order of adjacency list.
- **What We Need to Do**: BFS use karke graph ka traversal karna hai, vertex 0 se shuru karke, aur neighbors ko given order mein visit karna hai.
- **Why is This a Problem?**: BFS traversal graph ke structure ko level-wise explore karta hai, jo shortest path, connected components, aur network analysis mein use hota hai.
- **Hinglish**: Bhai, ek undirected graph hai, vertex 0 se BFS chala ke saare nodes visit karenge, aur neighbors ko adj list ke order mein add karenge.

**Constraints**:

- `1 ≤ V ≤ 10^4`
- `1 ≤ adj[i][j] ≤ 10^4`
- Graph is **connected** aur **undirected**.
- Neighbors ko adjacency list ke order mein visit karna hai.

**Examples**:

- Input: `adj = [[2,3,1], [0], [0,4], [0], [2]]`
  - Output: `[0, 2, 3, 1, 4]`
  - Explanation: Vertex 0 se shuru, neighbors [2,3,1] visit kiye (2, 3, 1), phir 2 ka neighbor 4 visit kiya.
- Input: `adj = [[1,2], [0,2], [0,1,3,4], [2], [2]]`
  - Output: `[0, 1, 2, 3, 4]`
  - Explanation: Vertex 0 se shuru, neighbors [1,2], phir 2 ke neighbors [3,4] visit kiye.

**Key Definitions**:

- **Undirected Graph**: Graph jisme edges dono direction mein kaam karte hain (no arrows).
- **BFS**: Breadth-First Search, jisme queue use karke level-wise nodes explore karte hain.
- **Adjacency List**: Har vertex ke liye ek list jisme uske neighbors hote hain.
- **Hinglish**: Graph mein edges dono taraf jaate hain, BFS se queue ke saath level-wise nodes visit karenge.

**Why This is a Graph Question?**:

- Yeh problem undirected graph ke traversal ka hai, jisme adjacency list se connections pata chalte hain.
- BFS se hum level-wise nodes visit karte hain, jo given order mein output deta hai.
- **Hinglish**: Bhai, yeh graph ka sawal hai kyunki vertices aur edges hain, aur BFS se level-wise traversal karna hai.

**Company Tags**:
- Flipkart, Amazon, Microsoft, Samsung, Ola Cabs, Adobe, SAP Labs.

---

### Concept: What, Why, How

**What**:
- Humein ek undirected graph ka BFS traversal karna hai, vertex 0 se shuru karke, aur neighbors ko adjacency list ke order mein visit karna hai.
- Output ek list hai jo BFS order mein vertices deta hai.

**Why**:
- BFS traversal ka use hota hai:
  - **Shortest Path**: Unweighted graphs mein shortest path nikalne ke liye.
  - **Connected Components**: Graph ke groups identify karne ke liye.
  - **Network Analysis**: Social networks ya connectivity check karne ke liye.
- **Hinglish**: Bhai, BFS se level-wise exploration hota hai, jo shortest path ya groups find karne ke kaam aata hai.

**How**:
- BFS use karenge:
  - Ek queue banao aur vertex 0 ko queue mein daal do.
  - Ek visited array banao to track visited vertices.
  - Jab tak queue khali nahi hoti:
    - Queue se node pop karo, usko result mein add karo.
    - Uske saare neighbors (adj list ke order mein) check karo.
    - Jo neighbors unvisited hain, unko queue mein daal do aur visited mark karo.
  - Result array return karo.
- **Hinglish**: Queue mein 0 daalo, visited array banao. Pop karke node result mein daalo, uske neighbors queue mein daalo agar unvisited hain.

---

### Intuition

- BFS level-wise traversal deta hai, matlab pehle vertex 0, phir uske direct neighbors, phir unke neighbors, etc.
- `adj` list ke order mein neighbors visit karna hai, so hum loop mein neighbors ko sequentially process karenge.
- Visited array ensure karta hai ki koi node dobara visit na ho, kyunki graph undirected hai aur cycles ho sakte hain.
- **Key Insight**: Queue se level-wise processing hoti hai, aur visited array duplicate visits rokta hai.
- **Hinglish**: Bhai, BFS se pehle 0, phir uske neighbors, phir unke neighbors visit honge. Visited array se dobara visit nahi hoga.

---

### Algorithm

1. Ek `visited` array banao size `V`, sab false initially.
2. Ek queue banao aur vertex 0 ko queue mein daal do, visited[0] = true.
3. Ek result array banao BFS order store karne ke liye.
4. Jab tak queue khali nahi hoti:
   - Queue se node pop karo, usko result mein add karo.
   - Uske neighbors (`adj[node]`) ke liye loop chala ke:
     - Agar neighbor unvisited hai, to queue mein daal do aur visited mark karo.
5. Result array return karo.
6. **Hinglish**: Visited array banao, 0 ko queue mein daalo. Pop karke result mein daalo, neighbors ko check karo, unvisited ko queue mein daalo.

---

### Pseudocode

```cpp
function bfsOfGraph(V, adj):
    visited = array of size V, all false
    queue = empty queue
    result = empty array
    queue.push(0)
    visited[0] = true
    while queue is not empty:
        node = queue.pop()
        result.append(node)
        for each neighbor in adj[node]:
            if not visited[neighbor]:
                queue.push(neighbor)
                visited[neighbor] = true
    return result
```

---

### Code (Using Teacher’s Style with Comments and Naming)

Tere teacher ke style mein code likh raha hu, with clear comments aur variable names jo unke lecture ke hisaab se samajh aayein. Main `visited`, `q`, aur `result` ka use karunga, aur `adj` list directly process karunga.

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    // Function to perform Breadth First Traversal of the given graph
    vector<int> bfs(vector<vector<int>> &adj) {
        int V = adj.size();                  // Number of vertices in the graph
        vector<bool> visited(V, false);      // Track visited nodes to avoid revisiting
        queue<int> q;                        // Queue to process nodes level by level
        vector<int> result;                  // Store BFS traversal order

        // Start BFS from vertex 0
        q.push(0);                           
        visited[0] = true;                   // Mark starting node as visited

        // Continue until there are no more nodes to process
        while(!q.empty()) {
            int node = q.front();            // Get the front node from queue
            q.pop();                         // Remove it from queue
            result.push_back(node);          // Add node to BFS traversal result

            // Visit all neighbors of the current node
            for(int neighbor : adj[node]) {
                // If neighbor is not visited, add it to the queue
                if(!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true; // Mark neighbor as visited
                }
            }
        }

        // Return the BFS traversal sequence
        return result;
    }
};

int main() {
    // Example input: adj = [[2,3,1], [0], [0,4], [0], [2]]
    int V = 5;
    vector<int> adj[V];
    adj[0] = {2, 3, 1};
    adj[1] = {0};
    adj[2] = {0, 4};
    adj[3] = {0};
    adj[4] = {2};

    // Get BFS traversal
    vector<int> bfs = bfsOfGraph(V, adj);
    cout << "BFS Traversal: ";
    for (int node : bfs) {
        cout << node << " ";
    }
    cout << endl;

    return 0;

  // 🔑 Explanation of the BFS Steps

  // Visited Array: Prevents revisiting nodes and infinite loops.

  // Queue: Ensures BFS processes nodes level by level (FIFO).

  // Push 0: BFS usually starts from node 0 (as per GFG / standard conventions).

  // Processing Queue: Pop the front node, add it to result, push unvisited neighbors.

  // Neighbors Check: Only push neighbors that haven’t been visited yet.

  // Result: Stores the exact BFS traversal order.
}
```

**Improvements Suggested**:
- Code clean hai, aur teacher ke style mein `visited`, `q`, aur `result` use kiya.
- Comments detailed hain taaki har step samajh aaye.
- `vector<bool>` use kiya for visited to optimize space, but `vector<char>` bhi use kar sakta hu for clarity.
- Main mein multiple test cases add kar sakta hu, bol agar chahiye.
- **Hinglish**: Bhai, code simple hai, adj list se direct BFS kiya. Agar tweaks ya extra test cases chahiye to bolna.

---

### Dry Run (Tabular Format)

**Example Input**:
- `V = 5`, `adj = [[2,3,1], [0], [0,4], [0], [2]]`
- Expected Output: `[0, 2, 3, 1, 4]`

| Step | Queue | Visited Array | Result | Action |
|------|-------|---------------|--------|--------|
| 1    | [0]   | [T, F, F, F, F] | []     | Start with vertex 0, push 0 to queue, visited[0]=true. |
| 2    | [2,3,1] | [T, F, T, T, F] | [0]    | Pop 0, add to result. Neighbors [2,3,1], all unvisited, push to queue, mark visited. |
| 3    | [3,1] | [T, F, T, T, T] | [0, 2] | Pop 2, add to result. Neighbor [0,4], 0 visited, push 4, visited[4]=true. |
| 4    | [1,4] | [T, F, T, T, T] | [0, 2, 3] | Pop 3, add to result. Neighbor [0], visited, no push. |
| 5    | [4]   | [T, T, T, T, T] | [0, 2, 3, 1] | Pop 1, add to result. Neighbor [0], visited, no push. |
| 6    | []    | [T, T, T, T, T] | [0, 2, 3, 1, 4] | Pop 4, add to result. Neighbor [2], visited, queue empty. |
| 7    | -     | -             | -      | Queue empty, return result. |

**Hinglish Explanation**:
- Step 1: 0 se shuru, queue mein 0, visited[0]=true.
- Step 2: 0 pop, result=[0]. Neighbors 2,3,1 unvisited, queue mein daale, visited mark kiye.
- Step 3: 2 pop, result=[0,2]. Neighbor 4 unvisited, queue mein daala.
- Step 4-5: 3, 1 pop, result=[0,2,3,1]. Koi naye neighbors nahi.
- Step 6: 4 pop, result=[0,2,3,1,4]. Queue khali, done.

**Dry Run for Another Input**:
- Input: `adj = [[1,2], [0,2], [0,1,3,4], [2], [2]]`
- Output: `[0, 1, 2, 3, 4]`

| Step | Queue | Visited Array | Result | Action |
|------|-------|---------------|--------|--------|
| 1    | [0]   | [T, F, F, F, F] | []     | Push 0, visited[0]=true. |
| 2    | [1,2] | [T, T, T, F, F] | [0]    | Pop 0, result=[0]. Neighbors [1,2], push, visited[1,2]=true. |
| 3    | [2]   | [T, T, T, F, F] | [0, 1] | Pop 1, result=[0,1]. Neighbors [0,2], both visited. |
| 4    | [3,4] | [T, T, T, T, T] | [0, 1, 2] | Pop 2, result=[0,1,2]. Neighbors [0,1,3,4], push 3,4, visited[3,4]=true. |
| 5    | [4]   | [T, T, T, T, T] | [0, 1, 2, 3] | Pop 3, result=[0,1,2,3]. Neighbor [2], visited. |
| 6    | []    | [T, T, T, T, T] | [0, 1, 2, 3, 4] | Pop 4, result=[0,1,2,3,4]. Neighbor [2], visited, queue empty. |

---

### Time Complexity (TC)

- **BFS**: Har node queue mein ek baar jata hai (`O(V)`), aur har edge ke liye neighbor check hota hai (`O(E)`).
- **Final TC**: `O(V + E)`, where `V` is vertices and `E` is edges in adjacency list.
- **Hinglish**: Bhai, har node aur edge ek baar visit hota hai, to time V + E hai.

### Space Complexity (SC)

- **Visited Array**: `O(V)`
- **Queue**: Worst case mein saare nodes, `O(V)`.
- **Result Array**: `O(V)`
- **Final SC**: `O(V)` (ignoring input adjacency list).
- **Hinglish**: Visited array, queue, aur result ke wajah se space V ke around hai.

---

### Key Points for Interview

- **Why BFS?**: BFS level-wise traversal deta hai, aur adjacency list ke order mein neighbors visit karna easy hai.
- **Why Undirected Graph?**: Edges dono direction mein hote hain, to visited array se cycles handle karte hain.
- **Edge Cases**:
  - `V=1`, empty adj list: `[0]`.
  - Fully connected graph: All nodes in BFS order.
- **Hinglish**: Interview mein BFS ka queue-based approach samjhao, visited array ka role clear karo, aur adj list ke order ka dhyan rakho.

---

### Additional Notes for Beginners

- **Why This Works**: BFS queue se level-wise nodes visit karta hai, aur visited array ensure karta hai ki undirected graph mein cycles ke wajah se dobara visit na ho.
- **Hinglish**: Bhai, BFS se level-wise nodes cover hote hain, aur visited array se dobara visit nahi hota.
- **Practice Cases**:
  - `adj=[[2,3,1], [0], [0,4], [0], [2]]` → `[0, 2, 3, 1, 4]`.
  - `adj=[[1,2], [0,2], [0,1,3,4], [2], [2]]` → `[0, 1, 2, 3, 4]`.
- **DFS Alternative**: DFS se bhi traversal ho sakta hai, but BFS level-wise order deta hai, jo is problem ke liye suitable hai.
- **Common Mistake**: Visited array na rakho to undirected graph mein infinite loop mein fas sakte ho. Ensure neighbors check karte waqt visited check karo.
