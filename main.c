/**
 * \file main.c
 * \author Aurelien DOUARD, Anthony Bertrand
 * \brief fichier contenant la fonction main()
 * \version 0.1
 * \date 13 janvier 2020
 *
 * fichier contenant la fonction main()
 *
 */

#include "main.h"

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




