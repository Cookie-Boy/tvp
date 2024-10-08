import numpy as np

class Imaginary:
    def __init__(self, real=0.0, imag=0.0):
        self.real = real
        self.imag = imag
        self.calc()

    def calc(self):
        self.mod = np.sqrt(self.real**2 + self.imag**2)
        if self.real > 0:
            self.arg = np.arctan(self.imag / self.real)
        elif self.real < 0 and self.imag >= 0:
            self.arg = np.pi + np.arctan(self.imag / self.real)
        elif self.real < 0 and self.imag < 0:
            self.arg = -np.pi + np.arctan(self.imag / self.real)
        elif self.real == 0 and self.imag != 0:
            self.arg = np.pi / 2 if self.imag > 0 else -np.pi / 2
        else:
            self.arg = 0

    def convert(self, mod, arg):
        self.real = mod * np.cos(arg)
        self.imag = mod * np.sin(arg)
        self.mod = mod
        self.arg = arg

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

def fft(arr):
    n = len(arr)
    if n <= 1:
        return arr

    even = fft(arr[0::2])
    odd = fft(arr[1::2])

    combined = [Imaginary() for _ in range(n)]
    for k in range(n // 2):
        t = Imaginary()
        t.convert(1, -2 * np.pi * k / n)
        t.mult(odd[k])
        combined[k] = Imaginary(even[k].real + t.real, even[k].imag + t.imag)
        combined[k + n // 2] = Imaginary(even[k].real - t.real, even[k].imag - t.imag)
    
    return combined

def reverse(arr):
    n = len(arr)
    if n <= 1:
        return arr
    
    conjugate = [Imaginary(x.real, -x.imag) for x in arr]
    fft_result = fft(conjugate)

    return [Imaginary(x.real / n, x.imag / n) for x in fft_result]

def check(n):
    if (n & (n - 1)) == 0:
        return n
    return 2 ** (int(np.log2(n)) + 1)

def convolution(x, h):
    size_x = len(x)
    size_h = len(h)
    n = check(size_x + size_h - 1)

    # Обнуление входных данных до длины n
    x_padded = x + [Imaginary(0, 0)] * (n - size_x)
    h_padded = h + [Imaginary(0, 0)] * (n - size_h)
    
    # Вычислите БПФ для обеих последовательностей
    X = fft(x_padded)
    H = fft(h_padded)

    # Поточечное умножение в частотной области
    Y = [Imaginary() for _ in range(n)]
    for i in range(n):
        Y[i] = Imaginary(X[i].real * H[i].real - X[i].imag * H[i].imag,
                         X[i].real * H[i].imag + X[i].imag * H[i].real)

    # Вычислите значение этого результата
    return reverse(Y)

def main():
    n = 16
    arr = [Imaginary(i, 0) for i in range(1, n + 1)]
    
    newN = check(n)
    arr += [Imaginary(0, 0)] * (newN - n)  # Add zeros to make it power of 2

    # Compute FFT
    result = fft(arr)
    
    print("FFT Result:")
    for i in range(newN):
        result[i].print()

    # Compute IFFT
    ifft_result = reverse(result)

    print("\nIFFT Result:")
    for i in range(newN):
        ifft_result[i].print()

    # Define two sequences to convolve
    x = [Imaginary(1, 0), Imaginary(2, 0), Imaginary(3, 0), Imaginary(4, 0), Imaginary(5, 0)]
    h = [Imaginary(6, 0), Imaginary(7, 0), Imaginary(8, 0)]

    # Compute convolution
    conv_result = convolution(x, h)

    print("\nConvolution Result:")
    for i in range(len(conv_result)):
        conv_result[i].print()

if __name__ == "__main__":
    main()