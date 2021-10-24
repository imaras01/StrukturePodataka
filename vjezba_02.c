#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 50

struct _person;
typedef struct _person* Position;
typedef struct _person
{
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int birthYear;
    Position next;
}Person;

int PrependList(Position head, char name[], char surname[], int birthYear);
int InsertAfter(Position p, Position Newperson);
int PrintList(Position first);
int AppendList(Position head, char name[], char surname[], int birthYear);
Position CreatePerson(char name[], char surname[], int birthYear);
Position FindLast(Position head);
Position FindBySurname(Position first, char surname[]);
int Delete(Position head, char surname[]);
Position FindBefore(Position head, Position p);

int main()
{
    Person head={.name={0}, .surname={0}, .birthYear=0, .next=NULL};
    Position p=NULL;

    p=&head;

    PrependList(p, "Ivan", "Marasovic", 2001);
    PrintList(p->next);
    puts("");
    PrependList(p, "Mate", "Matic", 2000);
    AppendList(p, "Jure", "Juric", 2006);
    PrintList(p->next);
    puts("");
    Delete(p, "Marasovic");
    PrintList(p->next);


    return 0;

}

int PrependList(Position head, char name[], char surname[], int birthYear)
{
    Position newPerson=NULL;

    newPerson=CreatePerson(name, surname, birthYear);
    if(newPerson==NULL)
        return -1;

    InsertAfter(head, newPerson);
    return 0;
}

int PrintList(Position first)
{
    Position temp=first;

    while(temp!=NULL)
    {
        printf("Name: %s, Surname: %s, Birth year: %d\n", temp->name, temp->surname, temp->birthYear);
        temp=temp->next;
    }
    return 0;
}

Position CreatePerson(char name[], char surname[], int birthYear)
{
    Position newPerson=NULL;
    newPerson=(Position)malloc(sizeof(Person));

    if(newPerson==NULL)
    {
        perror("Can't allocate memory!\n");
        return NULL;
    }

    strcpy(newPerson->name, name);
    strcpy(newPerson->surname, surname);
    newPerson->birthYear=birthYear;
    newPerson->next=NULL;

    return newPerson;
}

int InsertAfter(Position p, Position newPerson)
{
    newPerson->next=p->next;
    p->next=newPerson;

    return 0;
}

int AppendList(Position head, char name[], char surname[], int birthYear)
{
    Position newPerson=NULL, last=NULL;
    newPerson=CreatePerson(name, surname, birthYear);

    if(newPerson==NULL)
        return -1;

    last=FindLast(head);

    InsertAfter(last, newPerson);

    return 0;
}

Position FindLast(Position head)
{
    Position temp=head;

    while(temp->next!=NULL)
    {
        temp=temp->next;
    }

    return temp;
}

Position FindBySurname(Position first, char surname[])
{
    Position temp=first;

    while(temp->next)
    {
        if(strcmp(temp->surname, surname)==0)
            return temp;
        temp=temp->next;
    }
    return NULL;
}

int Delete(Position head, char surname[])
{
    Position temp=NULL, before=NULL;
    temp=FindBySurname(head->next, surname);
    before=FindBefore(head, temp);

    before->next=temp->next;
    free(temp);

    return 0;
}

Position FindBefore(Position head, Position p)
{
    Position before=head;
    while(before->next!=NULL)
    {
        if(before->next == p)
            return before;
        before=before->next;
    }
    return NULL;
}