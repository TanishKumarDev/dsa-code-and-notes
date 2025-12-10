#include <bits/stdc++.h>
using namespace std;
class Solution {
  public:
    // Helper function to perform Depth First Search (DFS) recursively
    void dfsTraversal(int node, vector<vector<int>>& adj, vector<bool>& visited, vector<int>& result) {
        visited[node] = true;                // Mark the current node as visited
        result.push_back(node);              // Add the current node to the DFS traversal result

        // Traverse all the neighbors of the current node
        for (int neighbor : adj[node]) {
            // If the neighbor has not been visited yet, recursively perform DFS on it
            if (!visited[neighbor]) {
                dfsTraversal(neighbor, adj, visited, result);
            }
        }
    }

    // Function to perform Depth First Traversal (DFS) of the given graph
    vector<int> dfs(vector<vector<int>>& adj) {
        int V = adj.size();                  // Number of vertices in the graph
        vector<bool> visited(V, false);      // Track visited nodes to avoid revisiting
        vector<int> result;                  // Store DFS traversal order

        // Start DFS from vertex 0 (assuming graph is connected)
        dfsTraversal(0, adj, visited, result);

        // Return the DFS traversal sequence
        return result;
    }
};
int main() {

    // Example adjacency list:
    // 0 -> 2, 3, 1
    // 1 -> 0
    // 2 -> 0, 4
    // 3 -> 0
    // 4 -> 2

    int V = 5;

    // Create adjacency list of type vector<vector<int>>
    vector<vector<int>> adj(V);

    adj[0] = {2, 3, 1};
    adj[1] = {0};
    adj[2] = {0, 4};
    adj[3] = {0};
    adj[4] = {2};

    // Create Solution object
    Solution obj;

    // Correct DFS call
    vector<int> ans = obj.dfs(adj);

    // Print DFS result
    cout << "DFS Traversal: ";
    for (int node : ans) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
