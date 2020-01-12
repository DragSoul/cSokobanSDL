#include "sokoban.h"

void createtablvl(int n){
    tabNiveau = malloc(sizeof(char)*(n));
}

void setupdatecharfunc(void(*func)(char,int)){
    updatecharfunc = func;
}

//création d'un tableau pour avoir le niveau en mémoire
void creationniveau(FILE *flot){
    char c;
    int i = 0, j = 0;
    point pos;
    
    while((c = fgetc(flot)) != EOF){
        if(c != '\n'){
            tabNiveau[i*N + j] = c;
            updatecharfunc(c, (i*N + j));
            if(c == PERS){
                pos.y = (i*N + j) / N;
                pos.x = (i*N + j) - (pos.y * N);
                setposperso(pos);
            }
            j++;
        }
        else{
            i++;
            j = 0;
        }
    }
    updatescreen();
}

void setupdatescreenfunc(void (*update)(void)){
    updatescreen = update;
}

void setposperso(point pos){
    posperso = pos;
}

point getposperso(){
    return posperso;
}

//appuie sur s pour sauvegarder le niveau
void save(){
    FILE *flot = fopen("sauv", "w");
    if(flot == NULL){
        printf("pb sauvegarde\n");
        exit(1);
    }
    clockEnd = clock();
    float extime=(float) (clockEnd-clockStart)/CLOCKS_PER_SEC; //seconde
    fprintf(flot, "%f\n%d\n", extime, nbMove);
    for (int i = 0; i < 11; i++){
        for (int j = 0; j < 10; j++){
            fprintf(flot, "%c", tabNiveau[i*N + j]);
        }
        fprintf(flot, "\n");
    }
    fclose(flot);
}

//charge le niveau depuis le fichier sauv
void load(){
    FILE *flot = fopen("sauv", "r");
    if(flot == NULL){
        printf("pb chargement\n");
        exit(1);
    }
    fscanf(flot, "%f\n%d\n", &extime, &nbMove);
    printf("time : %f\nnbCoup : %d\n", extime, nbMove);
    creationniveau(flot);
    fclose(flot);
}

//recherge un niveau
void restart(int lv){
    char filename[8];
    sprintf(filename, "niveau%d", lv);
    FILE *flot = fopen(filename, "r");
    if(flot == NULL){
        printf("pb ouverture fichier en lecture\n");
        exit(1);
    }
    creationniveau(flot);
    fclose(flot);
}

void movecaisse(int indexmove2, int x, int y){
    if(tabNiveau[indexmove2] == SOL){
        tabNiveau[indexmove2] = CAISSE;
        updatecharfunc(CAISSE, indexmove2);
    }
    else{
        tabNiveau[indexmove2] = CAISSECIBLE;
        updatecharfunc(CAISSECIBLE, indexmove2);
    }
}

int canMoveCaisse(int indexmove2){
    return tabNiveau[indexmove2] != MUR && tabNiveau[indexmove2] != CAISSE && tabNiveau[indexmove2] != CAISSECIBLE;
}

void movesoko(point *pos, int x, int y){
    int curentIndex = (pos->y)*N + (pos->x);
    int indexmove1 = ((pos->y)+y)*N + (pos->x)+x;
    int indexmove2 = ((pos->y)+(2*y))*N + (pos->x)+(2*x);
    switch(tabNiveau[indexmove1]){
        //mur
        case MUR:
            break;
        //caisse1
        case CAISSE:
            if(canMoveCaisse(indexmove2)){
                //move caisse
                movecaisse(indexmove2, x, y);
                moveperso(pos,x,y,PERS);
            }
            break;
        //caisse2
        case CAISSECIBLE:
            if(canMoveCaisse(indexmove2)){
                movecaisse(indexmove2,x,y);
                moveperso(pos,x,y,PERSCIBLE);
            }
            break;
        //dest
        case SOLCIBLE:
            moveperso(pos,x,y,PERSCIBLE);
            break;

        case SOL:
            moveperso(pos,x,y,PERS);
            break;
    }
}

void moveperso(point *pos, int x, int y, char movenext){
    nbMove++;
    int curentindex = (pos->y)*N + (pos->x);
    int indexmove1 = ((pos->y)+y)*N + (pos->x)+x;
    if(tabNiveau[curentindex] == PERSCIBLE){
        tabNiveau[curentindex] = SOLCIBLE;
        updatecharfunc(SOLCIBLE, curentindex);
    }
    else{
        tabNiveau[curentindex] = SOL;
        updatecharfunc(SOL, curentindex);
    }
    tabNiveau[indexmove1] = movenext;
    pos->x += x;
    pos->y += y;
    updatecharfunc(movenext, indexmove1);
    updatescreen();
}

int win(){
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