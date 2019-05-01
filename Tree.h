#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>

int pow(int base, int x);

COORD GetCursorPos();

void gotoxy(int x, int y);

class Node
{
	int value = 0;
	Node *left = 0;
	Node *right = 0;

public:
	Node(int data, Node* ptrL, Node* ptrR);

	void branchLeft(Node *node);
	void branchRight(Node *node);

	void balance();
	int height();
	int Weight();
	void turnLeft();
	void turnRight();

	void printTree();
	void drawTree(int start, int height, int origin);
	void Draw();

	Node* findMin();
	Node* findMax();

	void push(int data);
	void push(Node *node);
	Node* search(int target);
	Node* deletion(int target);

	void del();
};