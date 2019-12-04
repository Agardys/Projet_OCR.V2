#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matrix.h"
#include "segmentation_training.h"
#include <err.h>

int main(int argc, char* argv[]) {
    
    if (argc < 3 ) errx(1, "paramètres invalides");
    segmentation(argv[1],argv[2]);
    return 0;
}







