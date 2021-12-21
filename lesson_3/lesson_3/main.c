//
//  main.c
//  lesson_3
//
//  Created by Игорь Андрианов on 21.12.2021.
//

//1. Попробовать оптимизировать пузырьковую сортировку. Сравнить количество операций сравнения оптимизированной и не оптимизированной программы. Написать функции сортировки, которые возвращают количество операций.
//2. *Реализовать шейкерную сортировку.
//3. Реализовать бинарный алгоритм поиска в виде функции, которой передается отсортированный массив. Функция возвращает индекс найденного элемента или -1, если элемент не найден.


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CAPACITY 30

void bubble(int N, int *a, int *b);
int bubble_sort_opt(int N, int *a);
int bubble_sort_nonopt(int N, int *a);

void shaker(int N, int *a);
int shaker_sort(int N, int *a);

void binary(int N, int *a);
int binary_serch(int N, int *a, int val);

void swap(int *a, int *b);
void print_arr(int N, int *a);
void menu(void);

int main() {
    int command = 0;
    do {
        srand(time(0));
        int arr[MAX_CAPACITY];
        int arr1[MAX_CAPACITY];
        int arr2[MAX_CAPACITY];
        for(int i = 0; i < MAX_CAPACITY; ++i){
            arr[i] = rand() % 100;
            arr1[i] = arr[i];
            arr2[i] = arr[i];
        }
        menu();
        scanf("%i",&command);
        printf("\n");
        switch (command) {
            case 1:
                bubble(MAX_CAPACITY, arr1, arr2);
                break;
            case 2:
                shaker(MAX_CAPACITY, arr1);
                break;
            case 3:
                shaker_sort(MAX_CAPACITY, arr1);
                binary(MAX_CAPACITY, arr1);
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

//Задание 1. Попробовать оптимизировать пузырьковую сортировку. Сравнить количество операций сравнения оптимизированной и не оптимизированной программы. Написать функции сортировки, которые возвращают количество операций.
void bubble(int N, int *a, int *b) {
    printf("Given array: ");
    print_arr(MAX_CAPACITY, a);
    
    int counter_opt = bubble_sort_opt(MAX_CAPACITY, a);
    int counter_nonopt = bubble_sort_nonopt(MAX_CAPACITY, b);
    
    printf("Bubble sort: ");
    print_arr(MAX_CAPACITY, a);
    printf("Count of operations of optimized bubble sort - \t\t%d\n", counter_opt);
    printf("Count of operations of nonoptimized bubble sort - \t%d\n", counter_nonopt);
}

int bubble_sort_nonopt(int N, int *a) {
    int counter = 0;
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N-1; ++j) {
            ++counter;
            if( a[j] > a[j+1] ) {
                swap(&a[j], &a[j+1]);
            }
        }
    }
    return counter;
}

int bubble_sort_opt(int N, int *a) {
    int counter = 0;
    int is_change = 0;
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N-1; ++j) {
            ++counter;
            if( a[j] > a[j+1] ) {
                swap(&a[j], &a[j+1]);
                is_change = 1;
            }
        }
        if(!is_change) return counter;
        ++counter;
        is_change = 0;
    }
    return counter;
}

// Задание 2. *Реализовать шейкерную сортировку.
void shaker(int N, int *a) {
    printf("Given array: ");
    print_arr(MAX_CAPACITY, a);
    int count = shaker_sort(N, a);
    printf("Shaker sort: ");
    print_arr(MAX_CAPACITY, a);
    printf("Count of operations of shaker sort - %d\n", count);
}

int shaker_sort(int N, int *a){
    int counter = 0;
    int is_change = 0;
    for(int i = 0; i < N; ++i) {
        for(int j=i; j<N-1-i; ++j) {
            ++counter;
            if( a[j] > a[j+1] ) {
                swap(&a[j], &a[j+1]);
                is_change = 1;
            }
        }
        for(int j=N-1-i; j>0+i; --j) {
            ++counter;
            if( a[j-1] > a[j] ) {
                swap(&a[j-1], &a[j]);
                is_change = 1;
            }
        }
        if(!is_change) return counter;
        ++counter;
        is_change = 0;
    }
    return counter;
}

// Задание 3. Реализовать бинарный алгоритм поиска в виде функции, которой передается отсортированный массив. Функция возвращает индекс найденного элемента или -1, если элемент не найден.
void binary(int N, int *a){
    printf("Index array: ");
    for(int i=0; i<N; ++i)
        printf("%2d ", i);
    printf("\nGiven array: ");
    print_arr(N, a);
    printf("Enter number to search: ");
    int num = 0;
    scanf("%d", &num);
    int result = binary_serch(N, a, num);
    if(result == -1){
        printf("Number %d not found", num);
        return;
    }
    printf("Number %d at index %d",num ,result);
}

int binary_serch(int N, int *a, int val){
    int lht = 0, rht = N - 1;
    while(lht <= rht) {
        int mid = rht / lht;
        if (val == a[mid]) return mid;
        if (val < a[mid]) rht = mid - 1;
        else if ( val > a[mid]) lht = mid + 1;
    }
    return -1;
}


//Вспомогательные функции

void swap(int *a, int *b) {
    if (a != b) {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}

void print_arr(int N, int *a) {
    for (int i = 0; i < N; ++i) {
        printf("%2i ", a[i]);
    }
    printf("\n");
}

void menu(void) {
    printf("\n\n'1' - compare optimized and nonoptimized bubble sort");
    printf("\n'2' - make shaker sort");
    printf("\n'3' - binary searh");
    printf("\n'0' - quit");
    printf("\nSelect command: ");
}
