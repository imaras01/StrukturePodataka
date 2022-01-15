#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define MAX_LINE 1024

struct _country;
typedef struct _country* ListPosition;

struct _city;
typedef struct _city* TreePosition;

typedef struct _country
{
	char name[80];
	ListPosition next;
	TreePosition root;

}Country;

typedef struct _city
{
	int population;
	char name[80];
	TreePosition left;
	TreePosition right;
}City;

int ReadFile(ListPosition head, char* filename);
ListPosition CreateNewListElement(ListPosition head, char name[]);
int InsertInList(ListPosition head, ListPosition NewElement);
int FillTrees(ListPosition NewElement, char* filename);
TreePosition CreateNewTreeElement(char name[], int population);
TreePosition InsertInTree(TreePosition root, TreePosition NewElement);
ListPosition SearchCountry(ListPosition head, char search[]);
int SearchTree(TreePosition root, int reference_number);





#endif

