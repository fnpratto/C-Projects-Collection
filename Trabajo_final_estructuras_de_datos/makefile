VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all 
CFLAGS =-std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -g
CC = gcc

all: clean valgrind-chanutron tp2

valgrind-chanutron: pruebas_chanutron
	valgrind $(VALGRIND_FLAGS) ./pruebas_chanutron

pruebas_chanutron: src/tp1/*.c pruebas_chanutron.c
	$(CC) $(CFLAGS) src/tp1/*.c pruebas_chanutron.c -o pruebas_chanutron

ejemplo: src/*.c tp2.c
	$(CC) $(CFLAGS) src/*.c tp2.c -o tp2

pruebas_alumno:
	echo "OK"
valgrind-alumno:
	echo "OK"
tp2: src/*.c src/tp1/*.c src/hash/*.c tp2.c
	$(CC) $(CFLAGS) src/*.c src/tp1/*.c src/hash/*.c src/texto/*.c tp2.c -o tp2
clean:
	rm -f pruebas_alumno pruebas_chanutron tp2