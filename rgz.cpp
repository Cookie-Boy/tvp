#include <iostream>
#include <vector>
#include <algorithm>

#define INF INT32_MAX

using namespace std;

class node
{
  private:

    int current_v;
    int cost;
    int lower_border;
    vector<int> path;
    vector<int> remaining_v;

  public:
    
    node(int current_v, int cost, int lower_border, vector<int> &path, vector<int> &remaining_v): current_v(current_v), cost(cost), lower_border(lower_border), path(path), remaining_v(remaining_v) {}

    node() {}

    int get_current_v()
    {
        return current_v;
    }
    
    int get_cost()
    {
        return cost;
    }

    int get_lower_border()
    {
        return lower_border;
    }

    vector<int> get_path()
    {
        return path;
    }

    vector<int> get_remaining_v()
    {
        return remaining_v;
    }

    void print()
    {
        cout << "v: " << current_v << " cost: " << cost << " lower_border: " << lower_border << " path: " << path[0];

        for(int i = 1; i < path.size(); i++)
            cout << ", " << path[i];

        cout << " remaining v: " << remaining_v[0];

        for(int i = 1; i < remaining_v.size(); i++)
            cout << ", " << remaining_v[i];
    }
};

int lower_border(vector<vector<int>> &c, vector<int> &path, vector<int> &remaining_v)
{
    int border = 0;

}

int Branch_Border(vector<vector<int>> &c, int startv)
{
    int min_cost = INF;
    vector<int> current_path(1, startv);
}

int Brute_Force(vector<vector<int>> &c, int start_v)
{
    int n = c.size();
    vector<int> path(n);

    for(int i = 0; i < n; i++)
        path[i] = i;

    swap(path[0], path[start_v]);

    int min_cost = INF;
    vector<int> shortest_path;

    do 
    {
        int cost = 0;
        for(int i = 0; i < n - 1; i++)
        {
            if(c[path[i]][path[i+1]] != INF)
                cost += c[path[i]][path[i + 1]]; // summ cost of the entire path (each iteration sum path from current vertice to next vertice in the route)
            else 
            {
                cost = INF;                      // in case there are inf path between vertices cost equals inf and end loop ( as it's not actually going anywhere now)
                break;
            }
        }

        if(c[path[n - 1]][path[0]] != INF && cost != INF)       // check if infinite 
            cost += c[path[n - 1]][path[0]]; // add return cost 
            
        else 
            cost = INF;

        if(cost < min_cost)
        {
            min_cost = cost;
            shortest_path = path;
        }

    } while(next_permutation(path.begin() + 1, path.end())); // generating all perestanovki

    cout << "Brute force: \n" << "cost: " << min_cost << "\npath: " << shortest_path[0];

    for(int i = 1; i < n; i++)
        cout << " -> " << shortest_path[i]; 
}

int main()
{
    vector<vector<int>> c;
    c = {{INF, 13, 7, 5, 2, 9},
         {8, INF, 4, 7, 5, INF}, 
         {8, 4, INF, 3, 6, 2},
         {5, 8, 1, INF, 0, 1}, 
         {INF, 6, 1, 4, INF, INF}, 
         {0, 0, INF, 3, 7, INF}};

    int n = c.size();
    int start_v = 0;

    vector<int> path(1, start_v);

    vector<int> remaining_v;

    for(int i = 0; i < n; i++)
        if(start_v != i)
            remaining_v.push_back(i);

    node root = node(start_v, 0, 0, path, remaining_v);

    Brute_Force(c, 0);
    // Branch_Border(c, 0);

    return 0;
}