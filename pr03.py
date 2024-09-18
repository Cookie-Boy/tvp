import math
import numpy as np
import cmath
class ImaginaryNum:
    def __init__(self, a, b):
        self.a = a
        self.b = b

    def __add__(self, other):
        return ImaginaryNum(self.a + other.a, self.b + other.b)

    def __sub__(self, other):
        return ImaginaryNum(self.a - other.a, self.b - other.b)

    def __mul__(self, other):
        if isinstance(other, ImaginaryNum):
            return ImaginaryNum(self.a * other.a - self.b * other.b, self.a * other.b + self.b * other.a)
        elif isinstance(other, (float, int)):
            return ImaginaryNum(self.a * other, self.b * other)
        else:
            raise TypeError("Unsupported operand type")


    def __truediv__(self, other):
        if isinstance(other, ImaginaryNum):
            return ImaginaryNum((self.a * other.a + self.b * other.b) / (other.a * other.a + other.b * other.b), (self.b * other.a - self.a * other.b) / (other.a * other.a + other.b * other.b))
        elif isinstance(other, (float, int)):
            return ImaginaryNum(self.a / other, self.b / other)
        else:
            raise TypeError("Unsupported operand type")
        
    def __str__(self):
        if self.b < 0.0000001 and self.b > -0.0000001:
            return f"{self.a:.4f}"
        elif self.a < 0.0000001 and self.a > -0.0000001:
            return f"{self.b:.4f}i"
        else:
            return f"{self.a:.4f} + {self.b:.4f}i"
    
    def mod(self):
        return (self.a ** 2 + self.b ** 2) ** 0.5
    def arg(self):
        return math.atan2(self.b, self.a)
    
    @staticmethod
    def exp(i) -> 'ImaginaryNum': # e^ix = cos(x) + i*sin(x)
        if isinstance(i, ImaginaryNum):
            a = i.a
            b = i.b
            return ImaginaryNum(math.exp(a) * math.cos(b), math.exp(a) * math.sin(b))
        else:
            return ImaginaryNum(math.cos(i), math.sin(i))




def DiscreteFourierTransform(x):
    N = len(x)
    X = [ImaginaryNum(0, 0)] * N
    
    for k in range(N):
        for n in range(N):
            exp = -2 * math.pi * k * n / N
            X[k] += ImaginaryNum.exp(exp) * x[n]
    return X

def inverseFourierTransform(x):
    N = len(x)
    X = [ImaginaryNum(0, 0)] * N
    
    for k in range(N):
        for n in range(N):
            exp = 2 * math.pi * k * n / N
            X[k] += ImaginaryNum.exp(exp) * x[n] / N
    return X



def Semifast_Fourier(f):
    N = len(f)
    p1 = 1
    p2 = N
    for i in np.arange(1, math.sqrt(N) + 1, 1): # ищем факторы количества сигналов N, пока не найдем пару с минимальным различием p1 p2
        if (N % i == 0) and ((N / i - i) < (N - 1)):
            p1 = int(i) 
            p2 = int(N / p1)
    print(p1, p2)

    A1 = [ImaginaryNum(0,0)] * N
    i = ImaginaryNum(0, 1)
    for k1 in range(p1):
        for j2 in range(p2):
            for j1 in range(p1):
                A1[k1 + p1 * j2] += ImaginaryNum.exp(i * (-2) * math.pi * j1 * k1 / p1) * f[j2 + p2 * j1]
                #print("debug: ", k1, j2, j1, p1, p2, A1[k1 + p1 * j2], k1 + p1 * j2, "f", f[j2 + p2 * j1], j2 + p2 * j1, i * (-2) * math.pi * j1 * k1 / p1)  
            A1[k1 + p1 * j2] /= p1
    # for k1 in range(p1):
    #     for j2 in range(p2):
    #         #print("debug before:" , A1[k1 + p1 * j2], k1 + p1 * j2, p1)
            
    #         #print("debug after:" , A1[k1 + p1 * j2], k1 + p1 * j2, p1)
            

    print("A1:")
    for i, val in enumerate(A1):
        print(f"X[{i}] = {val}")
    A2 = [ImaginaryNum(0,0)] * N
    for k1 in range(p1):
        for k2 in range(p2):
            for j2 in range(p2):
                A2[k1 + p1 * k2] += A1[k1 + p1 * j2] * ImaginaryNum.exp(i * (-2) * math.pi * (  j2 / (p1 * p2) * (k1 + p1 * k2)))
                #print("debug: ", k1, j2, j1, p1, p2, A2[k1 + p1 * k2], k1 + p1 * j2, "A1", A1[k1 + p1 * j2], k1 + p1 * j2, i * (-2) * math.pi * ( (j1 * k1 / p1) +  j2 / (p1 * p2) * (k1 + p1 * k2)) )  
            A2[k1 + p1 * k2] /= p2
    print("A2:")
    for i, val in enumerate(A2):
        val = val * N
        print(f"X[{i}] = {val}")
    return A2

    

if __name__ == "__main__":
    input_signal = [3,0,2,2,2,3,4,2,4,5]
    dft_result = DiscreteFourierTransform(input_signal)
    
    for i, val in enumerate(dft_result):
        print(f"X[{i}] = {val}")
    input_signal2 = [3,0,2,2,2,3,4,2,4,5]
    ppf_result = Semifast_Fourier(input_signal2)

    print("inverse_result")
    inverse_result = inverseFourierTransform(dft_result)
    for i, val in enumerate(inverse_result):
        print(f"X[{i}] = {val}")

