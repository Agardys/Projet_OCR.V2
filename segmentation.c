#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matrix.h"
#include "segmentation.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include <err.h>

//globals;

long nbr_de_lignes = 0, nbr_de_chars = 1;


double** segmentation(char image[],int *compt) {

    ascii(image);                         // 1 et 2 : représente en ascii en faisant la moyenne des couleurs pour binariser
    lines(1, 0);                // 3 : découpe les lignes
    all_chars();
    nbr_de_chars-=1;                     // 4 : découpe les caractères
    //printf("nbr %d : ",nbr_de_chars);
    Matrix *list = matrix_listing(nbr_de_chars); // 5 : crée des matrices avec les caractères et en fait une liste
    double **linear_list= linear(list, nbr_de_chars); //6 : liste les matrices linéarisées
    //dernier nombre de chaque matrice linéarisée = option -> 0= rien 1= espaces (avant) 2= retour à la ligne (avant) 
    //si matrice vide (que des 0) sauf l'option : mettre caractere vide : ''
    for (int j = 0; j < nbr_de_chars; ++j) // affiche tous les caractères en ascii art
    {
       print_matrix(&list[j]);
       printf("\n");



    }
  /*for (int j = 0; j < nbr_de_chars; ++j) // affiche les matrices linéarisées
    {
       print_linear(linear_list[j]);
       printf("\n");



    }*/
    


   printf("\n /!\\ option : 0-> rien; 1-> espace (avant); 2-> retour à la ligne (avant)" );
    printf("\n \n \n *** end of segmentation  ***    \n  *** end of linearisation *** \n   *** end of image treatment ***\n");

    char n_str[10];
    sprintf(n_str, "%ld", nbr_de_chars+1);
    char name[1000] = "char";
    strcat(name, n_str);
    strcat(name, ".txt");

    remove(name); //supprimer le dernier fichier txt
    remove("res.bmp");
    remove("ascii.txt");
    free(list);
    *compt = nbr_de_chars;
    return linear_list;
}

SDL_Surface* load_image(char *path)
{
    SDL_Surface *img;

    // Load an image using SDL_image with format detection.
    // If it fails, die with an error message.
    img = IMG_Load(path);
    if (!img)
        errx(3, "can't load %s: %s", path, IMG_GetError());

    return img;
}



void all_chars() {
    for (int i = 1; i <= nbr_de_lignes; ++i) {
        char n_str[11] = "";
        sprintf(n_str, "%d", i);
        char name[1000] = "line";
        strcat(name, n_str);
        printf("working on : ");
        puts(name);
        strcat(name, ".txt");
        rr_matrix(name);
        charac(nbr_de_chars, 0, name, 0);
    }
}

int bin(char file[30]) {  /* binarise une image bmp*/ FILE *fp, *res;
    int ch;
    int ch2;
    int ch3;
    //int ch4;
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
                    if (ch3 != EOF) {
                        moy = (ch +ch2 + ch3 ) / 3;
                        if (moy >
                            135)     /* on prend 4 octet (X:R:V:B) et on vérifie que la moyenne soit sup a 127 pour mettre tt en blanc ou pas*/ {
                            fputc(255, res);
                            fputc(255, res);
                            fputc(255, res);
                            //fputc(255, res);
                        }
                        else {
                            fputc(0, res);
                            fputc(0, res);
                            fputc(0, res);
                            //fputc(0, res);
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


void ascii(char file[30])   /* creer un fichier txt avec l'ascii de l'image binarisée*/ {
    FILE *fp, *fp2;
    SDL_Surface* image_surface = NULL;
    fp = fopen(file, "rb");
    fp2 = fopen("ascii.txt", "wb");
    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    fclose(fp);
    image_surface = load_image(file);
    int width = image_surface->w;
    int height = image_surface->h;
    

    int x = 0;
    int y = 0;
    while(y < height)
    {
        x =0;
        while(x < width)
        {
            Uint32 pixel = get_pixel(image_surface, x, y);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            
            int average = (int)(r + g + b)/3;
            if (average < 135)
                fputc('0',fp2);
            else
                fputc(' ',fp2);
            x++;
            
            
        }
        y++;
        if(y < height)
            fputc('\n',fp2);
    }
    fclose(fp2);
    SDL_FreeSurface(image_surface);
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
    int boolz = 0;
    fseek(fp, l, SEEK_SET);
    int i = 0;
    while ((ch = fgetc(fp)) != EOF && ch != '0') {
        i++;
        if (ch == '\n') { i = 0; }
    }
   // fseek(fp, -1, SEEK_CUR);
    while (ch != EOF && boolz != 1) {
        while (i > 0) {
            i--;
            fputc(' ', res);
        }
        boolz = 1;
        while (ch != EOF && ch != '\n') { /* printf("%d \n",ch);*/ ch = fgetc(fp);
            if (ch == ' ') { fputc(' ', res); }
            if (ch == '0') {
                fputc('0', res);
                boolz = 0;
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





void charac(int a, int l, char file[],int min)  /* sépare les char*/ { // min = séparation minimum entre 2 charactères
   
    FILE *fp, *res;                                                                
    fp = fopen(file, "r");
    char n_str[10];
    sprintf(n_str, "%d", a);
    char name[1000] = "char";
    strcat(name, n_str);
    strcat(name, ".txt");
    res = fopen(name, "w");
    char ch;
    int boolean = 0;
    fseek(fp, l, SEEK_SET);
    int i = 0;
    int i2 = 0;
 
    char option = '1';   // option : '0' -> rien ; '1' -> espace ; '2' -> retour à la ligne

    while ((ch = fgetc(fp)) != EOF && ch != '0') {
        i++;
        if (ch == '\n') { i = 0; i2+=1; }
    }

    if (l > 0 && min == 0 ) min = i2;
    if (i2 > min) option = '0';
    if (l==0) option ='2';
    fseek(fp, -1, SEEK_CUR);
    while (ch != EOF && boolean == 0) 
    {
        while (i > 1) {
            fputc(' ', res);
            i--;
        }
        boolean = 1;
        while (ch != EOF && ch != '\n') {ch = fgetc(fp);
            if (ch == ' ') { fputc(' ', res); }
            if (ch == '0') {
                fputc('0', res);
                boolean = 0;
            }
        }
        fputc('\n', res);
        ch = fgetc(fp);
    }
    while ((ch = fgetc(fp)) != EOF && ch != '\n') {
        
    }
    if (ch != EOF) {

        nbr_de_chars += 1;
    
    fputc(option, res);
    charac(nbr_de_chars, ftell(fp), file,min); /* rajouter en parm l'emplacement ou on est*/ }
    fclose(fp);
    fclose(res);
    lr_matrix(name); /* remet droit le caractère*/ 
    remove(file); /*detruit le fichier avec la ligne*/ }





