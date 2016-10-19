#include <algorithm>
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <cmath>
#include <utility>
#include <memory>

using std::make_shared;
using std::map;
using std::vector;

struct Point
{
    Point() = default;
    Point(int x, int y) : x(x), y(y) {};
    
    int x { 0 };
    int y { 0 };
    
    bool operator==(const Point& p) const
    {
        return x == p.x && y == p.y;
    }
    
    bool operator!=(const Point& p) const
    {
        return !operator==(p);
    }
};
using spPoint = std::shared_ptr<Point>;

struct Edge
{
    Edge(spPoint p1, spPoint p2) : p1(p1), p2(p2) { calc_cost(); };
    
    spPoint p1;
    spPoint p2;
    double cost;
    
    bool operator==(const Edge& e) const
    {
        return p1 == e.p1 && p2 == e.p2;
    }
    
    bool operator!=(const Edge& e) const
    {
        return !operator==(e);
    }
    
    bool operator<(const Edge& e) const
    {
        return cost < e.cost;
    }
    
private:
    void calc_cost()
    {
        cost = sqrt( pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2) );
    }
};

vector<spPoint> create_points(const vector<int>& x, const vector<int>& y)
{
    vector<spPoint> points;
    
    for (auto i = 0; i < x.size(); ++i)
    {
        points.emplace_back( make_shared<Point>( x[i], y[i]));
    }
    
    return points;
}

vector<Edge> create_edges(const vector<spPoint>& points)
{
    vector<Edge> edges;
    
    for (int i = 0; i < points.size(); ++i)
    {
        for (int j = i + 1; j < points.size(); ++j)
        {
            edges.emplace_back(points[i], points[j]);
        }
    }
    
    return edges;
}

template<typename T, typename U>
void make_set(map<T, T>& parent, map<T, U>& rank, T i)
{
    parent[i] = i;
    rank[i] = 0;
}

template<typename T>
spPoint find(map<T, T>& parent, T i)
{
    if (!parent.count(i))
    {
        return nullptr;
    }
    
    if (i != parent[i]) {
        parent[i] = find(parent, parent[i]);
    }
    return parent[i];
}

template<typename T, typename U>
void set_union(map<T, T>& parent, map<T, U>& rank, T i, T j)
{
    T i_id = find(parent, i);
    T j_id = find(parent, j);
    
    if (i_id == j_id)
    {
        return;
    }
    else
    {
        if (rank[i_id] > rank[j_id])
        {
            parent[j_id] = i_id;
        }
        else
        {
            parent[i_id] = j_id;
            if (rank[i_id] == rank[j_id])
            {
                rank[j_id] += 1;
            }
        }
    }
}

double kruskal(const vector<int>& x, const vector<int>& y)
{
    double result { 0.0 };
    
    auto points = create_points(x, y);
    auto edges = create_edges(points);
    std::sort(edges.begin(), edges.end());
    
    map<spPoint, spPoint> parent;
    for (auto& point : points)
    {
        parent.insert( { point, point } );
    }
    map<spPoint, int> rank;
    for (auto& point : points)
    {
        rank.insert( { point, 0 } );
    }
    
    for (auto& edge : edges)
    {
        auto root1 = find(parent, edge.p1);
        auto root2 = find(parent, edge.p2);
        if (root1 != root2)
        {
            set_union(parent, rank, edge.p1, edge.p2);
            result += edge.cost;
        }
    }
    
    return result;
}

double minimum_distance(vector<int> x, vector<int> y) {
    return kruskal(x, y);
}

int main() {
    size_t n;
    std::cin >> n;
    vector<int> x(n), y(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }
    std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
