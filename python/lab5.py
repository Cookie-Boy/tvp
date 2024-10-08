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

    def print(self):
        print(f"Re = {self.real:.4f}, Im = {self.imag:.4f}")

def dft(array):
    n = len(array)
    result = [Imaginary() for _ in range(n)]
    
    for i in range(n):
        for j in range(n):
            mod = array[j].real  # Получение действительной части
            arg = -2 * np.pi * i * j / n
            temp = Imaginary()
            temp.convert(mod, arg)
            result[i].sum(temp)

    return result

def reverse(array):
    n = len(array)
    result = [Imaginary() for _ in range(n)]
    theta = -2 * np.pi

    for i in range(n):
        for j in range(n):
            real_part = array[j].real * np.cos(theta * i * j / n) / n
            imag_part = array[j].imag * np.sin(theta * i * j / n) / n
            result[i].sum(real_part + imag_part)

    return result

def check(n):
    if (n & (n - 1)) == 0:
        return n
    return 2 ** (int(np.log2(n)) + 1)

def convolution(x, h):
    size_x = len(x)
    size_h = len(h)
    n = check(size_x + size_h - 1)

    # Заполнение нулем
    x_padded = x + [Imaginary(0, 0)] * (n - size_x)
    h_padded = h + [Imaginary(0, 0)] * (n - size_h)

    # Вычислите DFT для обеих последовательностей
    X = dft(x_padded)
    H = dft(h_padded)

    # Поточечное умножение в частотной области
    Y = [Imaginary() for _ in range(n)]
    for i in range(n):
        Y[i] = Imaginary(X[i].real * H[i].real - X[i].imag * H[i].imag,
                         X[i].real * H[i].imag + X[i].imag * H[i].real)

    # Вычисление обратного значения DFT результата
    return reverse(Y)

def main():
    n = 16
    arr = [Imaginary(i, 0) for i in range(1, n + 1)]
    
    newN = check(n)
    arr += [Imaginary(0, 0)] * (newN - n)  # Добавляем нули, чтобы получить степень 2

    dft_result = dft(arr)
    
    print("DFT Result:")
    for i in range(newN):
        dft_result[i].print()

    idft_result = reverse(dft_result)

    print("\nIDFT Result:")
    for i in range(newN):
        idft_result[i].print()

    # Определим две последовательности для свертки
    x = [Imaginary(1, 0), Imaginary(2, 0), Imaginary(3, 0), Imaginary(4, 0), Imaginary(5, 0)]
    h = [Imaginary(1, 0), Imaginary(1, 0), Imaginary(1, 0)]

    # Вычислим свертку
    conv_result = convolution(x, h)

    print("\nConvolution Result:")
    for i in range(len(conv_result)):
        conv_result[i].print()

if __name__ == "__main__":
    main()