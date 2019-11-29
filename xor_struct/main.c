#include <stdio.h>
#include <stdlib.h>

#include "xor.h"

int main()
{

    struct Vecteur vect[EX];

    vect[0].premier = 1.0;
    vect[0].second  = 1.0;
    vect[0].res     = 0.0;    // XOR(1,1) = 0

    vect[1].premier = 1.0;
    vect[1].second  = 0.0;
    vect[1].res     = 1.0;   // XOR(0,0) = 0

    vect[2].premier = 0.0;
    vect[2].second  = 0.0;
    vect[2].res     = 0.0;   // XOR(0,1) = 1

    vect[3].premier = 0.0;
    vect[3].second  = 1.0;
    vect[3].res     = 1.0;   // XOR(1,0) = 1

    struct Neurone neuronEntree[NUMIN];
    struct Neurone neuronCachee[NUMHID];
    struct Neurone neuronSortie[NUMOUT];

    struct Neurone neuronBiais[NUMBIAS];
    struct Lien *lien[NB_LIENS];

    Network(neuronEntree, neuronCachee, neuronSortie, neuronBiais, lien);
    Apprentissage(neuronEntree, neuronCachee, neuronSortie, (struct Lien *) lien, vect);
    //save(lien);
    //load(lien);


        //============== Résultat Réseau ==========

    printf("XOR : \n");

    neuronEntree[0].poidsSortie = 1;
    neuronEntree[1].poidsSortie = 1;

    calculNeurones(lien, neuronCachee, 0);
    calculNeurones(lien, neuronCachee, 1);
    calculNeurones(lien, neuronSortie, 0);

    printf("1 XOR 1 = %lf\n", neuronSortie[0].poidsSortie);

    neuronEntree[0].poidsSortie = 1;
    neuronEntree[1].poidsSortie = 0;

    calculNeurones(lien, neuronCachee, 0);
    calculNeurones(lien, neuronCachee, 1);
    calculNeurones(lien, neuronSortie, 0);

    printf("1 XOR 0 = %lf\n", neuronSortie[0].poidsSortie);

    neuronEntree[0].poidsSortie = 0;
    neuronEntree[1].poidsSortie = 1;

    calculNeurones(lien, neuronCachee, 0);
    calculNeurones(lien, neuronCachee, 1);
    calculNeurones(lien, neuronSortie, 0);

    printf("0 XOR 1 = %lf\n", neuronSortie[0].poidsSortie);

    neuronEntree[0].poidsSortie = 0;
    neuronEntree[1].poidsSortie = 0;

    calculNeurones(lien, neuronCachee, 0);
    calculNeurones(lien, neuronCachee, 1);
    calculNeurones(lien, neuronSortie, 0);

    printf("0 XOR 0 = %lf\n", neuronSortie[0].poidsSortie);

    //save(lien);
    return 0;

}
