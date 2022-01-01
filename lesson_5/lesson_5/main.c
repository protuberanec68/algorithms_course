//
//  main.c
//  lesson_5
//
//  Created by Игорь Андрианов on 30.12.2021.
//
//1. Реализовать перевод из десятичной в двоичную систему счисления с использованием стека.
//2. Добавить в программу «реализация стека на основе односвязного списка» проверку на выделение памяти. Если память не выделяется, то выводится соответствующее сообщение.
//3. Написать программу, которая определяет, является ли введенная скобочная последовательность правильной. Примеры правильных скобочных выражений: (), ([])(), {}(), ([{}]), неправильных — )(, ())({), (, ])}), ([(]) для скобок [,(,{.
//Например: (2+(2*2)) или [2/{5*(4+7)}]
//4. *Создать функцию, копирующую односвязный список (то есть создает в памяти копию односвязного списка, не удаляя первый список).

#include <stdio.h>
#include <stdlib.h>

#define T char
#define SEQUENCE_MAX 100

struct TNode {
    T value;
    struct TNode *next;
};
typedef struct TNode Node;

struct TStack {
    Node *head;
    int count;
};

struct TStack Stack;

void dec2bin(void);
void push(T c, struct TStack *stack);
T pop(struct TStack *stack);
int is_empty(struct TStack *stack);

void is_sequence_right(void);
int check_sequence(T seq[SEQUENCE_MAX]);
T open_chars[3] = {'(','{','['};
T close_chars[3] = {')','}',']'};
int check_open_char(T c, struct TStack *stack);
int check_close_char(T c, struct TStack *stack);



void menu(void);

int main() {
    Stack.head = NULL;
    int command = 0;

    do {
        menu();
        scanf("%i",&command);
        printf("\n");
        switch (command) {
            case 1:
                dec2bin();
                break;
            case 2:
                is_sequence_right();
                break;
            case 3:
                
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

//1. Реализовать перевод из десятичной в двоичную систему счисления с использованием стека.

void dec2bin(){
    int temp;
    printf("Enter number: ");
    scanf("%d", &temp);
    int z;
    while(temp >= 2){
        z = (temp % 2);
        temp = temp / 2;
        push(z ? '1' : '0', &Stack);
    }
    push(temp ? '1' : '0', &Stack);
    
    struct TStack copy(struct TStack stack);
    
//    проверка задания 4
//    struct TStack new_stackkk;
//    new_stackkk = copy(Stack);
//    while(!is_empty(&Stack))
//        pop(&new_stackkk);
    
    printf("Number in binary is: ");
    while (!is_empty(&Stack))
        printf("%c",pop(&Stack));
    printf("\n");
}

void push(T c, struct TStack *stack){
    Node *temp;
    temp = (Node*) malloc(sizeof(Node));
    //2. Добавить в программу «реализация стека на основе односвязного списка» проверку на выделение памяти. Если память не выделяется, то выводится соответствующее сообщение.
    if (temp == NULL){
        printf("Memory was not allocated.\nTry late or contact your system administrator.");
        return;
    }
    temp->value = c;
    temp->next = stack->head;
    stack->head = temp;
    ++stack->count;
}

T pop(struct TStack *stack){
    if (is_empty(stack))
        return '_';
    T c;
    Node *temp;
    temp = (Node*) malloc(sizeof(Node));
    c = stack->head->value;
    temp = stack->head;
    stack->head = temp->next;
    free(temp);
    --stack->count;
    return c;
}

int is_empty(struct TStack *stack) {
    return (stack->count == 0);
}


//3. Написать программу, которая определяет, является ли введенная скобочная последовательность правильной. Примеры правильных скобочных выражений: (), ([])(), {}(), ([{}]), неправильных — )(, ())({), (, ])}), ([(]) для скобок [,(,{.
//Например: (2+(2*2)) или [2/{5*(4+7)}]

void is_sequence_right(void){
    printf("Enter sequence: ");
    T sequence[SEQUENCE_MAX];
    scanf("%s", sequence);
    printf("Sequence ");
    for(int i=0; sequence[i]!='\0'; ++i)
        printf("%c", sequence[i]);
    printf(" is %s", check_sequence(sequence) ? "right" : "wrong");
}

int check_sequence(T seq[SEQUENCE_MAX]){
    struct TStack seq_stack;
    seq_stack.count = 0;
    for(int i=0; seq[i]!='\0'; ++i){
        check_open_char(seq[i], &seq_stack);
        check_close_char(seq[i], &seq_stack);
    }
    return is_empty(&seq_stack);
}

int check_open_char(T c, struct TStack *stack){
    for(int i=0; i<3; ++i){
        if (c == open_chars[i]){
            push(c, stack);
            return 1;
        }
    }
    return 0;
}

int check_close_char(T c, struct TStack *stack){
    for(int i=0; i<3; ++i){
        if ((c == close_chars[i]) && (open_chars[i] == stack->head->value)){
            pop(stack);
            return 1;
        }
    }
    return 0;
}

//4. *Создать функцию, копирующую односвязный список (то есть создает в памяти копию односвязного списка, не удаляя первый список).

//мне не нравится эта реализация, половина кода задублирована
struct TStack copy(struct TStack stack){
    struct TStack new_stack;
    new_stack.count = 0;
    
    Node *head_node;
    head_node = (Node*) malloc(sizeof(Node));
    
    head_node->value = stack.head->value;
    head_node->next = NULL;
    
    new_stack.head = head_node;
    ++new_stack.count;
    
    Node *current_source_node = stack.head->next;
    Node *current_new_node = new_stack.head;
    
    while (current_source_node != NULL){
        Node *new_node;
        new_node = (Node*) malloc(sizeof(Node));
        
        new_node->value = current_source_node->value;
        new_node->next = NULL;
        
        current_new_node->next = new_node;
        current_new_node = new_node;
        current_source_node = current_source_node->next;
        ++new_stack.count;
    }
    return new_stack;
}

void menu(void) {
    printf("\n\n'1' - dec2bin");
    printf("\n'2' - is sequence right");
    printf("\n'0' - quit");
    printf("\nSelect command: ");
}
