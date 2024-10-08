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
x = np.array([1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16])
X = fft(x)
print(X)