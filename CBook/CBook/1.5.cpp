#include <stdio.h>


/* Измените программу преобразования
 * температур так, чтобы она печатала таблицу в
 * обратном порядке, т. е. от 300 до 0. */


int main()
{
    int fahr;
    for (fahr = 300; fahr >= 0; fahr = fahr - 20)
        printf ("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
    return 0;
}