#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <queue>

using std::vector;


int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t, int infinity) {
    
    vector<int> distance(adj.size(), infinity);
    distance[s] = 0;
    vector<int> previous(adj.size(), -1);
    std::vector<int> queue(adj.size());
    int n {0};
    std::generate(queue.begin(), queue.end(), [&n]{return n++;});
    
    auto change_priority = [&queue, &distance]()
    {
        std::sort(queue.begin(), queue.end(), [&](const int& a, const int& b){ return distance[a] > distance[b]; });
    };
    
    change_priority();
    while(!queue.empty())
    {
        auto node = queue.back();
        queue.pop_back();
        
        for (int neighbour {0}; neighbour < adj[node].size(); ++neighbour)
        {
            if (distance[adj[node][neighbour]] > (distance[node] + cost[node][neighbour]) )
            {
                distance[adj[node][neighbour]] = distance[node] + cost[node][neighbour];
                previous[adj[node][neighbour]] = node;
                change_priority();
            }
        }
    }
    
    if (distance[t] == infinity)
    {
        return -1;
    }
    else
    {
        return distance[t];
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());
    int infinity = 0;
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
        infinity += w;
    }
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, cost, s, t, ++infinity);
}
