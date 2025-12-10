#include <bits/stdc++.h>
using namespace std;
class Solution {
  public:
    // Function to detect a cycle in a Directed Graph using BFS (Kahn's Algorithm)
    bool isCyclic(int V, vector<vector<int>> &edges) {
        // Step 1: Build adjacency list and calculate in-degrees of all vertices
        vector<vector<int>> adj(V);          // Adjacency list representation
        vector<int> indegree(V, 0);          // Store in-degree (number of incoming edges) of each vertex

        for (auto &edge : edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);             // Directed edge u -> v
            indegree[v]++;                   // Increment in-degree of destination vertex
        }

        // Step 2: Initialize queue with all vertices having in-degree 0
        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.push(i);                   // Node with no dependencies → can be processed first
            }
        }

        // Step 3: Perform BFS (Kahn’s Algorithm)
        int count = 0;                       // To count how many vertices are processed
        while (!q.empty()) {
            int node = q.front();             // Get the front node
            q.pop();                          // Remove it from queue
            count++;                          // Node is now processed

            // For each neighbor of current node
            for (int neighbor : adj[node]) {
                indegree[neighbor]--;         // Remove dependency (edge)
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);         // If in-degree becomes 0, add to queue
                }
            }
        }

        // Step 4: Check if all vertices were processed
        // If not, there exists a cycle (some nodes still have in-degree > 0)
        return count != V;                   // true → cycle exists; false → no cycle
    }
};

int main() {
    Solution sol;

    // Test Case 1: Cycle exists
    int V = 4;
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 2}, {2, 0}, {2, 3}, {3, 3}};
    cout << "Test Case 1: " << (sol.isCyclic(V, edges) ? "Cycle Detected" : "No Cycle") << endl;

    // Test Case 2: No cycle
    V = 4;
    edges = {{0, 1}, {0, 2}, {1, 2}, {2, 3}};
    cout << "Test Case 2: " << (sol.isCyclic(V, edges) ? "Cycle Detected" : "No Cycle") << endl;

    return 0;
}
