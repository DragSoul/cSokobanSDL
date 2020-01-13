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



typedef struct{
    int x;
    int y;
}point;

typedef struct
{
    point posperso;
    clock_t clockStart, clockEnd;
    char *tabNiveau;
    float extime;
    int nbMove;
    void (*updatecharfunc)(char,int);
    void (*updatescreen)(char*);
    int badcaisse;
    int curentlvl;
}Game;


/**
 * \fn void creationniveau(Game *g, FILE *flot)
 * \brief Fonction qui initialise le tableau du niveau en mémoire
 * 
 * \param g Pointeur sur une structure Game
 * \param flot pointeur sur un fichier.
 */
void creationniveau(Game *g, FILE *flot);

/**
 * \fn void save(Game *g)
 * \brief Fonction qui sauvegarde l'état du jeu dans un fichier sauv
 * 
 * \param g Pointeur sur une structure Game
 */
void save();

/**
 * \fn void load(Game *g)
 * \brief Fonction qui charge un niveau depuis une sauvegarde dans un fichier sauv
 * 
 * \param g Pointeur sur une structure Game
 */
void load();

/**
 * \fn int canMoveCaisse(char tabNiveau[], int indexmove2)
 * \brief Fonction qui nous dit si la caisse peut être déplacée ou non
 * 
 * \param tabNiveau tableau du niveau
 * \param indexmove2 index du tableau correspondant à la case derriere la caisse
 */
int canMoveCaisse(char tabNiveau[], int indexmove2);

/**
 * \fn void movecaisse(Game *g, int indexmove2, int x, int y)
 * \brief Fonction qui permet de déplacer une caisse
 * 
 * \param g Pointeur sur une structure Game
 * \param indexmove2 index du tableau correspondant à la case derriere la caisse
 * \param x 
 * \param y 
 */
void movecaisse(Game *g, int indexmove2, int x, int y);

/**
 * \fn void movesoko(Game *g, point *pos, int x, int y)
 * \brief Fonction qui nous dit si la caisse peut être déplacée ou non
 * 
 * \param g Pointeur sur une structure Game
 * \param x entier représentant le déplacement du personnage sur l'axe horizontale (-1, 0 ou 1)
 * \param y entier représentant le déplacement du personnage sur l'axe verticale (-1, 0 ou 1)
 */
void movesoko(Game *g, int x, int y);

/**
 * \fn void moveperso(Game *g, point *pos, int x, int y, char movenext)
 * \brief Fonction qui déplace le personnage
 * 
 * \param g Pointeur sur une structure Game
 * \param pos pointeur sur une structure point représentant la position du personnage
 * \param x entier représentant le déplacement du personnage sur l'axe horizontale (-1, 0 ou 1)
 * \param y entier représentant le déplacement du personnage sur l'axe verticale (-1, 0 ou 1)
 * \param movenext caractère représentant le personnage suivant s'il est sur le sol oou sur une case cible
 */
void moveperso(Game *g, int x, int y, char movenext);

/**
 * \fn void restart(Game *g, int lv)
 * \brief Fonction qui recommence un niveau depuis le début
 * 
 * \param g Pointeur sur une structure Game
 * \param lvl entier correspondant au niveau
 */
void restart(Game *g, int lv);

/**
 * \fn int win(char tabNiveau[])
 * \brief Fonction qui renvoie 0 lorsque toutes les caisses sont sur des case "sol cible"
 * 
 * \param tabNiveau tableau du niveau
 */
int win(char tabNiveau[]);

/**
 * \fn void affichetab(char tab[])
 * \brief Fonction qui affiche le tableau (11 lignes, 10 colonnes)
 * 
 * \param tab tableau à afficher
 */
void affichetab(char tab[]);

/**
 * \fn void createtablvl(Game *g, int n)
 * \brief Fonction de création d'un tableau qui contiendra le niveau
 *
 * \param g pointeur sur une structure Game.
 * \param n taille du tableau.
 */
void createtablvl(Game *g, int n);

/**
 * \fn void initGame(Game *g, void (*updatecharfunc)(char,int), void (*updatescreen)(char*))
 * \brief Fonction qui initialise tout les élements de la structure Game
 *
 * \param g Pointeur sur une structure Game
 * \param updatecharfunc Pointeur sur une fonction de mise à jour de caractère.
 * \param updatescreen Pointeur sur une fonction de mise à jour d'écran.
 */
void initGame(Game *g, void (*updatecharfunc)(char,int), void (*updatescreen)(char*));

/**
 * \fn void callGameUpdateScreen(Game *g)
 * \brief Fonction qui met à jour l'écran
 * 
 * \param g Pointeur sur une structure Game
 */
void callGameUpdateScreen(Game *g);

/**
 * \fn void callGameUpdateChar(Game *g, char movenext, int indexmove1)
 * \brief Fonction qui met à jour 
 * 
 * \param g Pointeur sur une structure Game
 */
void callGameUpdateChar(Game *g, char movenext, int indexmove1);

/**
 * \fn int score(Game *g)
 * \brief Fonction de calcul du score en fonction du temps et du nobre de déplacements
 * 
 * \param g Pointeur sur une structure Game
 */
int score(Game *g);

#endif

