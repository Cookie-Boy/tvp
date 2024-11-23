#include <iostream>
#include <vector>
#include <algorithm>

#define INF INT32_MAX
int fine;

using namespace std;

class node
{
  private:

    int current_v;
    int path_cost;
    int lower_border;
    vector<int> path;
    vector<int> remaining_v;

    int static calc_lower_border(int current_v, int path_cost, vector<int> &path, vector<int> &remaining_v, vector<vector<int>> &c)
    {
        int lower_bound = path_cost;

        for(auto i: remaining_v)
        {
            int min_cost = INF;
            for(auto j: remaining_v)
                min_cost = c[i][j] < min_cost? c[i][j]: min_cost;
            lower_bound += min_cost != INF? min_cost: fine;
        }
        return lower_bound;
    }

  public:
    
    node(int current_v, int path_cost, vector<int> &path, vector<int> &remaining_v, vector<vector<int>> &c): current_v(current_v), path_cost(path_cost) ,path(path), remaining_v(remaining_v) 
    {
        this->lower_border = node::calc_lower_border(current_v, path_cost, path, remaining_v, c);
    }

    node() {}

    int get_current_v()
    {
        return current_v;
    }
    
    int get_cost()
    {
        return path_cost;
    }

    int get_lower_border()
    {
        return lower_border;
    }

    vector<int>& get_path()
    {
        return path;
    }

    vector<int>& get_remaining_v()
    {
        return remaining_v;
    }

    void print()
    {
        cout << "v: " << current_v << " cost: " << path_cost << " lower_border: " << lower_border << " path: " << path[0];

        for(int i = 1; i < path.size(); i++)
            cout << ", " << path[i];

        cout << " remaining v: " << remaining_v[0];

        for(int i = 1; i < remaining_v.size(); i++)
            cout << ", " << remaining_v[i];
    }

};

node Branch_Border(vector<vector<int>> &c, node Node)
{
    if(Node.get_remaining_v().empty())
    {
        int cost;
        if(c[Node.get_current_v()][Node.get_path()[0]] == INF || Node.get_cost() == INF)
            cost = INF;
        else 
            cost = c[Node.get_current_v()][Node.get_path()[0]] + Node.get_cost();
        node tmp = node(Node.get_current_v(), cost, Node.get_path(), Node.get_remaining_v(), c);
        return tmp;
    }

    vector<node> branches;
    for(int i: Node.get_remaining_v())
    {
        vector<int> tpath = Node.get_path();
        tpath.push_back(i);
        vector<int> trem = Node.get_remaining_v();
        trem.erase(find(trem.begin(), trem.end(), i));
        int tmpcost;
        if(c[Node.get_current_v()][i] == INF || Node.get_cost() == INF)
            tmpcost = INF;
        else 
            tmpcost = c[Node.get_current_v()][i] + Node.get_cost();

        branches.push_back(node(i, tmpcost, tpath, trem, c));
    }
    int min_path_cost = INF;
    node min_node;
    for(auto i: branches)
    {
        int branch_cost = INF;
        if(i.get_lower_border() < min_path_cost)
            branch_cost = Branch_Border(c, i).get_cost();

        if(branch_cost < min_path_cost)
        {
            min_path_cost = branch_cost;
            min_node = i;
        }   
    }
    return min_node;
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

    cout << "Brute force: \n" << "cost: " << min_cost << "\npath: ";

    for(int i = 0; i < n; i++)
        cout << shortest_path[i] << " -> "; 
    cout << shortest_path[0];
    return min_cost;
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

    for(auto i: c)
        for(auto j: i)
            if(fine < j)
                fine = j;
    fine *= 2;

    int n = c.size();
    int start_v = 0;

    vector<int> path(1, start_v);

    vector<int> remaining_v;

    for(int i = 0; i < n; i++)
        if(start_v != i)
            remaining_v.push_back(i);

    node root = node(start_v, 0, path, remaining_v, c);

    int brute_force = Brute_Force(c, start_v);
    node branch_border = Branch_Border(c, root);

    cout << endl << "Branch border:" << endl;
    cout << "cost: " << branch_border.get_cost() << endl;
    cout << "path: ";
    for(int i = 0; i < n; i++)
        cout << branch_border.get_path()[i] << " -> ";
    cout << branch_border.get_path()[0];
    return 0;
}