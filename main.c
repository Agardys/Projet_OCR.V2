#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matrix.h"
#include "segmentation.h"
#include <err.h>

int main(int argc, char* argv[]) {
    
    if (argc < 2 ) errx(1, "paramètre invalide");
    segmentation(argv[1]);
    return 0;
}







