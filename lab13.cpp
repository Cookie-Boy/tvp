#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <time.h>

#define MAX 50
#define INF INT32_MAX

using namespace std;

class Edge
{
    private:

    int v1;
    int v2;
    int weight;

    public:

    Edge() : v1(0), v2(1), weight(1)
    {
    }

    Edge(int v1, int v2, int weight): v1(v1), v2(v2), weight(weight)
    {
    }

    int get_v1() const 
    {
        return v1;
    }

    int get_v2() const
    {
        return v2;
    }

    int get_weight() const
    {
        return weight;
    }

};

class Graph
{
    private:

    vector<Edge> edges;
    int num_vertices;

    public:

    Graph(): edges(), num_vertices(0)
    {
    }

    void add_edge(Edge edge)
    {
        edges.push_back(edge);
    }

    void sort()
    {
        std::sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) {
        return e1.get_weight() < e2.get_weight(); // Сортировка по возрастанию веса
    });
    }

    void print()
    {
        for(Edge i: edges)
            cout << i.get_v1() << "*" << "---" << i.get_weight() << "---" << "*" <<i.get_v2() << endl;
        cout << endl;
    }

    int get_num_vertices()
    {
        return num_vertices;
    }

    vector<Edge> get_all_edges()
    {
        return this->edges;
    }

    void set_num_vertices(int num_vertices)
    {
        this->num_vertices = num_vertices;
    }

    Edge get_min_edge()
    {
        Edge rebro = edges[0];
        edges.erase(edges.begin());
        return rebro;
    }

};

void bellman(Graph graph, int v_start)
{
    vector<int> distance (graph.get_num_vertices(), INF);
    distance[v_start] = 0;

    vector<vector<int>> paths (graph.get_num_vertices());
    paths[v_start] = {v_start};

    for(int i = 0; i < graph.get_num_vertices() - 1; i++)
    {
        for(auto edge: graph.get_all_edges())
        {
            if(distance[edge.get_v1()] != INF && distance[edge.get_v1()] + edge.get_weight() < distance[edge.get_v2()])
            {
                distance[edge.get_v2()] = distance[edge.get_v1()] + edge.get_weight();
                paths[edge.get_v2()] = paths[edge.get_v1()];
                paths[edge.get_v2()].push_back(edge.get_v2());
            }
            else if(distance[edge.get_v2()] != INF && distance[edge.get_v2()] + edge.get_weight() < distance[edge.get_v1()])
            {
                distance[edge.get_v1()] = distance[edge.get_v2()] + edge.get_weight();
                paths[edge.get_v1()] = paths[edge.get_v2()];
                paths[edge.get_v1()].push_back(edge.get_v1());
            }
        }
    }

    for(auto edge: graph.get_all_edges())
    {
        if(distance[edge.get_v1()] != INF && distance[edge.get_v1()] + edge.get_weight() < distance[edge.get_v2()])
        {
            cout << "Graph has negative loops! " << endl;
            return;
        }
    }

    cout << "Shortest paths from " << v_start << ":" << endl;
    for(int v = 0; v < graph.get_num_vertices(); v++)
    {
        cout << "v: " << v << " dis: " << distance[v] << " "; 
        for(auto vert: paths[v])
            cout << "-> " << vert;
        cout << endl;
    }
}

Graph generate_connected_graph(int num_vertices)
{
    Graph graph = Graph();
    graph.set_num_vertices(num_vertices);

    for (int i = 0; i < num_vertices - 1; i++)
    {
        for (int j = i + 1; j < num_vertices; j++)
        {
            if(i == j)
            {
                graph.add_edge(Edge(i, i, 0));
                continue;
            }
            int weight = 1 + rand() % MAX;
            graph.add_edge(Edge(i, j, weight));
        }
    }
    return graph;
}

int main()
{
    int num_vertices = 5;
    srand(time(NULL));
    Graph graph = generate_connected_graph(num_vertices);
    cout << "Generated graph:" << endl;
    graph.print();
    int v_start = 4;
    bellman(graph, v_start);
    return 0;
}