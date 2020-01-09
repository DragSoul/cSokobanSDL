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


typedef enum{false,true}Boolean;

void menu();
void loadImg();
void freeImg();
void creationniveau1(FILE *flot);
void boucleEv();
void move(int *i, int *j, int x, int y);
void moveperso(int *i, int *j, int x, int y, int boul);
void restart(int lv);
void dessine(int boul);
int contient(char tab[], int n, char c);
int win();
void affichetab(char tab[]);

//images utilisées
SDL_Surface *imgmenu;
SDL_Surface *imgperso;
SDL_Surface *imgcaisse1;
SDL_Surface *imgcaisse2;
SDL_Surface *imgmur;
SDL_Surface *imgsol;
SDL_Surface *imgdest;
SDL_Surface *imgpersodest;

SDL_Rect positionperso;
SDL_Surface * ecran = NULL;

char *tabNiveau;

#endif




//Pour écrire avec SDL : SDL_ttf