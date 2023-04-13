#include <stdio.h>
#include <stdlib.h>

typedef struct // 행렬을 구성하는 구조체를 생성한다.
{
    int **matrix; // 행렬의 주소를 담당한다. 두 번(행, 열) 포인트해야 하므로 이중 포인터 형식이다.
    int row;      // 행과 열을 담당한다.
    int column;
} matrix;

int interface();                              // 반복적으로 생성되는 인터페이스를 생성한다.
void print_matrix(matrix A);                  // 멤버로 받은 행렬을 출력한다.
int **create_matrix(int row, int column);     // 멤버로 받은 행과 열을 가지는 행렬을 만들어 낸다.
void addition_matrix(matrix A, matrix B);     // 두 행렬을 더한다.
void substraction_matrix(matrix A, matrix B); // 두 행렬을 뺀다.
void transpose_matrix(matrix A);              // 한 행렬을 transpose한다.
void multifly_matrix(matrix A, matrix B);     // 두 행렬을 곱셈한다.
void free_matrix(matrix A, matrix B);         // 행렬을 선언할 때 했던 동적 할당을 해제한다.

int main()
{
    int run = 1; // 반복을 담당하는 변수이다. 이것이 1이면 계속 반복한다.
    matrix A, B, Result;
    printf("Insert A's row: "); // A 행렬의 행과 열을 입력받는다.
    scanf("%d", &A.row);
    printf("Insert A's column: ");
    scanf("%d", &A.column);
    printf("Insert B's row: "); // B 행렬의 행과 열을 입력받는다.
    scanf("%d", &B.row);
    printf("Insert B's column: ");
    scanf("%d", &B.column);
    A.matrix = create_matrix(A.row, A.column); // 입력받은 정보로 A, B 행렬을 생성한다.
    B.matrix = create_matrix(B.row, B.column);
    while (run) // run == 1인 동안 반복한다.
    {
        int number;
        number = interface(); // interface 함수를 실행하고, 결과로 실행할 명령의 번호를 number에 저장한다.
        switch (number)       // 가져온 number 변수를 이용해, switch 문을 실행한다.
        {
        case 1:                     // number == 1(함수 출력)인 경우,
            printf("Status A: \n"); // A와 B 행렬을 출력한다.
            print_matrix(A);
            printf("Status B: \n");
            print_matrix(B);
            break;
        case 2:                    // number == 2(행렬 덧셈)인 경우,
            addition_matrix(A, B); // A와 B를 더한다.
            break;
        case 3:                        // number == 3(행렬 뺄셈)인 경우,
            substraction_matrix(A, B); // A와 B를 뺀다.
            break;
        case 4:                  // number == 4(행렬 transpose)인 경우,
            transpose_matrix(A); // A의 transpose를 실행한다.
            break;
        case 5:                    // number == 5(행렬 곱셈)인 경우,
            multifly_matrix(A, B); // A와 B를 곱한다.
            break;
        case 6:      // number == 6(프로그램 종료)인 경우,
            run = 0; // 반복을 끝낸다.
            break;
        default:                       // 1~6의 입력이 아닌 경우,
            printf("Not Accurate.\n"); // 잘못 입력되었음을 알리고, 다시 반복한다.
            break;
        }
    }
    free_matrix(A, B); // 모든 반복이 종료되었으면, A, B의 동적 할당을 해제한다.
    return 0;
}

int interface() // 기본 정보를 출력하는 함수이다.
{
    int number;
    printf("\n\n[----- [Hyaejun mun] [2019015035] -----]\n");
    printf("1. Print Matrix\n");
    printf("2. Add Matrix\n");
    printf("3. Substract Matrix\n");
    printf("4. Transpose Matrix\n");
    printf("5. Multifly Matrix\n");
    printf("6. End\n");
    printf("Insert the number you want(1~6): "); // 원하는 연산의 번호를 입력한다.
    scanf("%d", &number);
    return number; // 그것을 switch문으로 보낸다.
}

void print_matrix(matrix A) // 행렬을 출력하는 함수이다.
{
    int i, j;
    for (i = 0; i < A.row; i++) // 행렬의 행을 결정한다.
    {
        for (j = 0; j < A.column; j++)     // 행렬의 열을 결정한다.
            printf("%4d", A.matrix[i][j]); // 행렬의 값을 출력한다.
        printf("\n");                      // 한 행을 다 출력했으면, 다음 행으로 넘어가면서 다음 줄로 넘어간다.
    }
}

int **create_matrix(int row, int column) // 행렬을 생성하는 함수이다.
{
    int **A, i, j;
    A = (int *)malloc(row * sizeof(*A)); // 행을 동적 할당한다.
    for (i = 0; i < row; i++)
        A[i] = (int *)malloc(column * sizeof(**A)); // 각각의 행에 대해, 열을 동적 할당한다.
    for (i = 0; i < row; i++)
        for (j = 0; j < column; j++)
            A[i][j] = rand() % 10; // 0~9까지의 난수를 각각 입력한다.
    return A;
}

void addition_matrix(matrix A, matrix B) // 행렬을 더해주는 함수이다.
{
    if (A.row != B.row || A.column != B.column) // 만약 두 행렬의 행과 열의 크기가 다르면, 실행될 수 없다.
    {
        printf("You can add only if two matrix's row and column are same.\n");
        return; // 따라서, 실행 불가 문장을 출력하고 바로 종료한다.
    }
    int i, j;
    matrix Result;                                  // 결과를 저장할 Result 구조체를 생성한다.
    Result.matrix = create_matrix(A.column, A.row); // 값은 A와 B의 덧셈으로 덮어씌워지니, 행렬 생성 함수로 만들어도 무방하다.
    Result.row = A.row;
    Result.column = A.column;
    printf("A + B = \n");
    for (i = 0; i < A.row; i++)
        for (j = 0; j < A.column; j++) // 각각의 원소를 A와 B의 원소의 합으로 대체한다.
            Result.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
    printf("result: \n");
    print_matrix(Result);            // 그 결과를 행렬 출력 함수를 통해 출력한다.
    for (i = 0; i < Result.row; i++) // 결과를 출력했으니, Result 함수는 동적 할당 해제해 준다.
        free(Result.matrix[i]);
    free(Result.matrix);
}

void substraction_matrix(matrix A, matrix B) // 행렬을 빼주는 함수이다.
{
    if (A.row != B.row || A.column != B.column) // 만약 두 행렬의 행과 열의 크기가 다르면, 실행될 수 없다.
    {
        printf("You can substract only if two matrix's row and column are same.\n");
        return; // 따라서, 실행 불가 문장을 출력하고 바로 종료한다.
    }
    int i, j;
    matrix Result;                                  // 결과를 저장할 Result 구조체를 생성한다.
    Result.matrix = create_matrix(A.column, A.row); // 값은 A와 B의 뺄셈으로 덮어씌워지니, 행렬 생성 함수로 만들어도 무방하다.
    Result.row = A.row;
    Result.column = A.column;
    printf("A - B = \n");
    for (i = 0; i < A.row; i++)
        for (j = 0; j < A.column; j++) // 각각의 원소를 A와 B의 원소의 차로로 대체한다.
            Result.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
    printf("result: \n");
    print_matrix(Result);            // 그 결과를 행렬 출력 함수를 통해 출력한다.
    for (i = 0; i < Result.row; i++) // 결과를 출력했으니, Result 함수는 동적 할당 해제해 준다.
        free(Result.matrix[i]);
    free(Result.matrix);
}

void transpose_matrix(matrix A) // 행렬을 transpose해주는 함수이다.
{
    int i, j;
    matrix T;                                  // 결과를 저장할 Result 구조체를 생성한다.
    T.matrix = create_matrix(A.column, A.row); // 값은 A의 transpose으로 덮어씌워지니, 행렬 생성 함수로 만들어도 무방하다.
    T.row = A.column;                          // 행렬을 transpose하면, 행과 열의 길이를 바꾸어 주어야 한다.
    T.column = A.row;
    for (i = 0; i < A.column; i++)
        for (j = 0; j < A.row; j++)
            T.matrix[i][j] = A.matrix[j][i]; // A의 j번째 행, i번째 열에 있는 원소를 T의 i번째 행, j번째 열에 있는 원소로 덮어씌운다.
    printf("transposed A(T): \n");
    print_matrix(T);            // 그 결과를 행렬 출력 함수를 통해 출력한다.
    for (i = 0; i < T.row; i++) // 결과를 출력했으니, Result 함수는 동적 할당 해제해 준다.
        free(T.matrix[i]);
    free(T.matrix);
}

void multifly_matrix(matrix A, matrix B) // 행렬을 곱해주는 함수이다.
{
    if (A.column != B.row) // 만약 앞 행렬의 열과 뒷 행렬의 열의 크기가 다르면, 실행될 수 없다.
    {
        printf("You can multifly matrix only if column of the first matrix and row of the second matrix are same.\n");
        return; // 따라서, 실행 불가 문장을 출력하고 바로 종료한다.
    }
    int i, j, k;
    matrix Result; // 결과를 저장할 Result 구조체를 생성한다.
    Result.matrix = (int *)malloc(A.row * sizeof(*A.matrix));
    for (i = 0; i < A.row; i++) // Result 의 원소들은 값을 덮어씌우지 않고, 더하는 식으로 생성되므로
                                // 랜덤하게 값을 넣으면 안 된다. 따라서 행렬 생성 함수를 쓰지 않고 직접 동적 할당한다.
        Result.matrix[i] = (int *)malloc(B.column * sizeof(**B.matrix));
    Result.row = A.row;
    Result.column = B.column;
    for (i = 0; i < A.row; i++)
        for (j = 0; j < B.column; j++) // Result의 모든 원소를 0으로 초기화한다.
            Result.matrix[i][j] = 0;
    printf("A * B = \n");
    for (i = 0; i < A.row; i++)            // 행렬의 곱셈의 연산 방식에 따라 연산한다.
        for (j = 0; j < B.column; j++)     // i번째 행, j번째 열: 앞 행렬의 행이 i번째인 모든 원소들과 뒷 행렬의 열이 i번째인 모든 원소들을
            for (k = 0; k < A.column; k++) // 모두 1대1 대응하여 곱하고, 그 값들을 모두 더한 값.
                Result.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
    print_matrix(Result);            // 그 결과를 행렬 출력 함수를 통해 출력한다.
    for (i = 0; i < Result.row; i++) // 결과를 출력했으니, Result 함수는 동적 할당 해제해 준다.
        free(Result.matrix[i]);
    free(Result.matrix);
}

void free_matrix(matrix A, matrix B) // 동적 할당한 A, B 행렬을 해제해 주는 함수이다.
{
    int i, j;
    for (i = 0; i < A.row; i++) // i번째 행에서 생성한, 열들을 가리키는 동적 할당을 해제한다.
        free(A.matrix[i]);
    for (i = 0; i < B.row; i++) // B는 A와 같은 방식으로 해제한다.
        free(B.matrix[i]);
    free(A.matrix); // 행들을 가리키는 동적 할당을 해제한다.
    free(B.matrix); // 열을 먼저 해제한 후, 행을 해제해 주어야 둘 다 해제할 수 있다.
} // 만일 행을 먼저 해제하면, 열들을 접근할 방법이 사라진다.