#include <iostream>
#include <algorithm>
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

void find_sink(const vector<vector<int>>& adj, vector<Status>& vertex_status, const int vertex, vector<int>& order)
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
                find_sink(adj, vertex_status, adj[vertex][i], order);
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
    
    order.push_back(vertex);
}


void dfs(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int x) {
    //write your code here
}

vector<int> toposort(vector<vector<int> > adj) {
    vector<int> used(adj.size(), 0);
    vector<int> order;
    
    vector<Status> vertex_status(adj.size());
    
    for (int i {0}; i < adj.size(); ++i)
    {
        if (vertex_status[i] == Status::Unexplored)
        {
            find_sink(adj, vertex_status, i, order);
        }
    }
    
    std::reverse(order.begin(), order.end());
    
    return order;
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
    vector<int> order = toposort(adj);
    for (size_t i = 0; i < order.size(); i++) {
        std::cout << order[i] + 1 << " ";
    }
}
