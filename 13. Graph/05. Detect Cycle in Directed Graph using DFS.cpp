#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    // DFS Helper Function to detect cycle starting from a node
    // node      : current vertex being visited
    // adj       : adjacency list of the graph
    // visited   : keeps track of visited nodes
    // recStack  : keeps track of nodes in current DFS path
    bool dfsCycle(int node, vector<vector<int>>& adj, vector<bool> &visited, vector<bool> &recStack) {
        // Mark current node as visited
        visited[node] = true;
        // Mark current node in recursion stack (current DFS path)
        recStack[node] = true;

        // Visit all neighbors of the current node
        for (int neighbor : adj[node]) {
            // If neighbor is not visited, explore it recursively
            if (!visited[neighbor]) {
                if (dfsCycle(neighbor, adj, visited, recStack))
                    return true; // Cycle found in deeper DFS
            }
            // If neighbor is visited and still in recursion stack → back edge → cycle
            else if (recStack[neighbor]) {
                return true; 
            }
        }

        // Remove current node from recursion stack before returning
        recStack[node] = false;

        return false; // No cycle found from this path
    }

    // Main function to detect cycle in a directed graph
    // V      : number of vertices
    // edges  : list of directed edges [[u1,v1],[u2,v2],...]
    bool isCyclic(int V, vector<vector<int>> &edges) {
        // Step 1: Build adjacency list from edge list
        vector<vector<int>> adj(V);
        for (auto &e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);   // Add directed edge u -> v
        }

        // Step 2: Initialize visited and recursion stack arrays
        vector<bool> visited(V, false);
        vector<bool> recStack(V, false);

        // Step 3: Check for cycles starting from all unvisited nodes
        // This ensures disconnected components are also checked
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (dfsCycle(i, adj, visited, recStack))
                    return true; // Cycle detected
            }
        }

        return false; // No cycle found in the graph
    }
};

int main() {
    Solution sol;

    // -------------------------------
    // Test Case 1: Simple Cycle
    // Graph: 0 -> 1 -> 2 -> 0
    // -------------------------------
    int V = 3;
    vector<vector<int>> edges1 = {{0,1}, {1,2}, {2,0}};
    cout << "Test Case 1: "
         << (sol.isCyclic(V, edges1) ? "Cycle Detected" : "No Cycle") << endl;


    // -----------------------------------
    // Test Case 2: No Cycle
    // Graph: 0->1, 1->2, 2->3
    // -----------------------------------
    V = 4;
    vector<vector<int>> edges2 = {{0,1}, {1,2}, {2,3}};
    cout << "Test Case 2: "
         << (sol.isCyclic(V, edges2) ? "Cycle Detected" : "No Cycle") << endl;


    // --------------------------------------------------------
    // Test Case 3: Self Loop (Cycle)
    // Graph: 3 -> 3 (self-loop means immediate cycle)
    // --------------------------------------------------------
    V = 4;
    vector<vector<int>> edges3 = {{0,1}, {1,2}, {2,3}, {3,3}};
    cout << "Test Case 3: "
         << (sol.isCyclic(V, edges3) ? "Cycle Detected" : "No Cycle") << endl;


    // --------------------------------------------------------
    // Test Case 4: Disconnected Graph with a Cycle in a Component
    // Component 1: 0->1->2->0 (cycle)
    // Component 2: 3->4 (no cycle)
    // --------------------------------------------------------
    V = 5;
    vector<vector<int>> edges4 = {{0,1}, {1,2}, {2,0}, {3,4}};
    cout << "Test Case 4: "
         << (sol.isCyclic(V, edges4) ? "Cycle Detected" : "No Cycle") << endl;


    // --------------------------------------------------------
    // Test Case 5: Disconnected Graph with NO cycle anywhere
    // --------------------------------------------------------
    V = 6;
    vector<vector<int>> edges5 = {{0,1}, {2,3}, {4,5}};
    cout << "Test Case 5: "
         << (sol.isCyclic(V, edges5) ? "Cycle Detected" : "No Cycle") << endl;


    return 0;
}

