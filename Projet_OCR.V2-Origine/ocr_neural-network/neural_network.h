#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUMIN 224
#define NUMHID 300
#define NUMOUT 70

#define NUMBIAS (NUMHID+NUMOUT)
#define NB_LIENS (NUMIN*NUMHID + NUMHID*NUMOUT + NUMHID + NUMOUT)

#define ALPHA 0.1
#define BIAS -1.0
#define DAY 50
#define LIMIT 0.001

#define NBPOLICES 25
#define EX 70

struct Neurone{ //structure de formation des neurones
    double poidsSortie;
    double petitDelta;
};

struct Vecteur{ //structure de formation des exemples
    double res[NUMOUT];
    double premier[NUMIN];
};

struct Lien{ //structure de la connexion entre deux neurones
    double poids;
    double grandDelta;

    struct Neurone *from;
    struct Neurone *to;
};

//Vecteur loadExemples();
void Apprentissage(struct Neurone neuronEntree[], struct Neurone neuronCachee[], struct Neurone neuronSortie[], struct Lien *lien, struct Vecteur *vecteur[]);

void Network(struct Neurone *neuronEntree, struct Neurone *neuronCachee, struct Neurone *neuronSortie,struct Neurone *neuronBiais, struct Lien **lien, struct Vecteur **vecteur);
void FreeNetwork(struct Lien **lien, struct Vecteur **vecteur);
void calculNeurones(struct Lien *lien[], struct Neurone neuron[], int x);

void WriteFile(char *filename, char *letters[],int size);
void load(struct Lien *lien[],char *filename);
void save(struct Lien *lien[],char *filename);
void loadExemple(struct Vecteur *vect[],char *filename);
void loadImage(struct Vecteur *vect[],double **Tab,int size);
char *PrintResultat(int pos);

#endif
