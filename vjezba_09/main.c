#include<stdio.h>
#include"binary_tree.h"

int main()
{
	StackElement head = { .number = 0, .next = NULL };
	Position root = NULL;
	Position NewElement = NULL;
	int status = 0;
	int numbers[10] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	int i = 0;

	for (i = 0; i < 10; i++)
	{
		NewElement = CreateNewTreeElement(numbers[i]);
		if (!NewElement)
			return -1;

		root = Insert(root, NewElement);
	}
	
	SortInOrder(root, &head);
	status = WriteInFile(&head, "FirstTree.txt");
	if (status)
		return -1;

	root = Replace(root);
	
	SortInOrder(root, &head);
	status = WriteInFile(&head, "SecondTree.txt");
	if (status)
		return -1;


	return 0;
}