#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "Matrix.h"
#include "segmentation.h"
#include "neural_network.h"

int main()
{
    //int argc,char *argv[]
    /*if(argc < 2)
        errx(1,"Not enough... try again !");*/



//=======INITIALISATION DU RÉSEAU DE NEURONE======

    struct Vecteur *vecteur[EX];
    struct Neurone neuronEntree[NUMIN];
    struct Neurone neuronCachee[NUMHID];
    struct Neurone neuronSortie[NUMOUT];
    struct Neurone neuronBiais[NUMBIAS];
    struct Lien *lien[NB_LIENS];
    Network(neuronEntree, neuronCachee, neuronSortie, neuronBiais, lien, vecteur);
    //Apprentissage(neuronEntree, neuronCachee, neuronSortie, (struct Lien *) lien, vecteur);
    //load(lien,"sauvegarde_poids/saveFirst3Alpha.txt");

//=================================================

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

    //============== Résultat Réseau ===============


    //compteur de caractères à reconnaitre : 
    /*int compt = 0;

    int *size = &compt;

    //traitement de tout les caractères de l'image :
    double **Tab = segmentation(argv[1],size);

    //loadImage(vecteur,Tab,compt);
    loadExemple(vecteur,"entrainement/dbs_police3alpha.txt");
    //Apprentissage(neuronEntree, neuronCachee, neuronSortie, (struct Lien *) lien, vecteur);
    //save(lien,"save1.txt");
    char *res[EX];*/
    char *filenames[NBPOLICES] = {"entrainement/police0.txt","entrainement/police1.txt","entrainement/police2.txt","entrainement/police3.txt","entrainement/police4.txt","entrainement/police5.txt",
                       "entrainement/police6.txt","entrainement/police7.txt","entrainement/police8.txt","entrainement/police9.txt","entrainement/police10.txt","entrainement/police11.txt",
                       "entrainement/police12.txt","entrainement/police13.txt","entrainement/police14.txt","entrainement/police15.txt","entrainement/police16.txt","entrainement/police17.txt",
                       "entrainement/police18.txt","entrainement/police19.txt","entrainement/police20.txt","entrainement/police21.txt","entrainement/police22.txt","entrainement/police23.txt",
                        "entrainement/police24.txt"};

    int i = 0;
    while(i<NBPOLICES)
    {
        printf("%s\n",filenames[i]);
        loadExemple(vecteur,filenames[i]);
        Apprentissage(neuronEntree, neuronCachee, neuronSortie, (struct Lien *) lien, vecteur);
        save(lien,"save1.txt");
        i++;
    }


    //interrogation du caractère pour l'OCR
    /*for(int k = 0;k<compt;k++)
    {
        for(int i = 0;i<NUMIN;i++)
            neuronEntree[i].poidsSortie = vecteur[k]->premier[i];

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

        res[k] = PrintResultat(j1);
    }

    WriteFile("RESULTAT.TXT",res,EX);*/

    FreeNetwork(lien, vecteur);


    return 0;

}

