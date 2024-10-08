#include <iostream>
using namespace std;

int main()
{
    int n = 10;
    int arr1[n] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int arr2[n] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int res[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for(int i = 0; i < n; i++)
    {   
        int j = 0;
        for(int k = i; k >= j; k--)
        {   
            j = i - k;
            if(k != j)
                res[i] = arr1[j] * arr2[k] + arr1[k] * arr2[j];
            else 
                res[i] = arr1[j] * arr2[k];
        }
    }
    for(int i = 0; i < n; i++)
        cout << "el: " << i << " " << "val: " << res[i] << endl;
}