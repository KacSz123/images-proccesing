__start__: clean_screen clean _free_lines_ obj all __end__ #run
INCPATH += inc/
CFLAGS = -Wall -pedantic -I$(INCPATH)# tutaj można dodawać inne flagi kompilatora
LIBS =  #tutaj można dodawać biblioteki
OUT=Program
bold := $(shell tput bold)
sgr0 := $(shell tput sgr0)


_free_lines_:
	@echo 
	@echo
	@echo

__end__:
	@echo
	@echo "Skompilowano i skonsolidowano program"
	@echo "Uruchom plik $(bold)${OUT}$(sgr0) w celu przetestowania programu"  
	@echo  ""
	
all: OBJ/odczyt.o OBJ/image.o OBJ/main.o
	@echo "Kompilacja i konsolidacja programu"
	@echo
	gcc ${CFLAGS} -o ${OUT} OBJ/main.o OBJ/odczyt.o OBJ/image.o
	@echo
	@echo

OBJ/odczyt.o: src/odczyt.c inc/odczyt.h
	@echo "Kompilacja pliku $(bold)odczyt.c$(sgr0)"
	@echo
	gcc -c ${CFLAGS} src/odczyt.c -o OBJ/odczyt.o
	@echo
	@echo

OBJ/main.o: src/main.c inc/odczyt.h
	@echo "Kompilacja pliku $(bold)main.c$(sgr0)"
	@echo
	gcc -c ${CFLAGS} src/main.c -o OBJ/main.o
	@echo
	@echo

OBJ/image.o: src/image.c inc/image.h
	@echo "Kompilacja pliku $(bold)Image.c$(sgr0)"
	@echo
	gcc -c ${CFLAGS} src/image.c -o OBJ/image.o
	@echo
	@echo

clean:
	if  test -d OBJ; then \
	echo "Usuwanie plikow $(bold)*.o$(sgr0) w katalogu $(bold)OBJ$(sgr0)" &&\
	echo &&\
	rm -f  OBJ/* &&\
	echo &&\
	echo "$(bold)Usuwanie$(sgr0) katalogu$(bold) OBJ$(sgr0)" &&\
	echo &&\
	rmdir OBJ; \
	fi

clean_exec:
	rm Program

obj: 
	if  !(test -d OBJ); then \
	echo "Tworzenie katalogu$(bold) OBJ$(sgr0)" &&\
	echo &&\
	mkdir OBJ &&\
	echo &&\
	echo; \
	fi

	
run: clean_screen go


go:
	@echo "Uruchamianie pliku $(bold)${OUT}$(sgr0)"
	./${OUT}


clean_screen:
	clear


clean_pgm:
	rm *.pgm




	