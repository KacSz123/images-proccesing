#pragma once

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include "image.h"
#define MAX 1024            /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII2 100      /* Dlugosc buforow pomocniczych */

/************************************************************************************
 * Funkcja wczytuje obraz PGM z pliku do tablicy       	       	       	       	    *
 *										                                            *
 * \param[in] plik_we uchwyt do pliku z obrazem w formacie PGM			            *
 * \param[out] obraz_pgm tablica, do ktorej zostanie zapisany obraz		            *
 * \param[out] wymx szerokosc obrazka						                        *
 * \param[out] wymy wysokosc obrazka						                        *
 * \param[out] szarosci liczba odcieni szarosci					                    *
 * \return liczba wczytanych pikseli						                        *
 ************************************************************************************/

int czytaj(FILE *plik_we, int obraz_pgm[MAX][MAX], int *wymx,int *wymy, int *szarosci); 


/* Wyswietlenie obrazu o zadanej nazwie za pomoca programu "display"   */
void wyswietl(char *n_pliku); 
/**
 * @brief 
 * 
 * @param[in] fp 
 * @param obraz_pgm 
 * @param wymx 
 * @param wymy 
 * @param szarosci 
 * @param nazwa 
 * @return int 
 */
int zapisz(FILE *fp,  int obraz_pgm[MAX][MAX],const int wymx,const int wymy, const int szarosci, char* nazwa);
void Negatyw(int (*obraz_pgm)[MAX][MAX],const int wymx, const int wymy,  int szarosci);
void Konturowanie(int (*o_pgm)[MAX][MAX], const int wymx, const int wymy); 
void Progowanie(int (*o_pgm)[MAX][MAX], const int wymx, const int wymy, const int szarosci, const int prog);
void Rozmycie_pion(int (*o_pgm)[MAX][MAX], const int wymx, const int wymy, const int promien);
void Rozmycie_poz(int (*o_pgm)[MAX][MAX], const int wymx, const int wymy, const int promien);