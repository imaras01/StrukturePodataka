#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#define MAX_LINE 1024

struct _city;
typedef struct _city* ListPosition;

struct _country;
typedef struct _country* TreePosition;

typedef struct _country
{
	char name[80];
	TreePosition right;
	TreePosition left;
	ListPosition head;

}Country;

typedef struct _city
{
	int population;
	char name[80];
	ListPosition next;
}City;

TreePosition ReadFile(TreePosition root, char* filename);
TreePosition CreateNewTreeElement(char name[]);
TreePosition InsertInTree(TreePosition root, TreePosition NewElement, char* filename);
ListPosition FillList(ListPosition head, char* filename);
ListPosition CreateNewListElement(char name[], int population);
ListPosition InsertInList(ListPosition head, ListPosition NewElement);


#endif