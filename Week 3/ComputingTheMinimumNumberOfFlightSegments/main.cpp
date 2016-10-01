#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

vector<int> bfs(const vector<vector<int>>& adj, int node)
{
    // Set "infinite" distance for all nodes
    int infinity { static_cast<int>(adj.size()) };
    vector<int> dist(adj.size(), infinity);
    
    dist[node] = 0; // strting node
    queue<int> processing;
    
    processing.push(node);
    while (!processing.empty())
    {
        node = processing.front();
        processing.pop();
        for (int i {0}; i < adj[node].size(); ++i)
        {
            if (dist[adj[node][i]] == infinity)
            {
                processing.push(adj[node][i]);
                dist[adj[node][i]] = dist[node] + 1;
            }
        }
    }
    
    return dist;
}

int distance(vector<vector<int> > &adj, int s, int t) {
    auto dist = bfs(adj, s);
    auto path_distance = dist[t];
    if (path_distance == adj.size())
    {
        return -1;
    }
    else
    {
        return path_distance;
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, s, t);
}
