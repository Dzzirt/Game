// TreeObhod.cpp: ���������� ����� ����� ��� ����������� ����������.
//
 
#include "TreeObhod.h"


using namespace std;

int read_from_file(FILE *F, Tree **r)
{
    char buf[DL];
    int i, k, m, len;
    Tree *p, *q, *t;       // *root = 0 
    m = 0;                 // ������� �������
    t = 0;
    while (!feof(F))
    {
		 k = fscanf(F, "%s", buf);
	     len = strlen(buf);              
		 if (len == 0) break;            // ���� ����� ����� � ��������� ������
	     k = 0;
	     while (buf[k] == '.') k++ ;     // k-������� �������
         p = new Tree;
         strncpy(p -> name, &buf[k], len-k+1);  // 0-(k-1) - �����, (k-1)-(len-1) - ���, \0 - ����� ������
		 buf[0] = '\0';                  // ���� ����� ����� � ��������� ������
         p -> urov = k;
         p -> left = 0;
         p -> right = 0;
	     if (k == 0)                    // ������
	     {
	         *r = p;
	         t = *r;
	         continue;
         }
         if (k > m)                  // ������� �� ��������� �������
	     {
	         t -> left = p;
	         p -> fath = t;
	     }
         else if (k == m)            // ��� �� �������
	     {
              t -> right = p;
              p -> fath = t-> fath;  // ���� ��� ��
         }
         else        // ������ �� ������ �� m-k �������
         {
              q = t;
              for (i = 0; i < m - k; i++) q = q -> fath;
              // q - ���������� ������� ���� �� ������
              p -> fath = q -> fath;   // ���� ��� ��, ��� � �����
              q -> right = p;
         }
         m = k;      // ������� �������
         t = p;      // ������� �������
    }
    fclose( F);
    return 0;
}

void back_from_bin(Tree *p)
{
    int i, j;
    char st[DL];
    if (p)
    {
        for (i = 0; i < p -> urov; i++) st[i] = '.';
        j = 0;
        while ((p -> name)[j] != 0) st[i++] = (p -> name)[j++];
        st[i] = '\0';
        printf("%s\n", st);
        back_from_bin(p -> left);
        back_from_bin(p -> right);
    }
}

void print_right_bin(Tree *p, int level)
{
    if (p)
    {
        print_right_bin(p -> left, level + 1);
        for (int i = 0; i < level; i++)
          printf("%c",'.');
        printf("%s\n", p -> name);
        print_right_bin(p -> right, level + 1);
    }
}

void print_up_bin(Tree *p, int level)
{
    if (p)
    {
        print_up_bin(p -> left, level + 1);
        print_up_bin(p -> right, level + 1);
        for (int i = 0; i < level; i++)
          printf("%c",'.');
        printf("%s\n", p -> name);
    }
}

void print_down_bin(Tree *p, int level)
{
    if (p)
    {
        for (int i = 0; i < level; i++)
          printf("%c",'.');
        printf("%s\n", p -> name);
        print_down_bin(p -> left, level + 1);
        print_down_bin(p -> right, level + 1);
    }
}
