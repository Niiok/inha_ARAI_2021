#pragma once
#include "Stack.h"
#include "Queue.h"
#include <assert.h>

template <typename T>
class BinaryTree
{
	struct Node {
		Node* parent = NULL;
		Node* left = NULL;
		Node* right = NULL;
		T* data;
		int index = 0;

		Node()
		{
			data = new T();
		}
		Node(Node* a, Node* b, Node* c, T d, int e)
			: parent{ a }, left{ b }, right{ c }, index{ e }
		{
			data = new T;
			*data = d;
		}
		~Node()
		{
			delete data;
		}

		void swap(Node* another)
		{
			T* temp = data;
			data = another->data;
			another->data = temp;

			int index_temp = index;
			index = another->index;
			another->index = index_temp;
		}
	};


public:
	BinaryTree();
	BinaryTree(int);
	virtual ~BinaryTree();

protected:
	Node* root_ = NULL;
	int size_ = 0;


public:

	// modifier
	virtual void Add(int index, T data);
	virtual void Remove(int index);


	// element access
	bool Search(int);
	T& operator[] (int index);

	// etc
	int size();
	virtual int foreach(int(*func)(T& a, T& b), T& b);
	//int binary_each(int(*func)(T& a, T& b), T& b);

protected:
	Node* FindNode(int index)
	{

		Node* prev = root_;

		while (prev != NULL)
		{
			if (index > prev->index)
				prev = prev->right;
			else if (index < prev->index)
				prev = prev->left;
			else if (index == prev->index)
				break;
		}

		return prev;
	}
	virtual int inorder(Queue<Node*>& que, Node* target);
	virtual int postorder(Queue<Node*>& que, Node* target);
};


#include "BinaryTree.cpp"


