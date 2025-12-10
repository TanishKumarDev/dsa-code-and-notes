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
    vector<vector<int>> adj(V);
    adj[0] = {2, 3, 1};
    adj[1] = {0};
    adj[2] = {0, 4};
    adj[3] = {0};
    adj[4] = {2};

    Solution obj;                            // Create object of the Solution class
    vector<int> bfsResult = obj.bfs(adj);    // Call the bfs() method

    cout << "BFS Traversal: ";
    for (int node : bfsResult) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}