#pragma once

#include <iostream>

using namespace std;

struct node {
	int value;
	node* left;
	node* right;
};

struct Node
{
	int data;
	struct Node* left, * right;
};



class btree {
public:
	btree();
	~btree();

	void insert(int key);
	node* search(int key);
	void destroy_tree();
	void inorder_print();
	void postorder_print();
	void preorder_print();

private:
	void destroy_tree(node* leaf);
	void insert(int key, node* leaf);
	node* search(int key, node* leaf);
	void inorder_print(node* leaf);
	void postorder_print(node* leaf);
	void preorder_print(node* leaf);

	node* root;
};


// credits : https://gist.github.com/toboqus/def6a6915e4abd66e922 
