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

#define FILE_PATH "/Users/igorandrianov/Documents/algorithms_course/lesson_7/lesson_7/data.txt"

enum PeakState{
    nonopened, opened, closed
};

struct matrix {
    int size;
    int arr[30][30];
};

typedef struct matrix Matrix;

Matrix* readMatrix(void);
void printMatrix(Matrix*);

enum PeakState isused[100];
void depth_graph_traversal(Matrix*);
void depth(Matrix*, int);

void breadth_graph_traversal(Matrix*);

int main() {
    Matrix *temp = readMatrix();
    if(temp == NULL){
        exit(1);
    }
    printMatrix(temp);
    depth_graph_traversal(temp);
    breadth_graph_traversal(temp);
    return 0;
}

//1. Написать функции, которые считывают матрицу смежности из файла и выводят ее на экран.
Matrix* readMatrix(void){
    Matrix *tempMatrix = malloc(sizeof(Matrix));
    FILE *file = fopen(FILE_PATH,"r");
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
    printf("That is matrix:\n");
    printf("%d\n", myMatrix->size);
    for(int i=0; i<myMatrix->size; ++i) {
        for(int j=0; j<myMatrix->size; ++j){
            printf("%d ",myMatrix->arr[i][j]);
        }
        printf("\n");
    }
}

//2. Написать рекурсивную функцию обхода графа в глубину.
void depth_graph_traversal(Matrix* myMatrix){
    for(int i=0; i<myMatrix->size; ++i){
        isused[i] = nonopened;
    }
    printf("\n----------------------------------------\n");
    printf("Depth graph traversal oreder:\n");
    depth(myMatrix, 0);
    printf("\n----------------------------------------\n");
}

void depth(Matrix *myMatrix, int t){
    isused[t] = opened;
    printf("That is %d peak opened\n", t+1);
    for(int i=0; i<myMatrix->size; ++i){
        if ((myMatrix->arr[t][i] != 0) && (isused[i] == nonopened)){
            depth(myMatrix, i);
        }
    }
    isused[t] = closed;
    printf("That is %d peak closed\n", t+1);
}
    

//3. Написать функцию обхода графа в ширину.
void breadth_graph_traversal(Matrix* myMatrix){
    enum PeakState peak[myMatrix->size];
    for(int i=0; i<myMatrix->size; ++i){
        peak[i] = nonopened;
    }
    printf("\n----------------------------------------\n");
    printf("Start of breadth graph traversal\n");
    printf("Status of peaks before traversal:\n");
    for(int i=0; i<myMatrix->size; ++i){
        printf("%d ", peak[i]);
    }
    printf("\n");
    
    peak[0] = opened;
    printf("Start traversal from 1 peak\n");
    for(int i=0; i<myMatrix->size; ++i){
        if (peak[i] == opened){
            for(int j=0; j<myMatrix->size; ++j){
                if( myMatrix->arr[i][j] != 0){
                    if (peak[j] == nonopened){
                        peak[j] = opened;
                        printf("That is %d peak opened\n", j+1);
                    }
                }
            }
        }
        peak[i] = closed;
        printf("That is %d peak closed\n", i+1);
    }
    printf("Status of peaks after traversal:\n");
    for(int i=0; i<myMatrix->size; ++i){
        printf("%d ", peak[i]);
    }
    printf("\nEnd of breadth graph traversal\n");
    printf("----------------------------------------\n");
}
