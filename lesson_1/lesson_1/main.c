//
//  main.c
//  lesson_1
//
//  Created by Игорь Андрианов on 14.12.2021.
//

#include <stdio.h>
#include <math.h>

void BMI_calc(void);
void max_num(void);
void reverse_nums();
void quad_eq(void);
void print_menu(void);

int main()
{
    int command = 0;

    do {
        print_menu();
        scanf("%i",&command);
        switch (command)
        {
            case 1:
                BMI_calc();
                break;
            case 2:
                max_num();
                break;
            case 3:
                reverse_nums();
                break;
            case 4:
                quad_eq();
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

// Задание 1. Ввести вес и рост человека. Рассчитать и вывести индекс массы тела по формуле I=m/(h*h); где m-масса тела в килограммах, h - рост в метрах.
void BMI_calc(void)
{
    int mass = 0;
    double hight = .0;
    double bmi = .0;
    
    printf("Enter mass (kg): ");
    scanf("%d", &mass);
    printf("Enter hight (cm): ");
    scanf("%lf", &hight);
    
    hight /= 100;
    bmi = mass / (hight * hight);
    printf("\nYour BMI - %.2f\n", bmi);
}

// Задание 2. Найти максимальное из четырех чисел. Массивы не использовать.
void max_num(void)
{
    int a, b, c, d = 0;
    printf("Enter 4 nums through spaces: ");
    scanf("%i %i %i %i", &a, &b, &c, &d);
    a = (a > b) ? a : b;
    a = (a > c) ? a : c;
    a = (a > d) ? a : d;
    printf("Max num - %i \n", a);
}

// Задание 3. Написать программу обмена значениями двух целочисленных переменных:
//a. с использованием третьей переменной;
//b. *без использования третьей переменной.
void reverse_nums(void)
{
    int a, b = 0;
    printf("Enter 2 nums through space: ");
    scanf("%i %i", &a, &b);
    //вариант 1
    int temp = a;
    a = b;
    b = temp;
    printf("Now \t\t\t\ta = %i, b = %i\n", a, b);
    //вариант 2
    a += b;
    b = a - b;
    a = a - b;
    printf("And now \t\t\ta = %i, b = %i\n", a, b);
    //вариант 3
    a -= b;
    b = a + b;
    a = b - a;
    printf("What about now?.. \ta = %i, b = %i\n", a, b);
    //вариант 4
    a *= b;
    b = a / b;
    a = a / b;
    printf("OK... finaly return a = %i, b = %i\n", a, b);
}

// Задание 4. Написать программу нахождения корней заданного квадратного уравнения.
void quad_eq(void)
{
    double a, b, c = .0;
    printf("Enter a, b and c nums: ");
    scanf("%lf %lf %lf", &a, &b, &c);
    int D = (b * b) - (4 * a * c);

    if (D < 0)
    {
        printf("Equation does not have roots ¯\\_(ツ)_/¯ \n");
        return;
    }
    
    if (!D)
    {
        printf("Equation has one root: %.2lf\n", (-b / (2 * a)) );
    }
    else
    {
        double x1 = (-b + sqrt(D)) / (2 * a);
        double x2 = (-b - sqrt(D)) / (2 * a);
        printf("Equation has two roots: %.2lf and %.2lf\n", x1 , x2 );
    }
}

void print_menu(void)
{
    printf("\n'1' - calc BMI");
    printf("\n'2' - search max num");
    printf("\n'3' - reverse two num");
    printf("\n'4' - find square roots");
    printf("\n'0' - quit");
    printf("\nSelect command: ");
}
