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

# Пример использования
if __name__ == "__main__":
    x = [1, 2, 3, 4, 5]  # Входной сигнал
    h = [6, 7, 8]        # Фильтр
    
    result = simple_convolution(x, h)
    print("Результат свертки:", result)

