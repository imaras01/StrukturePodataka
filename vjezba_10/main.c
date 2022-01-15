#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "linked_list.h"

int main()
{
	Country head = {.name = {0}, .next = NULL };
	ListPosition searched_country = NULL;
	int status = 0;
	int reference_number = 0;
	char search[80] = { 0 };

	status = ReadFile(&head, "drzave.txt");
	if (status)
		return -1;

	printf("Country search(enter 'exit' to exit):\n");

	do
	{
		printf("Which country do you want to search:");
		scanf(" %s", search);

		if (strcmp(search, "exit") == 0)
			break;

		searched_country = SearchCountry(&head, search);
		if (!searched_country)
			continue;

		printf("We will print all the cities in %s with population higher than:", searched_country->name);
		scanf(" %d", &reference_number);

		SearchTree(searched_country->root, reference_number);

	} while (1);

	return 0;
}