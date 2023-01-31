/**
 * @file image.h
 * @author Kaper Szczepanowski kacperszcz159@gmail.com
 * @brief 
 * @version 0.3
 * @date 2022-10-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
typedef enum ErroType{FILE_ERROR, OTHER_ERROR};

typedef int ppm[3];
//optional typedef struct ppm{int _rgb[3];}ppm; 
union imgPixel
{
    int _pixel;
    ppm _pixelRGB;

};
typedef struct Image{

char _magickNumber[2];
int _dimY;
int _dimX;
//future impPixel** _img;
int** _img;
int _shades;
char* _name;
}Image;

//
///
///

inline void LoadImage(Image *Img)
{
    Img=(Image*)malloc(sizeof(Img));
    Img->_img=(int**)malloc(sizeof(int)*(Img->_dimX)*(Img->_dimY));
}
inline void FreeImageSpace(Image *Img)
{
    free(Img->_name);
    free(Img);
}
////////
// bool a = true;
/*!
 * @brief 
 * 
 * @param file 
 * @param Img 
 * @return int 
 */
int ReadFile(FILE *file, Image *Img);
void WriteFile(FILE *file, const Image Img);
void ContureImage(Image ImgInput, Image ImgOutput);
void BlurrImageVertical(Image ImgInput, Image ImgOutput);
void BlurrImageHorizontal(Image ImgInput, Image ImgOutput);
void NegativeImage(Image ImgInput, Image ImgOutput, int Ray);
void ThresholdImage(Image ImgInput, Image ImgOutput, int Ray);