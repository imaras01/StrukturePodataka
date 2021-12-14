#include <stdio.h>
#include <stdlib.h>
#include <string.h>	
#include "directories.h"


int main()
{
	Directory root = { .name = "C:", .child = NULL, .sibling = NULL };
	Stack head = { .directory = NULL, .next = NULL };
	int status = 0;

	Push(&head, &root);
	
	do
	{
		status = Menu(&root, &head);

	} while (status >= 0);

	return status;
}
