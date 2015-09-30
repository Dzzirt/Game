#include <stdio.h>

/* ���������������� ��������� �������������� ���������� ����� �������, ����� ���
�������� ��� �������� ���������. */

int fromFahrToCels(float fahr);
int main()
{
	float fahr, celsius;
	int lower, upper, step;
	lower = 0; /* ������ ������� ������� ���������� */
	upper = 300; /* ������� ������� */
	step = 20; /* ��� */
	fahr = lower;
	printf("%3s %9s\n", "Fahren", "Cels");
	while (fahr <= upper) {
		celsius = fromFahrToCels(fahr);
		printf("%5.0f %9.1f\n", fahr, celsius);
		fahr = fahr + step;
	}
	return  0;
}

int fromFahrToCels(float fahr)
{
	return (5.0 / 9.0) * (fahr - 32.0);
}