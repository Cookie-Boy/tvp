#include <cmath>
#include <iostream>
#include <string>


using namespace std;

int powerOfTen(int n)
{
    int result = 1;
    for (int i = 0; i < n; ++i)
        result *= 10;
    return result;
}

int multiply(int x, int y)
{
    if (x < 10 || y < 10)
        return x * y;

    cout << x << " " << y << endl;

    int length = max(to_string(x).length(), to_string(y).length());
    int n = length / 2;

    int a = x / powerOfTen(n);
    int b = x % powerOfTen(n);
    int c = y / powerOfTen(n);
    int d = y % powerOfTen(n);

    int ac = multiply(a, c);
    int bd = multiply(b, d);
    int abcd = multiply(a + b, c + d) - ac - bd;

    return ac * powerOfTen(n * 2) + abcd * powerOfTen(n) + bd;
}

int main()
{
    int x = 9484;
    int y = 6261;
    cout << multiply(x, y) << " " << x * y;
}