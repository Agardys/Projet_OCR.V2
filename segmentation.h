
#ifndef SEGMENTATION_H
#define SEGMENTATION_H
#include "pixel_operations.h"

double** segmentation(char image[],int *compt);
void aff(); //affiche l'image en ascii
SDL_Surface* load_image(char *path);
void ascii();  //creer n fichier avec l'ascii
int bin(char file[30]); // binarise
void lines(int a, int l); // sépare les lignes
void charac(int a, int l, char file[], int min); // sépare les char
void all_chars();

#endif //UNTITLED_MATRIX_H