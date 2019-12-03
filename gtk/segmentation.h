
#ifndef SEGMENTATION_H
#define SEGMENTATION_H

int** segmentation(char image[]);
void aff(); //affiche l'image en ascii
void ascii();  //creer n fichier avec l'ascii
int bin(char file[30]); // binarise
void lines(int a, int l); // sépare les lignes
void charac(int a, int l, char file[]); // sépare les char
void all_chars();

#endif //UNTITLED_MATRIX_H