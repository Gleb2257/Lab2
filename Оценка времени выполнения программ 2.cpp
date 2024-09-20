#include <iostream>
#include <stack>
#include <cstdlib>
#include <algorithm>  // Для qsort и std::sort
#include <chrono>     // Для замера времени
#include <locale>     

using namespace std;
using namespace std::chrono;

// Вспомогательная функция для перестановки элементов
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void quicksort_iterative(int* items, int left, int right) {
    stack<pair<int, int>> stack;
    stack.push({ left, right });

    while (!stack.empty()) {
        auto range = stack.top();
        stack.pop();
        left = range.first;
        right = range.second;

        while (left < right) {
            int i = left, j = right;
            int pivot = items[(left + right) / 2];

            while (i <= j) {
                while (items[i] < pivot) i++;
                while (items[j] > pivot) j--;
                if (i <= j) {
                    swap(items[i], items[j]);
                    i++;
                    j--;
                }
            }

            // Обрабатываем меньший подмассив
            if (j - left < right - i) {
                if (left < j) stack.push({ left, j });
                left = i;
            }
            else {
                if (i < right) stack.push({ i, right });
                right = j;
            }
        }
    }
}

// Вспомогательная функция для вызова qsort
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Функция для замера времени работы сортировок
void measure_time(void (*sort_func)(int*, int, int), int* arr, int size, const string& description) {
    int* copy_arr = new int[size];
    copy(arr, arr + size, copy_arr);  

    auto start = high_resolution_clock::now();
    sort_func(copy_arr, 0, size - 1);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start).count();
    cout << description << " заняла: " << duration << " мс." << endl;

    delete[] copy_arr;
}

void std_sort_wrapper(int* arr, int left, int right) {
    sort(arr, arr + (right + 1));
}

void qsort_wrapper(int* arr, int left, int right) {
    qsort(arr, right - left + 1, sizeof(int), compare);
}

int main() {
  
    setlocale(LC_ALL, "Russian");

    const int SIZE = 10000;
    int arr[SIZE];

    // Генерация различных массивов
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 100;
    }
    cout << "Оценка времени работы на случайных данных:" << endl;
    measure_time(quicksort_iterative, arr, SIZE, "Итеративная быстрая сортировка");
    measure_time(std_sort_wrapper, arr, SIZE, "Стандартная std::sort");
    measure_time(qsort_wrapper, arr, SIZE, "Стандартная qsort");

    // Возрастающая последовательность
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i;
    }
    cout << "\nОценка времени работы на возрастающей последовательности:" << endl;
    measure_time(quicksort_iterative, arr, SIZE, "Итеративная быстрая сортировка");
    measure_time(std_sort_wrapper, arr, SIZE, "Стандартная std::sort");
    measure_time(qsort_wrapper, arr, SIZE, "Стандартная qsort");

    // Убывающая последовательность
    for (int i = 0; i < SIZE; i++) {
        arr[i] = SIZE - i;
    }
    cout << "\nОценка времени работы на убывающей последовательности:" << endl;
    measure_time(quicksort_iterative, arr, SIZE, "Итеративная быстрая сортировка");
    measure_time(std_sort_wrapper, arr, SIZE, "Стандартная std::sort");
    measure_time(qsort_wrapper, arr, SIZE, "Стандартная qsort");

    for (int i = 0; i < SIZE / 2; i++) {
        arr[i] = i;
    }
    for (int i = SIZE / 2; i < SIZE; i++) {
        arr[i] = SIZE - i;
    }
    cout << "\nОценка времени работы на полуупорядоченном массиве (возрастание и убывание):" << endl;
    measure_time(quicksort_iterative, arr, SIZE, "Итеративная быстрая сортировка");
    measure_time(std_sort_wrapper, arr, SIZE, "Стандартная std::sort");
    measure_time(qsort_wrapper, arr, SIZE, "Стандартная qsort");

    return 0;
}

