#include <iostream>
#include "imaginary.h"

using namespace std;

Imaginary *dft(double *array, int n)
{
    Imaginary *result = new Imaginary[n];
    Imaginary *value = new Imaginary(0, -2 * M_PI);
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double mod = array[j];
            double arg = value->getImag() * i * j / n;
            Imaginary temp;
            temp.convert(mod, arg);
            result[i].sum(temp);
        }
    }

    return result;
}

int main()
{
    int n = 4;
    double array[n] = {3, 79, 92, 12};
    Imaginary *result = dft(array, n);
    for (int i = 0; i < n; i++)
    {
        cout << fixed << "Re(" << i << ") = " << result[i].getReal() << ", Im(" << i << ") = " << result[i].getImag() << endl;
    }
    return 0;
}