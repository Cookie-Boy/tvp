import numpy as np

class Imaginary:
    def __init__(self, real=0.0, imag=0.0):
        self.real = real
        self.imag = imag
        self.calc()

    def calc(self):
        self.mod = np.sqrt(self.real**2 + self.imag**2)
        self.arg = np.arctan2(self.imag, self.real)

    def convert(self, mod, arg):
        self.real = mod * np.cos(arg)
        self.imag = mod * np.sin(arg)
        self.calc()

    def sum(self, number):
        if isinstance(number, Imaginary):
            self.real += number.real
            self.imag += number.imag
        else:
            self.real += number
        self.calc()

    def mult(self, number):
        if isinstance(number, Imaginary):
            tmp = self.real * number.real - self.imag * number.imag
            self.imag = self.real * number.imag + self.imag * number.real
            self.real = tmp
        else:
            self.real *= number
            self.imag *= number
        self.calc()

    def div(self, number):
        if isinstance(number, Imaginary):
            denom = number.real**2 + number.imag**2
            temp_real = (self.real * number.real + self.imag * number.imag) / denom
            self.imag = (self.imag * number.real - self.real * number.imag) / denom
            self.real = temp_real
        else:
            self.real /= number
            self.imag /= number
        self.calc()

    def ex(self, number):
        self.real = np.exp(number.real) * np.cos(number.imag)
        self.imag = np.exp(number.real) * np.sin(number.imag)
        self.calc()

    def print(self):
        print(f"Re = {self.real:.4f}, Im = {self.imag:.4f}")

def ppf(array, n):
    p1 = 1
    p2 = n
    for i in range(1, int(np.sqrt(n)) + 1):
        if n % i == 0:
            p1 = i
            p2 = n // i

    A1 = [Imaginary() for _ in range(n)]
    for k1 in range(p1):
        for j2 in range(p2):
            for j1 in range(p1):
                value = Imaginary()
                value.ex(Imaginary(0, -2 * np.pi * j1 * k1 / p1))
                value.mult(array[j2 + p2 * j1].real)  # Get real part to multiply
                A1[k1 + p1 * j2].sum(value)
            A1[k1 + p1 * j2].div(p1)

    A2 = [Imaginary() for _ in range(n)]
    for k1 in range(p1):
        for k2 in range(p2):
            for j2 in range(p2):
                value = Imaginary()
                value.ex(Imaginary(0, -2 * np.pi * (j2 / (p1 * p2) * (k1 + p1 * k2))))
                value.mult(A1[k1 + p1 * j2])
                A2[k1 + p1 * k2].sum(value)
            A2[k1 + p1 * k2].div(p2)
            A2[k1 + p1 * k2].mult(n)

    return A2

def reverse(array, n):
    p1 = 1
    p2 = n
    for i in range(1, int(np.sqrt(n)) + 1):
        if n % i == 0:
            p1 = i
            p2 = n // i

    A1 = [Imaginary() for _ in range(n)]
    for k1 in range(p1):
        for j2 in range(p2):
            for j1 in range(p1):
                value = Imaginary()
                value.ex(Imaginary(0, 2 * np.pi * j1 * k1 / p1))
                value.mult(array[j2 + p2 * j1])
                A1[k1 + p1 * j2].sum(value)

    A2 = [Imaginary() for _ in range(n)]
    for k1 in range(p1):
        for k2 in range(p2):
            for j2 in range(p2):
                value = Imaginary()
                value.ex(Imaginary(0, 2 * np.pi * (j2 / (p1 * p2) * (k1 + p1 * k2))))
                value.mult(A1[k1 + p1 * j2])
                A2[k1 + p1 * k2].sum(value)
            A2[k1 + p1 * k2].div(n)

    return A2

def check(n):
    if (n & (n - 1)) == 0:
        return n
    return 2 ** (int(np.log2(n)) + 1)

def convolution(x, h):
    size_x = len(x)
    size_h = len(h)
    n = check(size_x + size_h - 1)

    # Паддинг массивов
    x_padded = x + [Imaginary(0, 0)] * (n - size_x)
    h_padded = h + [Imaginary(0, 0)] * (n - size_h)

    # Применение FFT к обоим массивам
    X = ppf(x_padded, n)
    H = ppf(h_padded, n)

    # Поэлементное произведение в частотной области
    Y = [Imaginary() for _ in range(n)]
    for i in range(n):
        Y[i] = Imaginary(X[i].real * H[i].real - X[i].imag * H[i].imag,
                         X[i].real * H[i].imag + X[i].imag * H[i].real)

    # Обратное преобразование
    return reverse(Y, n)

def main():
    x = [Imaginary(1, 0), Imaginary(2, 0), Imaginary(3, 0), Imaginary(4, 0), Imaginary(5, 0)]
    h = [Imaginary(6, 0), Imaginary(7, 0), Imaginary(8, 0)]

    # Вычисление свертки
    conv_result = convolution(x, h)

    print("Результат свертки:")
    for i in range(len(conv_result)):
        conv_result[i].print()

    # Вычисление и вывод полубыстрого преобразования Фурье для массива от 1 до 16
    array_ff = [Imaginary(float(i), 0) for i in range(1, 17)]
    n_ff = len(array_ff)

    fft_result = ppf(array_ff, n_ff)

    print("\nПолубыстрое преобразование Фурье для массива от 1 до 16:")
    for i in range(len(fft_result)):
        fft_result[i].print()

    # Обратное преобразование
    inverse_fft_result = reverse(fft_result, n_ff)

    print("\nРезультат обратного преобразования Фурье:")
    for i in range(len(inverse_fft_result)):
        inverse_fft_result[i].print()

if __name__ == "__main__":
    main()