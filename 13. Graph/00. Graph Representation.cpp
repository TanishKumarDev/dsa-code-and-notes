// ============================================================================
// GRAPH REPRESENTATION IN C++
// 1. Adjacency List
// 2. Adjacency Matrix
// 3. Edge List
//
// NOTE:
// - This file only shows *how to store* a graph in different ways.
// - No DFS/BFS here, only representation.
// ============================================================================

#include <bits/stdc++.h>
using namespace std;

int main() {

    // ------------------------------------------------------------
    // INPUT EXAMPLE
    // Suppose graph has 5 nodes and 4 edges.
    // Edges are undirected for this example.
    // ------------------------------------------------------------

    int n = 5;
    vector<pair<int,int>> edges = {
        {1, 2},
        {2, 3},
        {1, 4},
        {4, 5}
    };

    // ========================================================================
    // 1. ADJACENCY LIST
    // vector<vector<int>> adj_list(n+1) creates n+1 lists (1-indexed graph)
    // ========================================================================

    vector<vector<int>> adj_list(n + 1);

    // Fill adjacency list
    for (auto &edge : edges) {
        int u = edge.first;
        int v = edge.second;

        adj_list[u].push_back(v); // insert v in list of u
        adj_list[v].push_back(u); // insert u in list of v (undirected)
    }

    // PRINT adjacency list
    cout << "Adjacency List:\n";
    for (int i = 1; i <= n; i++) {
        cout << i << " -> ";
        for (auto &nbr : adj_list[i]) {
            cout << nbr << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    // ========================================================================
    // 2. ADJACENCY MATRIX
    // Create matrix of size (n+1)x(n+1) and initialize to 0
    // ========================================================================

    vector<vector<int>> adj_matrix(n + 1, vector<int>(n + 1, 0));

    // Fill adjacency matrix
    for (auto &edge : edges) {
        int u = edge.first;
        int v = edge.second;

        adj_matrix[u][v] = 1;   // mark edge
        adj_matrix[v][u] = 1;   // remove if directed
    }

    // PRINT adjacency matrix
    cout << "Adjacency Matrix:\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << adj_matrix[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    // ========================================================================
    // 3. EDGE LIST
    // Already stored in `edges` vector
    // ========================================================================

    cout << "Edge List:\n";
    for (auto &edge : edges) {
        cout << edge.first << " -- " << edge.second << "\n";
    }
    cout << "\n";

    return 0;
}
