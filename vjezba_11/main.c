#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "hash_table.h"

int main()
{
	Country hash_table[11] = { 0 };
	int status = 0;

	status = ReadFile(hash_table, "drzave.txt");


	return 0;
}