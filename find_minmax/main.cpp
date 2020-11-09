#include <iostream>
#include <omp.h>
#include <time.h>

using namespace std;

int* create_array(int length)
{
    int* array = new int[length];
    return array;
}

// Найти элемент массива для разбиения
int get_midle(int* array, int start, int end)
{
    int last = array[end];
    int mid = start;
    
    for(int i = start; i < end; i++)
    {
        if(array[i] <= last)
        {
            swap(array[i], array[mid]);
            mid++;
        }
    }
    swap(array[end], array[mid]);
    
    return mid;
}

// Быстрая сортировка
void quick_sort(int* array, int start, int end)
{
    if (start < end)
    {
        int mid = get_midle(array, start, end);
        quick_sort(array, start, mid-1);
        quick_sort(array, mid+1, end);
    }
}

int* sorting(int* array, int length, int code)
{
    // Сортировка пузырьком
    if (code == 1)
    {
        for (int i = 0; i < (length-1); i++)
        {
            for (int j = 0; j < (length-i-1); j++)
            {
                if (array[j] > array[j+1])
                {
                    swap(array[j], array[j+1]);
                }
            }
        }
    }
    // Быстрая сортировка
    else if (code == 2)
    {
        quick_sort(array, 0, length-1);
    }
    // Гномья сортировка
    else if (code == 3)
    {
        int i = 0;
        while (i < length)
        {
            if (i == 0)
                i ++;
            if (array[i] >= array[i-1])
                i++;
            else
            {
                swap(array[i], array[i-1]);
                i--;
            }
        }
    }
    return array;
}

int* fillin_array(int* array, int length, int code)
{
    if (code == 1)
    {
        cout << "Начинается ввод массива" << endl;
        for (int i = 0; i < length; i++)
        {
            int n;
            cout << "Введите x" << i+1 << "\n> ";
            cin >> n;
            array[i] = n;
        }
    } else if (code == 2)
    {
        cout << "Заполнение массива рандомными элементами" << endl;
        srand((unsigned)time(0));
        for (int i = 0; i < length; i++)
        {
            array[i] = 0 + rand() % 20;
        }
        
    }
    return array;
}

void print_array(int* array, int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << array[i] << endl;
    }
}

int* menu()
{
    int choose;
    int* array = nullptr;
    int count = 0;
    int length = 0;
    do {
        cout << "Выберите действие" << endl;
        cout << "1 - Создать массив" << endl;
        cout << "2 - Ввести массив в ручную" << endl;
        cout << "3 - Заполнить массив рандомными числами" << endl;
        cout << "4 - Вывести массив" << endl;
        cout << "0 - Выход\n> ";
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
                {
                    array = fillin_array(array, length, 1);
                }
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
                {
                    print_array(array, length);
                }
                break;
                
            case 0:
                cout << "Программа завершена" << endl;
                break;
                
            default:
                cout << "Неправильный ввод" << endl;
                break;
        }
    } while (choose != 0);
    return array;
}

int main()
{
    int* array = menu();
    cout << "Не отсортированный массив" << endl;
    print_array(array, 10);
    cout << "Отсортированный массив" << endl;
    array = sorting(array, 10, 2);
    print_array(array, 10);
    
    return 0;
}
