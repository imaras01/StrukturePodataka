#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE 1024
#define MAX_SIZE 80

struct _element;
typedef struct _element* Position;
typedef struct _element
{
    int coefficient;
    int exponent;
    Position next;
}Element;

int ReadPoly(Position head1, Position head2);
int StringToList(Position head, char buffer[]);
int InsertInList(Position head, int coefficient, int exponent);
Position CreateElement(int coefficient, int exponent);
int PrintPoly(Position p);
int DeleteAfter(Position p);
int AddPoly(Position p1, Position p2, Position sum);
int PolyProduct(Position p1, Position p2, Position product);
int FreeMemory(Position p);

int main()
{
    Element head1={.coefficient=0, .exponent=0, .next=NULL};
    Element head2={.coefficient=0, .exponent=0, .next=NULL};
    Element headSum={.coefficient=0, .exponent=0, .next=NULL};
    Element headProduct={.coefficient=0, .exponent=0, .next=NULL};
    
    Position p1=&head1, p2=&head2, pSum=&headSum, pProduct=&headProduct;

    ReadPoly(p1, p2);

    printf("P1 =");
    PrintPoly(p1->next);
    puts("");

    printf("P2 =");
    PrintPoly(p2->next);
    puts("");

    AddPoly(p1->next, p2->next, pSum);
    printf("P1 + P2 =");
    PrintPoly(pSum->next);
    puts("");

    PolyProduct(p1->next, p2->next, pProduct);
    printf("P1*P2 =");
    PrintPoly(pProduct->next);
    puts("");

    FreeMemory(p1);
    FreeMemory(p2);
    FreeMemory(pSum);
    FreeMemory(pProduct);

    return 0;
}

int ReadPoly(Position head1, Position head2)
{
    FILE* fp=NULL;
    char fileName[MAX_SIZE]={0};
    char buffer[MAX_LINE]={0};
    int status=0;

    printf("Please enter the name of the file: ");
    scanf(" %s", fileName);

    fp=fopen(fileName, "r");
    if(!fp)
    {
        perror("Can't open the file!\n");
        return -1;
    }

    fgets(buffer, MAX_LINE, fp);
    status=StringToList(head1, buffer);
    if(status != 0)
        return 1;
    
    fgets(buffer, MAX_LINE, fp);
    status=StringToList(head2, buffer);
    if(status != 0)
        return 1;
    
    return 0;
}

int StringToList(Position head, char buffer[])
{
    char* currentBuffer=buffer;
    int coefficient=0;
    int exponent=0;
    int NumOfBytes=0;
    int status=0;

    while(strlen(currentBuffer)>0)
    {
        status=sscanf(currentBuffer, " %d %d %n", &coefficient, &exponent, &NumOfBytes);
        if(status!=2)
        {
            printf("There has been an error reading the file.");
            return 1;
        }

        status=InsertInList(head, coefficient, exponent);
        if(status != 0)
        {
            return 1;
        }

        currentBuffer+=NumOfBytes;
    }
    return 0;
}

int InsertInList(Position head, int coefficient, int exponent)
{
    Position NewElement=NULL;
    Position P=head;

    NewElement=CreateElement(coefficient, exponent);
    if(!NewElement)
    {
        perror("Can't allocate memory.");
        return -1;
    }

    while(P->next!=NULL && NewElement->exponent > P->next->exponent)
    {
        P=P->next;
    }
    if(P->next!=NULL && NewElement->exponent == P->next->exponent)
    {
        P->next->coefficient += NewElement->coefficient;
        if(P->next->coefficient == 0)
            DeleteAfter(P);
            
        free(NewElement);
    }
    else
    {
        NewElement->next=P->next;
        P->next=NewElement;
    }

    return 0;
}

Position CreateElement(int coefficient, int exponent)
{
    Position NewElement=NULL;

    NewElement=(Position)malloc(sizeof(Element));
    if(!NewElement)
        return NULL;
    
    NewElement->coefficient=coefficient;
    NewElement->exponent=exponent;
    NewElement->next=NULL;

    return NewElement;
}

int DeleteAfter(Position p)
{
    Position temp=p->next;

    p->next=temp->next;

    free(temp);
    return 0;
}

int PrintPoly(Position p)
{
    while(p!=NULL)
    {
        if(p->coefficient<0)
        {
            printf(" %dx**%d ", p->coefficient, p->exponent);
            p=p->next;
        }
        else
        {
            printf(" + %dx**%d ", p->coefficient, p->exponent);
            p=p->next;
        }
    }
    return 0;
}

int AddPoly(Position p1, Position p2, Position sum)
{
    int coefficientSum=0;
    Position temp=NULL;

    while(p1!=NULL && p2!=NULL)
    {
        if(p1->exponent == p2->exponent)
        {
            coefficientSum=p1->coefficient + p2->coefficient;
            if(coefficientSum==0)
            {
                p1=p1->next;
                p2=p2->next;
                continue;
            }
            else
            {
                InsertInList(sum, coefficientSum, p1->exponent);
                p1=p1->next;
                p2=p2->next;
            }
        }
        else if(p1->exponent < p2->exponent)
        {
            InsertInList(sum, p1->coefficient, p1->exponent);
            p1=p1->next;
        }
        else
        {
            InsertInList(sum, p2->coefficient, p2->exponent);
            p2=p2->next;
        }

    }

    if(p1!=NULL)
        temp=p1;

    if(p2!=NULL)
        temp=p2;

    while(temp!=NULL)
    {   
        InsertInList(sum, temp->coefficient, temp->exponent);
        temp=temp->next;
    }

    return 0;
}

int PolyProduct(Position p1, Position p2, Position product)
{
    Position temp=p2;
    while(p1!=NULL)
    {
        while(temp!=NULL)
        {
            InsertInList(product, p1->coefficient * temp->coefficient, p1->exponent + temp->exponent);
            temp=temp->next;
        }
        temp=p2;
        p1=p1->next;
    }

    return 0;
}

int FreeMemory(Position p)
{
    Position temp=p;

    while(temp->next!=NULL)
    {
        DeleteAfter(temp);
    }

    return 0;
}