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
#define DL_LINII 70 




/*!
 * @brief New type for ppm pixels. Table of 3 integer values [r,g,b].
 * 
 */
typedef int ppm[3];
//optional typedef struct ppm{int _rgb[3];}ppm; 
/*!
 * @brief imgPixel
 * Union of optional types for image pixel. For PGM it is int, for PPM it is ppm.
 */
union imgPixel
{
    int _pixel;
    ppm _pixelRGB;

};
typedef struct Image{
bool _allocationFlag;
char _magickNumber[3];
int _dimX;
int _dimY;
// impPixel** _img; //future 
int _shades;
int* _img;
// char _name[50];
}Image;

//
///
///



void loadImage(Image *Img);
void freeImageSpace(Image *Img);
void printImgParamStdout(const Image Img);


int ReadFile(FILE *inputFile, Image *img);
void WriteFile(FILE *file, const Image img);
void ContureImage(Image imgInput, Image imgOutput);
void BlurrImageVertical(Image imgInput, Image imgOutput);
void BlurrImageHorizontal(Image imgInput, Image imgOutput);
void NegativeImage(Image imgInput, Image imgOutput, int ray);
void ThresholdImage(Image imgInput, Image imgOutput, int ray);