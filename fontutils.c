/**
 * \file fontutils.c
 * \author Aurelien DOUARD, Anthony Bertrand
 * \brief Programme nécessaire à l'affichage de texte en sdl
 * \version 0.1
 * \date 13 janvier 2020
 *
 * Programme nécessaire à l'affichage de texte en sdl
 *
 */

#include "fontutils.h"
#include <string.h>

//lit les informations du fichier filename qui correspondes au fichier imagename de la font
font* readfontinfo(int size, char* filename, char* imagename){
    FILE *f = fopen(filename, "r");
    if(f == NULL){
        printf("pb fopen");
        exit(1);
    }
    font *ftt;
    ftt = malloc(sizeof(font));
    
    ftt->allfont = malloc(sizeof(fontchar)*size);
    fontchar ftc;
    int cpt = 0, k;
    while(!feof(f)){
        k = fscanf(f, "char id=%d\tx=%d\ty=%d\twidth=%d\theight=%d\txoffset=%d\tyoffset=%d\txadvance=%d\tpage=%d\tchnl=%d\n", 
        &ftc.cha, &ftc.x, &ftc.y, &ftc.width, &ftc.height, &ftc.xoffset, &ftc.yoffset, &ftc.xadvance, &ftc.page, &ftc.chnl);
        ftt->allfont[cpt] = ftc;
        //printf("cha : %d, k : %d\n", ftt.cha, k);
        if(k == 0){
            printf("pb lecture font");
            exit(1);
        }
        cpt ++;
        if(cpt >= size){
            break;
        }
    }
    ftt->fontcount = cpt;
    ftt->fontimg = SDL_LoadBMP(imagename);
    if(ftt->fontimg == NULL){
        printf("pb font img\n, %s",SDL_GetError());
        exit(1);
    }
    fclose(f);
    return ftt;
}

//affiche la chaine de caractère str dans la surface ecran a la position dest avec la font ftt
void displaystring(char *str, SDL_Surface *ecran, SDL_Rect dest, font* ftt){
    int spacing = 1;
    SDL_Rect blackRect;
    blackRect.w = strlen(str) * 22;
    blackRect.h = 24;
    blackRect.x = dest.x;
    blackRect.y = dest.y;
    SDL_FillRect(ecran, &blackRect, SDL_MapRGB(ecran->format,0,0,0));
    int coderblt;
    SDL_Rect tmprect;
    for(int i = 0; i < strlen(str); i++){
        for(int j = 0; j < ftt->fontcount; j++){
            if(str[i] == ftt->allfont[j].cha){
                tmprect.h = ftt->allfont[j].height;
                tmprect.w = ftt->allfont[j].width;
                tmprect.x = ftt->allfont[j].x;
                tmprect.y = ftt->allfont[j].y;                
                coderblt = SDL_BlitSurface(ftt->fontimg, &tmprect, ecran, &dest);
                dest.x += ftt->allfont[j].width + spacing;
                if(coderblt != 0){
                    printf("pb blt font\n");
                }
            }
            
        }
    }
}

void freefont(font *ftt){
    SDL_FreeSurface(ftt->fontimg);
    free(ftt->allfont);
    free(ftt);
}

