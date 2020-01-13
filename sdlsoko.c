/**
 * \file sdlsoko.c
 * \author Aurelien DOUARD, Anthony Bertrand
 * \brief fichier contenant les fonctions utilisées pour jouer au sokoban dans une fenêtre sdl
 * \version 0.1
 * \date 13 janvier 2020
 *
 * fichier contenant les fonctions utilisées pour jouer au sokoban dans une fenêtre sdl
 *
 */

#include "sdlsoko.h"


/**
 * \fn void addallimg(int * index, char car, SDL_Surface *imgrect)
 * \brief Fonction qui ajoute une image utilisée par le programme en mémoire
 * 
 * \param index index de l'image dans le tableau
 * \param car caractère utilisé pour l'image
 * \param imgrect image
 */
void addallimg(int * index, char car, SDL_Surface *imgrect){
    if(imgrect == NULL){
        printf("pas trouvé img\n");
        exit(1);
    }
    charimg img;
    img.car = car;
    img.img = imgrect;
    allimage[(*index)] = img;
    *index  = *index +1;
}

/**
 * \fn void loadImg()
 * \brief Fonction qui ajoute toutes les images utilisées par le programme en mémoire
 * 
 */
void loadImg(){
    int index = 0;
    addallimg(&index, MUR, SDL_LoadBMP("images/menu.bmp"));
    addallimg(&index, PERS, SDL_LoadBMP("images/joseph_pixel.bmp"));
    addallimg(&index, CAISSE, SDL_LoadBMP("images/caisse.bmp"));
    addallimg(&index, CAISSECIBLE, SDL_LoadBMP("images/caissesombre.bmp"));
    addallimg(&index, SOLCIBLE, SDL_LoadBMP("images/solcible.bmp"));
    addallimg(&index, PERSCIBLE, SDL_LoadBMP("images/joseph_cible.bmp"));
    addallimg(&index, MUR, SDL_LoadBMP("images/mur.bmp"));
    addallimg(&index, SOL, SDL_LoadBMP("images/sol.bmp"));
}


/**
 * \fn void boucleEv(Game *g, font* ftt)
 * \brief boucle du jeu
 * 
 * \param g pointeur sur une structure Game
 * \param ftt contient des caractère afin de pouvoir écrire avec la sdl
 */
void boucleEv(Game *g, font* ftt){
    
    int cont = 1;
    point pos;
    pos = g->posperso;
    SDL_Event event;

    //display move and timer 
    char buffer[30]; 
    SDL_Rect desttimer;
    desttimer.x = 10;
    desttimer.y = 10;
    SDL_Rect destmove;
    destmove.x = 10;
    destmove.y = 40;
    int keydown = 0;
    //fin display
    int oldtime = SDL_GetTicks();
    int time = 0;
    printf("%d\n", oldtime);
    while(cont){

        if(timer(oldtime, 1000)){
            oldtime = SDL_GetTicks();
            time += 1;
        }
        //dispaly move and timer
        sprintf(buffer, "time : %d s", time);
        displaystring(buffer, ecran, desttimer,ftt);
        sprintf(buffer, "%d", g->nbMove);
        displaystring(buffer, ecran, destmove,ftt);
        SDL_UpdateRect(ecran, destmove.x, destmove.x, 100, 24);
        SDL_UpdateRect(ecran, desttimer.x, desttimer.x, 100, 24);

        SDL_PollEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                cont = 0;
            case SDL_KEYDOWN:
                if(keydown != 0){
                    break;
                }
                keydown = 1;
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        //y-1
                        movesoko(g,&pos,0,-1);
                        break;

                    case SDLK_DOWN:
                        //y+1
                        movesoko(g,&pos,0,1);
                        break;

                    case SDLK_LEFT:
                        //x-1
                        movesoko(g,&pos,-1,0);
                        break;

                    case SDLK_RIGHT:
                        //x+1
                        movesoko(g,&pos,1,0);
                        break;

                    case 'r':
                        //restart level
                        restart(g,g->curentlvl);
                        pos = g->posperso;
                        break;

                    //affiche tab (debug)
                    case 'd':
                        printf("\ntab = \n");
                        affichetab(g->tabNiveau);
                        break;

                    case 's':
                        save();
                        break;

                    case 'q':
                        cont = 0;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                keydown = 0;
                break;
            default:
                break;
        }
        if(g->badcaisse == 0){
            endLvl(g, ftt);
            if(g->curentlvl == 2){
                cont = 0;
            }else{
                g->curentlvl +=1;
                restart(g,g->curentlvl);
                pos = g->posperso;
            }
        }
    }
}


/**
 * \fn void endLvl(Game *g, font *ftt)
 * \brief fonction de fin de niveau (calcul et affichage du score)
 * 
 * \param g pointeur sur une structure Game
 * \param ftt contient des caractère afin de pouvoir écrire avec la sdl
 */
void endLvl(Game *g, font *ftt){
    g->clockEnd = clock();
    g->extime = g->extime + (float) (g->clockEnd-g->clockStart)/CLOCKS_PER_SEC; //seconde
    char bufscore[40];
    sprintf(bufscore, "lvl : %d score : %d", g->curentlvl, score(g));
    SDL_Rect posScore;
    initrect(&posScore, 300,200, 100,24);
    displaystring(bufscore, ecran, posScore, ftt);
    SDL_Flip(ecran);
    SDL_Delay(1500);
}


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
void addbutton(allbutton *buttontab, SDL_Rect *rect, void(*callback)(void*), void* arg, char* strcontent){
    button b;
    b.callback = callback;
    b.rect = rect;
    b.arg = arg;
    strcpy(b.content, strcontent);
    buttontab->buttons[buttontab->len] = b;
    buttontab->len += 1;
}


/**
 * \fn int isinbutton(int x, int y,allbutton *buttontab)
 * \brief vérifie sur quel bouton on click
 * 
 * \param x coordonnée x de l'endroit où on a clické
 * \param y coordonnée y de l'endroit où on a clické
 * \param buttontab pointeur sur structure allbutton
 */
int isinbutton(int x, int y,allbutton *buttontab){
    for(int i = 0; i < buttontab->len; i++){
        if(y > buttontab->buttons[i].rect->y && y < buttontab->buttons[i].rect->y + buttontab->buttons[i].rect->h
                    && x > buttontab->buttons[i].rect->x && x < buttontab->buttons[i].rect->x + buttontab->buttons[i].rect->w){
            return i;
        }
    }
    return -1;
}


/**
 * \fn void menu(allbutton *buttontab, font * ftt)
 * \brief affiche le menu du jeu
 * 
 * \param buttontab pointeur sur structure allbutton
 * \param ftt contient des caractère afin de pouvoir écrire avec la sdl
 */
void menu(allbutton *buttontab, font * ftt){
    int count = 1;
    SDL_Event event;
    SDL_Rect pos;
    pos.x = 0;
    pos.y = 0;
    int indexbtn;
    int tmpindexbtn = -1;
    SDL_BlitSurface(allimage[0].img, NULL, ecran, &pos);
    displaybtn(buttontab, ecran, ftt);
    SDL_Flip(ecran);
    while(count){
        SDL_WaitEvent(&event);
        if(event.type == SDL_QUIT){
            exit(0);
        }
        EventMouseButton(event, ftt, &count, buttontab,&indexbtn, &tmpindexbtn);
    }
}


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
void EventMouseButton(SDL_Event event, font *ftt, int *count, allbutton *buttontab, int *indexbtn, int *tmpindexbtn){
    switch (event.type){
            case SDL_MOUSEMOTION:
                *indexbtn = isinbutton(event.motion.x, event.motion.y, buttontab);
                if(*indexbtn != -1){
                    if(*tmpindexbtn != -1){
                        displayonebtn(buttontab->buttons[*tmpindexbtn], ecran, ftt, 80,80,80);
                    }
                    *tmpindexbtn = *indexbtn;
                    displayonebtn(buttontab->buttons[*indexbtn], ecran, ftt, 150,150,150);
                }else{
                    if(*tmpindexbtn != -1) {
                        displayonebtn(buttontab->buttons[*tmpindexbtn], ecran, ftt, 80, 80, 80);
                    }
                }
                dessine(NULL);
                break;
            case SDL_MOUSEBUTTONUP:
                *indexbtn = isinbutton(event.button.x, event.button.y, buttontab);
                if(*indexbtn != -1){
                    buttontab->buttons[*indexbtn].callback(buttontab->buttons[*indexbtn].arg);
                    *count = 0;
                }
                break;

            default:
                break;
        }
}


/**
 * \fn void updatechar(char toupdate, int index)
 * \brief 
 * 
 * \param toupdate 
 * \param index 
 * 
 */
void updatechar(char toupdate, int index){
    int y = index / N;
    int x = index - (y * N);
    SDL_Rect rect;
    rect.x = x*LC;
    rect.y = y*LC;
    for(int i = 0; i<8; i++){
        if(toupdate == allimage[i].car){
            SDL_BlitSurface(allimage[i].img, NULL, ecran, &rect);
        }
    }
}


/**
 * \fn void dessine(char tabNiveau[])
 * \brief dessine le niveau à l'écran
 * 
 * \param tabNiveau tableau contenant le niveau 
 * 
 */
void dessine(char tabNiveau[]){//ça sert à rien du coup
    SDL_Flip(ecran);
}


/**
 * \fn void freeImg()
 * \brief libère l'espace mémoire occupé par les images
 * 
 */
void freeImg(){
    for(int i = 0; i<8; i++){
        SDL_FreeSurface(allimage[i].img);
    }
}


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
void displayonebtn(button btn, SDL_Surface *ecran, font *ftt, int r, int g, int b){
    SDL_Rect tmprect;
    SDL_FillRect(ecran, btn.rect, SDL_MapRGB(ecran->format,r,g,b));
    tmprect.x = btn.rect->x + 10;
    tmprect.y = btn.rect->y + 10;
    displaystring(btn.content, ecran, tmprect, ftt);
}


/**
 * \fn void displaybtn(allbutton *allb, SDL_Surface *ecran, font *ftt)
 * \brief affiche les boutons
 * 
 * \param allb contient le tableau avec tout les boutons
 * \param ecran contient la fenetre sdl
 * \param ftt contient des caractère afin de pouvoir écrire avec la sdl
 * 
 */
void displaybtn(allbutton *allb, SDL_Surface *ecran, font *ftt){
    for(int i = 0; i < allb->len; i++){
         displayonebtn(allb->buttons[i], ecran, ftt,80,80,80);
    }
}


/**
 * \fn void play(void* game)
 * \brief fonction du premier bouton qui lance les niveau un par un
 * 
 * \param g pointeur sur une structure Game
 * 
 */
void play(void* game){
    printf("nothing\n");
    FILE *flot = fopen("niveau0", "r");
    if(flot == NULL){
        printf("pb ouverture fichier en lecture\n");
        exit(1);
    }
    creationniveau((Game*)game, flot);
    ((Game*)game)->curentlvl = 0;
    fclose(flot);
}


/**
 * \fn void selecLvl(void* nothing)
 * \brief lance l'écran de sélection des niveaux (not implemented)
 * 
 * 
 */
void selecLvl(void* nothing){
    printf("ajkbfhksbhkfbz\n");
}


/**
 * \fn void loadlvl(void* game)
 * \brief fonction du troisième bouton qui lance le niveau sauvegardé dans le fichier sauv
 * 
 * \param g pointeur sur une structure Game
 * 
 */
void loadlvl(void* game){
    load((Game*)game);
}


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
void initrect(SDL_Rect *rect, int x, int y, int w, int h){
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
}


/**
 * \fn void graphic()
 * \brief fonction principale du fichier
 * 
 */
void graphic(){
    Game game;
    initGame(&game, &updatechar, &dessine);

    //int font
    font *ftt;
    ftt = readfontinfo(220, "images/font.fnt","images/font_0.bmp");

    //btn table
    button b[20];
    allbutton allb;
    allb.len = 0;
    allb.buttons = b;

    //btn pos
    SDL_Rect rectbtnPlay;
    initrect(&rectbtnPlay, 124,364,257,55);

    //btn pos
    SDL_Rect rectbtnSelec;
    initrect(&rectbtnSelec, 124,421,257,55);

    //btn pos
    SDL_Rect rectbtnCharge;
    initrect(&rectbtnCharge, 124,478,257,55);

    //add btn to allb
    addbutton(&allb, &rectbtnPlay, &play, (void*)&game, "Play");
    addbutton(&allb, &rectbtnSelec, &selecLvl, NULL, "Level");
    addbutton(&allb, &rectbtnCharge, &loadlvl, (void*)&game, "Load");

    loadImg();
    srand(time(NULL));
    createtablvl(&game,110);
    // Init
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr,"\nUnable to initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if((ecran = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE)) == NULL){
        fprintf(stderr, "Erreur VideoMode %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    menu(&allb, ftt);

    // Légende de la fenêtre
    SDL_WM_SetCaption("Sokoban", NULL);

    //load(); //commenter la création du lvl pour l'utiliser
    
    SDL_Flip(ecran);
    game.clockStart = clock();
    boucleEv(&game,ftt);
    game.clockEnd = clock();
    game.extime = game.extime + (float) (game.clockEnd-game.clockStart)/CLOCKS_PER_SEC; //seconde
    int superscore = score(&game);
    printf("time : %f\nnb Moves : %d, score : %d\n", game.extime, game.nbMove, superscore);
    freeImg();

    //free font
    freefont(ftt);

    SDL_Quit();
}


/**
 * \fn int timer(int oldtime, int ms)
 * \brief fonction qui compte les secondes
 * 
 * \param oldtime 
 * \param ms 
 * 
 */
int timer(int oldtime, int ms){
    int curenttime = SDL_GetTicks();
    if(curenttime - oldtime > ms){
        return 1;
    }
    return 0;
}
