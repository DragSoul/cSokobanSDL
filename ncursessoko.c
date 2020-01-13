/**
 * \file ncursessoko.c
 * \author Aurelien DOUARD, Anthony Bertrand
 * \brief fichier contenant les fonctions utilisées pour jouer au sokoban dans la console
 * \version 0.1
 * \date 13 janvier 2020
 *
 * fichier contenant les fonctions utilisées pour jouer au sokoban dans la console
 *
 */

#include "ncursessoko.h"

void updateshell(char toudate, int index){
    return;
}

void shelldisplaychar(char todisplay){
    switch (todisplay)
    {
    case SOL:
        attron(COLOR_PAIR(1));
        printw("   ");
        break;
    case CAISSE:
        attron(COLOR_PAIR(2));
        printw(" ¤ ");
        break;

    case MUR:
        attron(COLOR_PAIR(5));
        printw("   ");
        break;
    case CAISSECIBLE:
        attron(COLOR_PAIR(3));
        printw(" ¤ ");
        break;
    case PERSCIBLE:
        attron(COLOR_PAIR(8));
        printw(" @ ");
        break;
    case SOLCIBLE:
        attron(COLOR_PAIR(9));
        printw(" x ");
        break;
    case PERS:
        attron(COLOR_PAIR(7));
        printw(" @ ");
        break;
    default:
        break;
    }
    attron(COLOR_PAIR(0));
}

void initcolors(){
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_RED);
    init_pair(3, COLOR_WHITE, COLOR_GREEN);
    init_pair(4, COLOR_WHITE, COLOR_CYAN);
    init_pair(5, COLOR_BLACK, COLOR_WHITE);
    init_pair(6, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(7, COLOR_BLACK, COLOR_YELLOW);
    init_pair(8, COLOR_CYAN, COLOR_YELLOW);
    init_pair(9, COLOR_CYAN, COLOR_BLACK);
}

void dessineshell(char tabNiveau[]){
    clear();
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 10; j++){
            if(tabNiveau[i*N+j]=='+'){
                shelldisplaychar('@');
            }
            else{
                shelldisplaychar(tabNiveau[i*N+j]);
            }
            
        }
        printw("\n");
    }
}

void boucleshell(Game *g){
    int cont = 1;
    int ch;
    while((ch = getch()) != 'q')
    {
        switch(ch)
        {
            case KEY_UP: 
                movesoko(g,0,-1);
                break;
            case KEY_DOWN: 
                movesoko(g,0,1);
                break;
            case KEY_LEFT: 
                movesoko(g,-1,0);
                break;
            case KEY_RIGHT: 
                movesoko(g,1,0);
                break;
            case 'r':
                //restart level
                restart(g,1);
                break;
        }
        if(g->badcaisse == 0){
            cont = 0;
        }
        if(cont == 0){
            break;
        }
    }
}

void console(){
    //init curses
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    start_color();
    initcolors();

    Game game;
    game.extime = 0;

    game.updatecharfunc = &updateshell;
    game.updatescreen = &dessineshell;

    srand(time(NULL));
    createtablvl(&game, 110);

    FILE *flot = fopen("niveau1", "r");
    if(flot == NULL){
        printw("pb ouverture fichier en lecture\n");
        exit(1);
    }

    creationniveau(&game, flot);
    fclose(flot);
    game.clockStart = clock();
    boucleshell(&game);
    game.clockEnd = clock();
    game.extime = game.extime + (float) (game.clockEnd-game.clockStart)/CLOCKS_PER_SEC; //seconde
    printw("time : %f\nnb Moves : %d\n", game.extime, game.nbMove);
    refresh();
    getch();
    endwin();
}