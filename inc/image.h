# pragma once


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>




struct Image {
int _dimY;
int _DimX;
int _Img[1024][1024];
int _Shades;
};



void InitImage(int DimY, int DimX, int Sh);