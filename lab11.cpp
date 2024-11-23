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

    Graph(vector<Edge> edges, int num_vertices): edges(edges), num_vertices(num_vertices) {}

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

vector<int> &find(vector<vector<int>> &vector, int v1)
{
    for(auto &i: vector)
        for(auto num: i)
            if(num == v1)
                return i;
    cout << "not found";
}

void connect(vector<int> &v1, vector<int> &v2, vector<vector<int>> &connected_vertices)
{
    for (int i = 0; i < v2.size(); i++)
        if (find(v1.begin(), v1.end(), v2[i]) == v1.end())
            v1.push_back(v2[i]);
    connected_vertices.erase(find(connected_vertices.begin(), connected_vertices.end(), v2));
}

Graph kraskal(Graph graph)
{
    vector<vector<int>> connected_vertices;

    for(int i = 0; i < graph.get_num_vertices(); i++)
    {
        vector<int> rebro(1, i);
        connected_vertices.push_back(rebro);
    }

    Graph minGraph = Graph();
    while(connected_vertices.size() != 1)
    {
        Edge rebro = graph.get_min_edge();
        if(!find(connected_vertices, rebro.get_v1(), rebro.get_v2()))
        {
            connect(find(connected_vertices, rebro.get_v1()), find(connected_vertices, rebro.get_v2()), connected_vertices);
            minGraph.add_edge(rebro);
        }
    }
    return minGraph;
}

int main(int argc, char *argv[])
{
    int num_vertices = 5;
    srand(time(NULL));
    // Graph graph = generate_connected_graph(num_vertices);
    vector<Edge> edges;
    edges.push_back(Edge(0, 1, 2));
    edges.push_back(Edge(0, 3, 10));
    edges.push_back(Edge(1, 2, 4));
    edges.push_back(Edge(2, 3, 7));
    edges.push_back(Edge(3, 4, 1));
    Graph graph = Graph(edges, 5);
    cout << "Generated graph:" << endl;
    graph.print();
    graph.sort();
    Graph minGraph = kraskal(graph);
    cout << "Minimized graph:" << endl;
    minGraph.print();
    return 0;
}