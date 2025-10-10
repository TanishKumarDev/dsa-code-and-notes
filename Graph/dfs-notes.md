
## Problem: DFS of Graph

* https://www.geeksforgeeks.org/problems/depth-first-traversal-for-a-graph/1

**Problem Statement**:

Ek connected undirected graph diya hai, jisme `V` vertices hain, represented as an adjacency list `adj[][]`, jahan `adj[i]` vertex `i` ke neighbors ka list hai. Humein vertex `0` se shuru karke **Depth-First Search (DFS)** traversal karna hai, aur vertices ko left-to-right order mein visit karna hai, jaise `adj` list mein diye hain. Final output mein DFS traversal ka list return karna hai.

**Breakdown**:

- **Input**:
  - `V`: Number of vertices (0 to V-1).
  - `adj[][]`: Adjacency list jisme `adj[i]` vertex `i` ke neighbors ka list hai.
- **Output**:
  - `vector<int>`: DFS traversal ka result, starting from vertex 0, in the order of adjacency list.
- **What We Need to Do**: DFS use karke graph ka traversal karna hai, vertex 0 se shuru karke, aur neighbors ko given order mein visit karna hai.
- **Why is This a Problem?**: DFS traversal graph ke structure ko depth-wise explore karta hai, jo connected components, cycle detection, aur path finding mein use hota hai.
- **Hinglish**: Bhai, ek undirected graph hai, vertex 0 se DFS chala ke saare nodes visit karenge, aur neighbors ko adj list ke order mein explore karenge.

**Constraints**:

- `1 ≤ V ≤ 10^4`
- `1 ≤ adj[i][j] ≤ 10^4`
- Graph is **connected** aur **undirected**.
- Neighbors ko adjacency list ke order mein visit karna hai.

**Examples**:

- Input: `adj = [[2,3,1], [0], [0,4], [0], [2]]`
  - Output: `[0, 2, 4, 3, 1]`
  - Explanation: Vertex 0 se shuru, neighbor 2 visit kiya, phir 2 ka neighbor 4, phir backtrack karke 0 se 3 aur 1 visit kiye.
- Input: `adj = [[1,2], [0,2], [0,1,3,4], [2], [2]]`
  - Output: `[0, 1, 2, 3, 4]`
  - Explanation: Vertex 0 se shuru, neighbor 1 visit kiya, phir 1 se 2, phir 2 se 3 aur 4 visit kiye.

**Key Definitions**:

- **Undirected Graph**: Graph jisme edges dono direction mein kaam karte hain (no arrows).
- **DFS**: Depth-First Search, jisme hum ek node se shuru karke uske ek neighbor ko depth tak explore karte hain, phir backtrack karte hain.
- **Adjacency List**: Har vertex ke liye ek list jisme uske neighbors hote hain.
- **Hinglish**: Graph mein edges dono taraf jaate hain, DFS se ek node ke saath depth tak jaate hain, phir wapas aate hain.

**Why This is a Graph Question?**:

- Yeh problem undirected graph ke traversal ka hai, jisme adjacency list se connections pata chalte hain.
- DFS se hum depth-wise nodes visit karte hain, jo given order mein output deta hai.
- **Hinglish**: Bhai, yeh graph ka sawal hai kyunki vertices aur edges hain, aur DFS se depth-wise traversal karna hai.

**Company Tags**:
- Accolite, Amazon, Samsung, Intuit.

---

### Concept: What, Why, How

**What**:
- Humein ek undirected graph ka DFS traversal karna hai, vertex 0 se shuru karke, aur neighbors ko adjacency list ke order mein visit karna hai.
- Output ek list hai jo DFS order mein vertices deta hai.

**Why**:
- DFS traversal ka use hota hai:
  - **Connected Components**: Graph ke groups identify karne ke liye.
  - **Cycle Detection**: Graph mein cycles check karne ke liye.
  - **Path Finding**: Specific paths ya topologies explore karne ke liye.
- **Hinglish**: Bhai, DFS se depth-wise exploration hota hai, jo groups, cycles, ya paths find karne ke kaam aata hai.

**How**:
- DFS use karenge:
  - Ek visited array banao to track visited vertices.
  - Ek result array banao DFS order store karne ke liye.
  - Vertex 0 se DFS call karo:
    - Current node ko visited mark karo aur result mein add karo.
    - Uske neighbors (`adj[node]`) ke liye loop chala ke:
      - Agar neighbor unvisited hai, to uspe DFS call karo.
  - Result array return karo.
- **Hinglish**: Visited array banao, 0 se DFS shuru karo. Node ko result mein daalo, uske unvisited neighbors pe DFS call karo.

---

### Intuition

- DFS depth-wise traversal deta hai, matlab pehle ek neighbor ke saath poori depth tak jaate hain, phir backtrack karke dusre neighbors explore karte hain.
- `adj` list ke order mein neighbors visit karna hai, so hum loop mein neighbors ko sequentially process karenge.
- Visited array ensure karta hai ki koi node dobara visit na ho, kyunki graph undirected hai aur cycles ho sakte hain.
- **Key Insight**: DFS recursive calls se ek path ke saare nodes explore hote hain, aur visited array duplicate visits rokta hai.
- **Hinglish**: Bhai, DFS se ek neighbor ke saath poori depth tak jaate hain, phir wapas aake baaki neighbors dekhte hain. Visited array se dobara visit nahi hota.

---

### Algorithm

1. Ek `visited` array banao size `V`, sab false initially.
2. Ek `result` array banao DFS order store karne ke liye.
3. DFS function call karo vertex 0 ke liye:
   - Current node ko visited mark karo.
   - Node ko result mein add karo.
   - Uske neighbors (`adj[node]`) ke liye loop chala ke:
     - Agar neighbor unvisited hai, to uspe DFS call karo.
4. Result array return karo.
5. **Hinglish**: Visited array banao, 0 se DFS chala. Node ko result mein daalo, unvisited neighbors pe DFS call karo.

---

### Pseudocode

```cpp
function dfsOfGraph(V, adj):
    visited = array of size V, all false
    result = empty array
    dfs(0, adj, visited, result)
    return result

function dfs(node, adj, visited, result):
    visited[node] = true
    result.append(node)
    for each neighbor in adj[node]:
        if not visited[neighbor]:
            dfs(neighbor, adj, visited, result)
```

---

### Code (Using Teacher’s Style with Comments and Naming)

Tere teacher ke style mein code likh raha hu, with clear comments aur variable names jo unke lecture ke hisaab se samajh aayein. Main `visited` aur `result` ka use karunga, aur `adj` list directly process karunga.

```cpp
#include <bits/stdc++.h>
using namespace std;

// DFS function to traverse graph depth-wise
void dfs(int node, vector<int> adj[], vector<bool>& visited, vector<int>& result) {
    // Mark current node as visited and add to result
    visited[node] = true;
    result.push_back(node);

    // Check all neighbors of current node
    for (int neighbor : adj[node]) {
        // If neighbor is not visited, call DFS
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited, result);
        }
    }
}

// Function to perform DFS traversal starting from vertex 0
vector<int> dfsOfGraph(int V, vector<int> adj[]) {
    // Initialize visited array
    vector<bool> visited(V, false);
    // Result array to store DFS traversal
    vector<int> result;

    // Start DFS from vertex 0
    dfs(0, adj, visited, result);

    return result;
}

int main() {
    // Example input: adj = [[2,3,1], [0], [0,4], [0], [2]]
    int V = 5;
    vector<int> adj[V];
    adj[0] = {2, 3, 1};
    adj[1] = {0};
    adj[2] = {0, 4};
    adj[3] = {0};
    adj[4] = {2};

    // Get DFS traversal
    vector<int> dfs = dfsOfGraph(V, adj);
    cout << "DFS Traversal: ";
    for (int node : dfs) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
```

**Improvements Suggested**:
- Code clean hai, aur teacher ke style mein `visited` aur `result` use kiya.
- Comments detailed hain taaki har step samajh aaye.
- `vector<bool>` use kiya for visited to optimize space, but `vector<char>` bhi use kar sakta hu for clarity.
- Main mein multiple test cases add kar sakta hu, bol agar chahiye.
- **Hinglish**: Bhai, code simple hai, adj list se direct DFS kiya. Agar tweaks ya extra test cases chahiye to bolna.

---

### Dry Run (Tabular Format)

**Example Input**:
- `V = 5`, `adj = [[2,3,1], [0], [0,4], [0], [2]]`
- Expected Output: `[0, 2, 4, 3, 1]`

| Step | Node | Visited Array | Result | Action |
|------|------|---------------|--------|--------|
| 1    | 0    | [T, F, F, F, F] | [0]    | Start DFS(0), mark visited[0]=true, add 0 to result. |
| 2    | 2    | [T, F, T, F, F] | [0, 2] | Neighbors [2,3,1], call DFS(2) (first neighbor). Mark visited[2]=true, add 2. |
| 3    | 4    | [T, F, T, F, T] | [0, 2, 4] | Neighbors of 2: [0,4], 0 visited, call DFS(4). Mark visited[4]=true, add 4. |
| 4    | -    | [T, F, T, F, T] | [0, 2, 4] | Neighbors of 4: [2], visited. Backtrack to 2, then 0. |
| 5    | 3    | [T, F, T, T, T] | [0, 2, 4, 3] | Neighbors of 0: [3,1], call DFS(3). Mark visited[3]=true, add 3. |
| 6    | -    | [T, F, T, T, T] | [0, 2, 4, 3] | Neighbors of 3: [0], visited. Backtrack to 0. |
| 7    | 1    | [T, T, T, T, T] | [0, 2, 4, 3, 1] | Neighbors of 0: [1], call DFS(1). Mark visited[1]=true, add 1. |
| 8    | -    | [T, T, T, T, T] | [0, 2, 4, 3, 1] | Neighbors of 1: [0], visited. Backtrack, DFS complete. |

**Hinglish Explanation**:
- Step 1: 0 se shuru, visited[0]=true, result=[0].
- Step 2: Neighbor 2 pe DFS, visited[2]=true, result=[0,2].
- Step 3: 2 ka neighbor 4 pe DFS, visited[4]=true, result=[0,2,4].
- Step 4: Backtrack, koi naya neighbor nahi.
- Step 5-6: 0 ka neighbor 3 pe DFS, visited[3]=true, result=[0,2,4,3].
- Step 7-8: 0 ka neighbor 1 pe DFS, visited[1]=true, result=[0,2,4,3,1]. Done.

**Dry Run for Another Input**:
- Input: `adj = [[1,2], [0,2], [0,1,3,4], [2], [2]]`
- Output: `[0, 1, 2, 3, 4]`

| Step | Node | Visited Array | Result | Action |
|------|------|---------------|--------|--------|
| 1    | 0    | [T, F, F, F, F] | [0]    | DFS(0), visited[0]=true, add 0. |
| 2    | 1    | [T, T, F, F, F] | [0, 1] | Neighbors [1,2], call DFS(1). Visited[1]=true, add 1. |
| 3    | 2    | [T, T, T, F, F] | [0, 1, 2] | Neighbors of 1: [0,2], call DFS(2). Visited[2]=true, add 2. |
| 4    | 3    | [T, T, T, T, F] | [0, 1, 2, 3] | Neighbors of 2: [0,1,3,4], call DFS(3). Visited[3]=true, add 3. |
| 5    | -    | [T, T, T, T, F] | [0, 1, 2, 3] | Neighbors of 3: [2], visited. Backtrack to 2. |
| 6    | 4    | [T, T, T, T, T] | [0, 1, 2, 3, 4] | Neighbors of 2: [4], call DFS(4). Visited[4]=true, add 4. |
| 7    | -    | [T, T, T, T, T] | [0, 1, 2, 3, 4] | Neighbors of 4: [2], visited. Backtrack, DFS complete. |

---

### Time Complexity (TC)

- **DFS**: Har node ek baar visit hota hai (`O(V)`), aur har edge ke liye neighbor check hota hai (`O(E)`).
- **Final TC**: `O(V + E)`, where `V` is vertices and `E` is edges in adjacency list.
- **Hinglish**: Bhai, har node aur edge ek baar visit hota hai, to time V + E hai.

### Space Complexity (SC)

- **Visited Array**: `O(V)`
- **Result Array**: `O(V)`
- **Recursion Stack**: Worst case mein depth `O(V)` ho sakti hai.
- **Final SC**: `O(V)` (ignoring input adjacency list).
- **Hinglish**: Visited array, result, aur recursion stack ke wajah se space V ke around hai.

---

### Key Points for Interview

- **Why DFS?**: DFS depth-wise traversal deta hai, aur adjacency list ke order mein neighbors visit karna easy hai.
- **Why Undirected Graph?**: Edges dono direction mein hote hain, to visited array se cycles handle karte hain.
- **Edge Cases**:
  - `V=1`, empty adj list: `[0]`.
  - Fully connected graph: All nodes in DFS order.
- **Hinglish**: Interview mein DFS ka recursive approach samjhao, visited array ka role clear karo, aur adj list ke order ka dhyan rakho.

---

### Additional Notes for Beginners

- **Why This Works**: DFS depth-wise nodes explore karta hai, aur visited array ensure karta hai ki undirected graph mein cycles ke wajah se dobara visit na ho.
- **Hinglish**: Bhai, DFS se ek path ke saare nodes cover hote hain, aur visited array se dobara visit nahi hota.
- **Practice Cases**:
  - `adj=[[2,3,1], [0], [0,4], [0], [2]]` → `[0, 2, 4, 3, 1]`.
  - `adj=[[1,2], [0,2], [0,1,3,4], [2], [2]]` → `[0, 1, 2, 3, 4]`.
- **BFS vs DFS**: BFS level-wise traversal deta hai, DFS depth-wise. Is problem ke liye DFS suitable hai kyunki order adjacency list ke hisaab se chahiye.
- **Common Mistake**: Visited array na rakho to undirected graph mein infinite recursion mein fas sakte ho. Ensure neighbors check karte waqt visited check karo.
