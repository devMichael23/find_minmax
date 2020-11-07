#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
#pragma omp parallel
    {
        cout << "Hello World\n";
    }
    cout << omp_get_max_threads() << endl;
    return 0;
}
