#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../inc/odczyt.h"

void Show_menu()
{
    printf("******************************* \n");
    printf("******** Wybierz opcje ******** \n");
    printf("******************************* \n");
    printf("****   1 - Wczytaj obraz   **** \n");
    printf("****   2 - Zapisz obraz    **** \n");
    printf("****   3 - Wyswietl obraz  **** \n");
    printf("****   4 - **** \n");
    printf("****   5 - **** \n");
    printf("****   K - Zakoncz         **** \n ");
    printf("******************************* \n");
    printf("******************************* \n\n\n");

}
int Menu_function()
{
    int a;

    scanf("%d", &a);

    switch(a)
    {
        case 1:
        printf("Wybrano opcje nr 1\n");
        break;
        case 2:
        printf("Wybrano opcje nr 2\n");
        break;
        case 3:
        printf("Wybrano opcje nr 3\n");
        break;
        case 4:
        printf("Wybrano opcje nr 4\n");
        break;
        case 0:
        break;
        default:
        printf("zly wybor\n\n");
        break;
    }
    return a;
    
}


int main() 
{
  int obraz[MAX][MAX] ;
  int wymx,wymy,odcieni;

  int odczytano = 0;
  int wybor;
  FILE *plik;
  FILE *plik_wy;

  char nazwa[50];
  char nazwe_wy[50];
  Show_menu();
  printf("Podaj funkcję z zakresu 1-4:\n");
  Menu_function();

  /* Wczytanie zawartosci wskazanego pliku do pamieci */
  printf("Podaj nazwe pliku:\n");
  scanf("%s",nazwa);
  plik=fopen(nazwa,"r");

  if (plik != NULL) 
  {       /* co spowoduje zakomentowanie tego warunku */
    odczytano = czytaj(plik,obraz,&wymx,&wymy,&odcieni);
    fclose(plik);
  }



  //Negatyw(&obraz, wymx, wymy, odcieni);
  Konturowanie(&obraz, wymx, wymy);
  //Progowanie(&obraz, wymx, wymy, odcieni, 20);
  //Rozmycie_pion(&obraz, wymx, wymy, 5);
  zapisz(plik_wy,obraz, wymx, wymy, odcieni);


      if (odczytano != 0)
   // wyswietl(nazwa);
  /* Wyswietlenie poprawnie wczytanego obraza zewnetrznym programem */

      wyswietl("test.pgm");
  return odczytano;
}