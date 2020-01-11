#ifndef SDLD_H
#define SDLD_H

#define LC 50
#define WIDTH 10*LC
#define HEIGHT 11*LC
#define N 11

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <pthread.h>
#include <SDL/SDL_types.h>
#include <SDL/SDL_timer.h>
#include "sokoban.h"

void loadImg();
void boucleEv();
void updatechar(char toupdate, int index);
void dessine();
void freeImg();
void menu();
void addallimg(int * index, char car, SDL_Surface *imgrect);

typedef struct 
{
    char car;
    SDL_Surface *img;
}charimg;

//images utilisées
charimg allimage[8];

SDL_Rect positionperso;
SDL_Surface * ecran;
#endif