#include <iostream>
#include <omp.h>
#include <time.h>

using namespace std;

int* create_array(int length)
{
    int* array = new int[length];
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
        cout << "x[" << i << "] = " << array[i] << endl;
    }
}

void menu()
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
}

int main()
{
    cout << "Меню создания и управление массивом" << endl;
    menu();
    return 0;
}
