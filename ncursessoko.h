/**
 * \file ncursessoko.h
 * \author Aurelien DOUARD, Anthony Bertrand
 * \brief fichier contenant le prototype des fonctions du sokoban (jouable dans la console)
 * \version 0.1
 * \date 13 janvier 2020
 *
 * fichier contenant le prototype des fonctions du sokoban (jouable dans la console)
 *
 */

#ifndef NCSOKO_H
#define NCSOKO_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "sokoban.h"

/**
 * \fn void updateshell(char toudate, int index)
 * \brief fonction pour mettre à jour un caractère dans la console
 * 
 * \param toudate caractère a changer
 * \param index index où changer le caractère
 */
void updateshell(char toudate, int index);

/**
 * \fn void shelldisplaychar(char todisplay)
 * \brief fonction qui défini comment afficher un caractère dans la console
 * 
 * \param todisplay caractère a afficher
 */
void shelldisplaychar(char todisplay);

/**
 * \fn void initcolors()
 * \brief pour initialiser les couleurs utiliser dans la console
 * 
 */
void initcolors();

/**
 * \fn void dessineshell(char tabNiveau[])
 * \brief fonction qui dessine dans la console le niveau du jeu
 * 
 * \param tabNiveau tableau de caractère du niveau
 */
void dessineshell(char tabNiveau[]);

/**
 * \fn void boucleshell(Game *g)
 * \brief boucle d'évenement pour le jeu en console
 * 
 * \param g pointeur sur le game
 */
void boucleshell(Game *g);

/**
 * \fn void console()
 * \brief fonction pour lancer le jeu en mode console
 * 
 */
void console();

#endif