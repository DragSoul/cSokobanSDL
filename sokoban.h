#ifndef SOKO_H
#define SOKO_H

#define LC 50
#define WIDTH 10*LC
#define HEIGHT 11*LC
#define N 11

#define MENU 'm'
#define PERS '@'
#define PERSCIBLE '+'
#define SOL 's'
#define SOLCIBLE '.'
#define MUR '#'
#define CAISSE '$'
#define CAISSECIBLE '*'


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <pthread.h>
#include <SDL/SDL_types.h>
#include <SDL/SDL_timer.h>


typedef struct{
    int x;
    int y;
}point;

void creationniveau(FILE *flot);
void save();
void load();
int canMoveCaisse(int indexmove2);
void movecaisse(int indexmove2, int x, int y);
void movesoko(point *pos, int x, int y);
void moveperso(point *pos, int x, int y, char movenext);
void restart(int lv);
int contient(char tab[], int n, char c);
int win();
void affichetab(char tab[]);

void setupdatecharfunc(void(*func)(char,int));
void createtablvl(int n);
void (*updatecharfunc)(char,int);
void (*updatescreen)(void);
void setupdatescreenfunc(void (*update)(void));
void setposperso(point pos);
point getposperso();
void setupdatescreenfunc(void (*update)(void));

point posperso;
clock_t clockStart, clockEnd; //waitEvent nous gène, utiliser PollEvent ou faire un thread ?
char *tabNiveau;
float extime;
int nbMove;

#endif




//Pour écrire avec SDL : SDL_ttf