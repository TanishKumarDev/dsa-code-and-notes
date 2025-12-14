// ============================================================================
// GRAPH REPRESENTATION IN C++
//
// This file demonstrates THREE STANDARD ways to store a graph:
//
// 1. Adjacency List   -> Most commonly used in DSA (BFS, DFS, shortest paths)
// 2. Adjacency Matrix-> Useful for dense graphs and quick edge lookup
// 3. Edge List       -> Useful in Kruskal's algorithm and simple storage
//
// IMPORTANT:
// - This file focuses ONLY on *representation*, not traversal.
// - No BFS / DFS / Cycle detection here.
// - Graph is assumed to be UNDIRECTED unless stated otherwise.
// ============================================================================

#include <bits/stdc++.h>
using namespace std;

int main()
{

    // ------------------------------------------------------------
    // GRAPH INPUT (Hardcoded Example)
    //
    // n = number of nodes (1-based indexing)
    // edges = list of connections between nodes
    //
    // Graph:
    // 1 -- 2 -- 3
    // |
    // 4 -- 5
    // ------------------------------------------------------------

    int n = 5;

    // Edge List representation
    // Each pair (u, v) represents an undirected edge between u and v
    vector<pair<int, int>> edges = {
        {1, 2},
        {2, 3},
        {1, 4},
        {4, 5}};

    // ========================================================================
    // 1. ADJACENCY LIST REPRESENTATION
    //
    // Definition:
    // adj_list[u] contains all nodes directly connected to node u.
    //
    // Why use adjacency list?
    // - Space efficient for sparse graphs
    // - Faster neighbor traversal
    // - Preferred for BFS, DFS, shortest path problems
    //
    // Space Complexity: O(V + E)
    // ========================================================================

    // Create n+1 lists (index 0 unused because graph is 1-indexed)
    vector<vector<int>> adj_list(n + 1);

    // Convert edge list to adjacency list
    for (auto &edge : edges)
    {

        int u = edge.first;  // starting node
        int v = edge.second; // ending node

        // Add edge in both directions (UNDIRECTED GRAPH)
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    // Print adjacency list
    // Each row shows: node -> its neighbors
    cout << "Adjacency List:\n";
    for (int i = 1; i <= n; i++)
    {
        cout << i << " -> ";

        // Traverse neighbors of node i
        for (auto &nbr : adj_list[i])
        {
            cout << nbr << " ";
        }

        cout << "\n";
    }
    cout << "\n";

    // ========================================================================
    // 2. ADJACENCY MATRIX REPRESENTATION
    //
    // Definition:
    // adj_matrix[u][v] = 1 if there is an edge between u and v, else 0
    //
    // Why use adjacency matrix?
    // - Constant time edge lookup O(1)
    // - Simple to understand
    //
    // Drawbacks:
    // - High space usage: O(V^2)
    // - Inefficient for sparse graphs
    //
    // Used mostly when:
    // - Graph is dense
    // - Constraints are small
    // ========================================================================

    // Create (n+1) x (n+1) matrix initialized with 0
    vector<vector<int>> adj_matrix(n + 1, vector<int>(n + 1, 0));

    // Fill adjacency matrix using edge list
    for (auto &edge : edges)
    {

        int u = edge.first;
        int v = edge.second;

        // Mark edge existence
        adj_matrix[u][v] = 1;

        // Since graph is undirected, mark reverse as well
        adj_matrix[v][u] = 1;
    }

    // Print adjacency matrix
    cout << "Adjacency Matrix:\n";
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << adj_matrix[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    // ========================================================================
    // 3. EDGE LIST REPRESENTATION
    //
    // Definition:
    // Store graph as a list of edges (u, v)
    //
    // Why use edge list?
    // - Very simple representation
    // - Used in Kruskal's MST algorithm
    // - Useful when only edge processing is required
    //
    // Drawback:
    // - Slow to find neighbors of a node
    // ========================================================================

    cout << "Edge List:\n";
    for (auto &edge : edges)
    {
        cout << edge.first << " -- " << edge.second << "\n";
    }
    cout << "\n";

    return 0;
}
