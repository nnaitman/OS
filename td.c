/* Pour les constantes EXIT_SUCCESS et EXIT_FAILURE */
#include <stdlib.h>
/* Pour fprintf() */
#include <stdio.h>
/* Pour fork() */
#include <unistd.h>
/* Pour perror() et errno */
#include <errno.h>
/* Pour le type pid_t */
#include <sys/types.h>

#define NAMESIZE 30

typedef struct
{
	char name[1+NAMESIZE];
	int number;
} fiche;

int compareOnNumbers(const void *p1, const void *p2){
	fiche *e1= (fiche*)p1;
	fiche *e2= (fiche*)p2;
	return e1->number- e2-> number;
}

int compareOnNames(const void *p1, const void *p2){
	fiche *e1= (fiche*)p1;
	fiche *e2= (fiche*)p2;
	return strcmp(e1->name, e2-> name);
}

void display(fiche *d, int nb){
	int i;
	for (int i = 0; i < nb; ++i)
	{
		printf("\t %s - %d \n", d[i].name , d[i].number);
	}
}

int main (void){
	fiche directory[]= {
		{"Spirou",1},
		{"massi",4},
		{"nadir",3},
		{"mestapha",8},
		{"amirouche", 6},
	};

	int nb= sizeof(directory)/sizeof(fiche);
	int val = 0;
	pid_t pid;

	puts("fiches sorted by name: ");
	qsort(directory,nb,sizeof(fiche), compareOnNames);
	display(directory,nb);

	switch (pid = fork()){
        case -1:
            perror ("");
            exit (1);

        case 0;
            /*fils*/
            val = getppid();
            printf("\n fils: pid(%d), son père: pid (%d)\n", getpid(), getppid());
            printf("Valeur (et adresse) de val dans fils: %d(%p)\n", val, &val);
            puts("fin du fils"); exit(0);

        default:
            /*père*/
            while (waitpid(0,0,0)< 0);
            printf ("\n père: pid(%d), son père: pid(%d)\n", getpid(), getppid());
            printf ("Valeur (et adresse) du val dans père: %d(%p)\n", val, &val);
            put ("fin du père");
    }

    return 0;



}
