#include <iostream>
using namespace std;

class Tree
{
private:
	struct Node
	{
		int data;
		Node* left;
		Node* right;
		Node(int data) : data(data), left(nullptr), right(nullptr) {};
	};
	int size;
	Node* root;
	void clearnode(Node* node)
	{
		if (node == nullptr)
		{
			return;
		}
		clearnode(node->left);
		clearnode(node->right);
		delete node;
	}
public:
	Tree();
	~Tree();
	void add(int data);
	void remove(int data);
	bool contains(int data);
	int count();
	void clear();
};

Tree::Tree()
{
	size = 0;
	root = nullptr;
}

Tree::~Tree()
{
	clear();
}

void Tree::add(int data)
{
	Node* newnode = new Node(data);
	if (root == nullptr)
	{
		root = newnode;
	}
	else
	{
		Node* current = root;
		while (true)
		{
			if (data < current->data)
			{
				if (current->left == nullptr)
				{
					current->left = newnode;
					break;
				}
				current = current->left;
			}
			else
			{
				if (current->right == nullptr)
				{
					current->right = newnode;
					break;
				}
				current = current->right;
			}
		}
	}
	size++;
}

void Tree::remove(int data)
{
	Node* current = root;
	Node* parent = nullptr;
	while (current != nullptr && current->data != data)
	{
		parent = current;
		if (data < current->data)
		{
			current = current->left;
		}
		else
		{
			current = current->right;
		}
	}
	if (current == nullptr) return;
	
	if (current->left == nullptr || current->right == nullptr)
	{
		Node* newChild = (current->left != nullptr) ? current->left : current->right;
		if (parent == nullptr)
		{
			root = newChild;
		}
		else if (parent->left == current)
		{
			parent->left = newChild;
		}
		else
		{
			parent->right = newChild;
		}
	}

	else
	{
		Node* validSub = current->right;
		Node* validSubParent = current;
		while (validSub->left != nullptr)
		{
			validSubParent = validSub;
			validSub = validSub->left;
		}
		current->data = validSub->data;
		if (validSubParent == current)
		{
			validSubParent->right = validSub->right;
		}
		else
		{
			validSubParent->left = validSub->right;
		}
		current = validSub;
	}
	size--;
	delete current;
}

bool Tree::contains(int data)
{
	Node* current = root;
	while (current != nullptr)
	{
		if (current->data == data)
		{
			return true;
		}
		if (data < current->data)
		{
			current = current->left;
		}
		else
		{
			current = current->right;
		}
	}
	return false;
}

int Tree::count()
{
	return size;
}

void Tree::clear()
{
	clearnode(root);
	root = nullptr;
	size = 0;
}

int main()
{
	Tree tree;
	int choice;
	do
	{
		cout << "1. Add an element. " << endl;
		cout << "2. Remove an element. " << endl;
		cout << "3. Check if an element is in the tree. " << endl;
		cout << "4. Size of the tree. " << endl;
		cout << "5. Clear the tree. " << endl;
		cout << "0. Exit. " << endl;
		cin >> choice;
		int value;
		switch(choice)
		{
		case 1:
			cout << "Enter the element you want to add: " << endl;
			cin >> value;
			tree.add(value);
			cout << "The element is added. " << endl;
			break;
		case 2:
			cout << "Enter the element to remove: " << endl;
			cin >> value;
			tree.remove(value);
			cout << "The element is removed. " << endl;
			break;
		case 3:
			cout << "Enter the element to check: " << endl;
			cin >> value;
			if (tree.contains(value))
			{
				cout << "The element is in the tree. " << endl;
			}
			else
			{
				cout << "The element is not in the tree. " << endl;
			}
			break;
		case 4:
			cout << "The size of the tree is: " << tree.count() << endl;
			break;
		case 5:
			tree.clear();
			cout << "The tree is cleared. " << endl;
			break;
		case 0:
			break;
		default:
			cout << "An unknown command. Try again. " << endl;
			break;
		}
	} while (choice != 0);
	return 0;
}