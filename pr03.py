import numpy as np

def fft(x):
    N = len(x)
    if N <= 1:
        return x
    else:
        even = fft(x[0::2])
        odd = fft(x[1::2])
        T = np.exp(-2j * np.pi * np.arange(N) / N)
        return np.concatenate([even + T[:N//2] * odd,
                               even + T[N//2:] * odd])

# Пример использования
x = np.array([3, 79, 92, 12])
X = fft(x)
print(X)