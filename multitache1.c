#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
// Fonctions correspondant au corps d’un thread (tache)
void* etoile(void* inutilise);
void* diese(void* inutilise);
// Remarque : le prototype d’une tâche doit être : void *(*start_routine)(void *)

int main(void)
{
	pthread_t thrEtoile, thrDiese;	// les ID des de 2 threads
	setbuf(stdout, NULL);			// pas de tampon sur stdout
	printf("Je vais creer et lancer 2 threads\n");
	pthread_create(&thrEtoile, NULL, etoile, NULL);
	pthread_create(&thrDiese, NULL, diese, NULL);
	// printf("J’attends la fin des 2 threads\n");
	pthread_join(thrEtoile, NULL);
	pthread_join(thrDiese, NULL);
	printf("\nLes 2 threads se sont termines\n");
	printf("Fin du thread principal\n");
	pthread_exit(NULL);
	return EXIT_SUCCESS;
}
void* etoile(void* inutilise)
{
	int	 i;
	char c1 = '*';

	for (i = 1; i <= 200; i++)
	{
		write(1, &c1, 1);  // écrit un caractère sur stdout (descripteur 1)
	}
	return NULL;
}
void* diese(void* inutilise)
{
	int i;

	char c1 = '#';
	for (i = 1; i <= 200; i++)
	{
		write(1, &c1, 1);
	}
	return NULL;
}
