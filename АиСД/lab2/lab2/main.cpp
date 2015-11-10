#include <iostream>
#include <sstream>
#include "stack.h"

using namespace std;

/*  В   символьной  строке  записано  выражение  из  букв  и
операций в постфиксной форме (знак операции  после операндов).
Проверить   правильность   записи   и  перевести  выражение  в
инфиксную (обычную)  форму  со  скобками. Например,  выражение
(a+b)*c-d*e  записывается  в постфиксной форме как  ab+c*de*-.
Требуется выдать его в виде (((a+b)*c)-(d*e)) */


int main()
{
	setlocale(LC_ALL, "Russian");
	Stack stack;
	string post;
	string operators = "*-/+";
	string str;
	bool needToPrint = true;
	bool have_op = false;
	cout << "Введите выражение в постфиксной форме: ";
	cin >> post;
	for (size_t i = 0; i < post.size(); i++)
	{
		if ((post[i] >= 97 && post[i] <= 122) || (post[i] >= 65 && post[i] <= 90))
		{
			string post_el(1, post[i]);
			stack.push(post_el);
		}
		else if (operators.find_first_of(post[i])!= string::npos)
		{
			if (stack.getSize() > 1) {
				have_op = true;
				string second = stack.getData();
				stack.pop();
				string first = stack.getData();
				stack.pop();
				string result = "(" + first + post[i] + second + ")";
				stack.push(result);
			}
			else {
				needToPrint = false;
				break;
			}
			

		}
	}
	if (needToPrint && have_op) {
		cout << "Результат перевода: ";
		stack.print();
	}
	else {
		cout << "Неверно заданное выражение!" << endl;;
	}
	return 0;
}
