#include <iostream>
#include <time.h>

using namespace std;

int C = 0;

void selectSort(int *array, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (array[j] < array[minIdx])
                minIdx = j;
            C++;
        }
        if (i != minIdx)
        {
            int buffer = array[i];
            array[i] = array[minIdx];
            array[minIdx] = buffer;
        }
    }
}

void bubbleSort(int *array, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                int buffer = array[j];
                array[j] = array[j + 1];
                array[j + 1] = buffer;
            }
            C++;
        }
    }
}

void merge(int *array, int n, int left, int mid, int right)
{
    int tmp[n];
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        if (array[i] <= array[j])
            tmp[k++] = array[i++];
        else
            tmp[k++] = array[j++];
        C++;
    }

    while (i <= mid)
        tmp[k++] = array[i++];

    while (j <= right)
        tmp[k++] = array[j++];

    for (int i = left; i <= right; i++)
        array[i] = tmp[i];
}

void mergeSort(int *array, int n)
{
    // l - размер подмассивов для слияния
    for (int l = 1; l < n; l *= 2)
    {
        for (int left = 0; left < n - l; left += 2 * l)
        {
            int mid = left + l - 1;
            int right = min(left + 2 * l - 1, n - 1); // Для случая, когда выходим за границы массива (left + 2 * l - 1 > n)
            merge(array, n, left, mid, right);
        }
    }
}

void printArray(int *array, int n)
{
    for (int i = 0; i < n; i++)
        cout << array[i] << " ";
    cout << endl;
}

int main()
{
    int n = 10;
    srand(time(NULL));
    int selectArray[n];
    int bubbleArray[n];
    int mergeArray[n];
    cout << "Random array: " << endl;
    for (int i = 0; i < n; i++)
    {
        selectArray[i] = rand() % 100;
        mergeArray[i] = bubbleArray[i] = selectArray[i];
        cout << mergeArray[i] << " ";
    }
    cout << endl;

    cout << endl << "Select sort: " << endl;
    selectSort(selectArray, n);
    printArray(selectArray, n);
    cout << "Comparisons: " << C << endl;
    C = 0;

    cout << endl << "Bubble sort: " << endl;
    bubbleSort(bubbleArray, n);
    printArray(bubbleArray, n);
    cout << "Comparisons: " << C << endl;
    C = 0;

    cout << endl << "Merge sort: " << endl;
    mergeSort(mergeArray, n);
    printArray(mergeArray, n);
    cout << "Comparisons: " << C << endl;
    C = 0;
    return 0;
}