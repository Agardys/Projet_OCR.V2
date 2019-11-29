#ifndef XOR_H
#define XOR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUMIN 100
#define NUMHID 150
#define NUMOUT 4

#define NUMBIAS 154
#define NB_LIENS (NUMIN*NUMHID + NUMHID*NUMOUT + NUMHID + NUMOUT)

#define ALPHA 0.1
#define BIAS -1.0
#define DAY 300
#define LIMIT 0.001

#define EX 4

struct Neurone{ //structure de formation des neurones
    double poidsSortie;
    double petitDelta;
};

struct Vecteur{ //structure de formation des exemples
    double *res;
    double *premier;
};

struct Lien{ //structure de la connexion entre deux neurones
    double poids;
    double grandDelta;

    struct Neurone *from;
    struct Neurone *to;
};

void Apprentissage(struct Neurone neuronEntree[], struct Neurone neuronCachee[], struct Neurone neuronSortie[], struct Lien *lien, struct Vecteur vecteur[]);

void Network(struct Neurone *neuronEntree, struct Neurone *neuronCachee, struct Neurone *neuronSortie,struct Neurone *neuronBiais, struct Lien **lien);
void calculNeurones(struct Lien *lien[], struct Neurone neuron[], int x);

void load(struct Lien *lien[]);
void save(struct Lien *lien[]);

#endif
