// threads.2b.c

// #define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define GUI

#ifdef GUI
typedef enum
{
	NOIR,
	ROUGE,
	VERT,
	MARRON,
	BLEU,
	FUSHIA,
	CYAN,
	GRIS,
	NB_COULEURS
} Couleur;
typedef enum
{
	NORMAL,
	SOFTEN,
	NORMAL1,
	NORMAL2,
	SOULIGNE,
	BLINK,
	NORMAL3,
	INVERT
} Mode;

#define RESET_TERM() printf("\x1b[0m")
#define SET_BGCOLOR(color) printf("\x1b[1;37;4%dm", color)
#define SET_COLOR(color) printf("\x1b[0;3%dm", color)
#define SET_MODECOLOR(mode, color) printf("\x1b[%d;3%dm", mode, color)
#define SETCOLOR_SUCCESS() printf("\x1b[1;32m")
#define SETCOLOR_FAILURE() printf("\x1b[5;31m")
#define SETCOLOR_ERROR() printf("\x1b[1;31m")
#define SETCOLOR_WARNING() printf("\x1b[1;34m")
#define SETCOLOR_INFO() printf("\x1b[0;37m")
#define SETCOLOR_NORMAL() printf("\x1b[0;39m")
#define MOVE_TO_COL(col) printf("\x1B[%dG", col)
#define MOVE_XY(x, y) printf("\x1B[%d;%dH", x, y)
#define CLEAR_LINE(x, y) printf("\x1B[%d;%dH\x1b[2K", x, y)
#define RESET() printf("\x1B[2J")

#define LIGNE_THREAD1 4
#define LIGNE_THREAD2 LIGNE_THREAD1 + 5
#endif

pthread_mutex_t globale_lock = PTHREAD_MUTEX_INITIALIZER;

int value_globale = 10;

// Chaque thread (tache) va faire ses COUNT boucles
#define COUNT 25

// Fonctions correspondant au corps d'un thread (tache)
void* increment(void* inutilise);
void* decrement(void* inutilise);

int main(void)
{
	pthread_t thread1, thread2;

	setbuf(stdout, NULL);

#ifdef GUI
	RESET();
	RESET_TERM();
	MOVE_XY(0, 0);
#endif

#ifdef GUI
	printf("\x1B[%d;%dHAvant les threads : value = %d (%d boucles)", 0, 0, value_globale, COUNT);
#else
	printf("Avant les threads : value = %d (%d boucles)\n", value_globale, COUNT);
#endif

	pthread_create(&thread1, NULL, increment, NULL);
	pthread_create(&thread2, NULL, decrement, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

#ifdef GUI
	// printf("\x1B[%d;%dHApres les threads : value = %d (%d boucles)", 1, 0, value_globale, COUNT);
	MOVE_XY(15, 0);
	printf("\nApres les threads : value = %d (%d boucles)\n", value_globale, COUNT);
#else
	printf("\nApres les threads : value = %d (%d boucles)\n", value_globale, COUNT);
#endif

#ifdef GUI
	// for (int i = 0; i < 4; i++)
	// 	CLEAR_LINE(LIGNE_THREAD1 + i, 0);
	// for (int i = 0; i < 4; i++)
	// 	CLEAR_LINE(LIGNE_THREAD2 + i, 0);
	// RESET_TERM();
	// MOVE_XY(1, 0);
#endif
	printf("\nTerminé\n");

	return EXIT_SUCCESS;
}

void* increment(void* inutilise)
{
	int value;
	int count = 0;

	while (1)
	{
		pthread_mutex_lock(&globale_lock);

		// Récupère la value
		value = value_globale;

#ifdef GUI
		printf("\x1B[%d;%dH>>> Thread1 : load value (value = %02d / %02d)",
			   LIGNE_THREAD1,
			   2,
			   value,
			   value_globale);
#else
		printf("Thread1 : load value (value = %02d / %02d) ", value, value_globale);
#endif

		// Incrémente la value
		value += 1;

#ifdef GUI
		printf("\x1B[%d;%dH>>> Thread1 : increment value (value = %02d / %02d)",
			   LIGNE_THREAD1 + 1,
			   2,
			   value,
			   value_globale);
#else
		printf("Thread1 : increment value (value = %02d / %02d) ", value, value_globale);
#endif

		// Stocke la value
		value_globale = value;

#ifdef GUI
		printf("\x1B[%d;%dH>>> Thread1 : store value (value = %02d / %02d)",
			   LIGNE_THREAD1 + 2,
			   2,
			   value,
			   value_globale);
#else
		printf("Thread1 : store value (value = %02d / %02d) ", value, value_globale);
#endif

		pthread_mutex_unlock(&globale_lock);

		count++;
#ifdef GUI
		printf("\x1B[%d;%dH>>> Thread1 : %02d boucle(s)", LIGNE_THREAD1 + 3, 2, count);
		usleep(500000);
#endif

		if (count >= COUNT)
		{
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

		// Récupère la value
		value = value_globale;

#ifdef GUI
		printf("\x1B[%d;%dH>>> Thread2 : load value (value = %02d / %02d)",
			   LIGNE_THREAD2,
			   2,
			   value,
			   value_globale);
#else
		printf("Thread2 : load value (value = %02d / %02d) ", value, value_globale);
#endif

		// Décremente la value
		value -= 1;

#ifdef GUI
		printf("\x1B[%d;%dH>>> Thread2 : decrement value (value = %02d / %02d)",
			   LIGNE_THREAD2 + 1,
			   2,
			   value,
			   value_globale);
#else
		printf("Thread2 : increment value (value = %02d / %02d) ", value, value_globale);
#endif

		// Stocke la value
		value_globale = value;

#ifdef GUI
		printf("\x1B[%d;%dH>>> Thread2 : store value (value = %02d / %02d)",
			   LIGNE_THREAD2 + 2,
			   2,
			   value,
			   value_globale);
#else
		printf("Thread2 : store value (value = %02d / %02d) ", value, value_globale);
#endif

		pthread_mutex_unlock(&globale_lock);

		count++;
#ifdef GUI
		printf("\x1B[%d;%dH>>> Thread2 : %02d boucle(s)", LIGNE_THREAD2 + 3, 2, count);
		usleep(500000);
#endif

		if (count >= COUNT)
		{
			return (NULL);
		}
	}

	return NULL;
}
