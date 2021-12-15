#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "directories.h"

int Menu(Position root, StackPosition head)
{
	char choice[MAX_NAME_SIZE] = { 0 };
	Position temp = NULL;
	Position current_directory = Pop(head);
	int status = 0;
	
	scanf(" %[^\n]s", choice);
	
	if (strcmp(choice, "md") == 0)
	{
		status = MakeDirectory(current_directory);
		return status;
	}

	else if (strcmp(choice, "cd dir") == 0)
	{
		temp = ChangeDirectory(current_directory);
		if (!temp)
			return 0;
		else
		{
			status = Push(head, temp);
			return status;
		}
	}

	else if (strcmp(choice, "cd..") == 0)
	{
		if (head->next->next == NULL)
			return 0;

		DeleteAfter(head);
		return 0;
	}

	else if (strcmp(choice, "dir") == 0)
	{	
		if (current_directory->child == NULL)
		{
			printf("There aren't any directories.\n");
			return 0;
		}

		PrintDirectories(current_directory->child);
		return 0;
	}

	else if (strcmp(choice, "exit") == 0)
		return -1;

	else
	{
		printf("Your command is not recognized. Please try again.\n");
		return 0;
	}

}

int MakeDirectory(Position current_directory)
{
	char name[MAX_NAME_SIZE] = { 0 };
	Position NewDirectory = NULL;
	Position LastDirectory = NULL;

	printf("What is the name of the new file: ");
	scanf(" %[^\n]s", name);

	if (NameCheck(current_directory->child, name))
	{
		printf("Directory with that name already exists.\n");
		return 0;
	}

	NewDirectory = CreateNewDirectory(name);
	if (!NewDirectory)
		return -1;

	if (current_directory->child == NULL)
	{
		current_directory->child = NewDirectory;
	}
	
	else
	{
		LastDirectory = FindLastDirectory(current_directory->child);
		InsertAfter(LastDirectory, NewDirectory);
	}

	return 0;
}

Position CreateNewDirectory(char name[])
{
	Position NewDirectory = (Position)malloc(sizeof(Directory));
	if (!NewDirectory)
	{
		printf("Couldn't allocate memory!");
		return NULL;
	}

	strcpy(NewDirectory->name, name);
	NewDirectory->child = NULL;
	NewDirectory->sibling = NULL;
	return NewDirectory;
}

Position FindLastDirectory(Position first)
{
	Position temp = first;

	while (temp->sibling != NULL)
	{
		temp = temp->sibling;
	}
	
	return temp;
}

int InsertAfter(Position last_directory, Position new_directory)
{
	new_directory->sibling = last_directory->sibling;
	last_directory->sibling = new_directory;

	return 0;
}

Position ChangeDirectory(Position current_directory)
{
	char name[MAX_NAME_SIZE] = { 0 };
	Position temp = current_directory->child;

	printf("What directory do you want to go to: ");
	scanf(" %[^\n]s", name);

	while (temp != NULL && strcmp(name, temp->name) != 0)
	{
		temp = temp->sibling;
	}

	if (!temp)
	{
		printf("The system could not find the path specified.\n");
		return NULL;
	}

	return temp;
}

int DeleteAfter(StackPosition head)
{
	StackPosition temp = head->next;

	head->next = temp->next;
	free(temp);

	return 0;
}

int Push(StackPosition head, Position current_directory)
{
	StackPosition NewElement = (StackPosition)malloc(sizeof(Stack));
	if (!NewElement)
	{
		printf("Could not allocate memory!\n");
		return -1;
	}
	
	NewElement->directory = current_directory;
	NewElement->next = NULL;

	StackInsert(head, NewElement);

	return 0;
}

int StackInsert(StackPosition head, StackPosition new_element)
{
	new_element->next = head->next;
	head->next = new_element;

	return 0;
}

int PrintDirectories(Position first)
{
	while (first != NULL)
	{
		printf(" %s\n", first->name);
		first = first->sibling;
	}

	return 0;
}

Position Pop(StackPosition head)
{
	return head->next->directory;
}

int NameCheck(Position first, char name[])
{
	Position temp = first;

	while (temp != NULL)
	{
		if (strcmp(name, temp->name) == 0)
			return 1;
		temp = temp->sibling;
	}

	return 0;
}
