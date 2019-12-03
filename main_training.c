#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matrix.h"
#include "segmentation_training.h"
#include <err.h>

int main(int argc, char* argv[]) {
    
    printf("\n*******************************  SEGMENTATION TRAINING **************************\n");
    if (argc < 3 ) errx(1, "paramètres invalides");
    int compt = 0;
    int *a = &compt;
    segmentation(argv[1],a,argv[2]);
    printf("\n--> char detected : %d\n",compt );

    if(compt == 210)
    	printf("\nChecking DBS : OK\n\n");
    else
    	printf("\nChecking DBS : KO\n\n");
    return 0;
}







