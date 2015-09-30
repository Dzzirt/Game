#include <stdio.h>
#define MAXLINE 2147483647 /* ������������ ������ �������� ������ */
int getline(char line[], int maxline);
void copy(char to[], char from[]);
/* ������ ����� ������� ������ */
int main()
{	
	int len; /* ����� ������� ������ */
	int max; /* ����� ������������ �� ������������� ����� */
	char line[MAXLINE]; /* ������� ������ */
	char longest[MAXLINE]; /* ����� ������� ������ */
	max = 0;
	while ((len = getline(line, MAXLINE)) > 0)
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	if (max > 0) /* ���� �� ���� ���� ������? */
		printf("%s", longest);
	return 0;
}
/* getline: ������ ������ � s, ���������� ����� */

int getline(char s[], int lim)
{
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	s[i] = '\0';
	return i;
}
/* copy: �������� �� 'from' � 'to'; to ���������� ������� */
void copy(char to[], char from[])
{
	int i;
	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}