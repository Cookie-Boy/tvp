import numpy as np

def dft(x):
    N = len(x)
    X = np.zeros(N, dtype=complex)  # Массив для хранения результатов
    for k in range(N):
        for n in range(N):
            X[k] += x[n] * np.exp(-2j * np.pi * k * n / N)
    return X

# Входные данные (например, сигнал)
x = np.array([3, 79, 92, 12])

# Вычисление ДПФ
X = dft(x)

print("Ручное Дискретное преобразование Фурье:")
print(X)