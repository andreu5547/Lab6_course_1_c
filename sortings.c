#include "sortings.h"
#define swap(a, b, type) type c = a; \
                          a = b;      \
                          b = c;

int partOfSortHoara(int *arr, int left, int right) { // Часть сортировки Хоара
    int pivot = arr[(left + right) / 2]; // Опорный элемент, относительно которого сортируем
    while (left <= right) { // Повторяем пока левый указатель меньше или равен правому
        // Идём по массиву пока не найдём элемент стоящий не на своём месте, либо = опорному
        while (arr[left] < pivot) // Ищем элемент слева, который больше или равен опорного
            left++;
        while (arr[right] > pivot) // Ищем элемент справа, который меньше или равен опорного
            right--;
        if (left <= right) { // Если левый указатель меньше или равен правому, то меняем местами найденные элементы и передвигаем указатели
            // Меняем элементы местами
            swap(arr[left], arr[right], int)
            left++;
            right--;
        }
    }
    return left; // Возвращаем левый указатель, тк до и после него отсортированный массив относительно опорного элемента
}

void quickSortHoara(int *arr, int start, int end) { // Сортировка Хоара основная функция
    if (start >= end) return; // Если индекс начала больше конца, выходим
    int rightStart = partOfSortHoara(arr, start, end); // Запускаем часть сортировки, она вернёт индекс, тк до и после него отсортированный массив относительно опорного элемента
    // Рекурсивно вызываем сортировку, но уже с новой границей
    quickSortHoara(arr, start, rightStart - 1);
    quickSortHoara(arr, rightStart, end);
}

/*--------------------------------------------------------------------------------------------------------------------*/

void quickSortHoara_loop(int *arr, int start, int end) {
    int left, right; // Указатели для внутренней сортировки
    int l_part, r_part; // Границы фрагмента массива, сортируемого в цикле
    // Очередь запросов
    int *l_query = malloc(sizeof(int) * (end - start + 1));
    int *r_query = malloc(sizeof(int) * (end - start + 1));

    // Каждый запрос задается парой значений, а именно: левой(l_part) и правой(r_part) границами промежутка
    int q_pos = 0; // Текущая позиция очереди
    l_query[0] = start; // Начальная позиция сортировки
    r_query[0] = end; // Конечная позиция сортировки

    do {
        // Берём границы участка, который будем сортировать
        l_part = l_query[q_pos];
        r_part = r_query[q_pos];
        q_pos--;
        do {
            int pivot_position = (l_part + r_part) / 2; // Находим позицию опорного элемента
            int pivot = arr[pivot_position]; // и сам опорный элемент
            // Границы, которые будем двигать
            left = l_part;
            right = r_part;
            do { //
                while (arr[left] < pivot) left++; // Ищем номер элемента слева, который больше или равен опорного
                while (pivot < arr[right]) right--; // Ищем номер элемента справа, который меньше или равен опорного
                if (left <= right) { // Если левый указатель меньше или равен правому, то меняем местами найденные элементы и передвигаем указатели
                    // Меняем элементы местами
                    swap(arr[left], arr[right], int)
                    left++;
                    right--;
                }
            } while (left <= right);  // Повторяем пока левый указатель меньше или равен правому
            // Сейчас указатель i указывает на начало правого подмассива,
            // j - на конец левого

            // Отправляем большую часть в очередь и двигаем r_part, l_part
            if (left < pivot_position) { // Правая часть больше
                if (left < r_part) { // Если в ней больше 1 элемента, то нужно сортировать (добавляем в очередь)
                    q_pos++;
                    l_query[q_pos] = left;
                    r_query[q_pos] = r_part;
                }
                r_part = right; // Следующая итерация разделения, будет работать с левой частью
            } else { // Левая часть больше
                if (right > l_part) {// Если в ней больше 1 элемента, то нужно сортировать (добавляем в очередь)
                    q_pos++;
                    l_query[q_pos] = l_part;
                    r_query[q_pos] = right;
                }
                l_part = left; // Следующая итерация разделения, будет работать с правой частью
            }
        } while (l_part < r_part); // Пока в меньшей части есть хотя бы 1 элемент повторяем
    } while (q_pos != -1); // Пока есть запросы в очереди повторяем
    // Очищаем память очередей
    free(l_query);
    free(r_query);
}

//*------------------------------------------------------------------------------------------------------------------*//

void Merge(int *arr, int start, int end) { // Функция слияния
    int l_iterator, r_iterator, middle; // Создаём переменные для итераторов левого и правого, а также для середины
    int *mas = (int*) malloc((end - start + 1) * sizeof(int)); // Буфер для хранения массива, получившегося в результате слияния

    middle = (start + end) / 2;
    l_iterator = start;
    r_iterator = middle + 1;

    // Слияние
    for (int i = start; i <= end; i++) {
        // если левый итератор не перешел середину && (правый итератор зашёл за конец || значение элемента массива на месте левого итератора меньше чем на месте правого)
        if ((l_iterator <= middle) && ((r_iterator > end) || (arr[l_iterator] < arr[r_iterator]))) {
            mas[i - start] = arr[l_iterator]; // то записываем элемент, стоящий на месте левого итератора
            l_iterator++;
        } else {
            mas[i - start] = arr[r_iterator]; // иначе на месте правого
            r_iterator++;
        }
    }

    for (int i = start; i <= end; i++) // Записываем собранный массив на его место в исходном
        arr[i] = mas[i-start];

    free(mas);
}

void mergeSort(int *arr, int start, int end) { // Сортировка слиянием основная функция
    if (start >= end) return; // Если индекс начала больше конца, выходим
    // Рекурсивно вызываем сортировку, но уже с новой границей (средний элемент и справа от среднего)
    int mid = (start + end) / 2;
    mergeSort(arr, start, mid);
    mergeSort(arr, mid + 1, end);

    Merge(arr, start, end); // Функция слияния
}

//*------------------------------------------------------------------------------------------------------------------*//

void ShellSort(int *arr, int size) {
    int step, i, j, tmp; // Переменные для шага, счётчиков и временная переменная
    for (step = size / 2; step > 0; step /= 2) // Выбираем шаг сортировки
        for (i = step; i < size; i++) { // Проходим по всему массиву
            tmp = arr[i]; // Записываем текущий элемент
            for (j = i; j >= step; j -= step) { // Начинаем мини-сортировку вставками
                if (tmp < arr[j - step]) // Если элемент меньше текущего(), то сдвигаем элементы дальше
                    arr[j] = arr[j - step];
                else // Иначе выходим их цикла
                    break;
            }
            arr[j] = tmp; // и записываем наш элемент на его новое место, уже отсортированное по шагу
        }
}

/*--------------------------------------------------------------------------------------------------------------------*/

int pow_(int x, int y) { // Возведение x в степень y
    int o = 1;
    for (int i = 0; i < y; ++i)
        o *= x;
    return o;
}

void radixSort(int *arr, int start, int end) {
    int base = 10; // Основание системы счисления
    int max_num = arr[0]; // Максимальное число в массиве
    for (int i = start; i < end; ++i) // Поиск максимального числа в массиве
        if (max_num < arr[i]) max_num = arr[i];
    int radx = 0; // Максимальный разряд
    while (max_num != 0) { // Вычисляем максимальный разряд по максимальному числу
        radx++;
        max_num /= base;
    }
    int *base_arr = malloc(sizeof(int) * base); // Массив для хранения кол-ва чисел в каждом отсеке массива по разрядам
    for (int i = 0; i < base; ++i) base_arr[i] = 0; // Заполняем его нулями
    int **digits_arr = malloc(sizeof(int*) * base); // Массив массивов с числами, по разрядам
    for (int i = 0; i < base; ++i)
        digits_arr[i] = malloc(sizeof(int) * (end - start + 1));

    for (int i = 0; i < radx; ++i) { // Проходимся по всем разрядам от 0 до последнего
        for (int j = start; j < end; ++j) { // Разбиваем исходный массив по разрядному числу во вспомогательный массив, попутно считая кол-во чисел в каждой ячейке
            int digit = (arr[j] / pow_(base, i)) % base;
            digits_arr[digit][base_arr[digit]++] = arr[j];
        }
        int count = 0;
        for (int j = 0; j < base; ++j) { // Собираем исходный массив обратно
            for (int k = 0; k < base_arr[j]; ++k) {
                arr[count++] = digits_arr[j][k];
            }
        }
        for (int j = 0; j < base; ++j) base_arr[j] = 0; // Очищаем хранилище для кол-ва цифр
    }
    // Очищаем память
    for (int i = 0; i < base; ++i)
        free(digits_arr[i]);
    free(digits_arr);
    free(base_arr);
}