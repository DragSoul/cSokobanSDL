/**
 * \file sdlsoko.h
 * \author Aurelien DOUARD, Anthony Bertrand
 * \brief fichier contenant le prototype des fonctions du sokoban (partie graphique)
 * \version 0.1
 * \date 13 janvier 2020
 *
 * fichier contenant le prototype des fonctions du sokoban (partie graphique)
 *
 */

#ifndef SDLD_H
#define SDLD_H

#define LC 50
#define WIDTH 10*LC
#define HEIGHT 11*LC
#define N 11

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <pthread.h>
#include <SDL/SDL_types.h>
#include <SDL/SDL_timer.h>
#include "fontutils.h"
#include "sokoban.h"

typedef struct{
    SDL_Rect *rect;
    void(*callback)(void*);
    void* arg;
    char content[20];
}button;

typedef struct{
    button *buttons;
    int len;
}allbutton;

typedef struct 
{
    char car;
    SDL_Surface *img;
}charimg;


/**
 * \fn void loadImg()
 * \brief Fonction qui ajoute toutes les images utilisées par le programme en mémoire
 * 
 */
void loadImg();

/**
 * \fn void boucleEv(Game *g, font* ftt)
 * \brief boucle du jeu
 * 
 * \param g pointeur sur une structure Game
 * \param ftt contient des caractère afin de pouvoir écrire avec la sdl
 */
void boucleEv(Game *g, font* ftt);

/**
 * \fn void updatechar(char toupdate, int index)
 * \brief 
 * 
 * \param toupdate 
 * \param index 
 * 
 */
void updatechar(char toupdate, int index);

/**
 * \fn void dessine(char tabNiveau[])
 * \brief dessine le niveau à l'écran
 * 
 * \param tabNiveau tableau contenant le niveau 
 * 
 */
void dessine();

/**
 * \fn void freeImg()
 * \brief libère l'espace mémoire occupé par les images
 * 
 */
void freeImg();

/**
 * \fn void menu(allbutton *buttontab, font * ftt)
 * \brief affiche le menu du jeu
 * 
 * \param buttontab pointeur sur structure allbutton
 * \param ftt contient des caractère afin de pouvoir écrire avec la sdl
 */
void menu(allbutton *buttontab, font * ftt);

/**
 * \fn void addallimg(int * index, char car, SDL_Surface *imgrect)
 * \brief Fonction qui ajoute une image utilisée par le programme en mémoire
 * 
 * \param index index de l'image dans le tableau
 * \param car caractère utilisé pour l'image
 * \param imgrect image
 */
void addallimg(int * index, char car, SDL_Surface *imgrect);

/**
 * \fn void graphic()
 * \brief fonction principale du fichier
 * 
 */
void graphic();

/**
 * \fn void loadlvl(void* game)
 * \brief fonction du troisième bouton qui lance le niveau sauvegardé dans le fichier sauv
 * 
 * \param g pointeur sur une structure Game
 * 
 */
void loadlvl(void* game);

/**
 * \fn void displaybtn(allbutton *allb, SDL_Surface *ecran, font *ftt)
 * \brief affiche les boutons
 * 
 * \param allb contient le tableau avec tout les boutons
 * \param ecran contient la fenetre sdl
 * \param ftt contient des caractère afin de pouvoir écrire avec la sdl
 * 
 */
void displaybtn(allbutton *allb, SDL_Surface *ecran, font *ftt);

/**
 * \fn int isinbutton(int x, int y,allbutton *buttontab)
 * \brief vérifie sur quel bouton on click
 * 
 * \param x coordonnée x de l'endroit où on a clické
 * \param y coordonnée y de l'endroit où on a clické
 * \param buttontab pointeur sur structure allbutton
 */
int isinbutton(int x, int y,allbutton *buttontab);

/**
 * \fn void displayonebtn(button btn, SDL_Surface *ecran, font *ftt, int r, int g, int b)
 * \brief affiche un bouton
 * 
 * \param btn correspond à un bouton
 * \param ecran contient la fenetre sdl
 * \param ftt contient des caractère afin de pouvoir écrire avec la sdl
 * \param r indice de rouge
 * \param g indice de bleu 
 * \param b indice de vert
 * 
 */
void displayonebtn(button btn, SDL_Surface *ecran, font *ftt, int r, int g, int b);

/**
 * \fn int timer(int oldtime, int ms)
 * \brief fonction qui compte les secondes
 * 
 * \param oldtime 
 * \param ms 
 * 
 */
int timer(int oldtime, int ms);

/**
 * \fn void selecLvl(void* nothing)
 * \brief lance l'écran de sélection des niveaux (not implemented)
 * 
 * 
 */
void selecLvl(void* nothing);

/**
 * \fn void EventMouseButton(SDL_Event event, font *ftt, int *count, allbutton *buttontab, int *indexbtn, int *tmpindexbtn)
 * \brief gère les évenements liés à la souris sur les boutons
 * 
 * \param event evenement attrapé
 * \param ftt contient des caractère afin de pouvoir écrire avec la sdl
 * \param count entier permettant de sortir de la boucle
 * \param buttontab pointeur sur structure allbutton
 * \param indexbtn 
 * \param tmpindexbtn 
 * 
 */
void EventMouseButton(SDL_Event event, font *ftt, int *count, allbutton *buttontab, int *indexbtn, int *tmpindexbtn);

/**
 * \fn void initrect(SDL_Rect *rect, int x, int y, int w, int h)
 * \brief initialise les paramètre d'une structure SDL_Rect
 * 
 * \param rect structure SDL_Rect qu'on créer
 * \param x coordonnée x de rect
 * \param y coordonnée y de rect
 * \param w largeur de rect
 * \param h hauteur de rect
 * 
 */
void initrect(SDL_Rect *rect, int x, int y, int w, int h);

/**
 * \fn void addbutton(allbutton *buttontab, SDL_Rect *rect, void(*callback)(void*), void* arg, char* strcontent)
 * \brief fonction permettant de créer des boutons en sdl
 * 
 * \param buttontab pointeur sur structure allbutton
 * \param rect pointeur sur structure SDL_Rect, notre bouton
 * \param callback pointeur sur fonction, permet de lier une fonction à un bouton
 * \param arg argument pris par callback
 * \param strcontent contenu du bouton
 */
void addbutton(allbutton *buttontab, SDL_Rect *rect, void(*callback)(void*), void* arg, char* strcontent);

/**
 * \fn void endLvl(Game *g, font *ftt)
 * \brief fonction de fin de niveau (calcul et affichage du score)
 * 
 * \param g pointeur sur une structure Game
 * \param ftt contient des caractère afin de pouvoir écrire avec la sdl
 */
void endLvl(Game *g, font *ftt);

/**
 * \fn void play(void* game)
 * \brief fonction du premier bouton qui lance les niveau un par un
 * 
 * \param g pointeur sur une structure Game
 * 
 */
void play(void* game);

//images utilisées
charimg allimage[8];

SDL_Rect positionperso;
SDL_Surface * ecran;
#endif