#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "hash_table.h"

int main()
{
	Country hash_table[11] = { 0 };
	ListPosition searched_country = NULL;
	char search[80] = { 0 };
	int status = 0;
	int key = 0;
	int reference_number = 0;

	status = ReadFile(hash_table, "drzave.txt");
	if (status)
		return -1;

	printf("Country search(enter 'exit' to exit):\n");

	do
	{
		printf("Which country do you want to search:");
		scanf(" %s", search);

		if (strcmp(search, "exit") == 0)
			break;

		key = CalculateHash(search);

		searched_country = SearchCountry(&hash_table[key], search);
		if (!searched_country)
			continue;

		printf("We will print all the cities in %s with population higher than:", searched_country->name);
		scanf(" %d", &reference_number);

		SearchTree(searched_country->root, reference_number);

	} while (1);

	return 0;
}