#include <stdio.h>

/* ”совершенствуйте программу преобразовани€ температур таким образом, чтобы над
таблицей она печатала заголовок. */

int fromFahrToCels(float fahr);
int main()
{
	float fahr, celsius;
	int lower, upper, step;
	lower = 0; /* нижн€€ граница таблицы температур */
	upper = 300; /* верхн€€ граница */
	step = 20; /* шаг */
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