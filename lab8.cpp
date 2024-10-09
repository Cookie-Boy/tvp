#include <iostream>
#include <vector>
#include "imaginary.h"

using namespace std;

void printVector(vector<int> v, const char* name)
{
    cout << name << ":\t";
    cout << "[";
    for(int i: v)
        cout << i << " ";
    cout << "]" << endl;
}

void printVector(vector<Imaginary> &v, const char* name)
{
    cout << name << ":\t";
    cout << "[";
    for(Imaginary i: v)
        cout << fixed << i.getReal() << " ";
    cout << "]" << endl;
}

vector<Imaginary> reverse(vector<Imaginary> &array)
{
    int n = array.size();
    vector<Imaginary> result (n);
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

vector<Imaginary> fft(vector<Imaginary> &arr)
{
    int n = arr.size();
    if (n <= 1)
        return arr;
    
    double array[n];

    for (int i = 0; i < n; i++)
        array[i] = (double)i/n;

    vector<Imaginary> even((n + 1) / 2);
    vector<Imaginary> odd((n + 1) / 2);

    for (int i = 0; i < n; i += 2)
    {
        even[i / 2] = arr[i];
        odd[i / 2] = arr[i + 1];
    }

    vector<Imaginary> mass(n);

    for (int i = 0; i < n; i++)
    {
        mass[i].convert(1, -2 * M_PI * array[i]);
    }

    even = fft(even);
    odd = fft(odd);
    
    for (int i = 0; i < (n + 1) / 2; i++)
    {   
        mass[i].mult(odd[i]);
        mass[i].sum(even[i]);
    }
    int j = 0;
    for (int i = (n + 1) / 2; i < n; i++)
    {
        mass[i].mult(odd[j]);
        mass[i].sum(even[j++]);
    }

    return mass;
}

int check(int n)
{
    if((n & (n - 1)) == 0) // Хитрый бинарный трюк на проверку является ли число степенью 2
        return n;           // возвращаем само число, если оно является степенью двойки
    return (pow(2, (int)log2(n) + 1)); // Возвращаем ближайшую степень двойки
    
}

void svertka(vector<Imaginary> &v1, vector<Imaginary> &v2, vector<Imaginary> &result)
{
    v1 = fft(v1);
    v2 = fft(v2);
    
    for(int i = 0; i < result.size(); i++)
    {
        result[i].sum(v1[i]);
        result[i].mult(v2[i]);
    }
    result = reverse(result);
}

int main()
{
    vector<Imaginary> v1(10);
    vector<Imaginary> v2(5);

    for(int i = 0; i < v1.capacity(); i++)
        v1[i].sum(i);

    for(int i = 0; i < v2.capacity(); i++)
        v2[i].sum(2*i);

    vector<Imaginary> result (check(v1.size() + v2.size() -1));

    v1.resize(result.size());
    v2.resize(result.size());

    svertka(v1, v2, result);
    
    printVector(result, "Result");
    return 0;
}