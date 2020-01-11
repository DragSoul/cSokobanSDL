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
    addallimg(&index, 'm', SDL_LoadBMP("images/menu.bmp"));
    addallimg(&index, '@', SDL_LoadBMP("images/joseph_pixel.bmp"));
    addallimg(&index, '$', SDL_LoadBMP("images/caisse.bmp"));
    addallimg(&index, '*', SDL_LoadBMP("images/caissesombre.bmp"));
    addallimg(&index, '.', SDL_LoadBMP("images/solcible.bmp"));
    addallimg(&index, '+', SDL_LoadBMP("images/joseph_cible.bmp"));
    addallimg(&index, '#', SDL_LoadBMP("images/mur.bmp"));
    addallimg(&index, 's', SDL_LoadBMP("images/sol.bmp"));
}

void boucleEv(){
    int cont = 1;
    point pos;
    pos = getposperso();
    SDL_Event event;
    while(cont){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                cont = 0;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        //y-1
                        move(&pos,0,-1);
                        cont = win();
                        break;

                    case SDLK_DOWN:
                        //y+1
                        move(&pos,0,1);
                        cont = win();
                        break;

                    case SDLK_LEFT:
                        //x-1
                        move(&pos,-1,0);
                        cont = win();
                        break;

                    case SDLK_RIGHT:
                        //x+1
                        move(&pos,1,0);
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
        }
    }
}

void menu(){
    int count = 1;
    SDL_Event event;
    SDL_Rect pos;
    pos.x = 0;
    pos.y = 0;
    SDL_BlitSurface(allimage[0].img, NULL, ecran, &pos);
    SDL_Flip(ecran);
    while(count){
        SDL_WaitEvent(&event);
        switch (event.type){
            case SDL_MOUSEBUTTONUP:
                //bouton play (je gruge un peu avec les pixels)
                if(event.button.y > 364 && event.button.y < 419
                && event.button.x > 124 && event.button.x < 381){
                    count = 0; //si plusieurs boutons, faire de menu() la fonction qui fait les appel
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