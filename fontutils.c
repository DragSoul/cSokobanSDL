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

//affiche la chaine de caractère str dans la surface ecrant a la position dest avect la font ftt
void displaystring(char *str, SDL_Surface *ecran, SDL_Rect dest, font* ftt){
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
                dest.x += ftt->allfont[j].width;
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