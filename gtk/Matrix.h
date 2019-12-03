//
// Created by Mac Arthur on 08/10/2019.
//

#ifndef MATRIX_H
#define MATRIX_H

struct Matrix {
    int rows; // number of rows
    int cols; // number of columns
    double **data; // a pointer to an array of n_rows pointers to rows
};
typedef struct Matrix Matrix;  //structure d'une matrice


Matrix *matrix_filler(char file[]);  //remplir une matrice avec un fichier ascii
Matrix *make_matrix(int n_rows, int n_cols); // faire une matrice vide
Matrix *matrix_listing(long nbr_de_chars); //mets les matrices correspondantes aux cara dans une liste
Matrix *matrix_norm(Matrix *m); //normalise une matrice

void print_matrix(Matrix *m);
void rr_matrix(char file[]); // rotation de matrice droite format fichier texte
void lr_matrix(char file[]); // rotation de matrice gauche format fichier texte

int **linear(Matrix *list, long nbr_de_char);
void print_linear(int *list);

#endif //UNTITLED_MATRIX_H
