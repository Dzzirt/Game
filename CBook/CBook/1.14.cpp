#include <stdio.h>

/* подсчет цифр, символов-разделителей и прочих символов */

int main()
{
	int c, i, nwhite, nother;
	int ndigit[10];
	nwhite = nother = 0;
	for (i = 0; i < 10; ++i)
		ndigit[i] = 0;
	while ((c = getchar()) != 'E')
		if (c >= '0' && c <= '9')
			++ndigit[c - '0'];
		else if (c == ' ' || c == '\n' || c == '\t')
			++nwhite;
		else
			++nother;
		int num = 0;
	for (i = 0; i < 10; ++i)
	{
		printf("%d  ", num);
		num++;
		for (size_t j = 0; j < ndigit[i]; j++)
		{
			putchar('#');
		}
		putchar('\n');
	}
	printf("S  "); // Separators
	for (size_t i = 0; i < nwhite; i++)
	{
		putchar('#');
	}
	putchar('\n');
	printf("O  "); // Others
	for (size_t i = 0; i < nother; i++)
	{
		putchar('#');
	}
	putchar('\n');
	return 0;
}
