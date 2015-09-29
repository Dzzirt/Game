/*Напишите программу для подсчета пробелов, табуляций и новых строк.*/

#include <stdio.h>

int main() {
    int c;
    int newLine = 0 , tabula = 0, whitespace = 0;
    while ((c = getchar()) != 'E') {
        if (c == '\n') {
            newLine++;
        } else if (c == '\t') {
            tabula++;
        } else if (c == ' ') {
            whitespace++;
        }
    }
    printf("WhiteSpace %d\nTabulation %d\nNewLine %d", whitespace, tabula, newLine);
    return 0;
}

