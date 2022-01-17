#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hash_table.h"

int ReadFile(Country hash_table[], char* filename)
{
	FILE* file = NULL;
	ListPosition temp = NULL;
	char buffer[MAX_LINE] = { 0 };
	char name[80] = { 0 };
	char fname[80] = { 0 };
	int key = 0;

	file = fopen(filename, "r");
	if (!file)
	{
		printf("File could not be opened!");
		return -1;
	}

	while (fgets(buffer, MAX_LINE, file))
	{
		sscanf(buffer, " %s %s", name, fname);
		temp = CreateNewListElement(name);
		if (!temp)
			return -1;

		key = CalculateHash(name);
		InsertInTable(&hash_table[key], temp);
		FillTrees(temp, fname);
	}

	fclose(file);
	return 0;
}

ListPosition CreateNewListElement(char name[])
{
	ListPosition NewElement = NULL;

	NewElement = (ListPosition)malloc(sizeof(Country));
	if (!NewElement)
	{
		printf("Could not allocate memory!");
		return NULL;
	}

	strcpy(NewElement->name, name);
	NewElement->next = NULL;
	NewElement->root = NULL;

	return NewElement;
}

int InsertInTable(ListPosition head, ListPosition NewElement)
{
	ListPosition temp = head;

	while (temp->next != NULL && strcmp(NewElement->name, temp->next->name) > 0)
		temp = temp->next;

	NewElement->next = temp->next;
	temp->next = NewElement;

	return 0;
}

int FillTrees(ListPosition NewElement, char* filename)
{
	FILE* file = NULL;
	TreePosition temp = NULL;
	char buffer[MAX_LINE] = { 0 };
	char name[80] = { 0 };
	int population = 0;

	file = fopen(filename, "r");
	if (!file)
	{
		printf("File could not be opened!");
		return -1;
	}

	while (fgets(buffer, MAX_LINE, file))
	{
		sscanf(buffer, " %s %d", name, &population);
		temp = CreateNewTreeElement(name, population);
		if (!temp)
			return -1;

		NewElement->root = InsertInTree(NewElement->root, temp);
	}

	fclose(file);
	return 0;

}

TreePosition CreateNewTreeElement(char name[], int population)
{
	TreePosition NewElement = NULL;

	NewElement = (TreePosition)malloc(sizeof(City));
	if (!NewElement)
	{
		printf("Could not allocate memory!");
		return NULL;
	}

	strcpy(NewElement->name, name);
	NewElement->population = population;
	NewElement->left = NULL;
	NewElement->right = NULL;

	return NewElement;
}

TreePosition InsertInTree(TreePosition root, TreePosition NewElement)
{
	if (root == NULL)
		root = NewElement;

	else if (NewElement->population > root->population)
		root->right = InsertInTree(root->right, NewElement);

	else if (NewElement->population < root->population)
		root->left = InsertInTree(root->left, NewElement);

	else
	{
		if (strcmp(NewElement->name, root->name) < 0)
			root->left = InsertInTree(root->left, NewElement);

		else if (strcmp(NewElement->name, root->name) > 0)
			root->right = InsertInTree(root->right, NewElement);

	}

	return root;
}

int CalculateHash(char name[])
{
	int sum = 0;
	int i = 0;

	for (i = 0; i < 5; i++)
	{
		sum += (int)name[i];
	}

	return sum % 11;
}
