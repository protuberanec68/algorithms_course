//
//  main.c
//  lesson_6
//
//  Created by Игорь Андрианов on 03.01.2022.
//
//  1. Реализовать простейшую хеш-функцию. На вход функции подается строка, на выходе сумма кодов символов.

//  2. Переписать программу, реализующую двоичное дерево поиска.
//  а) Добавить в него обход дерева различными способами;
//  б) Реализовать поиск в двоичном дереве поиска;
#include <stdio.h>
#include <stdlib.h>

#define STR_LEN 100
#define COUNT 50

const int arr[COUNT] = {37,62,68,31,11,97,62,66,60,43,13,92,36,15,27,44,20,43,89,42,64,36,76,34,30,70,32,82,47,35,25,58,22,65,34,1,24,14,12,100,82,62,33,85,61,75,12,93,43,97};

void menu(void);
void hash(void);
int make_hash_sum(char str[STR_LEN]);

void bin_tree(void);
typedef int T;
typedef struct Node {
    T data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

void printTree(Node *root);
Node *getFreeNode(T value, Node *parent);
void insert(Node **head, int value);
void preOrderTravers(Node *root);
void simOrderTravers(Node *root);
void postOrderTravers(Node *root);
Node *search(T n, Node *root);

int main() {
    int command = 0;
    do {
        menu();
        scanf("%i",&command);
        printf("\n");
        switch (command) {
            case 1:
                hash();
                break;
            case 2:
                bin_tree();
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
//  Задание 1. Реализовать простейшую хеш-функцию. На вход функции подается строка, на выходе сумма кодов символов.
void hash(void){
    char str[STR_LEN];
    printf("Enter string: ");
    scanf("%s", str);
    printf("Hashsum of input is %d", make_hash_sum(str));
}

int make_hash_sum(char str[STR_LEN]){
    int sum = 0;
    for(int i = 0; str[i]!='\0'; ++i){
        sum += str[i];
        sum += i;
    }
    sum %= 100;
    return sum;
}

//  Задаиние 2. Переписать программу, реализующую двоичное дерево поиска.
//  а) Добавить в него обход дерева различными способами;
//  б) Реализовать поиск в двоичном дереве поиска;

void bin_tree(void){
    Node *Tree = NULL;
//    FILE *file = fopen("data.txt","r");
//    if(file == NULL)
//    {
//        puts("Can't open file!");
//        exit(1);
//    }
//    int count;
//    fscanf(file,"%d",&count);
//    int i;
//    for(i=0; i<count; ++i)
//    {
//        int value;
//        fscanf(file,"%d",&value);
//        insert(&Tree,value);
//        }
//        fclose(file);
    
    for(int i=0; i<COUNT; ++i){
        insert(&Tree,arr[i]);
    }
    
    printTree(Tree);
    printf("\nPreOrderTravers:");
    preOrderTravers(Tree);
    printf("\nSimOrderTravers:");
    simOrderTravers(Tree);
    printf("\nPostOrderTravers:");
    postOrderTravers(Tree);
    printf("\nEnter number for searh: ");
    T num = 0;
    scanf("%d", &num);
    Node *node = search(num, Tree);
    if (node == NULL) {
        printf("Node %d does NOT finded", num);
    } else {
        printf("Node %d is finded", node->data);
    }
}

void printTree(Node *root){
    if (root) {
        printf("%d",root->data);
        if(root->left || root->right) {
            printf("(");
            if(root->left)
                printTree(root->left);
            else
                printf("NULL");
            printf(",");
            if(root->right)
                printTree(root->right);
            else
                printf("NULL");
            printf(")");
        }
    }
}

Node *getFreeNode(T value, Node *parent){
    Node *tmp =(Node*) malloc(sizeof(Node));
    tmp->left = tmp->right = NULL;
    tmp->data = value;
    tmp->parent = parent;
    return tmp;
}

void insert(Node **head, int value){
    Node*tmp = NULL;
    if(*head == NULL){
        *head = getFreeNode(value,NULL);
        return;
    }
    tmp = *head;
    while(tmp){
        if(value >= tmp->data){
            if(tmp->right){
                tmp = tmp->right;
                continue;
            } else {
                tmp->right = getFreeNode(value,tmp);
                return;
            }
        } else if(value < tmp->data) {
            if(tmp->left) {
                tmp = tmp->left;
                continue;
            } else {
                tmp->left = getFreeNode(value,tmp);
                return;
            }
        } else {
            exit(2);
        }
    }
}
//прямой обход
void preOrderTravers(Node *root){
    if(root){
        printf("%d ",root->data);
        preOrderTravers(root->left);
        preOrderTravers(root->right);
    }
}

//  а) Добавить в него обход дерева различными способами;
//симметричный обход
void simOrderTravers(Node *root){
    if(root){
        simOrderTravers(root->left);
        printf("%d ",root->data);
        simOrderTravers(root->right);
    }
}
//обратный обход
void postOrderTravers(Node *root){
    if(root){
        postOrderTravers(root->left);
        postOrderTravers(root->right);
        printf("%d ",root->data);
    }
}

//  б) Реализовать поиск в двоичном дереве поиска;
Node *search(T n, Node *root){
    if(root){
        if(n == root->data)
            return root;
        else if (n < root->data)
            return search(n, root->left);
        else {
            return search(n, root->right);
        }
    }
    return NULL;
}

void menu(void) {
    printf("\n\n'1' - hash");
    printf("\n'2' - bin search tree");
    printf("\n'0' - quit");
    printf("\nSelect command: ");
}
