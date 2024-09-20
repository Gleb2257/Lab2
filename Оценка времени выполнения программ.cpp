#include <iostream>
#include <cstdlib> 
#include <ctime>   // для замера времени выполнения программы

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian"); 

    // Переменные для замера времени
    clock_t start, end;

    // Размер матрицы
    int n;
    cout << "Введите размер матрицы: ";
    cin >> n;

    // Динамическое выделение памяти для матриц
    int** a = new int* [n];
    int** b = new int* [n];
    int** c = new int* [n];
    for (int i = 0; i < n; i++) {
        a[i] = new int[n];
        b[i] = new int[n];
        c[i] = new int[n];
    }

    // Заполнение матриц случайными числами
    srand(time(0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = rand() % 100 + 1; // числа от 1 до 100
            b[i][j] = rand() % 100 + 1;
            c[i][j] = 0;
        }
    }

    // Замер времени выполнения перемножения матриц
    start = clock(); 

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    end = clock(); 
    double time_taken = double(end - start) / CLOCKS_PER_SEC; // вычисление времени

    // Вывод времени выполнения
    cout << "Время выполнения перемножения матриц: " << time_taken << " секунд\n";

    for (int i = 0; i < n; i++) {
        delete[] a[i];
        delete[] b[i];
        delete[] c[i];
    }
    delete[] a;
    delete[] b;
    delete[] c;

    return 0;
}
