#include <stdio.h>
/* Убедитесь в том, что выражение getchar() != EOF получает значение 0 или 1 */

int main ()
{
    int c;
    if ((c = getchar()) != EOF)
        printf("1\n");
    else printf("0\n");
    return 0;

}