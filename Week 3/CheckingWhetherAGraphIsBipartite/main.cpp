#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

bool bfs(const vector<vector<int>>& adj)
{
    enum class Tag
    {
        Unexplored,
        White,
        Black
    };
    vector<Tag> tags(adj.size());
    auto opposite = [&tags](int node)
    {
        if (tags[node] == Tag::White) { return Tag::Black; }
        if (tags[node] == Tag::Black) { return Tag::White; }
        else { return Tag::Unexplored; }
    };
    
    // Loop if there's separate components in graph
    for (int node {0}; node < adj.size(); ++node)
    {
        if (tags[node] != Tag::Unexplored) { continue; }
        tags[node] = Tag::White;
        queue<int> processing;
        
        processing.push(node);
        while (!processing.empty())
        {
            node = processing.front();
            processing.pop();
            for (int i {0}; i < adj[node].size(); ++i)
            {
                if (tags[adj[node][i]] == Tag::Unexplored)
                {
                    processing.push(adj[node][i]);
                    tags[adj[node][i]] = opposite(node);
                }
                else if (tags[node] == tags[adj[node][i]])
                {
                    return false;
                }
            }
        }
    }
    
    return true;
}

int bipartite(vector<vector<int> > &adj) {
    return bfs(adj);
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
    std::cout << bipartite(adj);
}
