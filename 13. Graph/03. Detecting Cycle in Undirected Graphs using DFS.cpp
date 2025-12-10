#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // DFS helper to detect cycle in undirected graph
    // node    : current node
    // parent  : parent of current node
    // adj     : adjacency list
    // visited : track visited nodes
    bool dfsCycle(int node, int parent, vector<vector<int>>& adj, vector<bool>& visited) {
        visited[node] = true;

        for(int neighbor : adj[node]) {
            if(!visited[neighbor]) {
                if(dfsCycle(neighbor, node, adj, visited))
                    return true; // Cycle found in deeper DFS
            }
            else if(neighbor != parent) {
                // Visited neighbor which is not parent → cycle detected
                return true;
            }
        }
        return false; // No cycle found in this path
    }

    // Main function to detect cycle in undirected graph
    bool isCycle(int V, vector<vector<int>>& edges) {
        // Step 1: Build adjacency list from edges
        vector<vector<int>> adj(V);
        for(auto &e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u); // undirected
        }

        // Step 2: Track visited nodes
        vector<bool> visited(V, false);

        // Step 3: Check all connected components
        for(int i = 0; i < V; i++) {
            if(!visited[i]) {
                if(dfsCycle(i, -1, adj, visited))
                    return true; // Cycle detected
            }
        }

        return false; // No cycle in any component
    }
};

int main() {
    Solution sol;

    // ------------------------------------
    // Test Case 1: No cycle
    // ------------------------------------
    int V = 4;
    vector<vector<int>> edges1 = {{0,1}, {0,2}, {1,2}, {2,3}};
    cout << "Test Case 1: "
         << (sol.isCycle(V, edges1) ? "Cycle Detected" : "No Cycle") << endl;


    // ------------------------------------
    // Test Case 2: Simple cycle
    // Graph: 0 -> 1 -> 2 -> 0
    // ------------------------------------
    V = 3;
    vector<vector<int>> edges2 = {{0,1}, {1,2}, {2,0}};
    cout << "Test Case 2: "
         << (sol.isCycle(V, edges2) ? "Cycle Detected" : "No Cycle") << endl;


    // ------------------------------------
    // Test Case 3: Self-loop (cycle)
    // ------------------------------------
    V = 4;
    vector<vector<int>> edges3 = {{0,1}, {1,2}, {2,3}, {3,3}};
    cout << "Test Case 3: "
         << (sol.isCycle(V, edges3) ? "Cycle Detected" : "No Cycle") << endl;


    // ------------------------------------
    // Test Case 4: Disconnected graph with a cycle
    // ------------------------------------
    V = 5;
    vector<vector<int>> edges4 = {{0,1}, {1,2}, {2,0}, {3,4}};
    cout << "Test Case 4: "
         << (sol.isCycle(V, edges4) ? "Cycle Detected" : "No Cycle") << endl;


    // ------------------------------------
    // Test Case 5: No cycle anywhere
    // ------------------------------------
    V = 6;
    vector<vector<int>> edges5 = {{0,1}, {2,3}, {4,5}};
    cout << "Test Case 5: "
         << (sol.isCycle(V, edges5) ? "Cycle Detected" : "No Cycle") << endl;

    return 0;
}
