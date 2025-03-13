#ifndef BINARYSEARCHTREE_H_DEFINED

#define BINARYSEARCHTREE_H_DEFINED

template<typename T> 
class BinarySearchTree {
private:
	struct Node {			// A fának csomópontjai
		T data;				// A csomópontban tárolt adat
		Node* prev;			// A csomópontnak a szülő csomópontja
		Node* left;			// A csomópont bal leszármazottja, kisebb nála
		Node* right;		// A csomópont jobb leszármazottja, nagyobb nála
		unsigned long long int size;	// A részfában lévő csomópontok
		Node(const T& n_data);			// Alap konstruktor
	};
	Node* root;		// A fa gyökere
	unsigned long long int numberOfNodes;	// A fa csomópontjainak a száma

	// Belső függvények
	void deleteNode(Node* node);	// Egy csomópont kitörlése
	Node* findNode(T n_data);		// Adat alapján egy csomópont megkeresése és egy mutató visszatérítése

public:
	// Konstruktorok
	BinarySearchTree();												// Alapkonstruktor
	BinarySearchTree(const char* fileName);							// Értékek beolvasása egy szöveges állományból
	BinarySearchTree(T array[], unsigned long long int array_size);	// Értékek beolvasása egy statikus tömbből
	// Destrukor
	~BinarySearchTree();

	// Műveletek
	void addElement(T n_data);			// Elem hozzáadása
	void addElements(T array[], unsigned long long int array_size);	//Elemek hozzáadása egy tömbből
	void removeElement(T n_data);		// Elem kitörlése
	bool findElement(T n_data);			// Elem keresése

	T MinElement();				// Legkisebb elem
	T MaxElement();				// Legnagyobb elem
	T PreviousElement(T);		// Megadott elem elötti elem
	T NextElement(T);			// Megadott utánni elötti elem
	T ithElement(unsigned long long int i);	// i-edik elem
	unsigned long long int Rank(T x);		// Megadott elem helye a sorozatban
	unsigned long long int size();			// Megadja a fa csomópontjainak a számát

	// Kiírását
	void printInOrder();					// Kiírás növekvő sorrendben
	void printInOrder(const char* fileName);// Kiírás egy szöveges állományba növekvő sorrendben
	void BFS();								// Kiírás szélességi bejárással
	void BFS(const char* fileName);			// Kiírás egy szöveges állományba szélességi bejárással
	void PreorderDFS();						// Kiírás mélységi bejárással preorder módon
	void PreorderDFS(const char* fileName);	// Kiírás egy szöveges állományba mélységi bejárással preorder módon
	void InorderDFS();						// Kiírás mélységi bejárással inorder módon
	void InorderDFS(const char* fileName);	// Kiírás egy szöveges állományba mélységi bejárással inorder módon
	void PostorderDFS();					// Kiírás mélységi bejárással postorder módon
	void PostorderDFS(const char* fileName);// Kiírás egy szöveges állományba mélységi bejárással postorder módon

};

#include "BinarySearchTree.cpp"

#endif  
