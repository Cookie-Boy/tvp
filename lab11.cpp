#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <time.h>

#define MAX 50

using namespace std;

class edge
{
    private:

    int v1;
    int v2;
    int weight;

    public:

    edge() : v1(0), v2(1), weight(1)
    {
    }

    edge(int v1, int v2, int weight): v1(v1), v2(v2), weight(weight)
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

    vector<edge> edges;

    public:

    Graph(): edges()
    {
    }

    void add_edge(edge edge)
    {
        edges.push_back(edge);
    }

    void sort()
    {
        std::sort(edges.begin(), edges.end(), [](const edge& e1, const edge& e2) {
        return e1.get_weight() < e2.get_weight(); // Сортировка по возрастанию веса
    });
    }

    void print()
    {
        for(edge i: edges)
            cout << i.get_v1() << "*" << "---" << i.get_weight() << "---" << "*" <<i.get_v2() << endl;
        cout << endl;
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
                graph.add_edge(edge(i, i, 0));
                continue;
            }
            int weight = 1 + rand() % MAX;
            graph.add_edge(edge(i, j, weight));
        }
    }
    return graph;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    Graph graph = generate_connected_graph(10);
    graph.print();
    graph.sort();
    graph.print();
    return 0;
}