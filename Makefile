__start__: clean_screen _oneline_ clean _free_lines_ _oneline_ obj all _doubleline_ __end__ #run obj
INCPATH += inc/
CFLAGS = -Wall -pedantic -I$(INCPATH) # flags for compilator
LIBS =  -lm# place for libs
OUT=Program
bold:=$(shell tput bold)
sgr0:=$(shell tput sgr0)
directory=$(test -d OBJ)

_free_lines_:
	@echo 
	@echo
	@echo

__end__:
	@echo
	@echo "\e[41mCompilation and consolidation completed.\e[49m"
	@echo "Run $(bold)${OUT}$(sgr0) file in order to test program."  
	@echo  ""
	
all: OBJ/odczyt.o OBJ/image.o OBJ/mymenu.o OBJ/main.o
	@echo "Compilation and consolidation"
	@echo
	gcc ${CFLAGS} -o ${OUT} OBJ/main.o OBJ/odczyt.o OBJ/image.o OBJ/mymenu.o  ${LIBS}
	@echo
	@echo

OBJ/odczyt.o: src/odczyt.c inc/odczyt.h
	@echo "\e[44mCompilation of  file: $(bold)odczyt.c$(sgr0)\e[49m"
	@echo
	gcc -c ${CFLAGS} src/odczyt.c -o OBJ/odczyt.o
	@echo
	@echo
OBJ/mymenu.o: src/mymenu.c inc/mymenu.h
	@echo "\e[44mCompilation o file: f $(bold)mymenu.c$(sgr0)\e[49m"
	@echo
	gcc -c ${CFLAGS} src/mymenu.c -o OBJ/mymenu.o
	@echo
	@echo

OBJ/image.o: src/image.c inc/image.h
	@echo "\e[44mCompilation of  file:  $(bold)Image.c$(sgr0)\e[49m"
	@echo
	gcc -c ${CFLAGS} src/image.c -o OBJ/image.o
	@echo
	@echo

OBJ/main.o: src/main.c inc/odczyt.h inc/image.h inc/mymenu.h
	@echo "\e[44mCompilation of file: $(bold)main.c$(sgr0)\e[49m"
	@echo
	gcc -c ${CFLAGS} src/main.c -o OBJ/main.o
	@echo
	@echo

clean: 
	@echo "Removing old $(bold) *.o$(sgr0) files"
	@if test -d OBJ; then echo "$(bold)OBJ $(sgr0)directory found"; else echo "$(bold)OBJ $(sgr0) not found... creating" && mkdir OBJ; fi;
	@[ -f OBJ/image.o ] && rm OBJ/image.o && echo "rm $(bold) image.o$(sgr0)" || echo no  " **$(bold) image.o doesn't exist$(sgr0) **"
	@[ -f OBJ/main.o ] && rm OBJ/main.o && echo "rm $(bold) main.o$(sgr0)" || echo no  " **$(bold) main.o doesn't exist$(sgr0) **"
	@[ -f OBJ/odczyt.o ] && rm OBJ/odczyt.o && echo "rm $(bold) odczyt.o$(sgr0)" || echo no  " **$(bold) odczyt.o doesn't exist$(sgr0) **"
	@[ -f OBJ/mymenu.o ] && rm OBJ/mymenu.o && echo "rm $(bold) mymenu.o$(sgr0)" || echo no  " **$(bold) mymenu.o doesn't exist$(sgr0) **"
	
clean_exec:
	rm Program

obj: 	

# @if [ -d OBJ ]; then\
# 	echo "OBJ directory found";\
# else echo "Making the $(bold) OBJ$(sgr0) directory" && mkdir OBJ;\
# fi

	
run: clean_screen go


_oneline_:
	@echo "----------------------------------------------------------------------------"

_doubleline_:
	@echo "----------------------------------------------------------------------------"
	@echo "----------------------------------------------------------------------------"

go:
	@echo "Runnning $(bold)${OUT}$(sgr0) file"

	./${OUT}


clean_screen:
	clear


clean_pgm:
	rm *.pgm




	