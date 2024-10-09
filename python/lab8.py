def simple_convolution(x, h):
    # Размеры входных последовательностей
    len_x = len(x)
    len_h = len(h)
    
    # Длина выходной последовательности
    len_y = len_x + len_h - 1
    
    # Инициализация массива для результата
    y = [0] * len_y
    
    # Выполнение свертки
    for n in range(len_y):
        # Суммируем произведения
        for k in range(len_h):
            if 0 <= n - k < len_x:
                y[n] += x[n - k] * h[k]
    
    return y
def matvei_hren(a,b):
    len_a = len(a)
    len_b = len(b)
    c = (len_a + len_b - 1) * [0]
    for i in range(len_a):
        for j in range(len_b):
            c[i + j] += (a[i] * b[j])
    return c

# Пример использования
if __name__ == "__main__":
    x = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]  # Входной сигнал
    h = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]        # Фильтр
    
    result = matvei_hren(x, h)
    print("Результат свертки:", result)
    result2 = simple_convolution(x, h)
    print("Результат свертки:", result2)
