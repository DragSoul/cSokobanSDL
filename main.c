#include <stdio.h>
#include <stdlib.h>
#include "sdlsoko.h"

int main(int argc, char ** argv){
    setupdatecharfunc(&updatechar);
    setupdatescreenfunc(&dessine);
    loadImg();
    srand(time(NULL));
    createtablvl(110);
    // Init
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr,"\nUnable to initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if((ecran = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE)) == NULL){
        fprintf(stderr, "Erreur VideoMode %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    FILE *flot = fopen("niveau1", "r");
    if(flot == NULL){
        printf("pb ouverture fichier en lecture\n");
        exit(1);
    }

    menu();
    // Légende de la fenêtre
    SDL_WM_SetCaption("Sokoban", NULL);
    creationniveau(flot);
    fclose(flot);
    //load(); //commenter la création du lvl pour l'utiliser
    SDL_Flip(ecran);

    
    clockStart = clock();
    boucleEv();
    clockEnd = clock();
    extime = extime + (float) (clockEnd-clockStart)/CLOCKS_PER_SEC; //seconde
    printf("time : %f\nnb Moves : %d\n", extime, nbMove);
    freeImg();
    SDL_Quit();
    
    return EXIT_SUCCESS;
}