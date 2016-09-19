#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::pair;


void explore(int v, int cc, vector< pair<bool, int> >& visited_nodes, const vector<vector<int>>& adj)
{
    visited_nodes[v].first = true;
    visited_nodes[v].second = cc;
    
    for (auto& w : adj[v])
    {
        if (!visited_nodes[w].first)
        {
            explore(w, cc, visited_nodes, adj);
        }
    }
}

int dfs(const vector<vector<int>>& adj)
{
    vector< pair<bool, int> > visited_nodes(adj.size());
    int cc { 1 };
    
    for (int v { 0 }; v < visited_nodes.size(); ++v)
    {
        if (!visited_nodes[v].first)
        {
            explore(v, cc, visited_nodes, adj);
            ++cc;
        }
    }
    
    return --cc;
}

int number_of_components(vector<vector<int> > &adj) {
    return dfs(adj);
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
    std::cout << number_of_components(adj);
}
