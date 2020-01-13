/**
 * \file fontutils.h
 * \author Aurelien DOUARD, Anthony Bertrand
 * \brief fichier contenant le prototype des fonctions de lecture/écriture en sdl
 * \version 0.1
 * \date 13 janvier 2020
 *
 * fichier contenant le prototype des fonctions de lecture/écriture en sdl
 *
 */

#ifndef FTU_h
#define FTU_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

typedef struct
{
    int x;
    int y;
    int cha;
    int height;
    int width;
    int xoffset;
    int yoffset;
    int xadvance;
    int page;
    int chnl;
}fontchar;

typedef struct{
    fontchar *allfont;
    int fontcount;
    SDL_Surface *fontimg;
}font;

font* readfontinfo(int size, char* filename, char* imagename);
void displaystring(char *str, SDL_Surface *ecran, SDL_Rect dest, font *ftt);
void freefont(font *ftt);

#endif