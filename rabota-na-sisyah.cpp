#include <iostream>

using namespace std;

int main() 
{
    // int a, b, c;
    // cin >> a >> b >> c;
    // cout << "Sr = " << double(a + b + c)/3 << endl;
    // int zaranee = 0;
    // for(int i = 1; i <= 100; i++)
    // {
    //     zaranee += i;
    // }
    // cout << zaranee << endl;
    int n;
    cout << "Enter ypur dimple" << endl;
    cin >> n;
    if(n == 1)
    {
        cout << "is not simple dimple cause it's one, silly" << endl;
        return 0;
    }
    for(int i = 2; i < n; i++)
    {
        if(n%i == 0)
        {
            cout << "is not simple dimple, dividable by " << i << endl;
            return 0;
        }
    }
    cout << "Is exactly a simple dimple as simple dimple as it can ever be" << endl;
    return 0;
}