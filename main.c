#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matrix.h"
#include "segmentation.h"
#include <err.h>

int main(int argc, char* argv[]) {
    printf("\n*******************************  SEGMENTATION *****************************\n");
    if (argc < 2 ) errx(1, "paramètre invalide");
    int compt = 0;
    int *a = &compt;
    segmentation(argv[1],a);
    printf("\nnumber of chars : %d\n\n",compt );
    return 0;
}







