smallsh: smallsh.o input.o
	gcc -Wall -pedantic -o smallsh input.o smallsh.o 
smallsh.o: smallsh.c smallsh.h
	gcc -Wall -pedantic -c smallsh.c
input.o: input.c smallsh.h
	gcc -Wall -pedantic -c input.c
clean:
	rm smallsh input.o smallsh.o
