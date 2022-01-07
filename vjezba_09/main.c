#include<stdio.h>
#include"binary_tree.h"

int main()
{
	StackElement head = { .number = 0, .next = NULL };
	Position root = NULL;
	int status = 0;

	root = FillTree(root);

	SortInOrder(root, &head);
	status = WriteInFile(&head, "FirstTree.txt");
	if (status)
		return -1;

	root = Replace(root);
	
	SortInOrder(root, &head);
	status = WriteInFile(&head, "SecondTree.txt");
	if (status)
		return -1;

	root = DeleteTree(root);

	root = FillRandomTree(root);

	SortInOrder(root, &head);
	status = WriteInFile(&head, "RandomTree.txt");
	if (status)
		return -1;

	return 0;
}