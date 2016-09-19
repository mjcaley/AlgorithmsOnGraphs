#include <iostream>
#include <vector>

using std::vector;
using std::pair;


void explore(int v, vector<bool>& visited_nodes, const vector<vector<int>>& adj)
{
    visited_nodes[v] = true;
    
    for (auto& w : adj[v])
    {
        if (!visited_nodes[w])
        {
            explore(w, visited_nodes, adj);
        }
    }
}

int reach(vector<vector<int> > &adj, int x, int y) {
    vector<bool> visited_nodes(adj.size());
    
    explore(x, visited_nodes, adj);
    
    if (visited_nodes[x] && visited_nodes[y])
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    int x, y;
    std::cin >> x >> y;
    std::cout << reach(adj, x - 1, y - 1);
}
