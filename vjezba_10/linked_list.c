#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "linked_list.h"

int ReadFile(ListPosition head, char* filename)
{
	FILE* file = NULL;
	ListPosition temp = NULL;
	char buffer[MAX_LINE] = { 0 };
	char name[80] = { 0 };
	char fname[80] = { 0 };

	file = fopen(filename, "r");
	if (!file)
	{
		printf("File could not be opened!");
		return -1;
	}

	while (fgets(buffer, MAX_LINE, file))
	{
		sscanf(buffer, " %s %s", name, fname);
		temp= CreateNewListElement(head, name);
		if (!temp)
			return -1;

		InsertInList(head, temp);
		FillTrees(temp, fname);
	}

	fclose(file);
	return 0;
}

ListPosition CreateNewListElement(ListPosition head, char name[])
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

int InsertInList(ListPosition head, ListPosition NewElement)
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
		if(strcmp(NewElement->name, root->name)<0)
			root->left = InsertInTree(root->left, NewElement);
		
		else if(strcmp(NewElement->name, root->name)>0)
			root->right = InsertInTree(root->right, NewElement);
		
	}

	return root;
}

ListPosition SearchCountry(ListPosition head, char search[])
{
	while (head->next != NULL)
	{
		if (strcmp(search, head->next->name) == 0)
			return head->next;

		head = head->next;
	}

	puts("");
	printf("Searched country doesn't exist. Please try again.\n");

	return NULL;
}

int SearchTree(TreePosition root, int reference_number)
{
	if (root == NULL)
		return 0;

	else if (root->population > reference_number)
	{
		SearchTree(root->left, reference_number);
		printf("%s %d\n", root->name, root->population);
		SearchTree(root->right, reference_number);
	}

	else if (root->population < reference_number)
		SearchTree(root->right, reference_number);

	return 0;
}



