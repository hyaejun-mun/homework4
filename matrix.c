#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int **matrix;
    int row;
    int column;
} matrix;

int interface();
void print_matrix(matrix A);
int **create_matrix(int row, int column);
void addition_matrix(matrix A, matrix B);
void substraction_matrix(matrix A, matrix B);
void transpose_matrix(matrix A);
void multifly_matrix(matrix A, matrix B);
void free_matrix(matrix A, matrix B);

int main()
{
    int run = 1;
    matrix A, B, Result;
    printf("Insert A's row: ");
    scanf("%d", &A.row);
    printf("Insert A's column: ");
    scanf("%d", &A.column);
    printf("Insert B's row: ");
    scanf("%d", &B.row);
    printf("Insert B's column: ");
    scanf("%d", &B.column);
    A.matrix = create_matrix(A.row, A.column);
    B.matrix = create_matrix(B.row, B.column);
    while (run)
    {
        int number;
        number = interface();
        switch (number)
        {
        case 1:
            printf("Status A: \n");
            print_matrix(A);
            printf("Status B: \n");
            print_matrix(B);
            break;
        case 2:
            addition_matrix(A, B);
            break;
        case 3:
            substraction_matrix(A, B);
            break;
        case 4:
            transpose_matrix(A);
            break;
        case 5:
            multifly_matrix(A, B);
            break;
        case 6:
            run = 0;
            break;
        default:
            printf("Not Accurate.\n");
            break;
        }
    }
    free_matrix(A, B);
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

void print_matrix(matrix A)
{
    int i, j;
    for (i = 0; i < A.row; i++)
    {
        for (j = 0; j < A.column; j++)
            printf("%4d", A.matrix[i][j]);
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

void addition_matrix(matrix A, matrix B)
{
    if (A.row != B.row || A.column != B.column)
    {
        printf("You can add only if two matrix's row and column are same.\n");
        return;
    }
    int i, j;
    matrix Result;
    Result.matrix = create_matrix(A.column, A.row);
    Result.row = A.row;
    Result.column = A.column;
    printf("A + B = \n");
    for (i = 0; i < A.row; i++)
        for (j = 0; j < A.column; j++)
            Result.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
    printf("result: \n");
    print_matrix(Result);
    for (i = 0; i < Result.row; i++)
        free(Result.matrix[i]);
    free(Result.matrix);
}

void substraction_matrix(matrix A, matrix B)
{
    if (A.row != B.row || A.column != B.column)
    {
        printf("You can add only if two matrix's row and column are same.\n");
        return;
    }
    int i, j;
    matrix Result;
    Result.matrix = create_matrix(A.column, A.row);
    Result.row = A.row;
    Result.column = A.column;
    printf("A - B = \n");
    for (i = 0; i < A.row; i++)
        for (j = 0; j < A.column; j++)
            Result.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
    printf("result: \n");
    print_matrix(Result);
    for (i = 0; i < Result.row; i++)
        free(Result.matrix[i]);
    free(Result.matrix);
}

void transpose_matrix(matrix A)
{
    int i, j;
    matrix T;
    T.matrix = create_matrix(A.column, A.row);
    T.row = A.column;
    T.column = A.row;
    for (i = 0; i < A.column; i++)
        for (j = 0; j < A.row; j++)
            T.matrix[i][j] = A.matrix[j][i];
    printf("transposed A(T): \n");
    print_matrix(T);
    for (i = 0; i < T.row; i++)
        free(T.matrix[i]);
    free(T.matrix);
}

void multifly_matrix(matrix A, matrix B)
{
    if (A.column != B.row)
    {
        printf("You can multifly matrix only if column of the first matrix and row of the second matrix are same.\n");
        return;
    }
    int i, j, k;
    matrix Result;
    Result.matrix = (int *)malloc(A.row * sizeof(*A.matrix));
    for (i = 0; i < A.row; i++)
        Result.matrix[i] = (int *)malloc(B.column * sizeof(**B.matrix));
    Result.row = A.row;
    Result.column = B.column;
    for (i = 0; i < A.row; i++)
        for (j = 0; j < A.column; j++)
            Result.matrix[i][j] = 0;
    printf("A * B = \n");
    for (i = 0; i < A.row; i++)
        for (j = 0; j < B.column; j++)
            for (k = 0; k < A.column; k++)
                Result.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
    print_matrix(Result);
    for (i = 0; i < Result.row; i++)
        free(Result.matrix[i]);
    free(Result.matrix);
}

void free_matrix(matrix A, matrix B)
{
    int i, j;
    for (i = 0; i < A.row; i++)
        free(A.matrix[i]);
    for (i = 0; i < B.row; i++)
        free(B.matrix[i]);
    free(A.matrix);
    free(B.matrix);
}