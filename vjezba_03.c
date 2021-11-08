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

int Menu(Position head);
int PersonInformation(Position head, int choice);
int PersonInformationInput(char name[], char surname[], int* birthYear);
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
    int choice=0;

    p=&head;

    do
    {
        choice = Menu(p);

    }while(choice!=0);

    return 0;

}

int Menu(Position head)
{
    int a=0;
    
    printf("Odaberite:"
            "\n\t1 za umetanje elementa na pocetak liste"
            "\n\t2 za umetanje elementa na kraj lise"
            "\n\t3 za brisanje zeljenog clana"
            "\n\t4 za umetanje ispred zeljenog clana"
            "\n\t5 za umetanje iza zeljenog clana"
            "\n\t6 ako zelite vidjeti svoju listu"
            "\n\t7 ako zelite sortirati listu"
            "\n\t8 ako zelite upisati listu u datoteku"
            "\n\t9 ako zelite procitati listu iz datoteke"
            "\n\t0 za izlazak iz programa\n");
    scanf("%d", &a);

    if(a<0 || a>9)
    {
        printf("Unijeli ste nepostojecu opciju. Molimo ponovite unos.\n");
        return -1;
    }

    a = PersonInformation(head, a);

    return a;
}

int PersonInformation(Position head, int choice)
{
    int birthYear=0;
    char name[MAX_SIZE]={0}, surname[MAX_SIZE]={0}, reference_surname[MAX_SIZE]={0};

    if(choice==0)
        return 0;

    switch (choice)
    {
    case 1:
        PersonInformationInput(name, surname, &birthYear);
        PrependList(head, name, surname, birthYear);
        return 1;
    case 2:
        PersonInformationInput(name, surname, &birthYear);
        AppendList(head, name, surname, birthYear);
        return 2;
    case 3:
        printf("Unesi prezime osobe koju zelis izbrisati:");
        scanf(" %s", surname);
        Delete(head, surname);
        return 3;
    case 4:
        printf("Unesi prezime osobe ispred koje zelis unijeti element:");
        scanf(" %s", reference_surname);
        PersonInformationInput(name, surname, &birthYear);
        AddBefore(head, reference_surname, name, surname, birthYear);
        return 4;
    case 5:
        printf("Unesi prezime osobe iza koje zelis unijeti element:");
        scanf(" %s", reference_surname);
        PersonInformationInput(name, surname, &birthYear);
        AddAfter(head, reference_surname, name, surname, birthYear);
        return 5;
    case 6:
        PrintList(head->next);
        return 6;
    case 7:
        Sort(head);
        return 7;
    case 8:
        WriteFile(head->next, "linked_list.txt");
        return 8;
    case 9:
        ReadFile("linked_list.txt");
        return 9;
    default:
        break;
    }
}

int PersonInformationInput(char name[], char surname[], int* birthYear)
{
    printf("Unesi ime osobe: ");
    scanf(" %s", name);
    printf("Unesi prezime osobe: ");
    scanf(" %s", surname);        
    printf("Unesi godinu rodenja osobe: ");
    scanf(" %d", birthYear);
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

    while(fgets(line, MAX_LINE, file))
    {
        sscanf(line," %s %s %d", name, surname, &birthYear);
        printf("%s %s %d\n", name, surname, birthYear);
    }

    fclose(file);
    return 0;
}