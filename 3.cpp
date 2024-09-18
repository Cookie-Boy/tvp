#include "imaginary.h"

Imaginary* ppf(Imaginary array[], int n)
{
    int p1 = 1, p2 = n;
    for (int i = 1; i < sqrt(n) + 1; i++)
    {
        if (n % i == 0)
        {
            p1 = i;
            p2 = n / i;
        }
    }
    // то, что внутри exp - arg, mod - на что умножаем exp
    Imaginary *A1 = new Imaginary[n];
    for (int k1 = 0; k1 < p1; k1++)
    {
        for (int j2 = 0; j2 < p2; j2++)
        {
            for (int j1 = 0; j1 < p1; j1++)
            {
                Imaginary value;
                value.convert(array[j2 + p2 * j1].getReal(), -2 * M_PI * j1 * k1 / p1);
                A1[k1 + p1 * j2].sum(value);
            }
            A1[k1 + p1 * j2].div(p1);
        }
    }

    Imaginary *A2 = new Imaginary[n];
    for (int k1 = 0; k1 < p1; k1++)
    {
        for (int k2 = 0; k2 < p2; k2++)
        {
            for (int j2 = 0; j2 < p2; j2++)
            {
                Imaginary value;
                Imaginary ivalue;
                value.convert(A1[k1 + p1 * j2].getReal(), -2 * M_PI * (j2 / (p1 * p2) * (k1 + p1 * k2)));
                ivalue.convert(A1[k1 + p1 * j2].getImag(), -2 * M_PI * (j2 / (p1 * p2) * (k1 + p1 * k2)));
                value.sum(ivalue);
                A2[k1 + p1 * k2].sum(value);
            }
            A2[k1 + p1 * k2].div(p2);
        }
    }

    cout << "A1" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << fixed << "Re(" << i << ") = " << A1[i].getReal() << ", Im(" << i << ") = " << A1[i].getImag() << endl;
    }

    cout << "A2" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << fixed << "Re(" << i << ") = " << A2[i].getReal() << ", Im(" << i << ") = " << A2[i].getImag() << endl;
    }

    return array;
}

int main()
{
    int n = 15;
    Imaginary NoProblem[n];
    for (int i = 0; i < n; i++)
    {
        NoProblem[i] = Imaginary(i + 1, 0);
    }
    
    Imaginary* result = ppf(NoProblem, n);
        
    // for (int i = 0; i < n; i++)
    // {
    //     cout << fixed << "Re(" << i << ") = " << result[i].getReal() << ", Im(" << i << ") = " << result[i].getImag() << endl;
    // }
    return 0;
}