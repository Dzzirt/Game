#include <stdio.h>

/* �������� ���������, ���������� ����������� ���� �������� ����. ����������� �����
�������� ��������������� ��������. ��������� ������������� �������� � ����� ������� ������. */

int main()
{
	int c, state;

	state = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			if (state == 1)
				putchar('\n');
			state = 0;
		}
		else {
			if (state == 0)
				state = 1;
			putchar('-');
		}
	}
	return 0;
}