#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include "BinarySearchTree.h"

using namespace std;

template<typename T>
BinarySearchTree<T>::Node::Node(const T& n_data) : data(n_data), prev(nullptr), left(nullptr), right(nullptr), size(1) {}

template<typename T>
BinarySearchTree<T>::BinarySearchTree() : root(nullptr), numberOfNodes(0) {}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const char* fileName) : root(nullptr), numberOfNodes(0)
{
	ifstream fin(fileName);
	T temp;
	while (!fin.eof()) {
		fin >> temp;
		addElement(temp);
	}
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(T array[], unsigned long long int array_size) : root(nullptr), numberOfNodes(0)
{
	addElements(array, array_size);
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	Node* curr;
	queue<Node*> listOfNodes;
	listOfNodes.push(root);
	while (!listOfNodes.empty()) {
		curr = listOfNodes.front();
		listOfNodes.pop();
		if (curr != nullptr) {
			listOfNodes.push(curr->left);
			listOfNodes.push(curr->right);

			delete curr;
		}
	}
}

template<typename T>
void BinarySearchTree<T>::addElement(T n_data)
{
	if (root == nullptr) {
		root = new Node(n_data);

		numberOfNodes++;
		return;
	}

	Node* curr = root;
	Node* prev = nullptr;
	while (curr != nullptr) {
		if (n_data < curr->data) {
			prev = curr;
			curr = curr->left;
		}
		else if (n_data > curr->data) {
			prev = curr;
			curr = curr->right;
		}
		else {
			return;
		}
	}

	numberOfNodes++;

	curr = new Node(n_data);
	curr->prev = prev;
	if (n_data < prev->data) {
		prev->left = curr;
	}
	else {
		prev->right = curr;
	}

	curr = prev;
	while (curr != nullptr) {
		if (curr->left == nullptr) {
			curr->size = 1 + (curr->right)->size;
		}
		else if (curr->right == nullptr) {
			curr->size = 1 + (curr->left)->size;
		}
		else {
			curr->size = 1 + (curr->left)->size + (curr->right)->size;
		}
		curr = curr->prev;
	}


}

template<typename T>
void BinarySearchTree<T>::addElements(T array[], unsigned long long int array_size)
{
	for (int i = 0; i < array_size; i++) {
		addElement(array[i]);
	}
}

template<typename T>
void BinarySearchTree<T>::deleteNode(Node* node)
{
	if (node == root) {
		delete root;
		root = nullptr;
	}
	else {
		if (*(node->prev)->left == node) {
			*(node->prev)->left = nullptr;
		}
		else if (*(node->prev)->right == node) {
			*(node->prev)->right = nullptr;
		}
		delete node;
	}
}

template<typename T>
void BinarySearchTree<T>::removeElement(T n_data)
{
	Node* curr = root;
	while (curr != nullptr) {
		if (n_data < curr->data) {
			curr = curr->left;
		}
		else if (n_data > curr->data) {
			curr = curr->right;
		}
		else {
			Node* repl = curr;
			if (curr->left == nullptr && curr->right == nullptr) {
				deleteNode(curr);
				return;
			}
			else if (curr->left == nullptr && curr->right != nullptr) {
				repl = repl->prev;
				if (repl->left == curr) {
					repl->left = curr->right;
					delete curr;
				}
				else {
					repl->right = curr->left;
					delete curr;
				}
			}
			else if (curr->left != nullptr && curr->right == nullptr) {
				repl = repl->prev;
				if (repl->right == curr) {
					repl->right = curr->left;
					delete curr;
				}
				else {
					repl->left = curr->right;
					delete curr;
				}
			}
			else if (curr->left != nullptr && *(curr->left)->right != nullptr) {
				repl = *(curr->left)->right;
				while (repl->right != nullptr) {
					repl = repl->right;
				}
				curr->data = repl->data;
				deleteNode(repl);

			}
			else if (curr->right != nullptr && *(curr->right)->left != nullptr) {
				repl = *(curr->right)->left;
				while (repl->left != nullptr) {
					repl = repl->left;
				}
				curr->data = repl->data;
				deleteNode(repl);
			}

			numberOfNodes--;

			return;
		}
	}
}

template<typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::findNode(T n_data)
{
	Node* curr = root;
	while (curr != nullptr) {
		if (n_data < curr->data) {
			curr = curr->left;
		}
		else if (n_data > curr->data) {
			curr = curr->right;
		}
		else {
			return curr;
		}
	}
	return nullptr;
}

template<typename T>
bool BinarySearchTree<T>::findElement(T n_data)
{
	return findNode(n_data) != nullptr;
}

template<typename T>
T BinarySearchTree<T>::MinElement()
{
	Node* curr = root;

	while (curr->left != nullptr) {
		curr = curr->left;
	}

	cout << curr->data;
}

template<typename T>
T BinarySearchTree<T>::MaxElement()
{
	Node* curr = root;

	while (curr->right != nullptr) {
		curr = curr->right;
	}

	cout << curr->data;
}

template<typename T>
T BinarySearchTree<T>::ithElement(unsigned long long int n_i)
{
	unsigned long long int i = n_i;
	Node* curr = root;

	while (curr != nullptr) {
		if (curr->left == nullptr || (curr->left)->size == i - 1) {
			return curr->data;
		}
		else if ((curr->left)->size >= i) {
			curr = curr->left;
		}
		else if ((curr->left)->size < i - 1) {
			i = i - (curr->left)->size - 1;
			curr = curr->right;
		}
	}
}

template<typename T>
unsigned long long int BinarySearchTree<T>::Rank(T x)
{
	Node* curr = root;
	unsigned long long int offset = 0;
	while (curr != nullptr) {
		if (curr->data == x) {
			if (curr->right != nullptr) {
				return curr->size - (curr->right)->size + offset;
			}
			else {
				return curr->size + offset;
			}
		}
		else if (curr->data > x) {
			curr = curr->left;
		}
		else {
			if (curr->right != nullptr) {
				offset += curr->size - (curr->right)->size ;
			}
			curr = curr->right;
		}
	}
	return 0;
}

template<typename T>
unsigned long long int BinarySearchTree<T>::size()
{
	return numberOfNodes;
}

template<typename T>
void BinarySearchTree<T>::BFS()
{
	Node* curr;
	queue<Node* > listOfNodes;
	listOfNodes.push(root);

	while (!listOfNodes.empty()) {
		curr = listOfNodes.front();
		listOfNodes.pop();
		if (curr != nullptr) {

			listOfNodes.push(curr->left);
			listOfNodes.push(curr->right);

			cout << curr->data << " ";
		}
	}
}

template<typename T>
void BinarySearchTree<T>::BFS(const char* fileName)
{
	ofstream fout(fileName);

	Node* curr;
	queue<Node* > listOfNodes;
	listOfNodes.push(root);

	while (!listOfNodes.empty()) {
		curr = listOfNodes.front();
		listOfNodes.pop();
		if (curr != nullptr) {

			listOfNodes.push(curr->left);
			listOfNodes.push(curr->right);

			fout << curr->data << " ";
		}
	}
}

template<typename T>
void BinarySearchTree<T>::PreorderDFS()
{
	if (root == nullptr) {
		return;
	}

	stack<Node*> listOfNodes;
	Node* curr;
	listOfNodes.push(root);

	while (!listOfNodes.empty()) {
		curr = listOfNodes.top();
		listOfNodes.pop();
		cout << curr->data << " ";

		if (curr->right != nullptr) {
			listOfNodes.push(curr->right);
		}
		if (curr->left != nullptr) {
			listOfNodes.push(curr->left);
		}
	}
}

template<typename T>
void BinarySearchTree<T>::PreorderDFS(const char* fileName)
{
	ofstream fout(fileName);

	if (root == nullptr) {
		return;
	}

	stack<Node*> listOfNodes;
	Node* curr;
	listOfNodes.push(root);

	while (!listOfNodes.empty()) {
		curr = listOfNodes.top();
		listOfNodes.pop();
		fout << curr->data << " ";

		if (curr->right != nullptr) {
			listOfNodes.push(curr->right);
		}
		if (curr->left != nullptr) {
			listOfNodes.push(curr->left);
		}
	}
}

template<typename T>
void BinarySearchTree<T>::InorderDFS()
{
	if (root == nullptr) {
		return;
	}

	stack<Node*> listOfNodes;
	Node* curr = root;

	while (!listOfNodes.empty() || curr != nullptr) {
		if (curr != nullptr) {
			listOfNodes.push(curr);
			curr = curr->left;
		}
		else {
			curr = listOfNodes.top();
			listOfNodes.pop();
			cout << curr->data << " ";
			curr = curr->right;
		}
	}
}

template<typename T>
void BinarySearchTree<T>::InorderDFS(const char* fileName)
{
	ofstream fout(fileName);

	if (root == nullptr) {
		return;
	}

	stack<Node*> listOfNodes;
	Node* curr = root;

	while (!listOfNodes.empty() || curr != nullptr) {
		if (curr != nullptr) {
			listOfNodes.push(curr);
			curr = curr->left;
		}
		else {
			curr = listOfNodes.top();
			listOfNodes.pop();
			fout << curr->data << " ";
			curr = curr->right;
		}
	}
}

template<typename T>
void BinarySearchTree<T>::PostorderDFS()
{
	if (root == nullptr) {
		return;
	}

	stack<Node*> listOfNodesMain;
	stack<Node*> listOfNodesRightSide;
	Node* curr = root;

	while (!listOfNodesMain.empty() || curr != nullptr) {
		if (curr != nullptr) {
			if (curr->right != nullptr) {
				listOfNodesRightSide.push(curr->right);
			}
			listOfNodesMain.push(curr);
			curr = curr->left;
		}
		else {
			curr = listOfNodesMain.top();
			if (!listOfNodesRightSide.empty() && curr->right == listOfNodesRightSide.top()) {
				curr = listOfNodesRightSide.top();
				listOfNodesRightSide.pop();
			}
			else {
				cout << curr->data << " ";
				listOfNodesMain.pop();
				curr = nullptr;
			}
		}
	}
}

template<typename T>
void BinarySearchTree<T>::PostorderDFS(const char* fileName)
{
	ofstream fout(fileName);

	if (root == nullptr) {
		return;
	}

	stack<Node*> listOfNodesMain;
	stack<Node*> listOfNodesRightSide;
	Node* curr = root;

	while (!listOfNodesMain.empty() || curr != nullptr) {
		if (curr != nullptr) {
			if (curr->right != nullptr) {
				listOfNodesRightSide.push(curr->right);
			}
			listOfNodesMain.push(curr);
			curr = curr->left;
		}
		else {
			curr = listOfNodesMain.top();
			if (!listOfNodesRightSide.empty() && curr->right == listOfNodesRightSide.top()) {
				curr = listOfNodesRightSide.top();
				listOfNodesRightSide.pop();
			}
			else {
				fout << curr->data << " ";
				listOfNodesMain.pop();
				curr = nullptr;
			}
		}
	}
}

template<typename T>
T BinarySearchTree<T>::PreviousElement(T x)
{
	Node* curr = findNode(x);

	if (curr != nullptr) {
		if (curr->left != nullptr) {
			curr = curr->left;
			while (curr->right != nullptr) {
				curr = curr->right;
			}
			return curr->data;
		}
		else {
			while (curr != nullptr && curr->data >= x) {
				curr = curr->prev;
			}
			if (curr != nullptr && curr->data != x) {
				return curr->data;
			}
		}
	}
	return 0;
}

template<typename T>
T BinarySearchTree<T>::NextElement(T x)
{
	Node* curr = findNode(x);

	if (curr != nullptr) {
		if (curr->left != nullptr) {
			curr = curr->right;
			while (curr->left != nullptr) {
				curr = curr->left;
			}
			return curr->data;
		}
		else {
			while (curr != nullptr && curr->data <= x) {
				curr = curr->prev;
			}
			if (curr != nullptr && curr->data != x) {
				return curr->data;
			}
		}
	}
	return 0;
}

template<typename T>
void BinarySearchTree<T>::printInOrder()
{
	InorderDFS();
}

template<typename T>
void BinarySearchTree<T>::printInOrder(const char* fileName)
{
	InorderDFS(fileName);
}
