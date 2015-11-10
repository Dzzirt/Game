#pragma once
#include <string>
#include <iostream>

struct Node
{
	std::string data;
	Node* next;
};

class Stack
{
public:

	Stack();

	void push(std::string data);

	void pop();

	void print();

	int getSize();

	std::string getData();

private:
	Node* head;
	int size;
};
