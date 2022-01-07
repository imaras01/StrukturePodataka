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

struct _stack;
typedef struct _stack* StackPosition;
typedef struct _stack
{
	int number;
	Position next;
}StackElement;

Position CreateNewTreeElement(int number);
Position FillTree(Position root);
Position Insert(Position root, Position NewElement);
int SortInOrder(Position root, StackPosition head);
Position Replace(Position root);
int CalculateSum(Position root, int* sum);
int Push(StackPosition head, int number);
StackPosition CreateNewStackElement(int number);
int WriteInFile(StackPosition head, char* filename);
int DeleteAfter(StackPosition head);
int Pop(StackPosition head);
Position DeleteTree(Position root);
Position FillRandomTree(Position root);



#endif
