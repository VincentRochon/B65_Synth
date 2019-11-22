#include "btree.h"

btree::btree() {
	root = NULL;
}

btree::~btree() {
	destroy_tree();
}

void btree::destroy_tree(node* leaf) {
	if (leaf != NULL) {
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

void btree::insert(int key, node* leaf) {

	if (key < leaf->value) {
		if (leaf->left != NULL) {
			insert(key, leaf->left);
		}
		else {
			leaf->left = new node;
			leaf->left->value = key;
			leaf->left->left = NULL;
			leaf->left->right = NULL;
		}
	}
	else if (key >= leaf->value) {
		if (leaf->right != NULL) {
			insert(key, leaf->right);
		}
		else {
			leaf->right = new node;
			leaf->right->value = key;
			leaf->right->right = NULL;
			leaf->right->left = NULL;
		}
	}

}



void btree::insert(int key) {
	if (root != NULL) {
		insert(key, root);
	}
	else {
		root = new node;
		root->value = key;
		root->left = NULL;
		root->right = NULL;
	}
}

node* btree::search(int key, node* leaf) {
	if (leaf != NULL) {
		if (key == leaf->value) {
			return leaf;
		}
		if (key < leaf->value) {
			return search(key, leaf->left);
		}
		else {
			return search(key, leaf->right);
		}
	}
	else {
		return NULL;
	}
}

node* btree::search(int key) {
	return search(key, root);
}

void btree::destroy_tree() {
	destroy_tree(root);
}

void btree::inorder_print() {
	inorder_print(root);
	cout << "\n";
}

void btree::inorder_print(node* leaf) {
	if (leaf != NULL) {
		inorder_print(leaf->left);
		cout << leaf->value << ",";
		inorder_print(leaf->right);
	}
}

void btree::postorder_print() {
	postorder_print(root);
	cout << "\n";
}

void btree::postorder_print(node* leaf) {
	if (leaf != NULL) {
		inorder_print(leaf->left);
		inorder_print(leaf->right);
		cout << leaf->value << ",";
	}
}

void btree::preorder_print() {
	preorder_print(root);
	cout << "\n";
}

void btree::preorder_print(node* leaf) {
	if (leaf != NULL) {
		cout << leaf->value << ",";
		inorder_print(leaf->left);
		inorder_print(leaf->right);
	}
}

node* btree::getRoot() {

	return root;
}

///////////////////////////////////////////////////////////////

// https://www.geeksforgeeks.org/find-median-bst-time-o1-space/



//struct node* insert(struct node* node, int key)
//{
//	/* If the tree is empty, return a new node */
//	if (node == NULL) return newNode(key);
//
//	/* Otherwise, recur down the tree */
//	if (key < node->value)
//		node->left = insert(node->left, key);
//	else if (key > node->value)
//		node->right = insert(node->right, key);
//
//	/* return the (unchanged) node pointer */
//	return node;
//}
//
//struct node* newNode(int item)
//{
//	struct node* temp = new node;
//	temp->value = item;
//	temp->left = temp->right = NULL;
//	return temp;
//}


int btree::countNodes(struct node* root)
{
	struct node* current, * pre;

	// Initialise count of nodes as 0 
	int count = 0;

	if (root == NULL)
		return count;

	current = root;
	while (current != NULL)
	{
		if (current->left == NULL)
		{
			// Count node if its left is NULL 
			count++;

			// Move to its right 
			current = current->right;
		}
		else
		{
			/* Find the inorder predecessor of current */
			pre = current->left;

			while (pre->right != NULL &&
				pre->right != current)
				pre = pre->right;

			/* Make current as right child of its
			   inorder predecessor */
			if (pre->right == NULL)
			{
				pre->right = current;
				current = current->left;
			}

			/* Revert the changes made in if part to
			   restore the original tree i.e., fix
			   the right child of predecssor */
			else
			{
				pre->right = NULL;

				// Increment count if the current 
				// node is to be visited 
				count++;
				current = current->right;
			} /* End of if condition pre->right == NULL */
		} /* End of if condition current->left == NULL*/
	} /* End of while */

	return count;
}


int btree::findMedian(struct node* root)
{
	if (root == NULL)
		return 0;

	int count = btree::countNodes(root);
	int currCount = 0;
	struct node* current = root, * pre, * prev;

	while (current != NULL)
	{
		if (current->left == NULL)
		{
			// count current node 
			currCount++;

			// check if current node is the median 
			// Odd case 
			if (count % 2 != 0 && currCount == (count + 1) / 2)
				return prev->value;

			// Even case 
			else if (count % 2 == 0 && currCount == (count / 2) + 1)
				return (prev->value + current->value) / 2;

			// Update prev for even no. of nodes 
			prev = current;

			//Move to the right 
			current = current->right;
		}
		else
		{
			/* Find the inorder predecessor of current */
			pre = current->left;
			while (pre->right != NULL && pre->right != current)
				pre = pre->right;

			/* Make current as right child of its inorder predecessor */
			if (pre->right == NULL)
			{
				pre->right = current;
				current = current->left;
			}

			/* Revert the changes made in if part to restore the original
			  tree i.e., fix the right child of predecssor */
			else
			{
				pre->right = NULL;

				prev = pre;

				// Count current node 
				currCount++;

				// Check if the current node is the median 
				if (count % 2 != 0 && currCount == (count + 1) / 2)
					return current->value;

				else if (count % 2 == 0 && currCount == (count / 2) + 1)
					return (prev->value + current->value) / 2;

				// update prev node for the case of even 
				// no. of nodes 
				prev = current;
				current = current->right;

			} /* End of if condition pre->right == NULL */
		} /* End of if condition current->left == NULL*/
	} /* End of while */
}




/*
int main() {

	//btree tree;
	btree* tree = new btree();

	tree->insert(10);
	tree->insert(6);
	tree->insert(14);
	tree->insert(5);
	tree->insert(8);
	tree->insert(11);
	tree->insert(18);

	tree->preorder_print();
	tree->inorder_print();
	tree->postorder_print();

	delete tree;

}*/