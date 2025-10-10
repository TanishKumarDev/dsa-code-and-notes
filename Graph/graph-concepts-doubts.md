# This is all my silly doubt

# Adjacency List Representation in C++: vector<int> adj[] vs vector<vector<int>> adj

## 1. Graph ko adjacency list me store karne ke tarike

Graph ko adjacency list me store karne ke 2 common tareeke hain C++ me:

---

### (A) **`vector<int> adj[]`**

* Yani **array of vectors**.
* Har index ek node represent karta hai, aur uske andar ek vector hota hai jo neighbors store karta hai.
* Example:

  ```cpp
  int V = 4;
  vector<int> adj[V];   // array of vectors

  adj[0].push_back(1);
  adj[1].push_back(2);
  adj[2].push_back(0);
  adj[2].push_back(3);
  ```
* Memory **stack pe allocate hoti hai** aur size `V` compile ke time fix hota hai.
* Ye style **GFG ke driver code** me zyada dikhega.

---

### (B) **`vector<vector<int>> adj`**

* Yani **vector of vectors**.
* Har index pe ek aur vector banta hai jo neighbors rakhta hai.
* Example:

  ```cpp
  int V = 4;
  vector<vector<int>> adj(V);  // vector of vectors

  adj[0].push_back(1);
  adj[1].push_back(2);
  adj[2].push_back(0);
  adj[2].push_back(3);
  ```
* Memory **heap pe dynamically allocate hoti hai**, aur size **runtime pe decide kar sakte ho**.
* Ye style **LeetCode / Interview code** me zyada expected hota hai, kyunki portable aur modern hai.

---

## 2. Function parameter me difference

### (A) `vector<int> adj[]`

* Jab function me `adj[]` dete ho, iska matlab hai "array of vectors".
* Example:

  ```cpp
  void dfs(int node, vector<int> adj[]) { ... }
  ```
* Iska size function ko nahi pata hota. Tumhe separately `V` pass karna padta hai.
* Isiliye GFG ke problems me aksar `dfs(int V, vector<int> adj[])` milta hai.

---

### (B) `vector<vector<int>>& adj`

* Jab function me `vector<vector<int>>& adj` dete ho, iska matlab hai ek **reference to vector of vectors**.
* Example:

  ```cpp
  void dfs(int node, vector<vector<int>>& adj) { ... }
  ```
* Yaha size `adj.size()` se directly nikal sakte ho. `V` alag se dene ki zarurat nahi hoti.
* Ye zyada **modern C++** way hai (safe + flexible).

---

## 3. Jab tum confusion dekhte ho

* Agar tum `vector<int> adj[]` aur `vector<vector<int>>& adj` mix kar doge → compiler confuse ho jayega (kyunki ek array hai aur ek vector hai).
* Isiliye **ek hi style consistently use karo**.

👉 **Interview prep ke liye best hai**:
`vector<vector<int>> adj` (kyunki portable hai aur C++ STL ke rules follow karta hai).

👉 **GFG ke practice ke liye**:
`vector<int> adj[]` (kyunki unke driver code isi form me hoti hai).

---

## 4. Ek short analogy 🎯

* `vector<int> adj[]`  = C style "array of vectors" (size compile-time pe fix).
* `vector<vector<int>> adj` = C++ style "vector of vectors" (size runtime pe flexible).
