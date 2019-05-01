#include "Tree.h"

int pow(int base, int x)
{
	if (x == 0)
	{
		return 1;
	}
	else
	{
		return base * pow(base, x - 1);
	}
}

COORD GetCursorPos()
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		COORD invalid = { 0, 0 };
		return invalid;
	}
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

Node::Node(int data, Node* ptrL, Node* ptrR)
{
	value = data;
	left = ptrL;
	right = ptrR;
}

void Node::branchLeft(Node *node)
{
	left = node;
}

void Node::branchRight(Node *node)
{
	right = node;
}

void Node::balance()
{
	if (left != nullptr)
		left->balance();
	if (right != nullptr)
		right->balance();

	int weight = Weight();
	if (weight >= 2)
	{
		if (right->Weight() < 0)
			right->turnRight();
		turnLeft();
	}
	else if (weight <= -2)
	{
		if (left->Weight() > 0)
			left->turnLeft();
		turnRight();
	}
}

int Node::height()
{
	if (this == 0)
		return 0;
	if ((left == 0) && (right == 0))
		return 1;

	int leftHeight = left->height();
	int rightHeight = right->height();

	return max(leftHeight, rightHeight) + 1;
}

int Node::Weight()
{
	return right->height() - left->height();
}

void Node::turnLeft()
{
	bool haveLeft = false;
	int tempV = value;
	Node* tempL = 0;
	Node* tempR = right;
	if (left != 0)
	{
		haveLeft = true;
		tempL = left;
	}
	Node* newNode = new Node(tempV, 0, 0);
	value = tempR->value;
	right = tempR->right;
	left = newNode;
	if (haveLeft)
	{
		newNode->left = tempL;
	}
	if (tempR->left != 0)
	{
		left->push(tempR->left);
	}
}

void Node::turnRight()
{
	bool haveRight = false;
	int tempV = value;
	Node* tempL = left;
	Node* tempR = 0;
	if (right != 0)
	{
		haveRight = true;
		tempR = right;
	}
	Node* newNode = new Node(tempV, 0, 0);
	value = tempL->value;							
	left = tempL->left;								
	right = newNode;								
	if (haveRight)									
	{												
		newNode->right = tempR;						
	}												
	if (tempL->right != 0)							
	{												
		right->push(tempL->right);
	}
}

void Node::printTree()
{
	if (left != 0)
		left->printTree();
	std::cout << value << ' ';
	if (right != 0)
		right->printTree();
}

void Node::drawTree(int start, int H, int origin)
{
	if (this == nullptr)
	{
		std::cout << "This is an empty tree." << std::endl;
	}
	else
	{
		if (left != 0)
			left->drawTree(start, H + 1, origin);
		gotoxy(start + pow(2, origin - H), H * 2);
		std::cout << value;
		if (right != 0)
			right->drawTree(start + pow(2, origin - H), H + 1, origin);
	}
}

void Node::Draw()
{
	system("cls");
	drawTree(0, 0, height());
	gotoxy(0, height() * 2 + 1);
}


Node* Node::findMin()
{
	if (left != nullptr)
		return left->findMin();
	return this;
}

Node* Node::findMax()
{

	if (right != nullptr)
		return right->findMin();
	return this;
}

void Node::push(int data)
{
	Node* next = new Node(data, 0, 0);
	if (data < value)
	{
		if (left == 0)
			left = next;
		else
			left->push(next);
	}
	else
	{
		if (right == 0)
			right = next;
		else
			right->push(next);
	}
}

void Node::push(Node *node)
{
	if (node->value < value)
	{
		if (left == 0)
			this->branchLeft(node);
		else
			left->push(node);
	}
	else
	{
		if (right == 0)
			this->branchRight(node);
		else
			right->push(node);
	}
}

Node* Node::search(int target)
{
	if (this == nullptr)
	{
		std::cout << "This is an empty tree." << std::endl;
	}
	else
	{
		if ((target < value) && (left != 0))
		{
			return left->search(target);
		}
		else if (target == value)
		{
			return this;
		}
		else if ((target > value) && (right != 0))
		{
			return right->search(target);
		}
	}
	return nullptr;
}

Node* Node::deletion(int target)
{
	if (this == nullptr)
		return this;
	else if (target < value)
		left = left->deletion(target);
	else if (target > value)
		right = right->deletion(target);
	else
	{
		if ((left == nullptr) && (right == nullptr))
		{
			delete this;
			return nullptr;
		}
		else if (left == nullptr)
		{
			Node* temp = right;
			delete this;
			return temp;
		}
		else if (right == nullptr)
		{
			Node* temp = left;
			delete this;
			return temp;
		}
		else
		{
			this->value = left->findMax()->value;
			left = left->deletion(value);
			balance();
		}
	}
	return this;
}

void Node::del()
{
	if (this == nullptr)
		return;
	if (left != nullptr)
		left->del();
	if (right != nullptr)
		right->del();
	if ((left == nullptr) && (right == nullptr))
		delete this;
}