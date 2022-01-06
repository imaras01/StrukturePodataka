#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include "binary_tree.h"

int Menu(Position root)
{
	Position NewElement = NULL;
	Position status = NULL;
	int choice = 0;
	int number = 0;

	do
	{
		choice = Choice(choice);

		switch (choice)
		{
		case 1:
			printf("Choose a number you want to insert:");
			scanf("%d", &number);

			NewElement = CreateNewElement(number);
			if (!NewElement)
				return -1;

			root=Insert(root, NewElement);
			break;

		case 2:
			PrintInorder(root);
			puts("");
			break;
		
		case 3:
			PrintPreorder(root);
			puts("");
			break;

		case 4:
			PrintPostorder(root);
			puts("");
			break;

		case 5:
			printf("What element do you want to find: ");
			scanf("%d", &number);

			status = FindElement(root, number);
			if (!status)
				printf("Your element doesn't exist.\n");
			else
				printf("Your element exists and can be its adress is %p.\n", status);

			break;

		case 6:
			printf("What element do you want to delete:");
			scanf("%d", &number);
			root = DeleteElement(root, number);
			break;

		default:
			break;
		}
	} while (choice != 7);
}

Position CreateNewElement(int number)
{
	Position NewElement = (Position)malloc(sizeof(TreeElement));
	if (!NewElement)
	{
		printf("Couldn't allocate memory!");
		return NULL;
	}

	NewElement->number = number;
	NewElement->left = NULL;
	NewElement->right = NULL;

	return NewElement;
}

Position Insert(Position root, Position NewElement)
{
	if (root == NULL)
		root = NewElement;

	else if (NewElement->number < root->number)
		root->left = Insert(root->left, NewElement);

	else if (NewElement->number > root->number)
		root->right = Insert(root->right, NewElement);

	else
		printf("That number already exists.\n");

	return root;
}

int Choice(int choice)
{
	printf("Choose:"
		"\n\t1 to insert a new number in the binary tree"
		"\n\t2 to print all binary tree elements (inorder)"
		"\n\t3 to print all binary tree elements (preorder)"
		"\n\t4 to print all binary tree elements (postorder)"
		"\n\t5 to find a binary tree element"
		"\n\t6 to delete a binary tree element"
		"\n\t7 to exit program\n");

	scanf("%d", &choice);

	return choice;
}

int PrintInorder(Position root)
{
	if (root)
	{
		PrintInorder(root->left);
		printf("%d ", root->number);
		PrintInorder(root->right);
	}
	return 0;
}

int PrintPreorder(Position root)
{
	if (root)
	{
		printf("%d ", root->number);
		PrintPreorder(root->left);
		PrintPreorder(root->right);
	}
	return 0;
}

int PrintPostorder(Position root)
{
	if (root)
	{
		PrintPostorder(root->left);
		PrintPostorder(root->right);
		printf("%d ", root->number);
	}

	return 0;
}

Position DeleteElement(Position root, int number)
{
	Position temp = NULL;

	if (root == NULL)
		return root;

	else if (number < root->number)
		root->left = DeleteElement(root->left, number);

	else if (number > root->number)
		root->right = DeleteElement(root->right, number);

	else
	{
		if (root->left && root->right)
		{
			temp = FindMin(root->right);
			root->number = temp->number;
			root->right = DeleteElement(root->right, root->number);
		}

		else
		{
			temp = root;

			if (root->left == NULL)
				root = root->right;

			else
				root = root->left;

			free(temp);
		}
	}

	return root;
}


Position FindElement(Position root, int number)
{
	if (root == NULL)
		return NULL;

	else if (number < root->number)
		return FindElement(root->left, number);

	else if (number > root->number)
		return FindElement(root->right, number);

	else
		return root;
}

Position FindMin(Position root)
{
	if (root == NULL)
		return NULL;

	else if (root->left == NULL)
		return root;

	else
		return FindMin(root->left);
}

