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
#include "fontutils.h"
#include "sokoban.h"

typedef struct{
    SDL_Rect *rect;
    void(*callback)(void*);
    void* arg;
}button;

typedef struct{
    button *buttons;
    int len;
}allbutton;

typedef struct 
{
    char car;
    SDL_Surface *img;
}charimg;

void loadImg();
void boucleEv(font *ftt);
void updatechar(char toupdate, int index);
void dessine();
void freeImg();
void menu();
void addallimg(int * index, char car, SDL_Surface *imgrect);
void graphic();



//images utilisées
charimg allimage[8];

SDL_Rect positionperso;
SDL_Surface * ecran;
#endif