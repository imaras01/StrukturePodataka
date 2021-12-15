#ifndef DIRECTORIES_H
#define DIRECTORIES_H
#define MAX_NAME_SIZE 120

struct _directory;
typedef struct _directory* Position;

typedef struct _directory {
	char name[MAX_NAME_SIZE];
	Position sibling;
	Position child;
}Directory;

struct _stack;
typedef  struct _stack* StackPosition;

typedef struct _stack
{
	Position directory;
	StackPosition next;
}Stack;

int Menu (Position root, StackPosition head);
int MakeDirectory (Position current_directory);
Position CreateNewDirectory (char name[]);
Position FindLastDirectory (Position first);
int InsertAfter(Position last_directory, Position new_directory);
Position ChangeDirectory(Position current_directory);
int DeleteAfter(StackPosition head);
int Push(StackPosition head, Position current_directory);
Position Pop(StackPosition head);
int StackInsert(StackPosition head, StackPosition new_element);
int PrintDirectories(Position first);
int NameCheck(Position first, char name[]);

#endif 
