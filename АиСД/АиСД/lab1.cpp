#include <iostream>
#include <string>
#include <fstream>

// ����� ������ ��-21 ���� 1.

/* ������� 9: �������  ���������  ����  �  ���������  ���������.   ���
�����������   �������������   ������.   ���������   ���������,
��������  ��  ������  �����  �������  �����������   ���������.
��������� ������������ ������ (6). */

using namespace std;

enum State {
	AFTER_DOT,
	BEFORE_DOT,
	FIRST_SENTENSE
};

int main() {
	State state = FIRST_SENTENSE;
	setlocale(LC_ALL, "rus");
	string file_name;
	cout << "������� ��� �����: ";
	cin >> file_name;
	fstream file(file_name, ios_base::in);
	fstream temp("temp.txt", ios_base::out);
	while (file.is_open() == false) {
		cout << "���� �� ����������!\n������� ��� �����: ";
		cin >> file_name;
		file.open(file_name);
	}
	int character = file.get();
	while (character != EOF) {
		if (character == 46) {
			state = AFTER_DOT;
		}
		if (state == FIRST_SENTENSE) {
			if ((character >= 192) && (character <= 223)) {
				state = BEFORE_DOT;
			}
			else if ((character >= 224) && (character <= 255)) {
				character -= 32;
				state = BEFORE_DOT;
			}
		}
		else if (state == AFTER_DOT) {
			if ((character >= 192) && (character <= 223)) {
				state = BEFORE_DOT;
			}
			else if ((character >= 224) && (character <= 255)) {
				character -= 32;
				state = BEFORE_DOT;
			}
		}
		temp << char(character);
		character = file.get();

	}
	file.close();
	temp.close();

	temp.open("temp.txt", ios_base::in);
	file.open(file_name, ios_base::out , ios_base::trunc);
	character = temp.get();
	while (character != EOF) {
		file << char(character);
		character = temp.get();
	}
	file.close();
	temp.close();
	remove("temp.txt");
	return 0;
}
