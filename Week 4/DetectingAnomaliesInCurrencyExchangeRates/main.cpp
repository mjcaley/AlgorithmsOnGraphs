#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using std::vector;

void reverse_graph(const vector<vector<int>>& in, vector<vector<int>>& out)
{
    out.resize(in.size());
    out.clear();
    
    for (int i {0}; i < in.size(); ++i)
    {
        for (int j {0}; j < in[i].size(); ++j)
        {
            out[in[i][j]].emplace_back(i);
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


bool bellman_ford(vector<vector<int> > &adj, vector<vector<int> > &cost, vector<int>& path)
{
    vector<int> distance(adj.size(), std::numeric_limits<int>::max());
    vector<int> previous(adj.size(), -1);
    
    distance[path.front()] = 0;
    
    for (auto& v : path)
    {
        auto vertex = v;
        for (int e {0}; e < adj[v].size(); ++e)
        {
            auto neighbour_vertex = adj[v][e];
            
            if (distance[neighbour_vertex] > (distance[vertex] + cost[v][e]))
            {
                distance[neighbour_vertex] = distance[vertex] + cost[v][e];
                previous[neighbour_vertex] = vertex;
            }
        }
    }
    
    for (auto& v : path)
    {
        auto vertex = v;
        for (int e {0}; e < adj[v].size(); ++e)
        {
            auto neighbour_vertex = adj[v][e];
            if (distance[neighbour_vertex] > (distance[vertex] + cost[v][e]))
            {
                return true;
            }
        }
    }
    
    return false;
}

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost)
{
    vector<vector<int>> r_adj;
    reverse_graph(adj, r_adj);
    
    vector<int> path;
    {
        vector<bool> visited(adj.size());
        path = dfs(adj, visited);
    }
    
    vector<vector<int>> connected_components;
    vector<bool> visited(adj.size());
    for (auto& p : path)
    {
        if (!visited[p])
        {
            connected_components.emplace_back(vector<int>());
            explore(r_adj, p, visited, connected_components.back());
        }
    }
    
    for (auto& vertexes : connected_components)
    {
        auto result = bellman_ford(adj, cost, vertexes);
        if (result)
        {
            return 1;
        }
    }
    
    return 0;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    std::cout << negative_cycle(adj, cost);
}
