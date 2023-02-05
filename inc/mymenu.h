#ifndef MYMENU_H
#define MYMENU_H



// #include "odczyt.h"
typedef enum
{
    NO_ERROR,
    FILE_LOADING,
    IMG_FUN_ERROR,
    OTHER_ERROR
} ERRORS;


int menuProgramPL();
int menuProgramENG();
void Show_menu();

void Show_menuENG();
void Show_menuPL();





#endif