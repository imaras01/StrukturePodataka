#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE 1024

struct _stackElement;
typedef struct _stackElement* Position;
typedef struct _stackElement
{
    double number;
    Position next;
}StackElement;

int Push(Position head, double number);
int Pop(double* operand, Position head);
int InsertAfter(Position head, Position newElement);
Position CreateElement(double number);
int ReadFile(Position head, char* fileName);
int ReadPostfix(Position head, char buffer[]);
int DeleteAfter(Position head);
int DeleteAll(Position head);
int PerformOperation(Position head, char operator);
int CheckStack(Position head);

int main()
{
    StackElement head={.number=0, .next=NULL};
    Position p=&head;
    int status=0;

    status=ReadFile(p, "postfix.txt");
    if(status != 0)
        return -1;
    else
    {
        printf("Postfix result is %lf", p->next->number);
        DeleteAfter(p);
    }

    return 0;
}

Position CreateElement(double number)
{
    Position newElement=NULL;
    newElement=(Position)malloc(sizeof(StackElement));
    if(!newElement)
    {
        printf("Couldn't allocate memory");
        return NULL;
    }

    newElement->number=number;
    newElement->next=NULL;

    return newElement;
}

int InsertAfter(Position head, Position p)
{
    p->next=head->next;
    head->next=p;

    return 0;
}

int ReadFile(Position head, char* fileName)
{
    FILE* fp=NULL;
    char buffer[MAX_LINE]={0};
    int status=0;

    fp=fopen(fileName, "r");
    if(!fp)
    {
        printf("Cannot open the file!");
        return -1;
    }
    fgets(buffer, MAX_LINE, fp);

    status=ReadPostfix(head, buffer);
    if(status!=0)
        return -1;
    
    fclose(fp);

    return 0;
}

int ReadPostfix(Position head, char buffer[])
{
    char* currentBuffer=buffer;
    int NumOfBytes=0;
    double number=0;
    int status=0;
    char operator=0;

    while(strlen(currentBuffer)>0)
    {
        status=sscanf(currentBuffer, "%lf %n", &number, &NumOfBytes);
        if(status==1)
        {
            status = Push(head, number);
            if(status!=0)
                DeleteAll(head);
        }
        else
        {
            sscanf(currentBuffer, " %c %n", &operator, &NumOfBytes);
            status=PerformOperation(head, operator);
            if(status!=0)
                DeleteAll(head);
        }

        currentBuffer+=NumOfBytes;
    }

    if(CheckStack(head) != 1)
    {
        printf("Postfix error!");
        return -1;
    }

    return 0;
}

int Push(Position head, double number)
{
    Position newElement=NULL;

    newElement=CreateElement(number);
    if(!newElement)
    {
        return -1;
    }

    InsertAfter(head, newElement);

    return 0;
}

int DeleteAfter(Position head)
{
    Position temp=head->next;

    head->next=temp->next;
    free(temp);

    return 0;
}

int DeleteAll(Position head)
{
    while(head->next!=NULL)
    {
        DeleteAfter(head);
    }

    return 0;
}

int PerformOperation(Position head, char operator)
{
    double operand1=0;
    double operand2=0;
    int status=0;

    status=Pop(&operand2, head);
    if(status!=0)
        return -1;

    status=Pop(&operand1, head);
    if(status!=0)
        return -1;

    switch (operator)
    {
    case '+':
        status=Push(head, operand1+operand2);
        if(status!=0)
            return -1;
        break;

    case '-':
        status=Push(head, operand1-operand2);
        if(status!=0)
            return -1;
        break;
    
    case '*':
        status=Push(head, operand1*operand2);
        if(status!=0)
            return -1;
        break;
    
    case '/':
        if(operand2==0)
        {
            printf("Cannot perform this operation.");
            return -1;
        }
        else    
            status=Push(head, operand1/operand2);
            if(status!=0)
                return -1;
        break;
    
    default:
        break;
    }

    return 0;
}

int Pop(double* operand, Position head)
{
    if(head->next==NULL)
    {
        printf("Postfix error!");
        return -1;
    }
    *operand = head->next->number;
    DeleteAfter(head);

    return 0;
}

int CheckStack(Position head)
{
    int counter=0;

    while(head->next!=NULL)
    {
        counter++;
        head=head->next;
    }

    return counter;
}