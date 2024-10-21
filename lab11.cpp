#include <iostream>
#include <stdlib.h>
#include <time.h>

#define MAX 50

using namespace std;

typedef struct
{
    int **adj_matrix;
    int num_vertices;
} Graph;

Graph *generate_connected_graph(int num_vertices)
{
    Graph *graph = new Graph;
    graph->num_vertices = num_vertices;
    graph->adj_matrix = new int *[num_vertices];
    for (int i = 0; i < num_vertices; i++)
    {
        graph->adj_matrix[i] = new int[num_vertices];
        graph->adj_matrix[i][i] = 0;
    }

    for (int i = 0; i < graph->num_vertices - 1; i++)
    {
        for (int j = i + 1; j < graph->num_vertices; j++)
        {
            int weight = 1 + rand() % MAX;
            graph->adj_matrix[j][i] = weight;
            graph->adj_matrix[i][j] = weight;
        }
    }
    return graph;
}

void print_graph(Graph *G)
{
    for (int i = 0; i < G->num_vertices; i++)
    {
        for (int j = 0; j < G->num_vertices; j++)
        {
            printf("%5d ", G->adj_matrix[i][j]);
        }
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    Graph *lecture_graph = generate_connected_graph(5);
    print_graph(lecture_graph);
    return 0;
}