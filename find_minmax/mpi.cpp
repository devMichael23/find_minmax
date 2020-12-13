#include <iostream>
#include "mpi.h"

using namespace std;

// Создание массива
int* create_array(int length)
{
    int* array = new int[length];
    return array;
}

// Заполнить массив в ручную или автоматически
int* fillin_array(int* array, int length, int code)
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
            srand((unsigned)time(0));
            for (int i = 0; i < length; i++)
            {
                array[i] = 0 + rand() % 10000;
            }

        }

    return array;
}

// Вывести массив
void print_array(int* array, int length, int code = 0, int start = 0, int stop = 0)
{
    if (code == 0)
    {
        cout << "[";
        for (int i = 0; i < length - 1; i++)
        {
            cout << array[i] << ", ";
        }
        cout << array[length - 1] << "]" << endl;
    }
    else
    {
        cout << "[";
        for (int i = start; i < stop - 1; i++)
        {
            cout << array[i] << ", ";
        }
        cout << array[stop - 1] << "]" << endl;
    }
}

// Сортировка разными способами
int* find_minmax(int* array, int length)
{
    int* result = new int[] {0 , 0};
    int min = array[0], max = array[0];

    for (int i = 0; i < length; i++)
        if (array[i] < min)
            min = array[i];
    for (int i = 0; i < length; i++)
        if (array[i] > max)
            max = array[i];

        result[0] = min;
        result[1] = max;

    return result;
}

void mpi_find_minmax(int* array, int n, int size, int rank)
{
    MPI_Bcast(array, n, MPI_INT, 0, MPI_COMM_WORLD);
    int recieve[] = { 0 };
    int arr[] = { 0 };
    int count = n / size;
    int start, stop;
    int local_min;
    int local_max;
    int global_min = 0;
    int global_max = 0;
    double begin = MPI_Wtime();

    if (rank == 0)
    {
        for (int i = 1; i < size; i++)
        {
            arr[0] = i * count;
            MPI_Send(arr, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
        }
        local_min = array[0];
        local_max = array[0];
        //cout << "Первый процесс получил ";
        //print_array(array, 10, 1, 0, count);
        for (int i = 0; i < count; i++)
        {
            if (array[i] < local_min)
                local_min = array[i];
            if (array[i] > local_max)
                local_max = array[i];
        }
    }
    if (rank > 0 && rank != size - 1)
    {
        MPI_Recv(recieve, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        start = recieve[0];
        stop = start + count;
        local_min = array[start];
        local_max = array[start];
        //cout << "Процесс " << rank << " получил ";
        //print_array(array, 10, 1, start, stop);
        // Включая start, не включая stop
        for (int i = start; i < stop; i++)
        {
            if (array[i] < local_min)
                local_min = array[i];
            if (array[i] > local_max)
                local_max = array[i];
        }
    }
    if (rank == size - 1)
    {
        MPI_Recv(recieve, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        start = recieve[0];
        stop = n;
        local_min = array[start];
        local_max = array[start];
        //cout << "Последний процесс получил ";
        //print_array(array, 10, 1, start, stop);
        // Включая start, не включая stop
        for (int i = start; i < stop; i++)
        {
            if (array[i] < local_min)
                local_min = array[i];
            if (array[i] > local_max)
                local_max = array[i];
        }
    }
    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        double end = MPI_Wtime();
        double time = end - begin;
        cout << endl;
        cout << "Распределенное находение элементов [min, max] = [" << global_min << ", " << global_max << "]" << endl;
        cout << "time = " << time << " sec" << "; n = " << n << endl;
    }
}

void tests(int* n, int code, int size = 0, int rank = 0)
{
    if (code == 1)
    {
        int choose;
        cout << "1 - Заполнить массив в ручную.\n2 - Запустить алгоритм проверки\n--> ";
        cin >> choose;
        if (choose == 1)
        {
            int len;
            int* result;
            cout << "Введите размер массива\n--> ";
            cin >> len;
            int* array = create_array(len);
            array = fillin_array(array, len, 1);
            clock_t start = clock();

            result = find_minmax(array, len);

            clock_t end = clock();
            double time = (double)(end - start) / CLOCKS_PER_SEC;
            cout << "Исходный массив: ";
            print_array(array, len);
            cout << "Последовательное находение элементов [min, max] = [" << result[0] << ", " << result[1] << "]" << endl;
            cout << "time = " << time << " sec" << "; n = " << len << endl;
        }
        else if (choose == 2)
        {
            for (int i = 0; i < 6; i++)
            {
                int* array = create_array(n[i]);
                int* result;
                array = fillin_array(array, n[i], 2);
                clock_t start = clock();

                result = find_minmax(array, n[i]);

                clock_t end = clock();
                double time = (double)(end - start) / CLOCKS_PER_SEC;
                cout << "Последовательное находение элементов [min, max] = [" << result[0] << ", " << result[1] << "]" << endl;
                cout << "time = " << time << " sec" << "; n = " << n[i] << endl;
                delete[] array;
                delete[] result;
            }
        }
    }
    else if (code == 0)
    {
        if (rank == 0)
        {
            int choose;
            cout << "1 - Заполнить массив в ручную.\n2 - Запустить алгоритм проверки\n--> ";
            cin >> choose;
        }
        for (int i = 0; i < 6; i++)
        {
            int* array = create_array(n[i]);
            array = fillin_array(array, n[i], 2);
            mpi_find_minmax(array, n[i], size, rank);
            delete[] array;
        }
    }
}

int main(int* argc, char** argv)
{
    setlocale(LC_ALL, "Russian");
	int size, rank;
    int n[] = { 1000000, 10000000, 25000000, 50000000, 75000000, 100000000 };
    char in = 'Y';

	MPI_Init(argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        cout << "Практическая работа №5" << endl;
        cout << "Распределенное программирование для систем с общей памятью с использованием основ технологии MPI" << endl;
        cout << "Бузыкин Игорь" << endl;
    }


    if (size == 1)
    {
        cout << "Начать работу программы? Y/N: ";
        cin >> in;
        if (in == 'Y')
            tests(n, 1, size, rank);
    }
    else 
    {
        if (rank == 0)
        {
            cout << "Начать работу программы? Y/N: ";
            cin >> in;
        }
        if (in == 'Y')
        {
            tests(n, 0, size, rank);
        }
        else
            if (rank == 0)
                cout << "Ошибка" << endl;
    }

	MPI_Finalize();

	return 0;
}