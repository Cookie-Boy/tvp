#include <iostream>
#include "imaginary.h"

using namespace std;

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

int mirr(int n, int pow)
{
    int tmp = 0;
    for(int i = 0; i < pow; i++)
        tmp = tmp | ((1 & (n >> (pow - 1 - i))) << i);
    return tmp;
}

void BinArrange(double arr[], int n)
{
    int power = log2(n);
    for(int i = 0; i < n/2; i++)
    {
        double tmp = arr[i];
        arr[i] = arr[mirr(i, power)];
        arr[mirr(i, power)] = tmp;
    }
}

int main()
{
    int n = 12;
    double arr[n] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int newN = check(n); // Проверяет, чтобы число было степенью 2
    double newArr[newN];
    for(int i = 0; i < n; i++)
        newArr[i] = arr[i];
    for(int i = n; i < newN; i++)
        newArr[i] = 0;
    BinArrange(newArr, newN);
    for(int i = 0; i < newN; i++)
        cout << newArr[i] << " ";
    cout << endl;
    BinArrange(newArr, newN);
        for(int i = 0; i < newN; i++)
        cout << newArr[i] << " ";
    return 0;
}