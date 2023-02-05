#include "mymenu.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "image.h"
// #include "odczyt.h"#ifndef MENU_H




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
    printf("****  9 - gammma kore        **** \n");
    printf("****  * - hist normal        **** \n");
    printf("****  m - Wyswietl menu      **** \n");
    printf("****  k - Zakoncz program    **** \n");
    printf("********************************* \n");
    printf("********************************* \n\n");
}


void Show_menuENG()
{
    printf("************ M E N U ************ \n");
    printf("********************************* \n");
    printf("******* Available options: ****** \n");
    printf("********************************* \n");
    printf("****  1 - Load image         **** \n");
    printf("****  2 - Save image in mem. **** \n");
    printf("****  3 - Show image in mem. **** \n");
    printf("****  4 - Contouring         **** \n");
    printf("****  5 - Vertical Blur      **** \n");
    printf("****  6 - Horizontal Blur    **** \n");
    printf("****  7 - Threshold          **** \n");
    printf("****  8 - Negative           **** \n");
    printf("****  9 - gamma correction   **** \n");
    printf("****  * - Histogram Normal.  **** \n");
    printf("****  m - Show Menu          **** \n");
    printf("****  k - End Program        **** \n");
    printf("********************************* \n");
    printf("********************************* \n\n");
}
void Show_menuPL()
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
    printf("****  9 - gammma kore        **** \n");
    printf("****  * - hist normal        **** \n");
    printf("****  m - Wyswietl menu      **** \n");
    printf("****  k - Zakoncz program    **** \n");
    printf("********************************* \n");
    printf("********************************* \n\n");
}
// void wyswietl(char *n_pliku)
// {
//     char polecenie[DL_LINII]; /* bufor pomocniczy do zestawienia polecenia */

//     strcpy(polecenie, "display "); /* konstrukcja polecenia postaci */
//     strcat(polecenie, n_pliku);    /* display "nazwa_pliku" &       */
//     strcat(polecenie, " &");
//     printf("%s\n", polecenie); /* wydruk kontrolny polecenia */
//     system(polecenie);
//     /* wykonanie polecenia        */
//     // printf("asfasfag\n");
// }
int menuProgramPL()
{
    int odczytano = 0;
    FILE *plik;
    FILE *plik_wy;

    Image img;
    img._allocationFlag = false;
    char nazwa[50];
    char nazwe_wy[50];
    char pokaz_nazwa[50];
    // const char sys[5]="clear";
    Show_menu();

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
                odczytano = ReadFile(plik, &img);
                fclose(plik);
                printImgParamStdout(img);

                printf("Wczytano plik %s", nazwa);
                // wyswietl(nazwa);
            }
            else
            {
                fprintf(stderr, "!\n");
                return 1;
            }
            // img2=img;
            break;
        case '2':
            printf("Zapisywanie pliku:\n");
            printf("Podaj nazwe pliku:\n");
            scanf("%s", nazwe_wy);
            if ((plik_wy = fopen(nazwe_wy, "w")) == NULL)
            {
                printf("Nie mogę otworzyć pliku %s do zapisu!\n", nazwa);
                exit(1);
            }
            else
            {
                WriteFile(plik_wy, img);
                // fclose(plik_wy);
                printf("Zapisano nowy plik o nazwie %s \n", nazwe_wy);
            }
            break;

        case '3':
            printf("Podaj nazwe pliku do wyswietlenia:\n");
            scanf("%s", pokaz_nazwa);
            ShowImage(pokaz_nazwa);
            break;
        case '4':
            ContureImage(&img);
            printf("Dokonano operacji konturowania\n");
            break;
        case '5':
            // scanf("%d", promien);
            BlurrImageHorizontal(&img, 5);
            printf("Dokonano operacji rozmycia pion.\n");
            break;
        case '6':
            // printf("Podaj promien (0-20)\n");
            // scanf("%d", promien);
            BlurrImageHorizontal(&img, 5);
            printf("Dokonano operacji rozmycia poz.\n");
            break;
        case '7':
            // Progowanie(&obraz, wymx, wymy, odcieni, 20);
            ThresholdImage(&img, 50);
            printf("Dokonano operacji progowania\n");
            break;
        case '8':
            NegativeImage(&img);
            printf("Dokonano operacji negatywu\n");
            break;
        case '9':
            GammaCorrection(&img, 0.5);
            printf("Dokonano operacji korekty gamma\n");
            break;
        case '*':
            HistogramNormalize(&img);
            printf("rozciagnieto histgram\n");
            break;
        case 'm':
            system("clear");
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

        ShowImage("test.pgm");
    return odczytano;


    return 0;
}



int menuProgramENG()
{
    int odczytano = 0;
    FILE *plik;
    FILE *plik_wy;

    Image img;
    img._allocationFlag = false;
    char nazwa[50];
    char nazwe_wy[50];
    char pokaz_nazwa[50];
    // const char sys[5]="clear";
    Show_menu();

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
                odczytano = ReadFile(plik, &img);
                fclose(plik);
                printImgParamStdout(img);

                printf("Wczytano plik %s", nazwa);
                // wyswietl(nazwa);
            }
            else
            {
                fprintf(stderr, "!\n");
                return 1;
            }
            // img2=img;
            break;
        case '2':
            printf("Zapisywanie pliku:\n");
            printf("Podaj nazwe pliku:\n");
            scanf("%s", nazwe_wy);
            if ((plik_wy = fopen(nazwe_wy, "w")) == NULL)
            {
                printf("Nie mogę otworzyć pliku %s do zapisu!\n", nazwa);
                exit(1);
            }
            else
            {
                WriteFile(plik_wy, img);
                // fclose(plik_wy);
                printf("Zapisano nowy plik o nazwie %s \n", nazwe_wy);
            }
            break;

        case '3':
            printf("Podaj nazwe pliku do wyswietlenia:\n");
            scanf("%s", pokaz_nazwa);
            ShowImage(pokaz_nazwa);
            break;
        case '4':
            ContureImage(&img);
            printf("Dokonano operacji konturowania\n");
            break;
        case '5':
            // scanf("%d", promien);
            BlurrImageHorizontal(&img, 5);
            printf("Dokonano operacji rozmycia pion.\n");
            break;
        case '6':
            // printf("Podaj promien (0-20)\n");
            // scanf("%d", promien);
            BlurrImageHorizontal(&img, 5);
            printf("Dokonano operacji rozmycia poz.\n");
            break;
        case '7':
            // Progowanie(&obraz, wymx, wymy, odcieni, 20);
            ThresholdImage(&img, 50);
            printf("Dokonano operacji progowania\n");
            break;
        case '8':
            NegativeImage(&img);
            printf("Dokonano operacji negatywu\n");
            break;
        case '9':
            GammaCorrection(&img, 0.5);
            printf("Dokonano operacji korekty gamma\n");
            break;
        case '*':
            HistogramNormalize(&img);
            printf("rozciagnieto histgram\n");
            break;
        case 'm':
            system("clear");
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

        ShowImage("test.pgm");
    return odczytano;


    return 0;
}
