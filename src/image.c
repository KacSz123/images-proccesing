#include "image.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void loadImage(Image *Img)
{
  if (Img->_allocationFlag)
    freeImageSpace(Img);

  Img->_img = malloc(Img->_type * sizeof(int) * (Img->_dimX) * (Img->_dimY));
  Img->_allocationFlag = true;
  
}

void freeImageSpace(Image *Img)
{
  if (!Img->_allocationFlag)
  {
    free(Img->_img);
    Img->_allocationFlag = false;
  }
}

void printImgParamStdout(const Image Img)
{
  printf("\n*****************\n"
         "Image parameters:\n"
         "*****************\n");
  // printf("Magick no: %c%c\n", Img._magickNumber[0], Img._magickNumber[1]);
  printf("X   Y: %d   %d\n", Img._dimX, Img._dimY);
  printf("Shades: %d\n\n", Img._shades);
}

int ReadFile(FILE *inputFile, Image *img)
{
  printf("start!\n");
  char buf[DL_LINII]; /* bufor pomocniczy do czytania naglowka i komentarzy */
  int sign;           /* zmienna pomocnicza do czytania komentarzy */
  int end = 0;        /* czy napotkano end danych w pliku */
  int i, j, p;

  // freeing space
  if (img->_allocationFlag)
    freeImageSpace(img);
  /*Sprawdzenie czy podano prawidlowy uchwyt pliku */

  printf("start2!\n");
  if (inputFile == NULL)
  {
    fprintf(stderr, "Blad: Nie podano uchwytu do pliku\n");
    return (0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien by� P2 */
  if (fgets(buf, DL_LINII, inputFile) == NULL) /* Wczytanie pierwszej linii pliku do bufora */
    end = 1;                                   /* Nie udalo sie? end danych! */

  printf("mag no. \n");
  printf("%c%c\n", buf[0], buf[1]);
  if ((buf[0] != 'P') || (buf[1] != '2' && buf[1] != '3') || end)
  {
    fprintf(stderr, "Blad: To nie jest plik PGM\n");
    return (0);
  }

  if (buf[1] == '2')
    img->_type = 1;
  else if (buf[1] == '3')
    img->_type = 3;
  else
  {
    fprintf(stderr, "Unknown type of image!\n");
    exit(1);
  }
  printf("comment %d\n", img->_type);

  /* Pominiecie komentarzy */
  do
  {
    if ((sign = fgetc(inputFile)) == '#')
    {                                              /* Czy linia rozpoczyna sie od signu '#'? */
      if (fgets(buf, DL_LINII, inputFile) == NULL) /* Przeczytaj ja do bufora                */
        end = 1;                                   /* Zapamietaj ewentualny end danych */
    }
    else
    {
      ungetc(sign, inputFile);   /* Gdy przeczytany sign z poczatku linii */
    }                            /* nie jest '#' zwroc go                 */
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

  loadImage(img);

  const int type = img->_type;

  int(*img_tab)[img->_dimX * type];
  img_tab = (int(*)[img->_dimX * type]) img->_img;

  printf("typ-%d", type);

  for (i = 0; i < img->_dimY; i++)
  {
    for (j = 0; j < img->_dimX; j++)
    {
      for (p = 0; p < type; p++)
      {
        if (fscanf(inputFile, "%d", &(img_tab[i][(j * type) + p])) != 1)
        {
          fprintf(stderr, "Error: Invalid image size\n");
          return (0);
        }
        printf("!!! %d !!!\n", j * type + p);
      }
    }
  }
  return 0;
}

void WriteFile(FILE *file, const Image img)
{
  int i, j, counter = 0, p;
  const int type = img._type;

  int(*img_tab)[img._dimX * type];
  img_tab = (int(*)[img._dimX * type]) img._img;

  if (type == 1)
    fprintf(file, "P2\n");
  else if (type == 3)
    fprintf(file, "P3\n");
  else
  {
    fprintf(stderr, "Wrong magic number!!\n");
    exit(1);
  }
  fprintf(file, "%d %d\n", img._dimX, img._dimY);
  fprintf(file, "%d\n", img._shades);
  for (i = 0; i < img._dimY; ++i)
  {
    for (j = 0; j < img._dimX; ++j)
    {
      for (p = 0; p < type; ++p)
      {
        counter += 3;
        fprintf(file, "%3d ", img_tab[i][j * type + p]);
        if (counter % 69 == 0 && counter != 0)
        {
          fprintf(file, "\n");
          counter = 0;
        }
      }
    }
  }

  fclose(file);
}
void ContureImage(Image *img)
{
  int i, j, p;
  const int type = img->_type;

  int(*img_tab)[img->_dimX * type];
  img_tab = (int(*)[img->_dimX * type]) img->_img;

  for (i = 0; i < img->_dimY; ++i)
  {
    for (j = 0; j < img->_dimX; ++j)
    {
      for (p = 0; p < type; ++p)
      {
        if (i == img->_dimY - 1)
        {
          img_tab[i][j * type + p] = img_tab[i - 1][j * type + p];
        }
        else if (j * type + p == img->_dimX - type)
        {
          img_tab[i][j * type + p] = img_tab[i][j - type];
        }
        else
          img_tab[i][j * type + p] = abs(img_tab[i + 1][j * type + p] - img_tab[i][j * type + type]) +
                                     +abs(img_tab[i][j * type + p + type] - img_tab[i][j * type + p]);
      }
    }
  }
}
void BlurrImageVertical(Image *img, int ray)
{
  int i, j, k, p;
  const int type = img->_type;

  int(*img_tab)[img->_dimX * type];
  img_tab = (int(*)[img->_dimX * type]) img->_img;
  for (i = 0; i <= ray; ++i)
  {

    for (j = 0; j < img->_dimX; ++j)
    {

      for (k = 1; k <= ray; ++k)
      {
        img_tab[i][j] += img_tab[i + k][j];
      }
      if (i > 0)
      {
        for (p = 1; p <= i; ++p)
          img_tab[i][j] += img_tab[i - p][j];
      }
      img_tab[i][j] /= ray + i + 1;
    }
  }

  for (i = ray + 1; i <= img->_dimY - ray - 2; ++i)
  {
    for (j = 0; j < img->_dimX; ++j)
    {
      for (k = 0; k < ray; ++k)
      {
        img_tab[i][j] += (img_tab[i + k][j] + img_tab[i - k][j]);
      }
      img_tab[i][j] /= ((2 * ray) + 1);
    }
  }

  for (i = img->_dimY - 1; i >= img->_dimY - ray - 1; --i)
  {
    for (j = 0; j < img->_dimX; ++j)
    {
      for (k = 1; k <= ray; ++k)
      {
        img_tab[i][j] += img_tab[i - k][j];
      }
      if ((img->_dimY - i) > 1)
      {
        for (p = 1; p <= (img->_dimY - i); ++p)
          img_tab[i][j] += img_tab[i + p][j];
      }
      img_tab[i][j] /= ray + (img->_dimY - i);
    }
  }
}
void BlurrImageHorizontal(Image *img, int ray)
{
  int i, j, k, p;
  const int type = img->_type;

  int(*img_tab)[img->_dimX * type];
  img_tab = (int(*)[img->_dimX * type]) img->_img;

  for (i = 0; i < img->_dimY; ++i)
  {
    for (j = 0; j <= ray; ++j)
    {
      for (k = 1; k <= ray; ++k)
      {
        img_tab[i][j] += img_tab[i][j + k];
      }
      if (j > 0)
      {
        for (p = 1; p <= j; ++p)
          img_tab[i][j] += img_tab[i][j - p];
      }
      img_tab[i][j] /= ray + j + 1;
    }
  }

  for (i = 0; i < img->_dimY; ++i)
  {
    for (j = ray + 1; j <= img->_dimX - ray - 1; ++j)
    {
      for (k = 0; k < ray; ++k)
      {
        img_tab[i][j] += (img_tab[i][j + k] + img_tab[i][j - k]);
      }
      img_tab[i][j] /= ((2 * ray) + 1);
    }
  }

  for (i = 0; i < img->_dimY; ++i)
  {
    for (j = img->_dimX - 1; j >= img->_dimX - ray - 1; --j)
    {
      for (k = 1; k <= ray; ++k)
      {
        img_tab[i][j] += img_tab[i][j - k];
      }
      if ((img->_dimX - j) > 1)
      {
        for (p = 1; p <= (img->_dimX - j); ++p)
          img_tab[i][j] += img_tab[i][j + p];
      }
      img_tab[i][j] /= ray + (img->_dimX - j);
    }
  }
}
void NegativeImage(Image *img)
{
  int i, j, p;
  const int type = img->_type;

  int(*img_tab)[img->_dimX * type];
  img_tab = (int(*)[img->_dimX])img->_img;

  for (i = 0; i < img->_dimY; ++i)
  {
    for (j = 0; j < img->_dimX; ++j)
    {
      for (p = 0; p < type; ++p)
      {
        img_tab[i][j * type + p] = img->_shades - img_tab[i][j * type + p];
      }
    }
  }
}
void ThresholdImage(Image *img, int threshold)
{
  int i, j, p;
  const int type = img->_type;
  int(*img_tab)[img->_dimX * img->_type];
  img_tab = (int(*)[img->_dimX * img->_type]) img->_img;
  for (i = 0; i < img->_dimY; ++i)
  {
    for (j = 0; j < img->_dimX; ++j)
    {
      for (p = 0; p < type; ++p)
      {
        if (img_tab[i][j * type + p] <= (img->_shades * threshold) / 100)
          img_tab[i][j * type + p] = 0;
        else
          img_tab[i][j * type + p] = img->_shades;
      }
    }
  }
}

void ThresholdImageWhite(Image *img, int threshold)
{
  int i, j, p;
  const int type = img->_type;
  int(*img_tab)[img->_dimX * img->_type];
  img_tab = (int(*)[img->_dimX * img->_type]) img->_img;
  for (i = 0; i < img->_dimY; ++i)
  {
    for (j = 0; j < img->_dimX; ++j)
    {
      for (p = 0; p < type; ++p)
      {
        if (img_tab[i][j * type + p] > (img->_shades * threshold) / 100)
          img_tab[i][j * type + p] = img->_shades;
      }
    }
  }
}

void ThresholdImageBlack(Image *img, int threshold)
{
  int i, j, p;
  const int type = img->_type;

  int(*img_tab)[img->_dimX * img->_type];
  img_tab = (int(*)[img->_dimX * img->_type]) img->_img;

  for (i = 0; i < img->_dimY; ++i)
  {
    for (j = 0; j < img->_dimX; ++j)
    {
      for (p = 0; p < type; ++p)
      {
        if (img_tab[i][j * type + p] <= (img->_shades * threshold) / 100)
          img_tab[i][j * type + p] = 0;
      }
    }
  }
}

void ConvertToGrey(Image *img)
{

  int i, j, p, sum;
  const int type = img->_type;

  if (type != 3)
    exit(123);

  int(*img_tab)[img->_dimX * type];
  img_tab = (int(*)[img->_dimX * type]) img->_img;

  int(*tmp_tab)[img->_dimX] = (int(*)[img->_dimX * img->_type]) malloc(sizeof(int) * img->_dimX * img->_dimY);

  for (i = 0; i < img->_dimY; ++i)
  {
    for (j = 0; j < img->_dimX; ++j)
    {
      sum = 0;
      for (p = 0; p < type; ++p)
      {
        sum += img_tab[i][j * type + p];
      }
      tmp_tab[i][j] = sum / 3;
    }

    freeImageSpace(img);
    img->_type = 1;

    loadImage(img);

    for (i = 0; i < img->_dimY; ++i)
    {
      for (j = 0; j < img->_dimX; ++j)
      {
        img_tab[i][j * type + p] = tmp_tab[i][j];
      }
    }
  }
}

void GammaCorrection(Image *img, double gamma)
{
  int i, j, p;
  const int type = img->_type;
  const double numPower = 1 / gamma;
  const double denomPower = (1 - gamma) / gamma;

  int(*img_tab)[img->_dimX * type];
  img_tab = (int(*)[img->_dimX * type]) img->_img;

  for (i = 0; i < img->_dimY; ++i)
  {
    for (j = 0; j < img->_dimX; ++j)
    {
      for (p = 0; p < type; ++p)
      {
        img_tab[i][j * type + p] =
            pow(img_tab[i][j * type + p], numPower) / pow(img->_shades, denomPower);
      }
    }
  }
}

static int FindMinValue(const Image *img, int p)
{
  int i, j, min = 255;
  const int type = img->_type;

  int(*img_tab)[img->_dimX * type];
  img_tab = (int(*)[img->_dimX * type]) img->_img;

  for (i = 0; i < img->_dimY; ++i)
  {
    for (j = 0; j < img->_dimX; ++j)
    {
      if (img_tab[i][j * type + p] < min)
        min = img_tab[i][j * type + p];
    }
  }
  return min;
}

static int FindMaxValue(const Image *img, int p)
{
  int i, j, max = 0;
  const int type = img->_type;

  int(*img_tab)[img->_dimX * type];
  img_tab = (int(*)[img->_dimX * type]) img->_img;

  for (i = 0; i < img->_dimY; ++i)
  {
    for (j = 0; j < img->_dimX; ++j)
    {
      if (img_tab[i][j * type + p] > max)
        max = img_tab[i][j * type + p];
    }
  }
  return max;
}

void HistogramNormalize(Image *img)
{
  int i, j, p;
  const int type = img->_type;
  int min[type];
  int max[type];

  for (p = 0; p < type; ++p)
  {
    min[p] = FindMinValue(img, p);
    max[p] = FindMaxValue(img, p);
    printf("max:%d, min%d", max[p], min[p]);
  }
  int(*img_tab)[img->_dimX * type];
  img_tab = (int(*)[img->_dimX * type]) img->_img;

  for (i = 0; i < img->_dimY; ++i)
  {
    for (j = 0; j < img->_dimX; ++j)
    {
      for (p = 0; p < type; ++p)
      {
        img_tab[i][j * type + p] =
            (img_tab[i][j * type + p] - min[p]) * (img->_shades / (max[p] - min[p]));
      }
    }
  }
}

void ShowImage(char* fileName)
{
  char command[DL_LINII]; /* bufor pomocniczy do zestawienia polecenia */

  strcpy(command, "display "); /* konstrukcja polecenia postaci */
  strcat(command, fileName);    /* display "nazwa_pliku" &       */
  strcat(command, " &");
  printf("%s\n", command); /* wydruk kontrolny polecenia */
  system(command);
  /* wykonanie polecenia        */
  // printf("asfasfag\n");
}
