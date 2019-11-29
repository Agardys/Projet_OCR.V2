#include <stdio.h>
#include <stdlib.h>

#include "xor.h"

int main()
{

    struct Vecteur vect[EX];

    double my1[2] = {1.0,1.0};
    vect[0].premier = my1;
    vect[0].res = 0.0;    // XOR(1,1) = 0

    double my2[2] = {0.0,0.0};
    vect[1].premier = my2;
    vect[1].res = 0.0;   // XOR(0,0) = 0

    double my3[2] = {0.0,1.0};
    vect[2].premier = my3;
    vect[2].res = 1.0;   // XOR(0,1) = 1

    double my4[2] = {1.0,0.0};
    vect[3].premier = my4;
    vect[3].res = 1.0;   // XOR(1,0) = 1

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

    printf("OCR : \n");

    neuronEntree[0].poidsSortie = 1;
    neuronEntree[1].poidsSortie = 1;

    /*calculNeurones(lien, neuronCachee, 0);
    calculNeurones(lien, neuronCachee, 1);
    calculNeurones(lien, neuronSortie, 0);*/

    for(int i = 0;i<NUMHID;i++)
        calculNeurones(lien, neuronCachee, i);

    for(int i = 0;i<NUMOUT;i++)
    {
        calculNeurones(lien, neuronSortie, i);
        printf("1 XOR 1 = %lf\n", neuronSortie[i].poidsSortie);
    }



    neuronEntree[0].poidsSortie = 1;
    neuronEntree[1].poidsSortie = 0;

    /*calculNeurones(lien, neuronCachee, 0);
    calculNeurones(lien, neuronCachee, 1);
    calculNeurones(lien, neuronSortie, 0);*/

    for(int i = 0;i<NUMHID;i++)
        calculNeurones(lien, neuronCachee, i);

    for(int i = 0;i<NUMOUT;i++)
    {
        calculNeurones(lien, neuronSortie, i);
        printf("1 XOR 0 = %lf\n", neuronSortie[i].poidsSortie);
    }



    neuronEntree[0].poidsSortie = 0;
    neuronEntree[1].poidsSortie = 1;

    for(int i = 0;i<NUMHID;i++)
        calculNeurones(lien, neuronCachee, i);

    for(int i = 0;i<NUMOUT;i++)
    {
        calculNeurones(lien, neuronSortie, i);
        printf("0 XOR 1 = %lf\n", neuronSortie[i].poidsSortie);
    }



    neuronEntree[0].poidsSortie = 0;
    neuronEntree[1].poidsSortie = 0;

    for(int i = 0;i<NUMHID;i++)
        calculNeurones(lien, neuronCachee, i);

    for(int i = 0;i<NUMOUT;i++)
    {
        calculNeurones(lien, neuronSortie, i);
        printf("0 XOR 0 = %lf\n", neuronSortie[i].poidsSortie);
    }



    //save(lien);
    return 0;

}
