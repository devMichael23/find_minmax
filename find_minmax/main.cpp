#include <iostream>
#include <omp.h>
#include <algorithm>
#include <time.h>

using namespace std;

// Создание массива
int* create_array(int length)
{
    int* array = new int[length];
    return array;
}

// Сортировка разными способами
int* sorting(int* array, int length, int code, int threads)
{
    int tmp = 0;
    omp_set_num_threads(threads);
#pragma omp parallel
    {
        // Сортировка пузырьком
        if (code == 1)
        {
    #pragma omp parallel for
            for (int i = 0; i < (length - 1); i++)
            {
        #pragma omp parallel for
                for (int j = 0; j < (length - i - 1); j++)
                {
                    if (array[j] > array[j + 1])
                    {
                        swap(array[j], array[j + 1]);
                    }
                }
            }
        }
        // Быстрая сортировка
        else if (code == 2)
        {
            sort(array, array + length);
        }
    }
    return array;
}

// Заполнить массив в ручную или автоматически
int* fillin_array(int* array, int length, int code)
{
    {
        if (code == 1)
        {
            cout << "Начинается ввод массива" << endl;
            for (int i = 0; i < length; i++)
            {
                int n;
                cout << "Введите x" << i + 1 << "\n> ";
                cin >> n;
                array[i] = n;
            }
        }
        else if (code == 2)
        {
            cout << "Заполнение массива рандомными элементами" << endl;
            srand((unsigned)time(0));
            for (int i = 0; i < length; i++)
            {
                array[i] = 0 + rand() % 100;
            }

        }
    }
    return array;
}

// Вывести массив
void print_array(int* array, int length)
{
    cout << "[";
    for (int i = 0; i < length - 1; i++)
    {
        cout << array[i] << ", ";
    }
    cout << array[length - 1] << "]" << endl;
}

// Осуществить тестирование программы
void testing(int* array, int length, int threads)
{
    int* tmp = array;
    clock_t start = clock();
    clock_t end = clock();
    
    double sec = 0;
    // Соритровка пузырьком
    start = clock();

    int* buble = sorting(array, length, 1, threads);

    end = clock();
    sec = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "type: bubblesort; min = " << buble[0] << "; max = " << buble[length - 1] << "; " << sec << " sec; threads = " << threads << "; n = " << length << endl;
   
    // Быстрая сортировка
    array = tmp;
    start = clock();

    int* quick = sorting(array, length, 2, threads);

    end = clock();
    sec = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "type: quicksort; min = " << quick[0] << "; max = " << quick[length - 1] << "; " << sec << " sec; threads = " << threads << "; n = " << length << endl;
    cout << endl;
}


// Вывод меню
void output()
{
    cout << "Выберите действие" << endl;
    cout << "1 - Создать массив" << endl;
    cout << "2 - Ввести массив в ручную" << endl;
    cout << "3 - Заполнить массив рандомными числами" << endl;
    cout << "4 - Вывести массив" << endl;
    cout << "5 - Найти максимальное и минимальное значения" << endl;
    cout << "6 - Вывести меню ещё раз" << endl;
    cout << "0 - Выход" << endl;
}

// Реализация меню
void menu()
{
    int choose;
    int* array = nullptr;
    int count = 0;
    int length = 0;
    output();
    do {
        cout << "> ";
        cin >> choose;
        switch (choose) {
        case 1:
            cout << "Введите размер массива\n> ";
            cin >> length;
            array = create_array(length);
            count += 1;
            break;

        case 2:
            if (count == 0)
                cout << "Вы пока не создали массив";
            else
                array = fillin_array(array, length, 1);
            break;

        case 3:
            if (count == 0)
                cout << "Вы пока не создали массив";
            else
            {
                array = fillin_array(array, length, 2);
            }
            break;

        case 4:
            if (count == 0)
                cout << "Вы пока не создали массив" << endl;
            else
                print_array(array, length);
            break;

        case 5:
            if (count == 0)
                cout << "Вы пока не создали массив" << endl;
            else
            {
                if (length == 10)
                {
                    cout << "Исходный массив" << endl;
                    print_array(array, length);
                    cout << endl;
                }
                testing(array, length, 1);
                testing(array, length, 2);
                testing(array, length, 4);
                testing(array, length, 8);
                testing(array, length, 16);
                testing(array, length, 32);

                if (length == 10)
                {
                    cout << "Итоговый массив" << endl;
                    print_array(array, length);
                    cout << endl;
                }
            }
            break;

        case 6:
            output();

        case 0:
            cout << "Программа завершена" << endl;
            break;

        default:
            cout << "Неправильный ввод" << endl;
            break;
        }
    } while (choose != 0);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Практическая работа №3" << endl;
    cout << "Параллельное программирование с использованием технолгии OpenMP" << endl;
    cout << "Бузыкин Игорь" << endl;
    cout << endl;
    menu();

    return 0;
}
