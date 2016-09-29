#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::pair;


enum class Status
{
    Unexplored,
    Visited,
    Sink,
    Cyclic
};

void find_sink(const vector<vector<int>>& adj, vector<Status>& vertex_status, int vertex)
{
    vertex_status[vertex] = Status::Visited;
    
    if (vertex_status[vertex] == Status::Sink || adj[vertex].empty())
    {
        vertex_status[vertex] = Status::Sink;
    }
    else
    {
        for (int i {0}; i < adj[vertex].size(); ++i)
        {
            if (vertex_status[ adj[vertex][i] ] == Status::Unexplored)
            {
                find_sink(adj, vertex_status, adj[vertex][i]);
                vertex_status[vertex] = Status::Sink;
            }
            else if (vertex_status[ adj[vertex][i] ] == Status::Sink)
            {
                vertex_status[vertex] = Status::Sink;
            }
            else if (vertex_status[ adj[vertex][i] ] == Status::Visited)
            {
                vertex_status[vertex] = Status::Cyclic;
            }
        }
    }
}



int acyclic(vector<vector<int> > &adj) {
    vector<Status> visited(adj.size());
    for (int i {0}; i < adj.size(); ++i)
    {
        if (visited[i] == Status::Unexplored)
        {
            find_sink(adj, visited, i);
        }
    }
    
    return std::find(visited.begin(), visited.end(), Status::Cyclic) != visited.end();
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }
    std::cout << acyclic(adj);
}
