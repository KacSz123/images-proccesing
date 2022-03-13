#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/odczyt.h"

void Show_menu()
{
    printf("************ M E N U ************ \n");
    printf("********************************* \n");
    printf("********  Wybierz opcje: ******** \n");
    printf("********************************* \n");
    printf("****  1 - Wczytaj obraz      **** \n");
    printf("****  2 - Zapisz obraz       **** \n");
    printf("****  3 - Wyswietl obraz     **** \n");
    printf("****  4 - Op. konturowania   **** \n");
    printf("****  5 - Op. rozmycia pion. **** \n");
    printf("****  6 - Op. rozmycia poz.  **** \n");
    printf("****  7 - Op. progowania     **** \n");
    printf("****  m - Wyswietl menu      **** \n");
    printf("****  k - Zakoncz program    **** \n");
    printf("********************************* \n");
    printf("********************************* \n\n\n");
}

int Menu_function()
{
    char a;

    //scanf("%d", &a);

    switch (a=getchar())
    {
    case '1':
        printf("Wybrano opcje nr 1\n");
        break;
    case '2':
        printf("Wybrano opcje nr 2\n");
        break;
    case '3':
        printf("Wybrano opcje nr 3\n");
        break;
    case '4':
        printf("Wybrano opcje nr 4\n");
        break;
    case 'm':
        Show_menu();
        break;
    case 'k':
        break;
    default:
        printf("zly wybor\n\n");
        break;
    }
    return a;
}

int main()
{
    int obraz[MAX][MAX];
    int wymx, wymy, odcieni;

    int odczytano = 0;
    int wybor;
    FILE *plik;
    FILE *plik_wy;

    char nazwa[50];
    char nazwe_wy[50];
    Show_menu();
   // printf("Podaj funkcję z zakresu 1-4:\n");
    //Menu_function();

    /* Wczytanie zawartosci wskazanego pliku do pamieci */
    


    // Negatyw(&obraz, wymx, wymy, odcieni);
    //Konturowanie(&obraz, wymx, wymy);
    // Progowanie(&obraz, wymx, wymy, odcieni, 20);
    // Rozmycie_pion(&obraz, wymx, wymy, 15);
     Rozmycie_poz(&obraz, wymx, wymy, 5);
    zapisz(plik_wy, obraz, wymx, wymy, odcieni);
    char a='0';
    
    while(a!='k' || a!='K')
    {
    scanf("%c", &a);
    //getchar();
    switch (a)
    {   
    case '1':
    printf("Wczytywanie pliku:\n");
    printf("Podaj nazwe pliku:\n");
    scanf("%s", nazwa);
        plik = fopen(nazwa, "r");

    if (plik != NULL)
    { /* co spowoduje zakomentowanie tego warunku */
        odczytano = czytaj(plik, obraz, &wymx, &wymy, &odcieni);
        fclose(plik);

        wyswietl(nazwa);
        
    }
        break;
    case '2':
        printf("Wybrano opcje nr 2\n");
        break;
    case '3':
        printf("Wybrano opcje nr 3\n");
        break;
    case '4':
        printf("Wybrano opcje nr 4\n");
        break;
    case 'm':
        Show_menu();
        break;
    case 'k':
        printf("KOOOONIEC\n");
        return 0;
        break;
    case '\n':
      //  printf("czytam enter\n");
        break;    
    default:
        printf("zly wybor\n\n");
        break;
    }
    }
    if (odczytano != 0)
        // wyswietl(nazwa);
        /* Wyswietlenie poprawnie wczytanego obraza zewnetrznym programem */

        wyswietl("test.pgm");
    return odczytano;
}