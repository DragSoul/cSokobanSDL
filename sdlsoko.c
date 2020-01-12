#include "sdlsoko.h"


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

void boucleEv(font* ftt){
    
    int cont = 1;
    point pos;
    pos = getposperso();
    SDL_Event event;

    //display move and timer
    char buftime[20]; 
    char bufmove[10]; 
    SDL_Rect desttimer;
    desttimer.x = 10;
    desttimer.y = 10;
    SDL_Rect destmove;
    destmove.x = 10;
    destmove.y = 40;
    nbMove = 0;
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
        sprintf(buftime, "time : %d s", time);
        displaystring(buftime, ecran, desttimer,ftt);
        sprintf(bufmove, "%d", nbMove);
        displaystring(bufmove, ecran, destmove,ftt);
        SDL_UpdateRect(ecran, destmove.x, destmove.x, 100, 24);
        SDL_UpdateRect(ecran, desttimer.x, desttimer.x, 100, 24);
        //dessine();
        // fin display

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
                        movesoko(&pos,0,-1);
                        cont = win();
                        break;

                    case SDLK_DOWN:
                        //y+1
                        movesoko(&pos,0,1);
                        cont = win();
                        break;

                    case SDLK_LEFT:
                        //x-1
                        movesoko(&pos,-1,0);
                        cont = win();
                        break;

                    case SDLK_RIGHT:
                        //x+1
                        movesoko(&pos,1,0);
                        cont = win();
                        break;

                    case 'r':
                        //restart level
                        restart(1);
                        pos = getposperso();
                        break;

                    //affiche tab (debug)
                    case 'd':
                        printf("\ntab = \n");
                        affichetab(tabNiveau);
                        break;

                    case 's':
                        save();
                        break;

                    case 'q':
                        cont = 0;
                        break;
                }
                break;
            case SDL_KEYUP:
                keydown = 0;
                break;
        }
    }
}

void addbutton(allbutton *buttontab, SDL_Rect *rect, void(*callback)(void*), void* arg, char* strcontent){
    button b;
    b.callback = callback;
    b.rect = rect;
    b.arg = arg;
    strcpy(b.content, strcontent);
    buttontab->buttons[buttontab->len] = b;
    buttontab->len += 1;
}

int isinbutton(int x, int y,allbutton *buttontab){
    for(int i = 0; i < buttontab->len; i++){
        if(y > buttontab->buttons[i].rect->y && y < buttontab->buttons[i].rect->y + buttontab->buttons[i].rect->h
                    && x > buttontab->buttons[i].rect->x && x < buttontab->buttons[i].rect->x + buttontab->buttons[i].rect->w){
            return i;
        }
    }
    return -1;
}

void menu(allbutton *buttontab, font * ftt){
    int count = 1;
    SDL_Event event;
    SDL_Rect pos;
    pos.x = 0;
    pos.y = 0;
    int indexbtn;
    int tmpindexbtn;
    SDL_BlitSurface(allimage[0].img, NULL, ecran, &pos);
    dsiplaybtn(buttontab, ecran, ftt);
    SDL_Flip(ecran);
    while(count){
        SDL_WaitEvent(&event);
        switch (event.type){
            case SDL_MOUSEMOTION:
                indexbtn = isinbutton(event.motion.x, event.motion.y, buttontab);
                if(indexbtn != -1){
                    tmpindexbtn = indexbtn;
                    dsiplayonebtn(buttontab->buttons[indexbtn], ecran, ftt, 120,120,120);
                }else{
                    dsiplayonebtn(buttontab->buttons[tmpindexbtn], ecran, ftt, 80,80,80);
                }
                dessine();
                break;
            case SDL_MOUSEBUTTONUP:
                indexbtn = isinbutton(event.button.x, event.button.y, buttontab);
                if(indexbtn != -1){
                    buttontab->buttons[indexbtn].callback(buttontab->buttons[indexbtn].arg);
                    count = 0;
                }
                break;
        
        default:
            break;
        }
    }
}

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

void dessine(){
    SDL_Flip(ecran);
}

void freeImg(){
    for(int i = 0; i<8; i++){
        SDL_FreeSurface(allimage[i].img);
    }
}

void printnth(void* nothing){
    printf("nothing\n");
}

void dsiplayonebtn(button btn, SDL_Surface *ecran, font *ftt, int r, int g, int b){
    SDL_Rect tmprect;
    SDL_FillRect(ecran, btn.rect, SDL_MapRGB(ecran->format,r,g,b));
    tmprect.x = btn.rect->x + 10;
    tmprect.y = btn.rect->y + 10;
    displaystring(btn.content, ecran, tmprect, ftt);
}

void dsiplaybtn(allbutton *allb, SDL_Surface *ecran, font *ftt){
    for(int i = 0; i < allb->len; i++){
         dsiplayonebtn(allb->buttons[i], ecran, ftt,80,80,80);
    }
}



void graphic(){
    //int font
    font *ftt;
    ftt = readfontinfo(220, "images/font.fnt","images/font_0.bmp");

    //btn table
    button b[20];
    allbutton allb;
    allb.len = 0;
    allb.buttons = b;

    //btn pos
    SDL_Rect rectbtn;
    rectbtn.x = 124;
    rectbtn.y = 364;
    rectbtn.w = 257;
    rectbtn.h = 55;

    //add btn to allb
    addbutton(&allb, &rectbtn, &printnth, NULL, "Play");

    setupdatecharfunc(&updatechar);
    setupdatescreenfunc(&dessine);
    loadImg();
    srand(time(NULL));
    createtablvl(110);
    // Init
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr,"\nUnable to initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if((ecran = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE)) == NULL){
        fprintf(stderr, "Erreur VideoMode %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    FILE *flot = fopen("niveau1", "r");
    if(flot == NULL){
        printf("pb ouverture fichier en lecture\n");
        exit(1);
    }
    //printf("key repit : %d\n",SDL_EnableKeyRepeat(0, 0));

    menu(&allb, ftt);
    // Légende de la fenêtre
    SDL_WM_SetCaption("Sokoban", NULL);
    creationniveau(flot);
    fclose(flot);
    //load(); //commenter la création du lvl pour l'utiliser
    
    SDL_Flip(ecran);
    clockStart = clock();
    boucleEv(ftt);
    clockEnd = clock();
    extime = extime + (float) (clockEnd-clockStart)/CLOCKS_PER_SEC; //seconde
    printf("time : %f\nnb Moves : %d\n", extime, nbMove);
    freeImg();
    //free font
    freefont(ftt);
    SDL_Quit();
}

int timer(int oldtime, int ms){
    int curenttime = SDL_GetTicks();
    if(curenttime - oldtime > ms){
        return 1;
    }
    return 0;
}
