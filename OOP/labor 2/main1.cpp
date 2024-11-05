#include <iostream>
#include <iomanip>

using namespace std;

void _RightDiagonal(int** matrix, int* Vector, int size);
void _LeftDiagonal(int** matrix, int* Vector, int size);
void _CenterSpiral(int** matrix, int* Vector, int size);
void _LeftSpiral(int** matrix, int* Vector, int size);
int** _GenerateRandomMatrix(int Size, int MaxValue); 
int* _GenerateRandomVector(int Size, int MaxValue);
void _PrintVector(int* Vector, int Size);
void _PrintMatrix(int** Matrix, int Size);

int main(){
    int _Size = 4;
    int _MaxValue = 100;
    cout << "Лабораторная работа 2, Задание 1" << endl;
    cout << "Создание матрицы со случайными числами:" << endl;
    cout << "Размер = "<< _Size << endl;
    cout << "Матрица: "<< endl;
        int** _Matrix = _GenerateRandomMatrix(_Size, _MaxValue);
        _PrintMatrix(_Matrix, _Size);
    cout << "Создание одномерного массива со случайными числами" << endl;
        int* _Vector = _GenerateRandomVector(_Size, _MaxValue);
        _PrintVector(_Vector, _Size);
        cout << endl;
    cout << "по правым диагоналям, начиная с правого верхнего элемента"<< endl;
        _RightDiagonal(_Matrix, _Vector, _Size);
        cout << "Vector: " << endl;
        _PrintVector(_Vector, _Size);
        _PrintMatrix(_Matrix, _Size);
        cout << endl;
    cout << "по левым диагоналям, начиная с левого верхнего элемента"<< endl;
        _LeftDiagonal(_Matrix, _Vector, _Size);
        cout << "Vector: " << endl;
        _PrintVector(_Vector, _Size);
        _PrintMatrix(_Matrix, _Size);
        cout << endl;
    cout << "по спирали, начиная с центрального элемента"<< endl;
        _CenterSpiral(_Matrix, _Vector, _Size);
        cout << "Vector: " << endl;
        _PrintVector(_Vector, _Size);
        _PrintMatrix(_Matrix, _Size);
        cout << endl;
    cout << "по спирали, начиная с левого верхнего элемента"<< endl;
        _LeftSpiral(_Matrix, _Vector, _Size);
        cout << "Vector: " << endl;
        _PrintVector(_Vector, _Size);
        _PrintMatrix(_Matrix, _Size);
        cout << endl;
    delete [] _Vector;
    for (int i = 0; i < _Size; i++) {delete [] _Matrix[i];}
    delete [] _Matrix;
}

int** _GenerateRandomMatrix(int Size, int MaxValue){
    int** ptr = new int*[Size];
    for(int i = 0; i < Size; i++){ptr[i] = new int [Size];}
    for(int i = 0; i < Size; i++){for(int j = 0; j < Size; j++){ptr[i][j] = rand() % MaxValue;}}
    return ptr;
}

void _PrintMatrix(int** Matrix, int Size){
    for(int i = 0; i < Size; i++){
        for(int j = 0; j < Size; j++){
            cout << setw(4) << Matrix[i][j];
            }
            cout << endl;
        }
}

int* _GenerateRandomVector(int Size, int MaxValue){
        int* Vector;
        Vector = new int [Size * Size];
        for(int i = 0; i < Size * Size; i++){
            Vector[i] = rand() % MaxValue;
        }
        return Vector;
}

void _PrintVector(int* Vector, int Size){
    for(int i = 0; i < Size * Size; i++){
        cout << Vector[i] << " ";
    }
    cout << endl;
}

void _RightDiagonal(int** matrix, int* Vector, int size)
{
    int count = 0;
    for (int k = 0; k < size*size; k ++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if(i + j == k)
                {
                    matrix[i][j] = Vector[count];
                    count ++;
                }
            }
        }
    }
}

void _LeftDiagonal(int** matrix, int* Vector, int size)
{
    int count = 0;
    for (int k = 0; k < size*size; k++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if(i + j == k)
                {
                    matrix[i][size-1-j] = Vector[count];
                    count ++;
                }
            }
        }
    }
}
void _CenterSpiral(int** matrix, int* Vector, int size)
{
    int _index;
    int _rowBegin = 0;
    int _rowEnd = size - 1;
    int _colBegin = 0; 
    int _colEnd = size - 1;
    int _count = size * size;
    while(_count)
    {
        for(_index = _colBegin; _index <= _colEnd && _count; _index++, _count--)
            matrix[_rowBegin][_index] = Vector[_count-1];
        _rowBegin++;
        for(_index = _rowBegin; _index <= _rowEnd && _count; _index++, _count--)
            matrix[_index][_colEnd] = Vector[_count-1];
        _colEnd--;
        for(_index = _colEnd; _index >= _colBegin && _count; _index--, _count--)
            matrix[_rowEnd][_index] = Vector[_count-1];       
        _rowEnd--;
        for(_index = _rowEnd; _index >= _rowBegin && _count; _index--, _count--)
            matrix[_index][_colBegin] = Vector[_count-1];
        _colBegin++;
    }
}

void _LeftSpiral(int** matrix, int* Vector, int size)
{
    int i, j ,k = 0, p = size / 2;
    for(i=1;i <= p; i++)
    {
        for (j = i - 1; j < size - i + 1; j++) 
        {
            matrix[i-1][j] = Vector[k];
            k++;
        }
        for (j = i; j < size - i + 1; j++) 
        {
            matrix[j][size-i] = Vector[k];
            k++;
        }
        for (j = size - i - 1; j >= i - 1; --j) 
        {
            matrix[size-i][j] = Vector[k];
            k++;
        }
        for (j = size - i - 1; j >= i; j--) 
        {
            matrix[j][i-1] = Vector[k];
            k++;
        }
        if (size % 2 == 1) 
        {
            matrix[p][p] = Vector[k];
            k++;
        }
    }
}