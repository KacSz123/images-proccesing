#include "image.h"


void loadImage(Image *Img)
{


    printf("alloc fun a\n");
    Img->_allocationFlag = true;  
    Img->_img=(int*)malloc(sizeof(int)*((Img->_dimY)*(Img->_dimX)));

}


void freeImageSpace(Image *Img)
{
  printf("WE ARE Freeeee \n");
    // for(int i=0; i<Img->_dimX; ++i)
    //     free(Img->_img[i]);
    free(Img->_img);
    Img->_allocationFlag = false;  
}
// const int a;

void printImgParamStdout(const Image Img)
{
    printf("\n*****************\n"
            "Image parameters:\n"
            "*****************\n");
    printf("Magick no: %c%c\n", Img._magickNumber[0], Img._magickNumber[1]);
    printf("X - Y: %d - %d\n", Img._dimX, Img._dimY);
    printf("Shades: %d\n\n", Img._shades);
    
}







int ReadFile(FILE *inputFile, Image *img)
{
    printf("start!\n");
  char buf[DL_LINII]; /* bufor pomocniczy do czytania naglowka i komentarzy */
  int sign;           /* zmienna pomocnicza do czytania komentarzy */
  int end = 0;     /* czy napotkano end danych w pliku */
  int i, j;
  
  
  // freeing space
  if(img->_allocationFlag)
    freeImageSpace(img);
  /*Sprawdzenie czy podano prawidlowy uchwyt pliku */


    printf("start2!\n");
  if (inputFile == NULL)
  {
    fprintf(stderr, "Blad: Nie podano uchwytu do pliku\n");
    return (0);
  }

//   printf("oto wksaznik file:");
//   printf("%p",inputFile);
  /* Sprawdzenie "numeru magicznego" - powinien by� P2 */
  if (fgets(buf, DL_LINII, inputFile) == NULL) /* Wczytanie pierwszej linii pliku do bufora */
    end = 1;                              /* Nie udalo sie? end danych! */


printf("mag no \n");
  if ((buf[0] != 'P') || (buf[1] != '2') || end)
  { /* Czy jest magiczne "P2"? */
    fprintf(stderr, "Blad: To nie jest plik PGM\n");
    return (0);
  }
    img->_magickNumber[0]=buf[0]; /*Write magick number into structure*/
    img->_magickNumber[1]=buf[1];

printf("comment \n");    

  /* Pominiecie komentarzy */
  do
  {
    if ((sign = fgetc(inputFile)) == '#')
    {                                            /* Czy linia rozpoczyna sie od signu '#'? */
      if (fgets(buf, DL_LINII, inputFile) == NULL) /* Przeczytaj ja do bufora                */
        end = 1;                              /* Zapamietaj ewentualny end danych */
    }
    else
    {
      ungetc(sign, inputFile);        /* Gdy przeczytany sign z poczatku linii */
    }                               /* nie jest '#' zwroc go                 */
  } while (sign == '#' && !end); /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil end danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(inputFile, "%d %d %d", &(img->_dimX), &(img->_dimY), &(img->_shades)) != 3)
  {
    fprintf(stderr, "Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return (0);
  }


    printf("dim and shades \n");
  /* Memory alocation */

    printf("alloc \n");
  loadImage(img);
    printf("alloc end\n");
  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  printf("x %d, y %d \n", img->_dimX,img->_dimY);
  for (i = 0; i < (img->_dimY); i++)
  { 
    for (j = 0; j < (img->_dimX); j++)
    {
      if (fscanf(inputFile, "%d", &(img->_img[(i*(img->_dimX))+j])) != 1)
      {
        fprintf(stderr, "Blad: Niewlasciwe wymiary obrazu\n");
        return (0);
      }
    }
  }
  return 0; 
} 



void WriteFile(FILE *file, const Image img)
{
      // FILE *fp; /* używamy metody wysokopoziomowej - musimy mieć zatem identyfikator pliku, uwaga na gwiazdkę! */
  // char *tekst = "Hello world123123";
  //char *nazwa = "test.pgm";

  int i, j;
  fprintf(file, "%c%c\n",img._magickNumber[0],img._magickNumber[1]);
  fprintf(file, "%d %d\n", img._dimX, img._dimY);
  fprintf(file, "%d\n", img._shades);
  for (i = 0; i < img._dimY; ++i)
  {
    for (j = 0; j < img._dimX; ++j){
      fprintf(file, "%d ", img._img[(i*(img._dimX))+j]);
      if(j%(DL_LINII-1)==0)fprintf(file, "\n");}
  }

  /* zapisz nasz łańcuch w pliku */
 /* zamknij plik */
 

  return  fclose(file);

}
void ContureImage(Image imgInput, Image imgOutput)
{

}
void BlurrImageVertical(Image imgInput, Image imgOutput)
{

}
void BlurrImageHorizontal(Image imgInput, Image imgOutput)
{

}
void NegativeImage(Image imgInput, Image imgOutput, int ray)
{

}
void ThresholdImage(Image imgInput, Image imgOutput, int ray)
{

}