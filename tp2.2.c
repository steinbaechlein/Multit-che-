#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
// Chaque thread (tache) va faire ses COUNT boucles
#define COUNT 50
// Fonctions correspondant au corps d’un thread (tache)
void* etoile(void* inutilise);
void* diese(void* inutilise);
int	  main(void)
{
	pthread_t thread1, thread2;
	printf("Le thread1 (etoile) doit faire au moins 1/3 de son travail (%d de ses %d boucles)\
n",
		   (int) (COUNT / 3),
		   COUNT);
	printf(
		"Le thread2 (diese) attendra que le thread1 (etoile) ait fait au moins 1/3 de son travail avant de démarrer le sien\n");
	pthread_create(&thread1, NULL, etoile, NULL);
	pthread_create(&thread2, NULL, diese, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("Fin du thread principal\n");
	return EXIT_SUCCESS;
}
void* etoile(void* inutilise)
{
	char c1	   = '*';
	int	 count = 0;
	while (1)
	{
		write(1, &c1, 1);  // écrit une ’*’ sur stdout (descripteur 1)
		count++;
		if (count == (int) (COUNT / 3))
		{
			printf("Le thread1 a fait au moins 1/3 (%d) de ses %d boucles\n", count, COUNT);
		}
		if (count >= COUNT)
		{
			return (NULL);
		}
		pthread_yield();
	}
	return NULL;
}
void* diese(void* inutilise)
{
	char c1	   = '#';
	int	 count = 0;
	while (1)
	{
		write(1, &c1, 1);  // écrit un ’#’ sur stdout (descripteur 1)
		count++;
		if (count >= COUNT)
		{
			return (NULL);
		}
		pthread_yield();
	}
	return NULL;
}