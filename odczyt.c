#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "odczyt.h" /* Dlugosc buforow pomocniczych */

/************************************************************************************
 * Funkcja wczytuje obraz PGM z pliku do tablicy       	       	       	       	    *
 *										    *
 * \param[in] plik_we uchwyt do pliku z obrazem w formacie PGM			    *
 * \param[out] obraz_pgm tablica, do ktorej zostanie zapisany obraz		    *
 * \param[out] wymx szerokosc obrazka						    *
 * \param[out] wymy wysokosc obrazka						    *
 * \param[out] szarosci liczba odcieni szarosci					    *
 * \return liczba wczytanych pikseli						    *
 ************************************************************************************/

int czytaj(FILE *plik_we, int obraz_pgm[][MAX], int *wymx, int *wymy, int *szarosci)
{
  char buf[DL_LINII]; /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;           /* zmienna pomocnicza do czytania komentarzy */
  int koniec = 0;     /* czy napotkano koniec danych w pliku */
  int i, j;

  /*Sprawdzenie czy podano prawid�owy uchwyt pliku */
  if (plik_we == NULL)
  {
    fprintf(stderr, "Blad: Nie podano uchwytu do pliku\n");
    return (0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien by� P2 */
  if (fgets(buf, DL_LINII, plik_we) == NULL) /* Wczytanie pierwszej linii pliku do bufora */
    koniec = 1;                              /* Nie udalo sie? Koniec danych! */

  if ((buf[0] != 'P') || (buf[1] != '2') || koniec)
  { /* Czy jest magiczne "P2"? */
    fprintf(stderr, "Blad: To nie jest plik PGM\n");
    return (0);
  }

  /* Pominiecie komentarzy */
  do
  {
    if ((znak = fgetc(plik_we)) == '#')
    {                                            /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf, DL_LINII, plik_we) == NULL) /* Przeczytaj ja do bufora                */
        koniec = 1;                              /* Zapamietaj ewentualny koniec danych */
    }
    else
    {
      ungetc(znak, plik_we);        /* Gdy przeczytany znak z poczatku linii */
    }                               /* nie jest '#' zwroc go                 */
  } while (znak == '#' && !koniec); /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we, "%d %d %d", wymx, wymy, szarosci) != 3)
  {
    fprintf(stderr, "Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return (0);
  }
  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i = 0; i < *wymy; i++)
  {
    for (j = 0; j < *wymx; j++)
    {
      if (fscanf(plik_we, "%d", &(obraz_pgm[i][j])) != 1)
      {
        fprintf(stderr, "Blad: Niewlasciwe wymiary obrazu\n");
        return (0);
      }
    }
  }
  return *wymx * *wymy; /* Czytanie zakonczone sukcesem    */
} /* Zwroc liczbe wczytanych pikseli */

/* Wyswietlenie obrazu o zadanej nazwie za pomoca programu "display"   */
void wyswietl(char *n_pliku)
{
  char polecenie[DL_LINII]; /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie, "display "); /* konstrukcja polecenia postaci */
  strcat(polecenie, n_pliku);    /* display "nazwa_pliku" &       */
  strcat(polecenie, " &");
  printf("%s\n", polecenie); /* wydruk kontrolny polecenia */
  system(polecenie);
  /* wykonanie polecenia        */
  //printf("asfasfag\n");
}

int zapisz(FILE *fp, int obraz_pgm[MAX][MAX],int wymx,int wymy, int szarosci)
{
    //FILE *fp; /* używamy metody wysokopoziomowej - musimy mieć zatem identyfikator pliku, uwaga na gwiazdkę! */
   //char *tekst = "Hello world123123";
   char *nazwa="test.pgm";
   if ((fp=fopen(nazwa, "w"))==NULL) {
     printf ("Nie mogę otworzyć pliku test.txt do zapisu!\n");
     exit(1);
     }
     int i,j;
   fprintf (fp, "P2\n" );
   fprintf (fp, "%d %d\n",wymx, wymy ); 
   fprintf (fp, "%d\n", szarosci );
   for(i=0; i<wymy; ++i)
   {
     for(j=0; j<wymx; ++j)
   fprintf (fp, "%d ",obraz_pgm[i][j] );


   fprintf (fp, "\n" );
   }
   
    /* zapisz nasz łańcuch w pliku */
   fclose (fp); /* zamknij plik */
 
   
   return 0;
}



void Negatyw(int (*obraz_pgm)[MAX][MAX], int wymx, int wymy, int szarosci)
{
  int i, j;
  for(i=0; i<wymy; ++i)
  {
    for(j=0; j<wymx; ++j)
    {
      (*obraz_pgm)[i][j]=szarosci-(*obraz_pgm)[i][j];
    }
  }
}
void Konturowanie(int (*o_pgm)[MAX][MAX], int wymx, int wymy)
{
  int i, j;
  for(i=0; i<wymy-1; ++i)
  {
    for(j=0; j<wymx-1; ++j)
    {
      (*o_pgm)[i][j]=abs((*o_pgm)[i+1][j]-(*o_pgm)[i][j])+abs((*o_pgm)[i][j+1]-(*o_pgm)[i][j]);
    }
  }
}
void Progowanie(int (*o_pgm)[MAX][MAX], int wymx, int wymy, int szarosci ,int prog)
{
  int i, j;
  for(i=0; i<wymy; ++i)
  {
    for(j=0; j<wymx; ++j)
    {
      if((*o_pgm)[i][j]<=(prog*szarosci)/100)
        (*o_pgm)[i][j]=0;
      else
        (*o_pgm)[i][j]=szarosci;
    }
  }
}
void Rozmycie_pion(int (*o_pgm)[MAX][MAX], int wymx, int wymy, int promien)
{
    int i, j, k, p;

    for(i=0; i<=promien; ++i)
  {
    for(j=0; j<wymx; ++j)
    {
      for(k=1; k<=promien; ++k)
      {
        (*o_pgm)[i][j]+=(*o_pgm)[i+k][j]; 
      }
     if(i>0)
      {
        for(p=1; p<=i; ++p)
          (*o_pgm)[i][j]+=(*o_pgm)[i-p][j]; 
      }
      (*o_pgm)[i][j]/=promien+i+1;
    }
  }

  for(i=promien+1; i<=wymy-promien-2; ++i)
  {
    for(j=0; j<wymx; ++j)
    {
      for(k=0; k<promien; ++k)
      {
        (*o_pgm)[i][j]+=((*o_pgm)[i+k][j]+(*o_pgm)[i-k][j]);
      }
      (*o_pgm)[i][j]/=((2*promien)+1);
    }
  }

    for(i=wymy-promien-1; i<wymy; ++i)
  {
    for(j=0; j<wymx; ++j)
    {
      for(k=1; k<=promien; ++k)
      {
        (*o_pgm)[i][j]+=(*o_pgm)[i-k][j]; 
      }
     if((wymy-i)>1)
      {
        for(p=1; p<=(wymy-i); ++p)
          (*o_pgm)[i][j]+=(*o_pgm)[i+p][j]; 
      }
      (*o_pgm)[i][j]/=promien+(wymy-i);
    }
  }

}
void Rozmycie_poz(int (*o_pgm)[MAX][MAX], int wymx, int wymy, int promien)
{
    int i, j, k, p;

    for(i=0; i<wymy; ++i)
  {
    for(j=0; j<=promien; ++j)
    {
      for(k=1; k<=promien; ++k)
      {
        (*o_pgm)[i][j]+=(*o_pgm)[i][j+k]; 
      }
     if(j>0)
      {
        for(p=1; p<=j; ++p)
          (*o_pgm)[i][j]+=(*o_pgm)[i][j-p]; 
      }
      (*o_pgm)[i][j]/=promien+j+1;
    }
  }

  for(i=0; i<wymy; ++i)
  {
    for(j=promien+1; j<=wymx-promien-2; ++j)
    {
      for(k=0; k<promien; ++k)
      {
        (*o_pgm)[i][j]+=((*o_pgm)[i][j+k]+(*o_pgm)[i][j-k]);
      }
      (*o_pgm)[i][j]/=((2*promien)+1);
    }
  }

    for(i=0; i<wymy; ++i)
  {
    for(j=wymx-promien-1; j<wymx; ++j)
    {
      for(k=1; k<=promien; ++k)
      {
        (*o_pgm)[i][j]+=(*o_pgm)[i][j-k]; 
      }
     if((wymx-j)>1)
      {
        for(p=1; p<=(wymx-j); ++p)
          (*o_pgm)[i][j]+=(*o_pgm)[i][j+p]; 
      }
      (*o_pgm)[i][j]/=promien+(wymx-j);
    }
  }

}
