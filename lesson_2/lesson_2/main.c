//
//  main.c
//  lesson_2
//
//  Created by Игорь Андрианов on 16.12.2021.
//

#include <stdio.h>
#include <math.h>

void dec_to_bin(void);
long long int bin_calc(int);

void exponentiation(void);
long long int exp_rec(int, int);
long long int exp_rec_fast(int, int, int);

void exec_calc(void);
int search_count_exec(int, int);

void print_menu(void);

int main() {
    int command = 0;

    do {
        print_menu();
        scanf("%i",&command);
        printf("\n");
        switch (command) {
            case 1:
                dec_to_bin();
                break;
            case 2:
                exponentiation();
                break;
            case 3:
                exec_calc();
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


// Задание 1. Реализовать функцию перевода из десятичной системы в двоичную, используя рекурсию.
void dec_to_bin(void) {
    int input = 0;
    printf("Enter number: ");
    scanf("%i", &input);
    
    long long int res = bin_calc(input);
    printf("The number %i in binary is 0b%lld", input, res);
}

long long int bin_calc(int x) {
    if (x < 2) {
        return x;
    }
    return (x % 2) + 10 * (bin_calc(x / 2));
}

// Задание 2. Реализовать функцию возведения числа a в степень b:
//a. без рекурсии;
//b. рекурсивно;
//c. *рекурсивно, используя свойство четности степени.
void exponentiation(void) {
    int num, degree = 0;
    printf("Enter number and degree: ");
    scanf("%i %i", &num, &degree);
    
    //вариант без рекурсии
    long long int res1 = 1;
    for(int i = degree ; i >= 1; --i) {
        res1 *= num;
    }
    printf("(Ver. NON_RECURSION) \t%i to the power of %i is %lld", num, degree, res1);
    
    //вариант с рекурсией
    long long int res2 = (degree == 0) ? 1 : exp_rec(num, degree);
    printf("\n(Ver. RECURSION) \t\t%i to the power of %i is %lld", num, degree, res2);
    
    //вариант с рекурсией (ускоренный)
    long long int res3 = exp_rec_fast(num, degree, 1);
    printf("\n(Ver. FAST_RECURSION) \t%i to the power of %i is %lld", num, degree, res3);
}

long long int exp_rec(int num, int degree) {
    if (degree <= 1) {
        return num;
    }
    return num * exp_rec(num, --degree);
}

long long int exp_rec_fast(int a, int b, int n){
    if (b == 0) {
        return n;
    }
    if (b % 2) {
        return exp_rec_fast(a, --b, n * a);
    } else {
        return exp_rec_fast(a * a, b / 2, n);
    }
}


// Задание 3. **Исполнитель Калькулятор преобразует целое число, записанное на экране. У исполнителя две команды, каждой команде присвоен номер:
//1) Прибавь 1
//2) Умножь на 2
//Первая команда увеличивает число на экране на 1, вторая увеличивает это число в 2 раза. Сколько существует программ, которые число 3 преобразуют в число 20?
void exec_calc(void) {
    int count = search_count_exec(3, 20);
    printf("Number of possible programs = %i", count);
}

int search_count_exec(int num, int final) {
    if (num > final / 2) {
        return 1;
    }
    return search_count_exec(num + 1, final) + search_count_exec(num * 2, final);
}

void print_menu(void) {
    printf("\n\n'1' - dec to bin");
    printf("\n'2' - exponentiation");
    printf("\n'3' - execute calculator");
    printf("\n'0' - quit");
    printf("\nSelect command: ");
}
