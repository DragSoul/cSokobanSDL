/**
 * \file sokoban.c
 * \author Aurelien DOUARD, Anthony Bertrand
 * \brief fichier contenant les fonctions du sokoban
 * \version 0.1
 * \date 13 janvier 2020
 *
 * fichier contenant les fonctions du sokoban
 *
 */

#include "sokoban.h"

void createtablvl(Game *g, int n){
    g->tabNiveau = malloc(sizeof(char)*(n));
}


void initGame(Game *g, void (*updatecharfunc)(char,int), void (*updatescreen)(char*)){
    g->nbMove = 0;
    g->extime = 0;
    g->updatecharfunc = updatecharfunc;
    g->updatescreen = updatescreen;
    g->badcaisse = 0;
    g->curentlvl = 0;
}


void creationniveau(Game *g, FILE *flot){
    char c;
    int i = 0, j = 0;
    point pos;
    g->badcaisse = 0;
    while((c = fgetc(flot)) != EOF){
        if(c != '\n'){
            if(c == CAISSE){
                g->badcaisse += 1;
            }
            g->tabNiveau[i*N + j] = c;
            g->updatecharfunc(c, (i*N + j));
            if(c == PERS){
                pos.y = (i*N + j) / N;
                pos.x = (i*N + j) - (pos.y * N);
                g->posperso = pos;
            }
            j++;
        }
        else{
            i++;
            j = 0;
        }
    }
    callGameUpdateScreen(g);
}


void save(Game *g){
    FILE *flot = fopen("sauv", "w");
    if(flot == NULL){
        printf("pb sauvegarde\n");
        exit(1);
    }
    g->clockEnd = clock();
    float extime=(float) (g->clockEnd-g->clockStart)/CLOCKS_PER_SEC; //seconde
    fprintf(flot, "%f\n%d\n", extime, g->nbMove);
    for (int i = 0; i < 11; i++){
        for (int j = 0; j < 10; j++){
            fprintf(flot, "%c", g->tabNiveau[i*N + j]);
        }
        fprintf(flot, "\n");
    }
    fclose(flot);
}


void load(Game *g){
    FILE *flot = fopen("sauv", "r");
    if(flot == NULL){
        printf("pb chargement\n");
        exit(1);
    }
    fscanf(flot, "%f\n%d\n", &(g->extime), &(g->nbMove));
    printf("time : %f\nnbCoup : %d\n", g->extime, g->nbMove);
    creationniveau(g, flot);
    fclose(flot);
}


void restart(Game *g, int lv){
    g->clockStart = clock();
    g->nbMove = 0;
    g->extime = 0;
    char filename[8];
    sprintf(filename, "niveau%d", lv);
    FILE *flot = fopen(filename, "r");
    if(flot == NULL){
        printf("pb ouverture fichier en lecture\n");
        exit(1);
    }
    creationniveau(g, flot);
    fclose(flot);
    g->curentlvl = lv;
}


void movecaisse(Game *g, int indexmove2, int x, int y){
    if(g->tabNiveau[indexmove2] == SOL){
        g->tabNiveau[indexmove2] = CAISSE;
        callGameUpdateChar(g, CAISSE, indexmove2);
    }
    else{
        g->tabNiveau[indexmove2] = CAISSECIBLE;
        g->badcaisse -=1;
        callGameUpdateChar(g, CAISSECIBLE, indexmove2);
    }
}


int canMoveCaisse(char tabNiveau[], int indexmove2){
    return tabNiveau[indexmove2] != MUR && tabNiveau[indexmove2] != CAISSE && tabNiveau[indexmove2] != CAISSECIBLE;
}


void movesoko(Game *g, int x, int y){
    int indexmove1 = ((g->posperso.y)+y)*N + (g->posperso.x)+x;
    int indexmove2 = ((g->posperso.y)+(2*y))*N + (g->posperso.x)+(2*x);

    switch(g->tabNiveau[indexmove1]){
        //mur
        case MUR:
            break;
        //caisse1
        case CAISSE:
            if(canMoveCaisse(g->tabNiveau, indexmove2)){
                //move caisse
                movecaisse(g, indexmove2, x, y);
                moveperso(g,x,y,PERS);
            }
            break;
        //caisse2
        case CAISSECIBLE:
            if(canMoveCaisse(g->tabNiveau, indexmove2)){
                movecaisse(g, indexmove2,x,y);
                g->badcaisse +=1;
                moveperso(g,x,y,PERSCIBLE);
            }
            break;
        //dest
        case SOLCIBLE:
            moveperso(g,x,y,PERSCIBLE);
            break;

        case SOL:
            moveperso(g,x,y,PERS);
            break;
    }
}


void moveperso(Game *g, int x, int y, char movenext){

    g->nbMove += 1;
    int curentindex = (g->posperso.y)*N + (g->posperso.x);
    int indexmove1 = ((g->posperso.y)+y)*N + (g->posperso.x)+x;
    if(g->tabNiveau[curentindex] == PERSCIBLE){
        g->tabNiveau[curentindex] = SOLCIBLE;
        callGameUpdateChar(g, SOLCIBLE, curentindex);
    }
    else{
        g->tabNiveau[curentindex] = SOL;
        callGameUpdateChar(g, SOL, curentindex);
    }
    g->tabNiveau[indexmove1] = movenext;
    g->posperso.x += x;
    g->posperso.y += y;
    if(g->updatecharfunc != NULL){
        callGameUpdateChar(g, movenext, indexmove1);
    }
    if(g->updatescreen != NULL){
        callGameUpdateScreen(g);
    }
}


void callGameUpdateScreen(Game *g){
    if(g->updatescreen != NULL){
        g->updatescreen(g->tabNiveau);
    }
}


void callGameUpdateChar(Game *g, char movenext, int indexmove1){
    if(g->updatecharfunc != NULL){
        g->updatecharfunc(movenext, indexmove1);
    }
}


int win(char tabNiveau[]){
    for(int i = 0; i < 110; i++){
        if(tabNiveau[i] == CAISSE){
            return 1;
        } 
    }
    return 0;
}


void affichetab(char tab[]){
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 10; j++){
            printf("%c", tab[i*N+j]);
        }
        printf("\n");
    }
}


int score(Game *g){
    if(g->badcaisse != 0){
        return 0;
    }
    int res = 9999;
    res = res - (int)(g->extime * g->nbMove * 10);
    if(res > 0){
        return res;
    }
    return 0;
}