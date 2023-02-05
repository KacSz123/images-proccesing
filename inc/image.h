/*!
 * @file image.h
 * @author Kaper Szczepanowski kacperszcz159@gmail.com
 * @brief File contains definition of Image structure and image proccesing functions. 
 * @version 0.3
 * @date 2022-10-06
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#define DL_LINII 70

/*!

 * @brief 
 * New type for Image structure
 * @typedef Image
 */
/*!
 * @struct Image 
 * @brief This structure ...
 * @var Image::_allocationFlag 
 * Flag for status of memory allocation: true if Image::*_img allocated, false if  Image::*_img not allocated.
 * @var Image::_type
 * Describes type of image: 1 for PGM img or 3 for PPM.
 * @var Image::_dimX
 * Width of image.
 * @var Image::_dimY
 * Height of image.
 * @var Image::_shades
 * Value of maximum shades.
 * @var Image::_img 
 *  Pointer for dynamic allocated pixels.
 */
typedef struct Image
{
    bool _allocationFlag;
    int _type;
    int _dimX;
    int _dimY;
    int _shades;
    void *_img;

}Image;

/*!
 * @typedef IMG_ERRORS
 * @brief Enumeration of image proccesing errors.
 * @var IMG_NO_ERROR 
 * [0] No error occured.
 * @var DIM_ERROR 
 * [1] Wrong dimensions error.
 * @var PARAMETER_ERROR 
 * [2] Incorrect function parameter.
 * 
 */
typedef enum{IMG_NO_ERROR,DIM_ERROR,PARAMETER_ERROR}IMG_ERRORS; 

/*!
 * @brief Read data from  FILE handler and write to structure of image.
 * 
 * @param[in] inputFile FILE handler
 * @param[out] img Pointer to structure describing the image in memory.
 * @return[int] operation status
 */
int ReadFile(FILE *inputFile, Image *img);


/*!
 * @brief 
 * Write data from image object to output file  
 * @param[out] file FILE handler 
 * @param[in] img constant object of image in memory
 */
void WriteFile(FILE *file, const Image img);



/*!
 * @brief 
 * 
 * @param Img 
 */
void loadImage(Image *Img);

/*!
 * @brief 
 * 
 * @param[out] Img 
 */
void freeImageSpace(Image *Img);

/*!
 * @brief 
 * 
 * @param[in] Img 
 */
void printImgParamStdout(const Image Img);


/*!
 * @brief 
 * 
 * @param[out] img 
 */
void ContureImage(Image *img);

/*!
 * @brief 
 * 
 * @param[out] img 
 * @param[in] ray 
 */
void BlurrImageVertical(Image *img, int ray);


/*!
 * @brief 
 * 
 * @param[out] img 
 * @param[in] ray 
 */
void BlurrImageHorizontal(Image *img, int ray);


/*!
 * @brief 
 * 
 * @param[out] img 
 */
void NegativeImage(Image *img);


/*!
 * @brief 
 * 
 * @param[out] img 
 * @param[in] threshold 
 */
void ThresholdImage(Image *img, int threshold);



void ThresholdImageWhite(Image *img, int threshold);

void ThresholdImageBlack(Image *img, int threshold);

/*!
 * @brief Convertion colour Image .ppm to grey image .pgm.
 * 
 * @param[out] img 
 */
void ConvertToGrey(Image *img);


void GammaCorrection(Image *img, double gamma);


void HistogramNormalize(Image *img);

void ShowImage(char *fileName);