#include <stdio.h>

/*Напишите программу,
 * которая будет печатать таблицу соответствия температур по
 * Цельсию температурам по Фаренгейту.*/

int main()
{
    float fahr, celsius;
    int lower, upper, step;
    lower = 0; /* нижняя граница таблицы температур */
    upper = 300; /* верхняя граница */
    step = 20; /* шаг */
    celsius = lower;
    printf("%3s %9s\n", "Cels", "Faren");
    while (celsius <= upper) {
        fahr = celsius / (5.0/9.0) + 32.0;
        printf ("%5.0f %9.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
    return  0;
}