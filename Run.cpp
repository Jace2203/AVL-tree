#include <Windows.h>
#include "Tree.h"

int main()
{
	int count;
	std::cin >> count;
	std::cout << std::endl;
	Node* Tree = nullptr;
	for (int i = 0; i < count; i++)
	{
		int a;
		std::cin >> a;
		if (Tree == nullptr)
		{
			Node* root = new Node(a, 0, 0);
			Tree = root;
		}
		else
		{
			Tree->push(a);
		}
		Tree->balance();
		Tree->Draw();
		std::cout << std::endl;
	}
	
	Tree->Draw();

	int a;
	std::cin >> a;
	std::cout << Tree->search(a) << std::endl;

	Tree = Tree->deletion(a);
	Tree->Draw();

	Tree->del();
	system("pause");
}