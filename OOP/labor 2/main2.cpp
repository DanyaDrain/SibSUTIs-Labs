#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

int** genRandMatrix(int size, int maxValue);
void printMatrix(int** matrix, int size);

int main()
{
    srand(time(NULL));
    int size=rand()%10;
    
    cout << size << endl;
    int maxValue = 100;
    int** matrix = genRandMatrix(size, maxValue);
    printMatrix(matrix, size);

    for (int i = 0; i < size; i++) 
    { 
        delete [] matrix[i]; 
    }
    delete [] matrix;
}

int** genRandMatrix(int size, int maxValue)
{
    int** ptr = new int* [size]; 
    int cols = 0;
    for(int i = 0; i < size; i++) 
    { 
        cols = rand()%10;
        ptr[i] = new int [cols+1]; 
        ptr[i][0] = cols;
    }

    for(int i = 0; i < size; i++) 
    {
        for(int j = 1; j <= ptr[i][0]; j++) 
        {
            ptr[i][j] = rand() % maxValue;
        }
    }
    
    return ptr;
}

void printMatrix(int** matrix, int size)
{
    for(int i = 0; i < size; i++) 
    {
        cout << matrix[i][0] << ": ";
        for(int j = 1; j <= matrix[i][0]; j++) 
        {
            cout << setw(4) << matrix[i][j];
        }
        cout <<"\n";
    }
}
