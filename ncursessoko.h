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

void updateshell(char toudate, int index);
void shelldisplaychar(char todisplay);
void initcolors();
void dessineshell(char tabNiveau[]);
void boucleshell(Game *g);
void console();

#endif