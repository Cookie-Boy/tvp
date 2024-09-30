#include <iostream>
#include "imaginary.h"

using namespace std;

Imaginary* fft(Imaginary arr[], int n)
{
    if(n <= 1)
        return arr;
    
    double array[n];

    for(int i = 0; i < n; i++)
        array[i] = (double)i/n;

    Imaginary* even = new Imaginary[(n + 1)/2];
    Imaginary* odd = new Imaginary[(n + 1)/2];

    for(int i = 0; i < n; i += 2)
    {
        even[i/2] = arr[i];
        odd[i/2] = arr[i + 1];
    }

    Imaginary* mass = new Imaginary[n];

    for(int i = 0; i < n; i++)
    {
        mass[i].convert(1, -2 * M_PI * array[i]);
    }

    even = fft(even, (n+1)/2);
    odd = fft(odd, (n+1)/2);
    
    for(int i = 0; i < (n + 1)/2; i++)
    {   
        mass[i].mult(odd[i]);
        mass[i].sum(even[i]);
    }
    int j = 0;
    for(int i = (n + 1)/2; i < n; i++)
    {
        mass[i].mult(odd[j]);
        mass[i].sum(even[j++]);
    }

    return mass;
}

Imaginary *reverse(Imaginary *array, int n)
{
    Imaginary *result = new Imaginary[n];
    double theta = -2 * M_PI;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            result[i].sum(array[j].getReal()*cos(theta*i*j/n)/n + array[j].getImag()*sin(theta*i*j/n)/n);
        }
    }

    return result;
}

int check(int n)
{
    if((n & (n - 1)) == 0) // Хитрый бинарный трюк на проверку является ли число степенью 2
        return n;           // возвращаем само число, если оно является степенью двойки
    return (pow(2, (int)log2(n) + 1)); // Возвращаем ближайшую степень двойки
    
}

int main()
{
    int n = 15;
    Imaginary arr[n] = {Imaginary(1,0), Imaginary(2,0), Imaginary(3,0), Imaginary(4,0), Imaginary(5,0), Imaginary(6,0), Imaginary(7,0), Imaginary(8,0), Imaginary(9,0), Imaginary(10,0), Imaginary(11,0), Imaginary(12,0), Imaginary(13,0), Imaginary(14,0), Imaginary(15,0)};

    int newN = check(n); // Проверяет, чтобы число было степенью 2
    cout << "New N: " << newN << endl;
    Imaginary newArr[newN];
    for(int i = 0; i < n; i++)
        newArr[i] = arr[i];
    for(int i = n; i < newN; i++)
        newArr[i] = Imaginary(0, 0);
    
    Imaginary* result = fft(newArr, newN);
    result = reverse(result, newN);
        
    for (int i = 0; i < newN; i++)
    {
        cout << fixed << "Re(" << i << ") = " << result[i].getReal() << ", Im(" << i << ") = " << result[i].getImag() << endl;
    }

    return 0;
}