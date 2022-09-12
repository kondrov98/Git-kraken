#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define false 1!=1
#define true 1==1

typedef struct node
{
	short key;							 //ключ узла
	struct node* left_branch;			 //левая ветвь бинарного дерева
	struct node* right_branch;			 //правая ветвь бинарного дерева
}Node;


Node* new_node(Node* tree, short key, short mode) //функция добавления узла
{
	short flag = false;
	Node* new_node = mode == 0?(Node*)malloc(sizeof(Node)):tree->right_branch;
	new_node->left_branch = mode == 0 ? NULL: new_node->left_branch;
	new_node->right_branch = mode == 0 ? NULL : new_node->right_branch;
	new_node->key = key;
	tree = mode == 0 ? tree : tree->left_branch;
	Node* current= tree;
	Node* parent = tree;
	if (tree == NULL)
	{
		tree = new_node;
	}
	else
	{
		while (current!=NULL)
		{
			parent = current;
			if (current->key > key)
			{
				current = parent->left_branch;
				if (current == NULL)
				{
					parent->left_branch = new_node;
				}
			}
			else
			{
				current = parent->right_branch;
				if (current == NULL)
				{
					parent->right_branch = new_node;
				}
			}
		}
	}
	return tree;
}

Node* delete_node(Node* tree, short key)
{
	Node* current = tree;
	Node* parent = tree;
	if (tree != NULL)
	{
		if (tree->key == key)
		{
			current = parent->right_branch != NULL ? new_node(current, current->right_branch->key, 1) : (parent->left_branch != NULL ? parent->left_branch : NULL);
			free(tree);
			tree = NULL;
		}
		else
		{
			if (current != NULL)
			{
				current = parent->left_branch;
				parent->left_branch = delete_node(current, key);
				current = parent->right_branch;
				parent->right_branch = delete_node(current, key);
			}
		}
	}
	return current;
} 

void tree_traversal(Node* tree)
{
	Node* current = tree;
	Node* parent = tree;
	if (current != NULL)
	{
		current = parent->left_branch;
		printf("%i-->", parent->key);
		tree_traversal(current);
		current = parent->right_branch;
		printf("%i-->", parent->key);
		tree_traversal(current);
	}
	else
	{
		printf("NULL\n");
	}
}



int main()
{
	Node* bin_tree = NULL;

	bin_tree = new_node(bin_tree, 48, 0);
	bin_tree = new_node(bin_tree, 56, 0);
	bin_tree = new_node(bin_tree, 13, 0);
	bin_tree = new_node(bin_tree, 23, 0);
	bin_tree = new_node(bin_tree, 33, 0);
	bin_tree = new_node(bin_tree, 65, 0);
	bin_tree = new_node(bin_tree, 21, 0);
	tree_traversal(bin_tree);
	printf("\n");

	bin_tree=delete_node(bin_tree, 48);
	printf("\n");
	tree_traversal(bin_tree);

	return 0;
}