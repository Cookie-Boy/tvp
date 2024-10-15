#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Number
{
    private:

    static int numA;
    static int numB;
    static int power;
    static int overflow;

    static void decompose(double a, double b)
    {
        numA = int(a);
        numB = int(b);
        double tmpa = a - numA;
        double tmpb = b - numB;
        while((tmpa > 1e-6))
        {
            numA *= 10;
            numA += int(tmpa * 10);
            tmpa = tmpa*10 - int(tmpa*10);
            power++;
        }
        
        while((tmpb > 1e-6))
        {
            numB *= 10;
            numB += int(tmpb * 10);
            tmpb = tmpb*10 - int(tmpb*10);
            power++;
        }
    }

    public:

    static double mult(double a, double b)
    {
        decompose(a, b);
        int tempA = numA;
        int tempB = numB;
        double result = 0;
        int maxLength = 0; // Максимальная длина строки, чтобы при выводе были норм отступы
        vector<string> items; // Вектор со строками, которые потом будем выводить

        string tempAStr = to_string(tempA);
        string tempBStr = to_string(tempB);
        items.push_back(to_string(tempA)); // Первое число
        items.push_back("*"); // Значок умножения
        items.push_back(to_string(tempB)); // Второе число
        
        maxLength = max(tempAStr.length(), tempBStr.length()); // Переопределяем максимальную длину
        string line(maxLength, '_');
        items.push_back(line); // Линия после двух чисел

        for (int i = 0; tempB != 0; i++) // Цикл, пока второе число не станет нулем (делим его на 10 на каждой итерации)
        {
            double preResult = 0;
            for (int j = 0; tempA != 0; j++)
            {
                preResult += (tempA % 10) * (tempB % 10 * pow(10, i + j)); // Домножаем на 10^(i + j) чтобы сделать сдвиг влево (как это делается при умножении в столбик)
                tempA /= 10;
            }
            result += preResult;
            tempA = numA; // Возвращаем tempA для следующей итерации
            tempB /= 10;
            string preResultStr = to_string((int)preResult);
            maxLength = max((int) preResultStr.length(), maxLength);
            items.push_back(preResultStr); // Добавляем результат на текущей итерации
        }

        string resultLine(maxLength, '_');
        items.push_back(resultLine);

        // Вывод
        for (int i = 0; i < items.size(); i++)
        {
            if (items[i] != "*" && items[i] != "+")
                for (int j = 0; j < maxLength - items[i].length(); j++)
                    cout << " ";
            cout << items[i] << endl;
        }

        result /= pow(10, power);
        cout << result << endl;
        return result;
    }

};

int Number::numB = 0;
int Number::numA = 0;
int Number::power = 0;
int Number::overflow = 0;

int main()
{
    double a = 123;
    double b = 45;
    Number::mult(a, b);
    return 0;
}