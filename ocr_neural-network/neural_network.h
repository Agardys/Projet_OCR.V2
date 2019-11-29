#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUMIN 224
#define NUMHID 300
#define NUMOUT 68

#define NUMBIAS (NUMHID+NUMOUT)
#define NB_LIENS (NUMIN*NUMHID + NUMHID*NUMOUT + NUMHID + NUMOUT)

#define ALPHA 0.1
#define BIAS -1.0
#define DAY 300
#define LIMIT 0.001

#define EX 68

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
void calculNeurones(struct Lien *lien[], struct Neurone neuron[], int x);

void load(struct Lien *lien[]);
void save(struct Lien *lien[]);
void loadExemple(struct Vecteur *vect[],char *filename);
void PrintResultat(int pos);

#endif
