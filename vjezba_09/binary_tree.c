#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "binary_tree.h"

Position CreateNewTreeElement(int number)
{
	Position NewElement = (Position)malloc(sizeof(TreeElement));
	if (!NewElement)
	{
		printf("Couldn't allocate memory!");
		return NULL;
	}

	NewElement->number = number;
	NewElement->right = NULL;
	NewElement->left = NULL;

	return NewElement;
}

Position Insert(Position root, Position NewElement)
{
	if (root == NULL)
		root = NewElement;

	else if (NewElement->number >= root->number)
		root->left = Insert(root->left, NewElement);

	else if (NewElement->number <= root->number)
		root->right = Insert(root->right, NewElement);

	return root;
}

int SortInOrder(Position root, StackPosition head)
{
	if (root)
	{
		SortInOrder(root->right, head);
		Push(head, root->number);
		SortInOrder(root->left, head);
	}

	return 0;
}

Position Replace(Position root)
{
	int sum = 0;

	CalculateSum(root, &sum);
	root->number = sum;

	if (root->left)
		root->left = Replace(root->left);

	if (root->right)
		root->right = Replace(root->right);

	return root;
}

int CalculateSum(Position root, int* sum)
{

	if (root->left)
		(*sum) += CalculateSum(root->left, sum);
	
	if (root->right)
		(*sum) += CalculateSum(root->right, sum);

	return root->number;
}

int Push(StackPosition head, int number)
{
	StackPosition NewElement = CreateNewStackElement(number);
	if (!NewElement)
		return -1;

	NewElement->next = head->next;
	head->next = NewElement;

	return 0;
}

StackPosition CreateNewStackElement(int number)
{
	StackPosition NewElement = (StackPosition)malloc(sizeof(StackElement));
	if (!NewElement)
	{
		printf("Couldn't allocate memory!");
		return NULL;
	}

	NewElement->number = number;
	NewElement->next = NULL;

	return NewElement;
}

int WriteInFile(StackPosition head, char* filename)
{
	FILE* file = NULL;

	file = fopen(filename, "w");
	if (!file)
	{
		printf("Error! Couldn't open the file.");
		return -1;
	}

	while (head->next)
		fprintf(file, "%d ", Pop(head));

	fclose(file);
	return 0;
}

int DeleteAfter(StackPosition head)
{
	StackPosition temp = NULL;

	temp = head->next;
	head->next = temp->next;
	free(temp);

	return 0;
}

int Pop(StackPosition head)
{
	int number = head->next->number;

	DeleteAfter(head);

	return number;
}

Position FillTree(Position root)
{
	Position NewElement = NULL;
	int numbers[10] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	int i = 0;

	for (i = 0; i < 10; i++)
	{
		NewElement = CreateNewTreeElement(numbers[i]);
		if (!NewElement)
			return -1;

		root = Insert(root, NewElement);
	}

	return root;
}

Position DeleteTree(Position root)
{
	if (root->left)
		root->left = DeleteTree(root->left);

	if (root->right)
		root->right = DeleteTree(root->right);

	free(root);

	return NULL;
}

Position FillRandomTree(Position root)
{
	Position NewElement = NULL;
	int numbers[10] = { 0 };
	int i = 0;

	srand(time(NULL));

	for (i = 0; i < 10; i++)
	{
		numbers[i] = rand() % 81 + 10;
		NewElement = CreateNewTreeElement(numbers[i]);
		if (!NewElement)
			return -1;

		root = Insert(root, NewElement);
	}

	return root;
}
