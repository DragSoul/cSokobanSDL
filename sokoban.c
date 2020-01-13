#include "sokoban.h"

void createtablvl(Game *g, int n){
    g->tabNiveau = malloc(sizeof(char)*(n));
}

//création d'un tableau pour avoir le niveau en mémoire
void creationniveau(Game *g, FILE *flot){
    char c;
    int i = 0, j = 0;
    point pos;
    
    while((c = fgetc(flot)) != EOF){
        if(c != '\n'){
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
    g->updatescreen(g->tabNiveau);
}

//appuie sur s pour sauvegarder le niveau
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

//charge le niveau depuis le fichier sauv
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

//recherge un niveau
void restart(Game *g, int lv){
    char filename[8];
    sprintf(filename, "niveau%d", lv);
    FILE *flot = fopen(filename, "r");
    if(flot == NULL){
        printf("pb ouverture fichier en lecture\n");
        exit(1);
    }
    creationniveau(g, flot);
    fclose(flot);
}

void movecaisse(Game *g, int indexmove2, int x, int y){
    if(g->tabNiveau[indexmove2] == SOL){
        g->tabNiveau[indexmove2] = CAISSE;
        g->updatecharfunc(CAISSE, indexmove2);
    }
    else{
        g->tabNiveau[indexmove2] = CAISSECIBLE;
        g->updatecharfunc(CAISSECIBLE, indexmove2);
    }
}

int canMoveCaisse(char tabNiveau[], int indexmove2){
    return tabNiveau[indexmove2] != MUR && tabNiveau[indexmove2] != CAISSE && tabNiveau[indexmove2] != CAISSECIBLE;
}

void movesoko(Game *g, point *pos, int x, int y){
    int indexmove1 = ((pos->y)+y)*N + (pos->x)+x;
    int indexmove2 = ((pos->y)+(2*y))*N + (pos->x)+(2*x);
    switch(g->tabNiveau[indexmove1]){
        //mur
        case MUR:
            break;
        //caisse1
        case CAISSE:
            if(canMoveCaisse(g->tabNiveau, indexmove2)){
                //move caisse
                movecaisse(g, indexmove2, x, y);
                moveperso(g, pos,x,y,PERS);
            }
            break;
        //caisse2
        case CAISSECIBLE:
            if(canMoveCaisse(g->tabNiveau, indexmove2)){
                movecaisse(g, indexmove2,x,y);
                moveperso(g,pos,x,y,PERSCIBLE);
            }
            break;
        //dest
        case SOLCIBLE:
            moveperso(g, pos,x,y,PERSCIBLE);
            break;

        case SOL:
            moveperso(g, pos,x,y,PERS);
            break;
    }
}

void moveperso(Game *g, point *pos, int x, int y, char movenext){
    g->nbMove += 1;
    int curentindex = (pos->y)*N + (pos->x);
    int indexmove1 = ((pos->y)+y)*N + (pos->x)+x;
    if(g->tabNiveau[curentindex] == PERSCIBLE){
        g->tabNiveau[curentindex] = SOLCIBLE;
        g->updatecharfunc(SOLCIBLE, curentindex);
    }
    else{
        g->tabNiveau[curentindex] = SOL;
        g->updatecharfunc(SOL, curentindex);
    }
    g->tabNiveau[indexmove1] = movenext;
    pos->x += x;
    pos->y += y;
    g->updatecharfunc(movenext, indexmove1);
    g->updatescreen(g->tabNiveau);
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