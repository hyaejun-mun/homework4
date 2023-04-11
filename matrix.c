#include <stdio.h>
#include <stdlib.h>

int interface();
void print_matrix(int **M, int row, int column);
int **create_matrix(int row, int column);
void addition_matrix(int **A, int **B, int **Result, int row, int column);
void substraction_matrix(int **A, int **B, int **Result, int row, int column);
void transpose_matrix(int **A, int row, int column);
void free_matrix(int **A, int **B, int **Result, int row);
int main()
{
    int row, column;
    printf("Insert row: ");
    scanf("%d", &row);
    printf("Insert column: ");
    scanf("%d", &column);
    int **A, **B, **Result;
    A = create_matrix(row, column);
    B = create_matrix(row, column);
    Result = create_matrix(row, column);
    while (1)
    {
        int number;
        number = interface();
        switch (number)
        {
        case 1:
            print_matrix(A, row, column);
            print_matrix(B, row, column);
            break;
        case 2:
            addition_matrix(A, B, Result, row, column);
            break;
        case 3:
            substraction_matrix(A, B, Result, row, column);
            break;
        case 4:
            transpose_matrix(A, row, column);
            break;
        case 5:
            print_matrix(Result, row, column);

            break;
        case 6:
            print_matrix(Result, row, column);

            break;
        default:
            printf("Not Accurate.\n");
            break;
        }
    }
    free_matrix(A, B, Result, row);
}

int interface()
{
    int number;
    printf("\n\n[----- [Hyaejun mun] [2019015035] -----]\n");
    printf("1. Print Matrix\n");
    printf("2. Add Matrix\n");
    printf("3. Substract Matrix\n");
    printf("4. Transpose Matrix\n");
    printf("5. Multifly Matrix\n");
    printf("6. End\n");
    printf("Insert the number you want(1~6): ");
    scanf("%d", &number);
    return number;
}

void print_matrix(int **M, int row, int column)
{
    int i, j;
    printf("Status: \n");
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
            printf("%4d", M[i][j]);
        printf("\n");
    }
}

int **create_matrix(int row, int column)
{
    int **A, i, j;
    A = (int *)malloc(row * sizeof(*A));
    for (i = 0; i < row; i++)
        A[i] = (int *)malloc(column * sizeof(**A));
    for (i = 0; i < row; i++)
        for (j = 0; j < column; j++)
            A[i][j] = rand() % 10; // 0~9까지의 난수를 각각 입력한다.
    return A;
}

void addition_matrix(int **A, int **B, int **Result, int row, int column)
{
    int i, j;
    printf("A + B = \n");
    for (i = 0; i < row; i++)
        for (j = 0; j < column; j++)
            Result[i][j] = A[i][j] + B[i][j];
    print_matrix(Result, row, column);
}

void substraction_matrix(int **A, int **B, int **Result, int row, int column)
{
    int i, j;
    printf("A - B = \n");
    for (i = 0; i < row; i++)
        for (j = 0; j < column; j++)
            Result[i][j] = A[i][j] - B[i][j];
    print_matrix(Result, row, column);
}

void transpose_matrix(int **A, int row, int column)
{
    int **T, i, j;
    T = (int *)malloc(column * sizeof(*A));
    for (i = 0; i < column; i++)
        T[i] = (int *)malloc(row * sizeof(**A));
    for (i = 0; i < column; i++)
        for (j = 0; j < row; j++)
            T[i][j] = A[j][i];
    print_matrix(T, column, row);
    for (i = 0; i < row; i++)
        free(T[i]);
    free(T);
}

void free_matrix(int **A, int **B, int **Result, int row)
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        free(A[i]);
        free(B[i]);
        free(Result[i]);
    }
    free(A);
    free(B);
    free(Result);
}