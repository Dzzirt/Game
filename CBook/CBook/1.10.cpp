#include <stdio.h>


/*Напишите программу, копирующую вводимые символы в выходной поток с заменой
символа табуляции на \t, символа забоя на \b и каждой обратной наклонной черты на \\. Это сделает
видимыми все символы табуляции и забоя.*/


int main()
{
	int c;
	int newLine = 0, tabula = 0, whitespace = 0;
	int isWhiteSpace = 0;
	while ((c = getchar()) != 'E')
	{
		switch (c)
		{
		case '\b':
			putchar('\\');
			putchar('b');
			break;
		case '\t':
			putchar('\\');
			putchar('t');
			break;
		case 92:
			putchar(92);
			putchar(92);
			break;
		default:
			putchar(c);
			break;
		}
	}
	return 0;
}
