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

	Node* deleteByMerging(Node*& node) {
		Node* tmp = node;
		if (node != nullptr) {
			if (!node->right) node = node->left;
			else if (node->left == nullptr) node = node->right;
			else {
				tmp = node->left;
				while (tmp->right != nullptr) tmp = tmp->right;
				tmp->right = node->right;
				tmp = node;
				node = node->left;
			}
			delete tmp;
			size--;
			return node;
		}
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
	if (contains(data))
	{
		return;
	}
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

void Tree:: remove(int value) {
	Node* node = root, * prev = 0;
	while (node != nullptr) {
		if (node->data == value)
			break;
		prev = node;
		if (value < node->data)
			node = node->left;
		else node = node->right;
	}
	if (node != nullptr && node->data == value) {
		if (node == root)
			root = deleteByMerging(root);
		else if (prev->left == node)
			prev->left = deleteByMerging(prev->left);
		else
			prev->right = deleteByMerging(prev->right);
	}
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
			break;
		case 2:
			cout << "Enter the element to remove: " << endl;
			cin >> value;
			tree.remove(value);
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