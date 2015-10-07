#include <iostream>
#include <string>
#include <fstream>

// Кузин Никита ПС-21 Лаба 1.

/* Вариант 9: Имеется  текстовый  файл  с  некоторым  описанием.   Все
предложения   заканчиваются   точкой.   Требуется   проверить,
является  ли  первая  буква  каждого  предложения   прописной.
Исправить обнаруженные ошибки (6). */

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
	cout << "Введите имя файла: ";
	cin >> file_name;
	fstream file(file_name, ios_base::in);
	fstream temp("temp.txt", ios_base::out);
	while (file.is_open() == false) {
		cout << "Файл не существует!\nВведите имя файла: ";
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
