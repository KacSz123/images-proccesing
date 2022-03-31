#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "odczyt.h"

void Show_menu()
{
    printf("************ M E N U ************ \n");
    printf("********************************* \n");
    printf("********  Wybierz opcje: ******** \n");
    printf("********************************* \n");
    printf("****  1 - Wczytaj obraz      **** \n");
    printf("****  2 - Zapisz akt. obraz  **** \n");
    printf("****  3 - Wyswietl obraz     **** \n");
    printf("****  4 - Op. konturowania   **** \n");
    printf("****  5 - Op. rozmycia pion. **** \n");
    printf("****  6 - Op. rozmycia poz.  **** \n");
    printf("****  7 - Op. progowania     **** \n");
    printf("****  8 - Negatyw            **** \n");
    printf("****  m - Wyswietl menu      **** \n");
    printf("****  k - Zakoncz program    **** \n");
    printf("********************************* \n");
    printf("********************************* \n\n");
}

int main()
{
    int obraz[MAX][MAX];
    int wymx, wymy, odcieni; //int prog;
    //__uint8_t promien;

    int odczytano = 0;
    //int wybor;
    FILE *plik;
    FILE *plik_wy;

    char nazwa[50];
    char nazwe_wy[50];
    char pokaz_nazwa[50];
    Show_menu();
    // printf("Podaj funkcję z zakresu 1-4:\n");
    // Menu_function();

    /* Wczytanie zawartosci wskazanego pliku do pamieci */

    // Negatyw(&obraz, wymx, wymy, odcieni);
    // Konturowanie(&obraz, wymx, wymy);
    // Progowanie(&obraz, wymx, wymy, odcieni, 20);
    // Rozmycie_poz(&obraz, wymx, wymy, 5);

    char a = '0';

    while (a != 'k' || a != 'K')
    {
        scanf("%c", &a);
        // getchar();
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
            printf("Zapisywanie pliku:\n");
            printf("Podaj nazwe pliku:\n");
            scanf("%s", nazwe_wy);
            zapisz(plik_wy, obraz, wymx, wymy, odcieni, nazwe_wy);
            break;
        case '3':
            printf("Podaj nazwe pliku do wyswietlenia:\n");
            scanf("%s", pokaz_nazwa);
            wyswietl(pokaz_nazwa);
            break;
        case '4':
            Konturowanie(&obraz, wymx, wymy);
            break;
        case '5':
            // scanf("%d", promien);
            Rozmycie_pion(&obraz, wymx, wymy, 5);
            break;
        case '6':
            // printf("Podaj promien (0-20)\n");
            // scanf("%d", promien);
            Rozmycie_pion(&obraz, wymx, wymy, 5);
            break;
        case '7':
            Progowanie(&obraz, wymx, wymy, odcieni, 20);
            break;
        case '8':
            Negatyw(&obraz, wymx, wymy, odcieni);
            break;
        case 'm':
            Show_menu();
            break;
        case 'k':
            printf("Koniec! Do zobaczenia! :)\n");
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