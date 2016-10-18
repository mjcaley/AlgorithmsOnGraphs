#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;


const long long infinity { std::numeric_limits<long long>::max() };


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

vector<int> dfs_single(const vector<vector<int>>& adj, int start)
{
    vector<int> path;
    vector<bool> visited(adj.size());
    
    if (!visited[start])
    {
        explore(adj, start, visited, path);
    }
    
    std::reverse(path.begin(), path.end());
    return path;
}

vector<int> dfs(const vector<vector<int>>& adj, int start, vector<bool>& visited)
{
    vector<int> path;
    
    for (int v {start}; v < adj.size(); ++v)
    {
        if (!visited[v])
        {
            explore(adj, v, visited, path);
        }
    }
    
    std::reverse(path.begin(), path.end());
    return path;
}

vector<int> dfs(const vector<vector<int>>& adj, vector<bool>& visited)
{
    return dfs(adj, 0, visited);
}

vector<int> dfs(const vector<vector<int>>& adj)
{
    vector<bool> visited(adj.size());
    return dfs(adj, visited);
}


void bellman_ford(const vector<vector<int>>& adj, const vector<vector<int> >& cost, const int start, vector<int>& path, vector<long long>& distance, vector<int>& shortest)
{
    vector<int> previous(adj.size(), -1);
    
    distance[start] = 0;
    
    for (auto& v : path)
    {
        auto vertex = v;
        for (int e {0}; e < adj[v].size(); ++e)
        {
            auto neighbour_vertex = adj[v][e];
            
            if (distance[vertex] != infinity
                && distance[neighbour_vertex] > (distance[vertex] + cost[v][e]))
            {
                distance[neighbour_vertex] = distance[vertex] + cost[v][e];
                previous[neighbour_vertex] = vertex;
            }
        }
    }
    
    queue<int> relaxed;
    for (auto& v : path)
    {
        auto vertex = v;
        for (int e {0}; e < adj[v].size(); ++e)
        {
            auto neighbour_vertex = adj[v][e];
            if (distance[vertex] != infinity
                && distance[neighbour_vertex] > (distance[vertex] + cost[v][e]))
            {
                distance[neighbour_vertex] = distance[vertex] + cost[v][e];
                shortest[neighbour_vertex] = false;
                relaxed.push(neighbour_vertex);
            }
        }
    }
    
    while(!relaxed.empty())
    {
        auto next = relaxed.front();
        relaxed.pop();
        vector<int> path;
        path = dfs_single(adj, next);
        for (auto i : path)
        {
            shortest[i] = false;
        }
    }
}

void reachable_vertexes(const vector<vector<int>>& adj, const int start, vector<int>& reachable)
{
    auto path = dfs_single(adj, start);
    for (auto& v : path)
    {
        reachable[v] = true;
    }
}

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
    auto path = dfs(adj);
    
    // Determine which vertexes are unreachable
    reachable_vertexes(adj, s, reachable);
    
    // Get distances and return negative paths
    bellman_ford(adj, cost, s, path, distance, shortest);
}

int main() {
    int n, m, s;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    std::cin >> s;
    s--;
    vector<long long> distance(n, std::numeric_limits<long long>::max());
    vector<int> reachable(n, 0);
    vector<int> shortest(n, 1);
    shortest_paths(adj, cost, s, distance, reachable, shortest);
    for (int i = 0; i < n; i++) {
        if (!reachable[i]) {
            std::cout << "*\n";
        } else if (!shortest[i]) {
            std::cout << "-\n";
        } else {
            std::cout << distance[i] << "\n";
        }
    }
}
