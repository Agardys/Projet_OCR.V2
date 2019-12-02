#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matrix.h"
#include "segmentation.h"
#include <err.h>

int main(int argc, char* argv[]) {
    
    if (argc < 2 ) errx(1, "paramètre invalide");
    int compt = 0;
    int *a = &compt;
    segmentation(argv[1],a);
    printf("nombre de char : %d\n",compt );
    return 0;
}







