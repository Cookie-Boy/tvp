#pragma once

#include <cmath>
#include <iostream>

using namespace std;

class Imaginary
{
    private:
    double real;
    double imag;
    double mod;
    double arg;
    void calc()
    {
        mod = sqrt(pow(real,2) + pow(imag,2));
        if(real > 0)
            arg = atan(imag/real);
        else if(real < 0 && imag >=0)
            arg = M_PI + atan(imag/real);
        else if(real < 0 && imag < 0)
            arg = -M_PI + atan(imag/real);
        else if(real == 0 && imag != 0)
            arg = imag > 0? M_PI/2 : -M_PI/2;
        else 
            arg = 0;
    }

    public:

    double getReal()
    {
        return real;
    }

    double getImag()
    {
        return imag;
    }

    void convert(double mod, double arg)
    {
        real = mod*cos(arg);
        imag = mod*sin(arg);
        this->mod = mod;
        this->arg = arg;
    }
    double sum(Imaginary number)
    {
        real+= number.getReal();
        imag+= number.getImag();
        calc();
    }

    void mult(Imaginary number)
    {
        double tmp = real * number.getReal() - imag * number.getImag();
        imag = real * number.getImag() + imag*number.getReal();
        real = tmp;
        calc();
    }

    double sum(double number)
    {
        real += number;
        calc();
    }

    void mult(double number)
    {
        real *= number;
        imag *= number;
        calc();
    }

    void div(double number)
    {
        real /= number;
        imag /= number;
        calc();
    }

    void div(Imaginary number)
    {
        double tmpReal = real * number.getReal() - imag * number.getImag();
        this->imag = real * number.getImag() + imag*number.getReal();
        this->real = tmpReal;
        calc();
    }

    void ex(Imaginary number)
    {
        double real = number.real;
        double imag = number.imag;
        this->real = exp(real) * cos(imag);
        this->imag = exp(real) * sin(imag);
    }

    void print()
    {
        cout << fixed << "Re = " << this->getReal() << ", Im = " << this->getImag() << endl;
    }

    Imaginary(): real(0), imag(0), arg(0), mod(0)
    {
    }
    Imaginary(double real, double imag): real(real), imag(imag)
    {
        calc();
    }
};