#include <iostream>
#include <cmath>
#include <string>

using namespace std;

int multiply(int x, int y)
{
    if (x < 10 || y < 10)
        return x * y;

    cout << x << " " << y << endl;

    int length = max(to_string(x).length(), to_string(y).length());

    int a = x / pow(10, length/2);
    int b = x - a * pow(10, length/2);
    int c = y / pow(10, length/2);
    int d = y - c * pow(10, length/2);

    int ac = multiply(a, c);
    int bd = multiply(b, d);
    int abcd = multiply(a + b, c + d) - ac - bd;

    return abcd * pow(10, length/2) + ac * pow(10, length) + bd;
}

int main()
{
    int x = 9484;
    int y = 6261;
    cout << multiply(x, y) << " " << x * y;
}