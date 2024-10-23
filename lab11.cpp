#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <time.h>

#define MAX 50

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
        num_vertices++;
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

    Edge get_min_edge()
    {
        Edge tmp = edges[0];
        edges.erase(edges.begin());
        return tmp;
    }

};

Graph generate_connected_graph(int num_vertices)
{
    Graph graph = Graph();

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

bool find(vector<vector<int>> &vector, int v1, int v2)
{
    for(auto i: vector)
    {   
        int count = 0;
        for(int v: i)
            if(v == v1 || v == v2)
            {
                count++;
            }
        if (count == 2)
            return true;
    }
    return false;
}

vector<int> find(vector<vector<int>> &vector, int v1)
{
    for(auto i: vector)
        for(auto num: i)
            if(num == v1)
                return i;
}

Graph kraskal(Graph graph)
{
    vector<vector<int>> connected_vertices;

    for(int i = 0; i < graph.get_num_vertices(); i++)
    {
        vector<int> tmp(1, i);
        connected_vertices.push_back(tmp);
    }

    Graph minGraph = Graph();
    while(connected_vertices.size() != 1)
    {
        Edge tmp = graph.get_min_edge();
        if(!find(connected_vertices, tmp.get_v1(), tmp.get_v2()))
        {
            connect(comp1, comp2, vector)
            minGraph.add_edge();
        }
    }
    return minGraph;
}

int main(int argc, char *argv[])
{
    int num_vertices = 10;
    srand(time(NULL));
    Graph graph = generate_connected_graph(num_vertices);
    graph.print();
    graph.sort();
    Graph minGraph = kraskal(graph);
    minGraph.print();
    return 0;
}