__start__: clean _free_lines_ obj all __end__
	
CFLAGS = -Wall -pedantic # tutaj można dodawać inne flagi kompilatora
LIBS =  # tutaj można dodawać biblioteki
OUT=Program

_free_lines_:
	@echo 
	@echo
	@echo

__end__:
	@echo
	@echo "Skompilowano i skonsolidowano program"
	@echo "Uruchom plik"  
	@echo ${OUT}
	@echo  "w celu przetestowania programu"
	
all: OBJ/odczyt.o OBJ/main.o
	@echo "Kompilacja i konsolidacja programu"
	@echo
	gcc ${CFLAGS} -o ${OUT} OBJ/main.o OBJ/odczyt.o
	@echo
	@echo

OBJ/odczyt.o: odczyt.c odczyt.h
	@echo "Kompilacja pliku odczyt.h"
	@echo
	gcc -c ${CFLAGS} odczyt.c -o OBJ/odczyt.o
	@echo
	@echo

OBJ/main.o: main.c odczyt.h
	@echo "Kompilacja pliku main.c"
	@echo
	gcc -c ${CFLAGS} main.c -o OBJ/main.o
	@echo
	@echo

clean:
	@echo "Usuwanie plikow .o w katalogu OBJ"
	@echo
	rm -f OBJ/*
	@echo
	@echo "Usuwanie katalogu OBJ"
	@echo
	rmdir OBJ

clean_exec:
	rm Program

obj: 
	@echo "Tworzenie katalogu OBJ"
	@echo
	mkdir OBJ
	@echo
	@echo
	