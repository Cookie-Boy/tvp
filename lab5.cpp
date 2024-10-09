#include <iostream>
#include <vector>

using namespace std;

void printVector(vector<int> v, const char* name)
{
    cout << name << ":";
    cout << "[";
    for(int i: v)
        cout << i << " ";
    cout << "]" << endl;
}

int main()
{
    vector<int> v1 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> v2 {0, 2, 4, 6, 8};
    vector<int> result (v1.size() + v2.size() - 1, 0);

    if(v1.size() != v2.size())
    {
        if(v1.size() < v2.size())
            v1.resize(v2.size(), 0);
        else 
            v2.resize(v1.size(), 0);
    }


    for(int i = 0; i < result.size(); i++)
    {   
        for(int k = 0; k < v1.size(); k++)
        {   
            int j = i - k;
            if(j >= 0 && j < v1.size())
            result[i] += v1[j] * v2[k];
        }
    }
    printVector(v1, "Vector 1");
    printVector(v2, "Vector 2");
    printVector(result, "Result vector");
}