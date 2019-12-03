#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matrix.h"
#include "segmentation.h"




//globals;

long nbr_de_lignes = 0, nbr_de_chars = 1;


int** segmentation(char image[]) {
    bin(image);               // 1 : binarise
    ascii();                         // 2 : représente en ascii le fichier en noire & blanc
    lines(1, 0);                // 3 : découpe les lignes
    all_chars();                     // 4 : découpe les caractères
    //printf("nbr %d : ",nbr_de_chars);
    Matrix *list = matrix_listing(nbr_de_chars); // 5 : crée des matrices avec les caractères et en fait une liste
    int **linear_list= linear(list, nbr_de_chars);

    for (int j = 0; j < nbr_de_chars; ++j) // affiche tous les caractères en ascii art
    {
       print_matrix(&list[j]);
       printf("\n");



    }
    size_t j =0;
        while(linear_list[j])
        {          
           print_linear(linear_list[j]);
           printf("\n");  
           j++;
        }



    printf("*** end of linearisation ***    \n*** fin du traitement d'image *** \n");

    remove("res.bmp");
    remove("ascii.txt");
    return linear_list;
}









void all_chars() {
    for (int i = 1; i <= nbr_de_lignes; ++i) {
        char n_str[3] = "";
        sprintf(n_str, "%d", i);
        char name[1000] = "line";
        strcat(name, n_str);
        printf("working on : ");
        puts(name);
        strcat(name, ".txt");
        rr_matrix(name);
        charac(nbr_de_chars, 0, name);
    }
}

int bin(char file[30]) {  /* binarise une image bmp*/ FILE *fp, *res;
    int ch;
    int ch2;
    int ch3;
    int ch4;
    fp = fopen(file, "rb"); /* read mode*/ res = fopen("res.bmp", "wb");
    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    int moy;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {} else { i++; }
        if (i > 54)  /* nombre exact d'octet a by pass = 54 car on est en 32 bit      c.f format bmp*/ {
            if ((ch2 = fgetc(fp)) != EOF) {
                if ((ch3 = fgetc(fp)) != EOF) {
                    if ((ch4 = fgetc(fp)) != EOF) {
                        moy = (ch2 + ch3 + ch4) / 4;
                        if (moy >
                            135)     /* on prend 4 octet (X:R:V:B) et on vérifie que la moyenne soit sup a 127 pour mettre tt en blanc ou pas*/ {
                            fputc(255, res);
                            fputc(255, res);
                            fputc(255, res);
                            fputc(255, res);
                        }
                        else {
                            fputc(0, res);
                            fputc(0, res);
                            fputc(0, res);
                            fputc(0, res);
                        }
                    }
                }
            }
        }
        else { fputc(ch, res); }
    }
    fclose(fp);
    fclose(res);
    return 0;
}

void aff()  /* affiche en console l'ascii de l'image binariser*/ {
    FILE *fp;
    int ch;
    int ch2;
    int ch3;
    int ch4;
    int moy;
    fp = fopen("res.bmp", "rb");
    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    int size = 1;
    while ((ch = fgetc(fp)) != EOF) {
        i++;
        if (i == 19) {
            int t = fgetc(fp);
            i++; /* printf("%d",ch+t*256); printf("\n");*/ size = ch + t *
                                                                       256;  /* 4 octet alouer a la largeur de l'image  les (18-22)eme octets calcul qui permet d'avoir la taille de l'image en pixels*/ }
        if (i > 54) { /*printf("  i : %d  -> "  , i );*/ if (i % size * 4 == 0) { printf("\n"); } else {}
            if ((ch2 = fgetc(fp)) != EOF) {
                if ((ch3 = fgetc(fp)) != EOF) {
                    if ((ch4 = fgetc(fp)) != EOF) {
                        moy = (ch + ch2 + ch3 + ch4) / 4;
                        if (moy == 0) { printf("0"); } else { printf(" "); }
                    }
                }
            }
        }
    }
    fclose(fp);
}


void ascii()   /* creer un fichier txt avec l'ascii de l'image binarisée*/ {
    FILE *fp, *fp2;
    int ch;
    int ch2;
    int ch3;
    int ch4;
    int moy;
    fp = fopen("res.bmp", "rb");
    fp2 = fopen("ascii.txt", "wb");
    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    int size = 1;
    while ((ch = fgetc(fp)) != EOF) {
        i++;
        if (i == 19) {
            int t = fgetc(fp);
            i++; /* printf("%d",ch+t*256); printf("\n");*/ size = ch+t *256;  /* 4 octet alouer a la largeur de l'image  les (18-22)eme octets calcul qui permet d'avoir la taille de l'image en pixels*/ }
        if (i > 54) { /*printf("  i : %d  -> "  , i );*/ 
            if ((ch2 = fgetc(fp)) != EOF) {
                if ((ch3 = fgetc(fp)) != EOF) {
                    if ((ch4 = fgetc(fp)) != EOF) {
                        moy = (ch + ch2 + ch3 + ch4) / 4;
                        if (moy == 0) { fputc('0', fp2); } else { fputc(' ', fp2); }
                    }
                }
            }
            if ((i-54) % size * 4 == 0) { fputc('\n', fp2); }
        }
    }
    fclose(fp);
}

void lines(int a, int l)  /* sépare les lignes*/ {
    FILE *fp, *res;
    fp = fopen("ascii.txt", "r");
    char n_str[10];
    sprintf(n_str, "%d", a);
    char name[1000] = "line";
    strcat(name, n_str);
    strcat(name, ".txt");
    res = fopen(name, "w");
    char ch;
    int bool = 0;
    fseek(fp, l, SEEK_SET);
    int i = 0;
    while ((ch = fgetc(fp)) != EOF && ch != '0') {
        i++;
        if (ch == '\n') { i = 0; }
    }
    while (ch != EOF && bool < 2) {
        while (i > 0) {
            i--;
            fputc(' ', res);
        }
        bool += 1;
        while (ch != EOF && ch != '\n') { /* printf("%d \n",ch);*/ ch = fgetc(fp);
            if (ch == ' ') { fputc(' ', res); }
            if (ch == '0') {
                fputc('0', res);
                bool = 0;
            }
        }
        fputc('\n', res);
        ch = fgetc(fp);
    }
    if (ch != EOF) {
        nbr_de_lignes += 1;
        lines(a + 1, ftell(fp)); /* rajouter en parm l'emplacement ou on est*/ } else remove(name);
    fclose(fp);
    fclose(res);
}





void charac(int a, int l, char file[])  /* sépare les char*/ {
    FILE *fp, *res;
    fp = fopen(file, "r");
    char n_str[10];
    sprintf(n_str, "%d", a);
    char name[1000] = "char";
    strcat(name, n_str);
    strcat(name, ".txt");
    res = fopen(name, "w");
    char ch;
    int bool = 0;
    fseek(fp, l, SEEK_SET);
    int i = 0;
    while ((ch = fgetc(fp)) != EOF && ch != '0') {
        i++;
        if (ch == '\n') { i = 0; }
    }
    while (ch != EOF && bool < 1) {
        while (i > 0) {
            fputc(' ', res);
            i--;
        }
        bool += 1;
        while (ch != EOF && ch != '\n') { /* printf("%d \n",ch);*/ ch = fgetc(fp);
            if (ch == ' ') { fputc(' ', res); }
            if (ch == '0') {
                fputc('0', res);
                bool = 0;
            }
        }
        fputc('\n', res);
        ch = fgetc(fp);
    }
    if (ch != EOF) {
        nbr_de_chars += 1;
        charac(nbr_de_chars, ftell(fp), file); /* rajouter en parm l'emplacement ou on est*/ }
    fclose(fp);
    fclose(res);
    lr_matrix(name); /* remet droit le caractère*/ remove(file); /*detruit le fichier avec la ligne*/ }







