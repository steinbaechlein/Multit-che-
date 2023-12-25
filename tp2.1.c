#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
pthread_mutex_t globale_lock  = PTHREAD_MUTEX_INITIALIZER;
int				value_globale = 1;	// la variable globale partagée
// Chaque thread (tache) va faire ses COUNT boucles
#define COUNT 25
// Fonctions correspondant au corps d’un thread (tache)
void* increment(void* inutilise);
void* decrement(void* inutilise);
int	  main(void)
{
	pthread_t thread1, thread2;
	printf("Exemple avec le mutex\n");
	printf("Avant les threads : value = %d\n", value_globale);
	pthread_create(&thread1, NULL, increment, NULL);
	pthread_create(&thread2, NULL, decrement, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("Apres les threads : value = %d\n", value_globale);
	printf("Fin du thread principal\n");
	return EXIT_SUCCESS;
}
void* increment(void* inutilise)
{
	int value;
	int count = 0;
	while (1)
	{
		pthread_mutex_lock(&globale_lock);
		value = value_globale;
		printf("Thread1 : load value (value = %d) ", value);
		value += 1;
		printf("Thread1 : increment value (value = %d) ", value);
		value_globale = value;
		printf("Thread1 : store value (value = %d) ", value_globale);
		pthread_mutex_unlock(&globale_lock);
		count++;
		usleep(100000);
		if (count >= COUNT)
		{
			printf("Le thread1 a fait ses %d boucles\n", count);
			return (NULL);
		}
	}
	return NULL;
}
void* decrement(void* inutilise)
{
	int value;
	int count = 0;
	while (1)
	{
		pthread_mutex_lock(&globale_lock);
		value = value_globale;
		printf("Thread2 : load value (value = %d) ", value);
		value -= 1;
		printf("Thread2 : decrement value (value = %d) ", value);
		value_globale = value;
		printf("Thread2 : store value (value = %d) ", value_globale);
		pthread_mutex_unlock(&globale_lock);
		count++;
		usleep(100000);
		if (count >= COUNT)
		{
			printf("Le thread2 a fait ses %d boucles\n", count);
			return (NULL);
		}
	}
	return NULL;
}
