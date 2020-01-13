/**
 * \file sokoban.h
 * \author Aurelien DOUARD, Anthony Bertrand
 * \brief fichier contenant le prototype des fonctions du sokoban (partie logique)
 * \version 0.1
 * \date 13 janvier 2020
 *
 * fichier contenant le prototype des fonctions du sokoban (partie logique)
 *
 */

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

typedef struct
{
    point posperso;
    clock_t clockStart, clockEnd; //waitEvent nous gène, utiliser PollEvent ou faire un thread ?
    char *tabNiveau;
    float extime;
    int nbMove;
    void (*updatecharfunc)(char,int);
    void (*updatescreen)(char*);
    int badcaisse;
    int curentlvl;
}Game;

void creationniveau(Game *g, FILE *flot);
void save();
void load();
int canMoveCaisse(char tabNiveau[], int indexmove2);
void movecaisse(Game *g, int indexmove2, int x, int y);
void movesoko(Game *g, point *pos, int x, int y);
void moveperso(Game *g, point *pos, int x, int y, char movenext);
void restart(Game *g, int lv);
int contient(char tab[], int n, char c);
int win(char tabNiveau[]);
void affichetab(char tab[]);
void createtablvl(Game *g, int n);
void initGame(Game *g, void (*updatecharfunc)(char,int), void (*updatescreen)(char*));
void callGameUpdateScreen(Game *g);
void callGameUpdateChar(Game *g, char movenext, int indexmove1);
int score(Game *g);




#endif




//Pour écrire avec SDL : SDL_ttf