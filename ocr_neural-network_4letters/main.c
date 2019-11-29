#include <stdio.h>
#include <stdlib.h>

#include "xor.h"

int main()
{

    struct Vecteur vect[EX];

    double my1pr[100] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,1.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,1.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,1.0,1.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,1.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,1.0,0.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0,1.0,1.0,0.0,0.0,0.0};
    double my1re[4] = {1.0,0.0,0.0,0.0};
    vect[0].premier = my1pr;
    vect[0].res = my1re;    // LETTRE(1,0,0,0)

    double my2pr[100] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,0.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,1.0,1.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0};
    double my2re[4] = {0.0,1.0,0.0,0.0};
    vect[1].premier = my2pr;
    vect[1].res = my2re;   // LETTRE(0,1,0,0)

    double my3pr[100] = {0.0,0.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0,1.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.0,0.0,1.0,1.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,1.0,1.0,0.0,1.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,1.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
    double my3re[4] = {0.0,0.0,1.0,0.0};
    vect[2].premier = my3pr;
    vect[2].res = my3re;   // LETTRE(0,0,1,0)

    double my4pr[100] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,0.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
    double my4re[4] = {0.0,0.0,0.0,1.0};
    vect[3].premier = my4pr;
    vect[3].res = my4re;   // LETTRE(0,0,0,1)

    struct Neurone neuronEntree[NUMIN];
    struct Neurone neuronCachee[NUMHID];
    struct Neurone neuronSortie[NUMOUT];

    struct Neurone neuronBiais[NUMBIAS];
    struct Lien *lien[NB_LIENS];

    printf("ici\n");

    Network(neuronEntree, neuronCachee, neuronSortie, neuronBiais, lien);
    Apprentissage(neuronEntree, neuronCachee, neuronSortie, (struct Lien *) lien, vect);
    //save(lien);
    //load(lien);


    //============== Résultat Réseau ==========

    printf("OCR : \n");
    printf("Test A : \n");

    for(int i = 0;i<NUMIN;i++)
        neuronEntree[i].poidsSortie = vect[0].premier[i];

    for(int i = 0;i<NUMHID;i++)
        calculNeurones(lien, neuronCachee, i);

    for(int i = 0;i<NUMOUT;i++)
    {
        calculNeurones(lien, neuronSortie, i);
        printf("A = %lf\n", neuronSortie[i].poidsSortie);
    }

    /*calculNeurones(lien, neuronSortie, 0);
    printf("A = %lf\n", neuronSortie[0].poidsSortie);
    calculNeurones(lien, neuronSortie, 1);
    printf("B = %lf\n", neuronSortie[1].poidsSortie);
    calculNeurones(lien, neuronSortie, 2);
    printf("C = %lf\n", neuronSortie[2].poidsSortie);
    calculNeurones(lien, neuronSortie, 3);
    printf("D = %lf\n", neuronSortie[3].poidsSortie);*/


    printf("Test B : \n");

    for(int i = 0;i<NUMIN;i++)
        neuronEntree[i].poidsSortie = vect[1].premier[i];

    for(int i = 0;i<NUMHID;i++)
        calculNeurones(lien, neuronCachee, i);

    for(int i = 0;i<NUMOUT;i++)
    {
        calculNeurones(lien, neuronSortie, i);
        printf("B = %lf\n", neuronSortie[i].poidsSortie);
    }

    /*calculNeurones(lien, neuronSortie, 0);
    printf("A = %lf\n", neuronSortie[0].poidsSortie);
    calculNeurones(lien, neuronSortie, 1);
    printf("B = %lf\n", neuronSortie[1].poidsSortie);
    calculNeurones(lien, neuronSortie, 2);
    printf("C = %lf\n", neuronSortie[2].poidsSortie);
    calculNeurones(lien, neuronSortie, 3);
    printf("D = %lf\n", neuronSortie[3].poidsSortie);*/


    printf("Test C : \n");

    for(int i = 0;i<NUMIN;i++)
        neuronEntree[i].poidsSortie = vect[2].premier[i];

    for(int i = 0;i<NUMHID;i++)
        calculNeurones(lien, neuronCachee, i);

    for(int i = 0;i<NUMOUT;i++)
    {
        calculNeurones(lien, neuronSortie, i);
        printf("C = %lf\n", neuronSortie[i].poidsSortie);
    }

    /*calculNeurones(lien, neuronSortie, 0);
    printf("A = %lf\n", neuronSortie[0].poidsSortie);
    calculNeurones(lien, neuronSortie, 1);
    printf("B = %lf\n", neuronSortie[1].poidsSortie);
    calculNeurones(lien, neuronSortie, 2);
    printf("C = %lf\n", neuronSortie[2].poidsSortie);
    calculNeurones(lien, neuronSortie, 3);
    printf("D = %lf\n", neuronSortie[3].poidsSortie);*/


    printf("Test D : \n");

    for(int i = 0;i<NUMIN;i++)
        neuronEntree[i].poidsSortie = vect[3].premier[i];

    for(int i = 0;i<NUMHID;i++)
        calculNeurones(lien, neuronCachee, i);

    for(int i = 0;i<NUMOUT;i++)
    {
        calculNeurones(lien, neuronSortie, i);
        printf("D = %lf\n", neuronSortie[i].poidsSortie);
    }

    /*calculNeurones(lien, neuronSortie, 0);
    printf("A = %lf\n", neuronSortie[0].poidsSortie);
    calculNeurones(lien, neuronSortie, 1);
    printf("B = %lf\n", neuronSortie[1].poidsSortie);
    calculNeurones(lien, neuronSortie, 2);
    printf("C = %lf\n", neuronSortie[2].poidsSortie);
    calculNeurones(lien, neuronSortie, 3);
    printf("D = %lf\n", neuronSortie[3].poidsSortie);*/



    //save(lien);
    return 0;

}