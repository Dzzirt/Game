#include <stdio.h>



/* Выясните, что произойдет, если в строковую константу
 * аргумента printf вставить \с, где с — символ,
 * не входящий в представленный выше список. */


int main() {
    printf("Hello world!\c");
    return 0;
}