//
//  main.c
//  lesson_4
//
//  Created by Игорь Андрианов on 23.12.2021.
//

//1. *Количество маршрутов с препятствиями. Реализовать чтение массива с препятствием и нахождение количество маршрутов.

//2. Решить задачу о нахождении длины максимальной последовательности с помощью матрицы.

//3. ***Требуется обойти конем шахматную доску размером NxM, пройдя через все поля доски по одному разу. Здесь алгоритм решения такой же, как в задаче о 8 ферзях. Разница только в проверке положения коня.

#include <stdio.h>
#include <string.h>

#define SIZE 20

void find_number_paths(void);
void print_matrix(int *arr, int m, int n);

void lcs(void);
void print(unsigned long i, unsigned long j);
void print_arrays(unsigned long i, unsigned long j);
int c[SIZE][SIZE];
char x[SIZE], y[SIZE], b[SIZE][SIZE];

#define M 8
#define N 8

void find_horse_path(void);
void first_step(void);
int next_step(int m, int n, int count);
void print_board(void);
void prepare_board(void);

int board[M][N];
int moves[8][2]  = {
    {-1, -2}, {-2, -1}, {-2,  1}, { 1, -2},
    {-1,  2}, { 2, -1}, { 1,  2}, { 2,  1}
};

void menu(void);


int main() {
    int command = 0;

    do {
        menu();
        scanf("%i",&command);
        printf("\n");
        switch (command) {
            case 1:
                find_number_paths();
                break;
            case 2:
                lcs();
                break;
            case 3:
                find_horse_path();
                break;
            case 0:
                printf("Exit\n");
                break;
            default:
                printf("Wrong command.\n");
                break;
        }
    }
    while (command != 0);
    return 0;
}

//1. *Количество маршрутов с препятствиями. Реализовать чтение массива с препятствием и нахождение количество маршрутов.
void find_number_paths(void) {
    const int m = 8, n = 8;
    int arr[m][n] = {{1,1,1,1,0,1,1,0},{0,1,0,1,1,1,1,1},{0,1,0,1,1,1,0,1},{1,1,1,1,1,1,1,1},{1,0,1,1,1,1,1,1},{1,0,1,1,1,1,0,1},{1,1,1,1,0,1,1,1},{1,1,1,1,1,1,0,1}};
    printf("Original map:\n");
    print_matrix(&arr[0][0], m, n);
    
    for(int i = 1; i < n; ++i)
        arr[i][0] *= arr[i-1][0];
    for(int j = 1; j < n; ++j)
        arr[0][j] *= arr[0][j-1];
    for (int i = 1; i < n; ++i)
        for (int j = 1; j < m; ++j)
            arr[i][j] *= (arr[i][j - 1] + arr[i - 1][j]);
    
    printf("Map of the number of possible paths:\n");
    print_matrix(&arr[0][0], m, n);
    printf("%d - the max number of possible paths", arr[m-1][n-1]);
}

void print_matrix(int *arr, int m, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            printf("%2d ", *((arr+i*n) + j));
        printf("\n");
    }
}

//2. Решить задачу о нахождении длины максимальной последовательности с помощью матрицы.
void print_arrays(unsigned long i, unsigned long j){
    for (int k = 0; k <= i; ++k){
        for(int l = 0; l <= j; ++l) {
            printf("%c ", b[k][l]);
        }
        printf("\n");
    }
    printf("\n");
    for (int k = 1; k <= i; ++k){
        for(int l = 1; l <= j; ++l) {
            printf("%2d", c[k][l]);
        }
        printf("\n");
    }
}

void print(unsigned long i, unsigned long j) {
    if (i == 0 || j == 0)
        return;
    if (b[i][j] == 'c') {
        print(i - 1, j - 1);
        printf("%c", x[i - 1]);
    }
    else if (b[i][j] == 'u')
        print(i - 1, j);
    else
        print(i, j - 1);
}

void lcs(void) {
    int i, j;
    unsigned long m, n;
    
    printf("Enter 1st sequence:");
    scanf("%s", x);
    printf("Enter 2nd sequence:");
    scanf("%s", y);
    printf("\nThe Longest Common Subsequence is ");

    m = strlen(x);
    n = strlen(y);
    for (i = 0; i <= m; ++i)
        c[i][0] = 0;
    for (i = 0; i <= n; ++i)
        c[0][i] = 0;


    for (i = 1; i <= m; ++i)
        for (j = 1; j <= n; ++j) {
            if (x[i - 1] == y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 'c';
            }
            else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = 'u';
            }
            else {
                c[i][j] = c[i][j - 1];
                b[i][j] = 'l';
            }
        }
    print(m, n);
    print_arrays(m, n);
}

//3. ***Требуется обойти конем шахматную доску размером NxM, пройдя через все поля доски по одному разу. Здесь алгоритм решения такой же, как в задаче о 8 ферзях. Разница только в проверке положения коня.

void find_horse_path(void){
    prepare_board();
    first_step();
    print_board();
}

void first_step(void){
    for(int i = 0; i < M; ++i)
        for(int j = 0; j < N; ++j) {
            board[i][j] = 1;
            if (next_step(i, j, 1))
                return;
            board[i][j] = 0;
        }
}

int next_step(int m, int n, int count){
    if (count == 64)
        return 1;
    for(int i = 0; i < 8; ++i){
        int a = m + moves[i][0];
        int b = n + moves[i][1];
        if (!((a >= 0) && (a < M) && (b >= 0) && (b < N)))
            continue;
        if (board[a][b] != 0)
            continue;
        board[a][b] = count+1;
        if(next_step(a, b, count+1))
            return 1;
        board[a][b] = 0;
    }
    return 0;
}

void prepare_board(void){
    for(int i = 0; i < M; ++i)
        for(int j = 0; j < N; ++j)
            board[i][j] = 0;
}

void print_board(void){
    for(int i = 0; i < M; ++i) {
        for(int j = 0; j < N; ++j){
            printf("%3d", board[i][j]);
        }
    printf("\n");
    }
}

void menu(void) {
    printf("\n\n'1' - find the way");
    printf("\n'2' - LCS");
    printf("\n'3' - find the horse path");
    printf("\n'0' - quit");
    printf("\nSelect command: ");
}
