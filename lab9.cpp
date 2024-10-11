#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Number
{
    public:

    static int integerA;
    static int fractionA;
    static int integerB;
    static int fractionB;
    static int overflow;


    static void decompose(double a, double b)
    {
        integerA = int(a);
        integerB = int(b);
        double tmpa = a - integerA;
        double tmpb = b - integerB;
        while((tmpa > 1e-6) || (tmpb > 1e-6))
        {
            fractionA *= 10;
            fractionB *= 10;
            fractionA += int(tmpa*10);
            fractionB += int(tmpb*10);
            tmpa = tmpa*10 - int(tmpa*10);
            tmpb = tmpb*10 - int(tmpb*10);
        }
    }

    public:

    static double mult(double a, double b)
    {
        decompose(a, b);
        cout << "a " << integerA << " " << fractionA << " b " << integerB << " " << fractionB << endl;
    }

};

    int Number::fractionA = 0;
    int Number::fractionB = 0;
    int Number::integerA = 0;
    int Number::integerB = 0;


int main()
{
    double a = 15.15;
    double b = 1.5;
    cout << "\t" << a << endl;
    cout << "\t" << b << endl;

    Number::mult(a, b);

    // cout << mult(first, second) << endl;
    return 0;
}