//
//  main.c
//  lesson_8
//
//  Created by Игорь Андрианов on 13.01.2022.
//
//1. Реализовать сортировку подсчетом.
//2. Реализовать быструю сортировку.
//3. *Реализовать сортировку слиянием.
//4. **Реализовать алгоритм сортировки со списком.
//Проанализировать время работы каждого из вида сортировок для 100, 10000, 1000000 элементов.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CAPACITY 200
#define HIGH_LIMIT 100

void counterMain(int, int*);
int counter_sort(int, int*);

void quickMain(int, int*);
int quick_sort(int*, int, int);
int quick_part(int*, int, int);

void bubbleMain(int, int*);
int bubble_sort(int, int*);

void shakerMain(int, int*);
int shaker_sort(int, int*);

void swap(int*, int*);
void print_arr(int, int*);
void menu(void);

void counterSort(int, int*);

int main() {
    srand(time(0));
    int arr[MAX_CAPACITY];
    int arr1[MAX_CAPACITY];
    int arr2[MAX_CAPACITY];
    int arr3[MAX_CAPACITY];
    for(int i = 0; i < MAX_CAPACITY; ++i){
        arr[i] = rand() % HIGH_LIMIT;
        arr1[i] = arr[i];
        arr2[i] = arr[i];
        arr3[i] = arr[i];
    }
    printf("Given array: ");
    print_arr(MAX_CAPACITY, arr);
    
    counterMain(MAX_CAPACITY, arr);
    quickMain(MAX_CAPACITY, arr1);
    bubbleMain(MAX_CAPACITY, arr2);
    shakerMain(MAX_CAPACITY, arr3);
    return 0;
}

//1. Реализовать сортировку подсчетом.
void counterMain(int N, int *a){
    int count = counter_sort(N, a);
    printf("Counter sort: ");
    print_arr(N, a);
    printf("Count of operations of counter sort - %d\n", count);
}

int counter_sort(int N, int *a){
    int counter = 0;
    int temp_arr[HIGH_LIMIT];
    for(int i=0;i<HIGH_LIMIT;++i){
        temp_arr[i] = 0;
    }
    for(int i=0;i<N;++i){
        ++counter;
        ++temp_arr[a[i]];
    }
    int k=0;
    for(int i=0;i<HIGH_LIMIT;++i){
        ++counter;
        for(int j=0;j<temp_arr[i];++j){
            ++counter;
            a[k] = i;
            ++k;
        }
    }
    return counter;
}

//2. Реализовать быструю сортировку.
void quickMain(int N, int *a){
    int count = quick_sort(a, 0, N-1);
    printf("Quick sort: ");
    print_arr(N, a);
    printf("Count of operations of quick sort - %d\n", count);
}

int quick_sort(int *arr, int low, int high){
    int counter = 1, counter1 = 0, counter2 = 0;
    if (low < high){
        int temp = quick_part(arr, low, high);
        counter1 = quick_sort(arr, low, temp);
        counter2 = quick_sort(arr, temp+1, high);
    }
        return counter + counter1 + counter2;
}

int quick_part(int *arr, int low, int high){
    int counter = 0;
    int mid = arr[(low+high) / 2];
    int i = low;
    int j = high;
    while(1){
        while(arr[i] < mid){
            ++counter;
            ++i;
        }
        while(arr[j] > mid){
            ++counter;
            --j;
        }
        ++counter;
        if(i >= j)
            return j;
        swap(&arr[i++], &arr[j--]);
    }
}


void bubbleMain(int N, int *a) {
    int counter = bubble_sort(N, a);
    printf("Bubble sort: ");
    print_arr(N, a);
    printf("Count of operations of bubble sort - %d\n", counter);
}

int bubble_sort(int N, int *a) {
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

void shakerMain(int N, int *a) {
    int count = shaker_sort(N, a);
    printf("Shaker sort: ");
    print_arr(N, a);
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
