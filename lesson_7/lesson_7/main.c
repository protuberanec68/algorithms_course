//
//  main.c
//  lesson_7
//
//  Created by Игорь Андрианов on 13.01.2022.
//
//1. Написать функции, которые считывают матрицу смежности из файла и выводят ее на экран.
//2. Написать рекурсивную функцию обхода графа в глубину.
//3. Написать функцию обхода графа в ширину.

#include <stdio.h>
#include <stdlib.h>

struct matrix {
    int size;
    int arr[30][30];
};

typedef struct matrix Matrix;

Matrix* readMatrix(void);
void printMatrix(Matrix*);


int main() {
    Matrix *temp = readMatrix();
    if(temp == NULL){
        exit(1);
    }
    printMatrix(temp);
    return 0;
}

//1. Написать функции, которые считывают матрицу смежности из файла и выводят ее на экран.

Matrix* readMatrix(void){
    Matrix *tempMatrix = malloc(sizeof(Matrix));
    FILE *file = fopen("/Users/igorandrianov/Documents/algorithms_course/lesson_7/lesson_7/data.txt","r");
    if(file == NULL)
    {
        puts("Can't open file!");
        return NULL;
    }
    fscanf(file,"%d", &tempMatrix->size);
    for(int i=0; i<tempMatrix->size; ++i) {
        for(int j=0; j<tempMatrix->size; ++j){
            fscanf(file,"%d",&tempMatrix->arr[i][j]);
        }
    }
    fclose(file);
    return tempMatrix;
}

void printMatrix(Matrix* myMatrix){
    printf("%d\n", myMatrix->size);
    for(int i=0; i<myMatrix->size; ++i) {
        for(int j=0; j<myMatrix->size; ++j){
            printf("%d ",myMatrix->arr[i][j]);
        }
        printf("\n");
    }
}

//2. Написать рекурсивную функцию обхода графа в глубину.


//3. Написать функцию обхода графа в ширину.


//Обход всех вершин графа
//  Если статус Текущей Вершины = 2, то
//      Для всех вершин смежных Текущей
//          Если статус смежной=1, то Статус смежной = 2
//  Статус Текущей = 3
