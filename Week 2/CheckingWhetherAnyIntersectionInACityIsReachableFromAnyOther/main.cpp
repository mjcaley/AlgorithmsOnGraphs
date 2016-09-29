#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;


void explore(const vector<vector<int>>& adj, const int v, vector<bool>& visited)
{
    visited[v] = true;
    for (int i {0}; i < adj[v].size(); ++i)
    {
        if (!visited[ adj[v][i] ])
        {
            explore(adj, adj[v][i], visited);
        }
    }
}

void explore(const vector<vector<int>>& adj, const int v, vector<bool>& visited, vector<int>& path)
{
    visited[v] = true;
    for (int i {0}; i < adj[v].size(); ++i)
    {
        if (!visited[ adj[v][i] ])
        {
            explore(adj, adj[v][i], visited, path);
        }
    }
    path.push_back(v);
}

vector<int> dfs(const vector<vector<int>>& adj, vector<bool>& visited)
{
    vector<int> path;
    
    for (int v {0}; v < adj.size(); ++v)
    {
        if (!visited[v])
        {
            explore(adj, v, visited, path);
        }
    }
    
    std::reverse(path.begin(), path.end());
    return path;
}


int number_of_strongly_connected_components(const vector<vector<int> >& adj, const vector<vector<int> >& r_adj) {
    int result = 0;
    
    // first pass
    vector<bool> visited(adj.size());
    auto path = dfs(adj, visited);
    
    // second pass
    std::fill(visited.begin(), visited.end(), false);
    for (auto& p : path)
    {
        if (!visited[p])
        {
            ++result;
            explore(r_adj, p, visited);
        }
    }
    
    return result;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int>> r_adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        r_adj[y - 1].push_back(x - 1);
    }
    std::cout << number_of_strongly_connected_components(adj, r_adj);
}
