#include "stack.h"

using namespace std;

void Stack::push(string data)
{
	Node* next = head;
	head = new Node();
	head->data = data;
	head->next = next;
	size++;
}

void Stack::pop()
{
	Node* new_head = head->next;
	delete head;
	head = new_head;
	size--;
}

void Stack::print()
{
	for (Node*& iter = head; iter != nullptr; iter = head->next)
	{
		cout << iter->data << endl;
	}
}

string Stack::getData()
{
	return head->data;
}

int Stack::getSize()
{
	return size;
}

Stack::Stack() {
	size = 0;
	head = nullptr;
}