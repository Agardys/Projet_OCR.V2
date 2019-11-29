#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "neural_network.h"
//-------------------------------------------------

//-------Fonctions nécessaires au programme--------

//fonction sigmoide
double sigmoide(double x)
{
    return 1 / (1 + exp(-1 * x));;
    //return 1 / (1+ pow(2.71828, -x));
}

//fonction dérivé de sigmoide
double sigmoideDeriv(double x)
{
    return sigmoide(x) * (1 - (sigmoide(x)));
    //return x * (1-x);
}

void calculNeurones(struct Lien *lien[], struct Neurone neuron[], int x)
{
        double tmpoids = 0.0;

        for(int i = 0; i<NB_LIENS; i++)
        {
            if(lien[i]->to == &(neuron[x]))
                tmpoids += (lien[i]->from->poidsSortie) * (lien[i]->poids);
        }

        neuron[x].poidsSortie = sigmoide(tmpoids);

        return;
}

void CalculSortieErreur(double erreur, struct Neurone neuron[], int x)
{
    neuron[x].petitDelta = erreur * sigmoideDeriv(neuron[x].poidsSortie);

    return;
}

void CalculCoucheCacheeErreur(struct Lien *lien[], struct Neurone neuron[], int x)
{
    for(int i = 0; i<NB_LIENS; i++)
    {
        if(lien[i]->from == &(neuron[x]))
            neuron[x].petitDelta = lien[i]->poids * lien[i]->to->petitDelta * sigmoideDeriv(neuron[x].poidsSortie);
    }
}

void Backpropagation(struct Lien *lien[])
{
    for(int i = 0; i<NB_LIENS; i++)
    {
        lien[i]->grandDelta = ALPHA * (lien[i]->from->poidsSortie) * (lien[i]->to->petitDelta);
        lien[i]->poids += lien[i]->grandDelta;
    }
}

//=================================================

short int checkLimite(double tab[]){

    double sum = 0.0;

    for(int i=0; i<EX; i++)
        sum += tab[i] * tab[i];

    sum = sum / 2;

    if(sum < LIMIT)
        return 0;
    else
        return 1;
}

double Random()
{
    double res   = 0.0;
    short int sign  = 0;

    while(res==0.0 || (res<(- 4.0) || res>4.0) || (res>(- 0.59) && res<0.59))
    {
        sign = rand()%2;

        if(sign==1)
            res = (double)(rand()%1000) / (rand()%1000);
        else
            res = -1 * (double)(rand()%1000) / (rand()%1000);
    }
    return res;
    //return (double)rand()/(double)RAND_MAX;
}

void Apprentissage(struct Neurone neuronEntree[], struct Neurone neuronCachee[], struct Neurone neuronSortie[], struct Lien *lien, struct Vecteur *vecteur[])
{
    double networkErrorTab[EX];
    double networkError = 0.0;
    int    randomTab[EX]; //sélection aléatoire d'un vecteur d'apprentissage ==> résultat
    int    verif = 0;
    int    nb  = 0;

    for(long int x=0; x<(DAY * EX); x++) //nb d'itération * nb d'exemples à apprendre (pour le XOR = 4 exemples)
    {
        if((x%EX)==0) //tous les nb_ex ==> on remet le randomTab et networkErrorTab à 0
        {
            for(int i=0; i<EX; i++)
            {
                randomTab[i]    = 0;
                networkErrorTab[i] = 0.0;
            }
        }
        do
            {
            nb = rand()%EX;         // ==> on prend un ex au hasard

            if(x%EX==0)
            {                      //si le jour est un multiple du nombre de vecteurs d'apprentissage : insertion
                verif = 1;
                randomTab[x%EX] = nb;
            }
            else
                {                                   //sinon il regarde à travers la table utilisée et cherche celui qui n'a pas été utilisé
                for(int i=0; i<(x%EX);i++)
                {
                    if(randomTab[i]==nb)
                    {
                        verif = 0;
                        break;                            //s'il est utilisé, il sort de la boucle
                    }
                    else
                        {
                        verif = 1;
                    }
                }
                if(verif==1) randomTab[x%EX] = nb;
            }
        }while(verif!=1);


        //donnant l'exemple du réseau
        for(int i = 0;i<NUMIN;i++)
            neuronEntree[i].poidsSortie = vecteur[nb]->premier[i];

        //calculs pour les neurones
        for(int i = 0;i<NUMHID;i++)
            calculNeurones((struct Lien **) lien, neuronCachee, i);

        for(int i = 0;i<NUMOUT;i++)
            calculNeurones((struct Lien **) lien, neuronSortie, i);

        //calcul pour les neurones et
        //calcul d'erreur pour la couche de sortie
    //int verif = 0;
    for(int i = 0;i<NUMOUT;i++)
    {
        networkError = vecteur[nb]->res[i] - neuronSortie[i].poidsSortie;
        printf("%lf\n",neuronSortie[i].poidsSortie);

        networkErrorTab[x%EX] = networkError;
        /*if(x%EX%4)
        {
            if(checkLimite(networkErrorTab) == 0)
            {
                //verif = 1;
                //break;
                printf("coucou\n");
            }
        }*/
        CalculSortieErreur(networkError, neuronSortie, i);
    }
    //if(verif == 1)
        //break;

    for(int i = 0;i<NUMHID;i++)
    {
        CalculCoucheCacheeErreur((struct Lien **) lien, neuronCachee, i);
    }


        //propagation des erreurs (amélioration des poids de connexions)
        Backpropagation((struct Lien **) lien);

        //on répète pour d'autres vecteurs d'exemples
    }
}


//connecte les couches
void ConnectCouche(struct Neurone neuronCouche1[], struct Neurone neuronCouche2[], struct Lien *lien[], int linkCount, int biasCount, int x, int y){

    int i = linkCount;

    if(biasCount == 0)
    {
        for(int j = 0; j < x; j++)
        {
            for(int k = 0; k < y; k++)
            {
                lien[i]->poids = Random();
                //lien[i]->poids = 0.0;
                //printf("lien Couche %i = %d\n",i,lien[i]);

                lien[i]->from = &(neuronCouche1[j]);
                lien[i]->to   = &(neuronCouche2[k]);
                i++;
            }
        }
    }
    else printf("Erreur : lors du comptage de biais\n");

    return;
}

void connectBias(struct Neurone neuron1[], struct Neurone neuron2[], struct Lien *lien[], int lCount, int bCount, int x, int y){

    int i = lCount;
    int k = 0;
    int j = bCount;

    while(j < x && k < y)
    {
        lien[i]->poids = Random();
        //lien[i]->poids = 0.0;
        //printf("lien Bias %i = %d\n",i,lien[i]);

        lien[i]->from = &(neuron1[j]);
        lien[i]->to   = &(neuron2[k]);
        i++;
        j++;
        k++;
    }

    return;
}

void Network(struct Neurone *neuronEntree, struct Neurone *neuronCachee, struct Neurone *neuronSortie,
             struct Neurone *neuronBiais, struct Lien **lien, struct Vecteur **vecteur){

    //initialisation des vecteurs d'exemples
    for(int i = 0;i<EX;i++)
        vecteur[i] = calloc(1, sizeof(struct Vecteur));

    //initialisation des neurones de polarisations
    for(int i = 0;i<NUMBIAS;i++)
        neuronBiais[i].poidsSortie = BIAS;

    //création des liens / connexions entre les neurones
    for(int i = 0;i<NB_LIENS;i++)
        lien[i] = calloc(1, sizeof(struct Lien));

    int comptLien = 0;
    int comptBiais = 0;

    srand(time(0));

    ConnectCouche(neuronEntree,neuronCachee,lien,comptLien,comptBiais,NUMIN,NUMHID);
    comptLien += (NUMIN*NUMHID);

    ConnectCouche(neuronCachee, neuronSortie, lien, comptLien, comptBiais, NUMHID, NUMOUT);
    comptLien += (NUMHID*NUMOUT);

    connectBias(neuronBiais,neuronCachee,lien,comptLien,comptBiais,NUMBIAS,NUMHID);
    comptLien += NUMHID;
    comptBiais += NUMHID;

    connectBias(neuronBiais,neuronSortie,lien,comptLien,comptBiais,NUMBIAS,NUMOUT);
    comptLien += NUMOUT;
    comptBiais += NUMOUT;
}




//=================================================

void save(struct Lien *lien[])
{
    FILE *fp = fopen("save1.txt","wb");

    if(fp != NULL)
    {

        for (int i = 0; i < NB_LIENS; i++) {
            //printf("poids = %lf\n",lien[i]->poids);
            fprintf(fp,"%lf\n",lien[i]->poids);
        }

    }
    else
        printf("Erreur : lors de l'ouverture\n");

    if(fclose(fp) == EOF)
        printf("Erreur : lors de la fermeture du fichier\n");
}

void load(struct Lien *lien[])
{
    FILE *fp = fopen("save1.txt", "r");
    if(fp != NULL)
    {
        for(int i = 0;i<NB_LIENS;i++)
        {
            fscanf(fp,"%lf\n",&lien[i]->poids);
        }
    }
    else
        printf("Erreur : lors de l'ouverture du fichier\n");

    if(fclose(fp) == EOF)
        printf("Erreur : lors de la fermeture du fichier\n");
}

void loadExemple(struct Vecteur *vect[],char *filename)
{
    FILE *fp = fopen(filename, "r");
    if(fp != NULL)
    {
        int j = 0;
        while(j<EX)
        {
            //parcours le fichier et rentre les matrices de chaque lettres
            for (int i = 0; i < NUMIN; i++)
            {
                fscanf(fp, "%lf\n", &vect[j]->premier[i]);
            }

            //crée le tableau de sortie résultat de type {1.0,0.0,...,0.0} pour le "a"
            for(int i = 0;i<NUMOUT;i++)
            {
                if(i == j)
                    vect[j]->res[i] = 1.0;
                else
                    vect[j]->res[i] = 0.0;
            }
            j++;
        }

    }
    else
        printf("Erreur : lors de l'ouverture du fichier\n");

    if(fclose(fp) == EOF)
        printf("Erreur : lors de la fermeture du fichier\n");
}

void PrintResultat(int pos)
{
	switch(pos)
	{
		case 0:
			printf("Lettre trouvé : a\n");
			break;
		case 1:
			printf("Lettre trouvé : b\n");
			break;
		case 2:
			printf("Lettre trouvé : c\n");
			break;
		case 3:
			printf("Lettre trouvé : d\n");
			break;
		case 4:
			printf("Lettre trouvé : e\n");
			break;
		case 5:
			printf("Lettre trouvé : f\n");
			break;
		case 6:
			printf("Lettre trouvé : g\n");
			break;
		case 7:
			printf("Lettre trouvé : h\n");
			break;
		case 8:
			printf("Lettre trouvé : i\n");
            break;
		case 9:
			printf("Lettre trouvé : j\n");
            break;
		case 10:
			printf("Lettre trouvé : k\n");
            break;
		case 11:
			printf("Lettre trouvé : l\n");
            break;
		case 12:
			printf("Lettre trouvé : m\n");
            break;
		case 13:
			printf("Lettre trouvé : n\n");
            break;
		case 14:
			printf("Lettre trouvé : o\n");
            break;
		case 15:
			printf("Lettre trouvé : p\n");
            break;
		case 16:
			printf("Lettre trouvé : q\n");
            break;
		case 17:
			printf("Lettre trouvé : r\n");
            break;
		case 18:
			printf("Lettre trouvé : s\n");
            break;
		case 19:
			printf("Lettre trouvé : t\n");
            break;
		case 20:
			printf("Lettre trouvé : u\n");
            break;
		case 21:
			printf("Lettre trouvé : v\n");
            break;
		case 22:
			printf("Lettre trouvé : w\n");
            break;
		case 23:
			printf("Lettre trouvé : x\n");
            break;
		case 24:
			printf("Lettre trouvé : y\n");
            break;
		case 25:
			printf("Lettre trouvé : z\n");
            break;
		case 26:
			printf("Lettre trouvé : A\n");
            break;
		case 27:
			printf("Lettre trouvé : B\n");
            break;
		case 28:
			printf("Lettre trouvé : C\n");
            break;
		case 29:
			printf("Lettre trouvé : D\n");
            break;
		case 30:
			printf("Lettre trouvé : E\n");
            break;
		case 31:
			printf("Lettre trouvé : F\n");
            break;
		case 32:
			printf("Lettre trouvé : G\n");
            break;
		case 33:
			printf("Lettre trouvé : H\n");
            break;
		case 34:
			printf("Lettre trouvé : I\n");
            break;
		case 35:
			printf("Lettre trouvé : J\n");
            break;
		case 36:
			printf("Lettre trouvé : K\n");
            break;
		case 37:
			printf("Lettre trouvé : L\n");
            break;
		case 38:
			printf("Lettre trouvé : M\n");
            break;
		case 39:
			printf("Lettre trouvé : N\n");
            break;
		case 40:
			printf("Lettre trouvé : O\n");
            break;
		case 41:
			printf("Lettre trouvé : P\n");
            break;
		case 42:
			printf("Lettre trouvé : Q\n");
            break;
		case 43:
			printf("Lettre trouvé : R\n");
            break;
		case 44:
			printf("Lettre trouvé : S\n");
            break;
		case 45:
			printf("Lettre trouvé : T\n");
            break;
		case 46:
			printf("Lettre trouvé : U\n");
            break;
		case 47:
			printf("Lettre trouvé : V\n");
            break;
		case 48:
			printf("Lettre trouvé : W\n");
            break;
		case 49:
			printf("Lettre trouvé : X\n");
            break;
		case 50:
			printf("Lettre trouvé : Y\n");
            break;
		case 51:
			printf("Lettre trouvé : Z\n");
            break;
		case 52:
			printf("Lettre trouvé : 0\n");
            break;
		case 53:
			printf("Lettre trouvé : 1\n");
            break;
		case 54:
			printf("Lettre trouvé : 2\n");
            break;
		case 55:
			printf("Lettre trouvé : 3\n");
            break;
		case 56:
			printf("Lettre trouvé : 4\n");
            break;
		case 57:
			printf("Lettre trouvé : 5\n");
            break;
		case 58:
			printf("Lettre trouvé : 6\n");
            break;
		case 59:
			printf("Lettre trouvé : 7\n");
            break;
		case 60:
			printf("Lettre trouvé : 8\n");
            break;
		case 61:
			printf("Lettre trouvé : 9\n");
            break;
		case 62:
			printf("Lettre trouvé : .\n");
            break;
		case 63:
			printf("Lettre trouvé : ,\n");
            break;
		case 64:
			printf("Lettre trouvé : !\n");
            break;
		case 65:
			printf("Lettre trouvé : ?\n");
            break;
		case 66:
			printf("Lettre trouvé : -\n");
            break;
		case 67:
			printf("Lettre trouvé : (lettre_vide)\n");
		default:
			printf("Pas de lettre trouvé.\n");
			break;
	}
}
