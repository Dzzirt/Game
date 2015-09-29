/* Напишите программу, копирующую символы ввода в выходной поток и заменяющую
стоящие подряд пробелы на один пробел.*/

#include <stdio.h>

int main() {
    int c;
    int newLine = 0 , tabula = 0, whitespace = 0;
	int isWhiteSpace = 0;
    while ((c = getchar()) != 'E') {
        if (c == ' ' && isWhiteSpace == 0) {
			isWhiteSpace = 1;
			putchar(c);
        }else if (c != ' ')
        {
			isWhiteSpace = 0;
			putchar(c);
        }
    }
    printf("WhiteSpace %d\nTabulation %d\nNewLine %d", whitespace, tabula, newLine);
    return 0;
}