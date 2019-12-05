//
// Created by Mac Arthur on 08/10/2019.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Matrix.h"

Matrix *matrix_norm(Matrix *m) {
    int column_size = 15;
    int line_size = 15;
    int x = 0;
    int y = 0;
    Matrix *norm = make_matrix(column_size, line_size);
    for (int i = 0; i < m->rows; ++i) {
        if (i >= m->rows * (x) / column_size) {
            for (int j = 0; j < m->cols; ++j) {
                if (j >= m->cols * (y + 1) / line_size) {
                    norm->data[x][y] = m->data[i][j];
                    y++;
                }
            }
            x++;
            y = 0;
        }
    }
    norm->data[norm->rows-1][norm->cols-1] = m->data[m->rows-1][m->cols-1];

    //free(m);
    return norm;
}

Matrix *make_matrix(int n_rows, int n_cols) {
    struct Matrix *matrix = malloc(sizeof(Matrix));
    matrix->rows = n_rows;
    matrix->cols = n_cols;
    double **data = malloc(sizeof(long double *) * n_rows);
    for (int x = 0; x < n_rows; x++) { data[x] = calloc(n_cols, sizeof(long double)); }
    matrix->data = data;
    return matrix;
}


void print_matrix(Matrix *m) {
    for (int x = 0; x < m->rows; x++) {
        printf("\n");
        for (int y = 0; y < m->cols; y++) { if (m->data[x][y] == 1) { printf("#"); } else { printf("."); }}
    }
    printf("--> option : %d",(int)m->data[m->rows-1][m->cols-1]);

}

Matrix *matrix_filler(char file[]) {
    
    FILE *fp = fopen(file, "r");
    unsigned long nbr_cars = 0;
    unsigned long nbr_lignes = 0;
    char ch;
    while ((ch = fgetc(fp)) != EOF) { if (ch == '\n') { nbr_lignes++; } else { nbr_cars += 1; }}
    if (nbr_lignes>0) nbr_cars /= nbr_lignes;
    Matrix *mat = make_matrix(nbr_lignes, nbr_cars);
    rewind(fp);
    int x = 0;
    int y = 0;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            y += 1;
            x = 0;
        }
       else if (ch == ' ') {
            mat->data[y][x] = 0;
            x += 1;
        }
        else if (ch == '0') {
            mat->data[y][x] = 1;
            x += 1;
        }

        else if (ch == '1') {
            mat->data[y][x] = 0;
            x += 1;
        }
        else if (ch == '2') {
            mat->data[y][x] = 2;
            x += 1;
        }


    }
    fseek(fp, -1, SEEK_CUR);
    mat->data[y-1][nbr_cars] = fgetc(fp) ;
    fclose(fp);
   // print_matrix(mat);
    remove(file); /*detruit le fichier avec le char*/ 
    return mat;
}



void rr_matrix(char file[]) {
    FILE *fp, *rotate;
    fp = fopen(file, "r");
    rotate = fopen("rot.txt", "w");
    char ch;
    int nbr_char = 0;
    int nbr_lignes = 0;
    while ((ch = fgetc(fp)) != EOF) { if (ch == '\n') { nbr_lignes++; }}
    nbr_lignes += 1;
    rewind(fp);
    while ((ch = fgetc(fp)) != EOF && ch != '\n') {
        nbr_char++; /*printf(ch); printf('\n'); fputc(ch,rotate);*/ int n = 0;
        while (n < nbr_lignes) {
            fputc(' ', rotate);
            n++;
        }
        fputc('\n', rotate);
    }
    rewind(fp);
    int i = 1;
    int i2 = 1;
    while ((ch = fgetc(fp)) != EOF) {
        i2++;
        if (ch == '\n') { /*fputc(ch,rotate);*/ i++;
            i2 = 0; /* printf("----------------------------- \n \n");*/ }
        else {
            int index = i2 * (nbr_lignes + 1) - i - 1; /* printf("%d \n",index);*/ fseek(rotate, index, SEEK_SET);
            fputc(ch, rotate);
        }
    }
    fclose(fp);
    fclose(rotate);
    remove(file);
    rename("rot.txt", file);
}

void lr_matrix(char file[]) {
    FILE *fp, *rotate;
    fp = fopen(file, "r");
    rotate = fopen("rot.txt", "w");
    char ch;
    int nbr_char = 0;
    int nbr_lignes = 0;
    while ((ch = fgetc(fp)) != EOF) { if (ch == '\n') { nbr_lignes++; }}
    nbr_lignes += 1;
    rewind(fp);
    while ((ch = fgetc(fp)) != EOF && ch != '\n') {
        nbr_char++;
        int n = 0;
        while (n < nbr_lignes) {
            fputc(' ', rotate);
            n++;
        }
        fputc('\n', rotate);
    }
    rewind(fp);
    int i = 0;
    int i2 = 0;
    while ((ch = fgetc(fp)) != EOF) {
        i2++;
        if (ch == '\n') {
            i++;
            i2 = 0;
        }
        else {
            int index = ((nbr_char - i2) * (nbr_lignes) + i - i2) + nbr_char;
            fseek(rotate, index, SEEK_SET);
            fputc(ch, rotate);
        }
    }
    fclose(fp);
    fclose(rotate);
    remove(file);
    rename("rot.txt", file);
}

Matrix *matrix_listing(long nbr_de_chars) {
    Matrix *list = malloc(nbr_de_chars * sizeof(Matrix));
    for (int i = 1; i <= nbr_de_chars; ++i) {
        char n_str[300] = "";
        sprintf(n_str, "%d", i);
        char name[1000] = "char";
        strcat(name, n_str);
        strcat(name, ".txt");
        list[i - 1] = *matrix_norm(matrix_filler(name)); // renvoie la matrice normaliser de la matrice remplie par la fonction filler du fichier "name"
	
    }
    char n_str[300] = "";
    sprintf(n_str, "%ld", nbr_de_chars+1);
    char name[1000] = "char";
    strcat(name, n_str);
    strcat(name, ".txt");
    return list;
}

int check_matrix(Matrix *m) {
    
    for (int x = 0; x < m->rows; x++) {
        for (int y = 0; y < m->cols; y++) { if (m->data[x][y] == 1) { return 1; }}
    }
    return 1;
}

double **linear(Matrix *list, long nbr_de_char) {
    double **res = calloc(sizeof(double*),nbr_de_char);
    int size = (list[0].rows) * (list[0].cols);
    long p=-1;
    for (int i = 0; i < nbr_de_char; ++i) {


        double *line = calloc(sizeof(unsigned long  long),size);
        Matrix *m = &list[i];
        if (check_matrix(m))
        {
        
        int j = 0;
        for (int x = 0; x < m->rows; x++) {
            for (int y = 0; y < m->cols; y++) {
                line[j] = (double)m->data[y][x];
                j += 1;
            }

        }
            p++;
            //printf("%ld\n",i);
            res[p] = line;
        }
        //print_linear(line);

        //free(line);
        //free(m);
        
    }
    //printf("number of characters : %ld\n",p+1 );
    res[p+1]=NULL;
    
    return res;
}

void print_linear(double* list)
{
        for (int j = 0; j < (15*15) ; j++) //limited at 100 for the print because more would be useless
        {
            printf("%f",(list[j]));
           //if(j%15==0){printf("\n");}

        }
}


