#include <stdio.h>


/* �������� ���������, ������� �������� ���������� ������ �����, ������� �� ������
����� �� ������ ������. */


int main()
{
	int c;
	while ((c = getchar()) != 'E')
	{
		if (c < 65 || (c > 90 && c < 97) || c > 122)
		{
			putchar(c);
			putchar('\n');
		}
		else putchar(c);
	}
	return 0;
}
