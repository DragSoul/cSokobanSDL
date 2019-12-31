#ifndef TEST_H
#define TEST_H

#define LC 50
#define WIDTH 10*LC
#define HEIGHT 11*LC
#define N 11



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_types.h>


void loadImg();
void freeImg();
void creationniveau1(FILE *flot);
void boucleEv();
void move(int *i, int *j, int x, int y);
void moveperso(int *i, int *j, int x, int y);
void restart(int lv);
void dessine();

//images utilisées
SDL_Surface *imgperso;
SDL_Surface *imgcaisse1;
SDL_Surface *imgcaisse2;
SDL_Surface *imgmur;
SDL_Surface *imgsol;
SDL_Surface *imgdest;

SDL_Rect positionperso;
SDL_Surface * ecran = NULL;

char *tabNiveau;

#endif