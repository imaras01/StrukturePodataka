#ifndef BINARY_TREE_H
#define BINARY_TREE_H

struct _tree;
typedef struct _tree* Position;
typedef struct _tree
{
	int number;
	Position left;
	Position right;
}TreeElement;

int Menu(Position root);
int Choice(int choice);
Position CreateNewElement(int number);
Position Insert(Position root, Position NewElement);
int PrintInorder(Position root);
int PrintPreorder(Position root);
int PrintPostorder(Position root);
int DeleteElement(Position root, int number);
Position FindElement(Position root, int number);
Position FindMin(Position root);





#endif

