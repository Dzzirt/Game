#include <stdio.h>

/* Усовершенствуйте программу преобразования температур таким образом, чтобы над
таблицей она печатала заголовок. */


int main()
{
    float fahr, celsius;
    int lower, upper, step;
    lower = 0; /* нижняя граница таблицы температур */
    upper = 300; /* верхняя граница */
    step = 20; /* шаг */
    fahr = lower;
    printf("%3s %9s\n", "Faren", "Cels");
    while (fahr <= upper) {
        celsius = (5.0/9.0) * (fahr-32.0);
        printf ("%5.0f %9.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
    return  0;
}