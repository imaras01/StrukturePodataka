#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "binary_tree.h"

TreePosition ReadFile(TreePosition root, char* filename)
{
	FILE* file = NULL;
	TreePosition temp = NULL;
	char buffer[MAX_LINE] = { 0 };
	char name[80] = { 0 };
	char fname[80] = { 0 };

	file = fopen(filename, "r");
	if (!file)
	{
		printf("File could not be opened!");
		return NULL;
	}

	while (fgets(buffer, MAX_LINE, file))
	{
		sscanf(buffer, " %s %s", name, fname);
		temp = CreateNewTreeElement(name);
		if (!temp)
			return NULL;

		root = InsertInTree(root, temp, fname);
	}

	fclose(file);
	return root;
}

TreePosition CreateNewTreeElement(char name[])
{
	TreePosition NewElement = NULL;

	NewElement = (TreePosition)malloc(sizeof(Country));
	if (!NewElement)
	{
		printf("Could not allocate memory!");
		return NULL;
	}

	strcpy(NewElement->name, name);
	NewElement->left = NULL;
	NewElement->right = NULL;
	NewElement->head = NULL;

	return NewElement;
}

TreePosition InsertInTree(TreePosition root, TreePosition NewElement, char* filename)
{
	if (root == NULL)
	{
		root = NewElement;
		root->head = FillList(root->head, filename);
	}

	else if (strcmp(NewElement->name,root->name) > 0)
		root->right = InsertInTree(root->right, NewElement, filename);

	else if (strcmp(NewElement->name, root->name) < 0)
		root->left = InsertInTree(root->left, NewElement, filename);

	return root;
}

ListPosition FillList(ListPosition head, char* filename)
{
	FILE* file = NULL;
	ListPosition temp = NULL;
	char buffer[MAX_LINE] = { 0 };
	char name[80] = { 0 };
	int population = 0;

	file = fopen(filename, "r");
	if (!file)
	{
		printf("File could not be opened!");
		return NULL;
	}

	while (fgets(buffer, MAX_LINE, file))
	{
		sscanf(buffer, " %s %d", name, &population);
		temp = CreateNewListElement(name, population);
		if (!temp)
			return NULL;

		head = InsertInList(head, temp);
	}

	fclose(file);
	return head;

}

ListPosition CreateNewListElement(char name[], int population)
{
	ListPosition NewElement = NULL;

	NewElement = (ListPosition)malloc(sizeof(Country));
	if (!NewElement)
	{
		printf("Could not allocate memory!");
		return NULL;
	}

	strcpy(NewElement->name, name);
	NewElement->population = population;
	NewElement->next = NULL;

	return NewElement;
}

ListPosition InsertInList(ListPosition head, ListPosition NewElement)
{
	ListPosition temp = head;

	if (head == NULL)
		head = NewElement;

	else if (head->population < NewElement->population)
		head->next = InsertInList(head->next, NewElement);

	else if (head->population > NewElement->population)
	{
		head = NewElement;
		NewElement = temp;
		head->next = InsertInList(head->next, NewElement);
	}

	else
	{
		if(strcmp(head->name, NewElement->name)<0)
			head->next = InsertInList(head->next, NewElement);

		else
		{
			head = NewElement;
			NewElement = temp;
			head->next = InsertInList(head->next, NewElement);
		}
	}

	return head;
}