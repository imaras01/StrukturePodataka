#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
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
	{
		fprintf(file, "%d ", head->next->number);
		head = head->next;
	}

	fclose(file);
	DeleteStack(head);
	return 0;
}

int DeleteStack(StackPosition head)
{
	StackPosition temp = NULL;

	while (head->next)
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}

	return 0;
}
