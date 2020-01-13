/**
 * \file sdlsoko.h
 * \author Aurelien DOUARD, Anthony Bertrand
 * \brief fichier contenant le prototype des fonctions du sokoban (partie graphique)
 * \version 0.1
 * \date 13 janvier 2020
 *
 * fichier contenant le prototype des fonctions du sokoban (partie graphique)
 *
 */

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
    char content[20];
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
void boucleEv(Game *g, font* ftt);
void updatechar(char toupdate, int index);
void dessine();
void freeImg();
void menu(allbutton *buttontab, font * ftt);
void addallimg(int * index, char car, SDL_Surface *imgrect);
void graphic();
void displaybtn(allbutton *allb, SDL_Surface *ecran, font *ftt);
int isinbutton(int x, int y,allbutton *buttontab);
void displayonebtn(button btn, SDL_Surface *ecran, font *ftt, int r, int g, int b);
int timer(int oldtime, int ms);
void EventMouseButton(SDL_Event event, font *ftt, int *count, allbutton *buttontab, int *indexbtn, int *tmpindexbtn);
void initrect(SDL_Rect *rect, int x, int y, int w, int h);
void endLvl(Game *g, font *ftt);

//images utilisées
charimg allimage[8];

SDL_Rect positionperso;
SDL_Surface * ecran;
#endif