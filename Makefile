all: threads.2a threads.2b threads.2b-bloc threads.3a threads.3b

threads.2a: threads.2a.c
	gcc -o $@ $< -lpthread -D_REENTRANT -D_GNU_SOURCE

threads.2b: threads.2b.c
	gcc -o $@ $< -lpthread -D_REENTRANT -D_GNU_SOURCE

threads.2b-bloc: threads.2b-bloc.c
	gcc -o $@ $< -lpthread -D_REENTRANT -D_GNU_SOURCE

threads.3a: threads.3a.c
	gcc -o $@ $< -lpthread -D_REENTRANT -D_GNU_SOURCE

threads.3b: threads.3b.c
	gcc -o $@ $< -lpthread -D_REENTRANT -D_GNU_SOURCE

clean:
	rm -f threads.2a threads.2b threads.2b-bloc threads.3a threads.3b *~
