#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024

typedef struct _studenti
{
    char ime[80];
    char prezime[80];
    float bodovi;
}student;

int BrojRedaka(char *nazivDatoteke);
student *AlocirajProstor(char *nazivDatoteke, int broj_studenata); 

int main()
{
    int broj_studenata=0,i=0;
    int max_bodovi=50;
    student *studenti=NULL;

    broj_studenata=BrojRedaka("rezultati.txt");
    studenti=AlocirajProstor("rezultati.txt", broj_studenata);

    for(i=0; i<broj_studenata; i++)
    {
        printf("Student %s %s ima %f bodova sto je %f posto.\n", studenti[i].ime, studenti[i].prezime,studenti[i].bodovi, studenti[i].bodovi/max_bodovi*100);
    }    

    return 0;
}

int BrojRedaka(char *nazivDatoteke)
{
    FILE *datoteka=NULL;
    int brojac=0;
    char buffer[MAX_LINE]={0};

    datoteka=fopen(nazivDatoteke, "r");

    if(!datoteka)
    {
        printf("Greska!");
        return -1;
    }
    while(!feof(datoteka))
    {
        fgets(buffer, MAX_LINE, datoteka);
        brojac++;
    }

    fclose(datoteka);

    return brojac;
}

student *AlocirajProstor(char *nazivDatoteke, int broj_studenata)
{
    int brojac=0;
    student *studenti=NULL;
    FILE *datoteka=NULL;

    studenti=(student*)malloc(broj_studenata*sizeof(student));
    datoteka=fopen(nazivDatoteke, "r");

    if(!datoteka)
    {
        printf("Greška prilikom alociranja!");
        free(studenti);
        return NULL;
    }
    while(!feof(datoteka))
    {
        fscanf(datoteka, " %s %s %f ", studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].bodovi);
        brojac++;
    }
    fclose(datoteka);

    return studenti;
}