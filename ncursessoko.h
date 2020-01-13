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