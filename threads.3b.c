// threads.3b.c
// Mise en oeuvre des variables conditions
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t condition_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t	condition_var
	= PTHREAD_COND_INITIALIZER;	 // Chaquethread(tache)vafairesesCOUNTboucles
#define COUNT 50
int	  count = 0;  // Fonctionscorrespondantaucorpsd’unthread(tache)
void* etoile(void* inutilise);
void* diese(void* inutilise);
int	  main(void)
{
	pthread_t thread1, thread2;
	printf(
		"Le thread1 (etoile) doit faire au moins 1/3 du travail( %d des %d boucles) et il le signalera au thread2 (diese)\n",
		(int) (COUNT / 3),
		COUNT);
	printf(
		"Le thread2( diese) attendra que le thread1 (etoile) ait fait au moins 1/3 du travail avant de démarrer le sien\n");
	write(1, "[", 1);  // écrituncaractèresurstdout(descripteur1)
	pthread_create(&thread1, NULL, etoile, NULL);
	pthread_create(&thread2, NULL, diese, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	write(1, "]", 1);  // écrituncaractèresurstdout(descripteur1)
	printf("\nFinduthreadprincipal\n");
	pthread_exit(NULL);
	return EXIT_SUCCESS;
}

void* etoile(void* inutilise)
{
	char c1 = '*';
	while (1)
	{
		pthread_mutex_lock(&condition_lock);
		write(1, &c1, 1);  // écrit un caractère sur stdout(descripteur1)
		count++;
		if (count == (int) (COUNT / 3))
		{
			write(1, "|", 1);  // écrit un caractère sur stdout(descripteur1)
			pthread_cond_broadcast(&condition_var);
		}
		pthread_mutex_unlock(&condition_lock);
		if (count >= COUNT)
		{
			return (NULL);
		}
		sched_yield();
	}
	return NULL;
}

void* diese(void* inutilise)
{
	char c1 = '#';
	// intcount=0;
	printf("Thread2 : attendra que thread1 ait fait une partie de son travail");
	while (1)
	{
		pthread_mutex_lock(&condition_lock);
		while (count < (int) (COUNT / 3))
		{
			pthread_cond_wait(&condition_var, &condition_lock);
		}
		write(1, &c1, 1);  // écrituncaractèresurstdout(descripteur1)
		count++;
		pthread_mutex_unlock(&condition_lock);
		if (count >= COUNT)
		{
			return (NULL);
		}
		sched_yield();
	}
	return NULL;
}