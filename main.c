#include <stdio.h>
#include <stdlib.h>
#include "sdlsoko.h"
#include "ncursessoko.h"
#include "main.h"
#include <string.h>

int main(int argc, char ** argv){
    if(argc == 1){
        graphic();
    }else{
        if(strcmp(argv[1],"-c")==0){
            console();
        }
        if(strcmp(argv[1],"-g")==0){
            graphic();
        }
    }
    return EXIT_SUCCESS;
}




