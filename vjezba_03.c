#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 50
#define MAX_LINE 1024

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
int AddAfter(Position first, char reference_surname[], char name[], char surname[], int birthYear);
int AddBefore(Position head, char reference_surname[], char name[], char surname[], int birthYear);
int Sort(Position head);
int WriteFile(Position first, char *fileName);
int ReadFile(char *fileName);

int main()
{
    Person head={.name={0}, .surname={0}, .birthYear=0, .next=NULL};
    Position p=NULL;
    int counter;

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
    puts("");

    AddAfter(p->next, "Juric", "Ivan", "Marasovic", 2001);
    PrintList(p->next);
    puts("");

    AddBefore(p, "Marasovic", "Ante", "Antic", 1999);
    PrintList(p->next);
    puts("");

    Sort(p);
    PrintList(p->next);
    puts("");

    WriteFile(p->next, "linked_list.txt");
    ReadFile("linked_list.txt");

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

    while(temp)
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

int AddAfter(Position first, char reference_surname[], char name[], char surname[], int birthYear)
{
    Position newPerson=NULL, temp=NULL;

    newPerson=CreatePerson(name, surname, birthYear);
    if(newPerson==NULL)
        return -1;
    
    temp=FindBySurname(first, reference_surname);
    if(temp==NULL)
    {
        printf("Osoba koju ste unijeli ne postoji.");
        return 1;
    }
    InsertAfter(temp, newPerson);

    return 0;
}

int AddBefore(Position head, char reference_surname[], char name[], char surname[], int birthYear)
{
    Position newPerson=NULL, temp=NULL, before=NULL;

    newPerson=CreatePerson(name, surname, birthYear);
    if(newPerson==NULL)
        return -1;
    
    temp=FindBySurname(head->next, reference_surname);
    if(temp==NULL)
    {
        printf("Osoba koju ste unijeli ne postoji.");
        return 1;
    }

    before=FindBefore(head, temp);
    InsertAfter(before, newPerson);

    return 0;
}

int Sort(Position head)
{
    Position j, prev_j, temp, end=NULL;

    while(head->next !=end)
    {
        prev_j=head;
        j=head->next;
        while(j->next!=end)
        {
            if(strcmp(j->surname, j->next->surname)>0)
            {
                temp=j->next;
                prev_j->next=temp;
                j->next=temp->next;
                temp->next=j;
                j=temp;
            }
            prev_j=j;
            j=j->next;
        }
        end=j;
    }

    return 0;
}

int WriteFile(Position first, char *fileName)
{
    FILE *file=NULL;
    Position temp=first;

    file=fopen(fileName, "w");
    if(!file)
    {
        printf("Error!");
        return -1;
    }

    while(temp!=NULL)
    {
        fprintf(file, "%s %s %d.\n", temp->name, temp->surname, temp->birthYear);
        temp=temp->next;
    }

    fclose(file);
    return 0;
}

int ReadFile(char *fileName)
{
    FILE *file=NULL;
    char line[MAX_LINE]={0};
    int birthYear=0;
    char name[MAX_SIZE]={0}, surname[MAX_SIZE]={0};

    file=fopen(fileName, "r");
    if(!file)
    {
        printf("Error!");
        return -1;
    }

    while(!feof(file))
    {
        fgets(line, MAX_LINE, file);
        sscanf(line," %s %s %d", name, surname, &birthYear);
        printf("%s %s %d\n", name, surname, birthYear);
    }

    fclose(file);
    return 0;
}