#include <stdio.h>
#include <stdlib.h>

#include "neural_network.h"

int main()
{
    struct Vecteur *vecteur[EX];
    struct Neurone neuronEntree[NUMIN];
    struct Neurone neuronCachee[NUMHID];
    struct Neurone neuronSortie[NUMOUT];
    struct Neurone neuronBiais[NUMBIAS];
    struct Lien *lien[NB_LIENS];

    Network(neuronEntree, neuronCachee, neuronSortie, neuronBiais, lien, vecteur);
    loadExemple(vecteur);

    //Apprentissage(neuronEntree, neuronCachee, neuronSortie, (struct Lien *) lien, vecteur);
    load(lien);


//script au cas ou pour vérification du chargement des vecteurs exemples :
    /*for(int i = 0;i<EX;i++)
{
    printf("vecteur premier %d : ",i);
    for(int j = 0;j<NUMIN;j++) {
        printf("%f ", vecteur[i]->premier[j]);
    }
    printf("\n");
    printf("vecteur res %d : ",i);
    for(int z = 0;z<NUMOUT;z++)
    {
        printf("%f ", vecteur[i]->res[z]);
    }
    printf("\n");
    printf("\n");
}*/

    //============== Résultat Réseau ==========


    printf("Test \"a\" :\n");

    for(int i = 0;i<NUMIN;i++) {
        neuronEntree[i].poidsSortie = vecteur[0]->premier[i];
    }

    for(int i = 0;i<NUMHID;i++)
        calculNeurones(lien, neuronCachee, i);

    int j1 = 0;
    double max1 = 0.0;
    for(int i = 0;i<NUMOUT;i++)
    {
        calculNeurones(lien, neuronSortie, i);
        if(neuronSortie[i].poidsSortie>max1)
	    {
		      max1 = neuronSortie[i].poidsSortie;
		      j1 = i;
	    }
    }

    PrintResultat(j1);
	

    printf("Test \"B\" : \n");

    for(int i = 0;i<NUMIN;i++)
        neuronEntree[i].poidsSortie = vecteur[27]->premier[i];

    for(int i = 0;i<NUMHID;i++)
        calculNeurones(lien, neuronCachee, i);

    int j2 = 0;
    double max2 = 0.0;
    for(int i = 0;i<NUMOUT;i++)
    {
        calculNeurones(lien, neuronSortie, i);
        if(neuronSortie[i].poidsSortie>max2)
        {
              max2 = neuronSortie[i].poidsSortie;
              j2 = i;
        }
    }

    PrintResultat(j2);


    printf("Test \"3\" : \n");

    for(int i = 0;i<NUMIN;i++)
        neuronEntree[i].poidsSortie = vecteur[55]->premier[i];

    for(int i = 0;i<NUMHID;i++)
        calculNeurones(lien, neuronCachee, i);

    int j3 = 0;
    double max3 = 0.0;
    for(int i = 0;i<NUMOUT;i++)
    {
        calculNeurones(lien, neuronSortie, i);
        if(neuronSortie[i].poidsSortie>max3)
        {
              max3 = neuronSortie[i].poidsSortie;
              j3 = i;
        }
    }

    PrintResultat(j3);


    printf("Test \"!\"");

    for(int i = 0;i<NUMIN;i++)
        neuronEntree[i].poidsSortie = vecteur[64]->premier[i];

    for(int i = 0;i<NUMHID;i++)
        calculNeurones(lien, neuronCachee, i);

    int j4 = 0;
    double max4 = 0.0;
    for(int i = 0;i<NUMOUT;i++)
    {
        calculNeurones(lien, neuronSortie, i);
        if(neuronSortie[i].poidsSortie>max4)
        {
              max4 = neuronSortie[i].poidsSortie;
              j4 = i;
        }
    }

    PrintResultat(j4);


    //save(lien);


    return 0;

}

