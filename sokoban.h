#ifndef TEST_H
#define TEST_H

#define LC 50
#define WIDTH 10*LC
#define HEIGHT 11*LC



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_types.h>


void creationniveau1(FILE *flot);
void boucleEv();
void dessine();

//images utilisées
SDL_Surface *imgperso;
SDL_Surface *imgcaisse1;
SDL_Surface *imgcaisse2;
SDL_Surface *imgmur;
SDL_Surface *imgsol;
SDL_Surface *imgdest;

SDL_Rect positionperso;
SDL_Surface * ecran = NULL ;

#endif