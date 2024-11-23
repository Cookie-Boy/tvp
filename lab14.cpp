#include <iostream>
#include <vector>


using namespace std;

int backpack(int W, vector<int> &Wi, vector<int> &Ci)
{
    int n = Wi.size();
    vector<int> max_value(W + 1, 0);
    for(int w = 1; w <= W; w++) // Go from weight = 1 to W
    {
        for(int i = 0; i < n; i++) // Go through vectors of weight and cost 
        {
            if(Wi[i] <= w) // if we cat put item in backpack
            {
                max_value[w] = max(max_value[w], max_value[w - Wi[i]] + Ci[i]); // Choose max between old max and new max (new max is value we'd get if we freed some space to fit item I into a backpack)
            }
        }
    }
    return max_value[W];
}

int main(int argc, char* argv[])
{
    int W;
    vector<int> Wi;
    vector<int> Ci;
    if(argc == 1)
    {
        cout << "no input data! used default parameters: weight = 20, w1 = 1, w2 = 3, w3 = 4, c1 = 1, c2 = 4, c3 = 5" << endl;
        W = 13;
        Wi = {3, 5, 8};
        Ci = {8, 14, 23};
    }
    else if(argc == 2)
    {
        cout << "Inputed only backpack capacity. weight = 20, w1 = 1, w2 = 3, w3 = 4, c1 = 1, c2 = 4, c3 = 5" << endl;
        W = atoi(argv[1]);
        Wi = {1, 3, 4};
        Ci = {1, 4, 5};
    }
    else if(argc%2 == 1)
    {
        cout << "Unpaired parameter will be passed!" << endl;
        W = atoi(argv[1]);
        for(int i = 2; i + 1 < argc; i+=2)
        {
            Wi.push_back(atoi(argv[i]));
            Ci.push_back(atoi(argv[i+1]));
        }

        if(argc == 3)
        {
            cout << "No proper parameters. Used w1 = 1, w2 = 3, w3 = 4, c1 = 1, c2 = 4, c3 = 5" << endl;
            Wi = {1, 3, 4};
            Ci = {1, 4, 5}; 
        }
    }
    cout << "Max value: " << backpack(W, Wi, Ci) << endl;
}