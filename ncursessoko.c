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

void dessineshell(){
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

void boucleshell(){
    int cont = 1;
    point pos;
    pos = getposperso();
    int ch;
    while((ch = getch()) != 'q')
    {
        switch(ch)
        {
            case KEY_UP: 
                movesoko(&pos,0,-1);
                cont = win();
                break;
            case KEY_DOWN: 
                movesoko(&pos,0,1);
                cont = win();
                break;
            case KEY_LEFT: 
                movesoko(&pos,-1,0);
                cont = win();
                break;
            case KEY_RIGHT: 
                movesoko(&pos,1,0);
                cont = win();
                break;
            case 'r':
                //restart level
                restart(1);
                pos = getposperso();
                break;
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

    setupdatecharfunc(&updateshell);
    setupdatescreenfunc(&dessineshell);

    srand(time(NULL));
    createtablvl(110);

    FILE *flot = fopen("niveau1", "r");
    if(flot == NULL){
        printw("pb ouverture fichier en lecture\n");
        exit(1);
    }

    creationniveau(flot);
    fclose(flot);

    clockStart = clock();
    boucleshell();
    clockEnd = clock();
    extime = extime + (float) (clockEnd-clockStart)/CLOCKS_PER_SEC; //seconde
    printw("time : %f\nnb Moves : %d\n", extime, nbMove);
    refresh();
    getch();
    endwin();
}