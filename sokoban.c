#include "sokoban.h"

int main(int argc, char ** argv){
    loadImg();
    srand(time(NULL));
    tabNiveau = malloc(sizeof(char)*110);
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

    menu();
    //rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, LC, LC, 32, 0, 0, 0, 0);
    //SDL_FillRect(rectangle, NULL, SDL_MapRGB(rectangle->format, 255, 255, 255));
    // Légende de la fenêtre
    SDL_WM_SetCaption("Sokoban", NULL);
    creationniveau1(flot);
    
    SDL_Flip(ecran);
    boucleEv();


    freeImg();
    SDL_Quit();
    fclose(flot);
    return EXIT_SUCCESS;
}

void loadImg(){
    imgmenu = SDL_LoadBMP("images/menu.bmp");
    imgperso = SDL_LoadBMP("images/joseph_pixel.bmp");
    imgcaisse1 = SDL_LoadBMP("images/caisse.bmp");
    imgcaisse2 = SDL_LoadBMP("images/caissesombre.bmp");
    imgsol = SDL_LoadBMP("images/sol.bmp");
    imgdest = SDL_LoadBMP("images/solcible.bmp");
    imgmur = SDL_LoadBMP("images/mur.bmp");
    imgpersodest = SDL_LoadBMP("images/joseph_cible.bmp");
    if(imgperso == NULL || imgcaisse1 == NULL ||imgcaisse2 == NULL ||imgsol == NULL ||imgdest == NULL ||imgmur == NULL || imgpersodest == NULL){
        printf("pas trouvé img\n");
        exit(1);
    }
}

void freeImg(){
    SDL_FreeSurface(imgmenu);
    SDL_FreeSurface(imgperso);
    SDL_FreeSurface(imgcaisse1);
    SDL_FreeSurface(imgcaisse2);
    SDL_FreeSurface(imgsol);
    SDL_FreeSurface(imgdest);
    SDL_FreeSurface(imgmur);
    SDL_FreeSurface(imgpersodest);
}

void menu(){
    int count = 1;
    SDL_Event event;
    SDL_Rect pos;
    pos.x = 0;
    pos.y = 0;
    SDL_BlitSurface(imgmenu, NULL, ecran, &pos);
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

//création d'un tableau pour avoir le niveau en mémoire
void creationniveau1(FILE *flot){
    char c;
    int i = 0, j = 0;
    SDL_Rect pos;
    pos.x = 0;
    pos.y = 0;
    while((c = fgetc(flot)) != EOF){
        switch(c){
            //sol
            case 's':
                tabNiveau[i*N + j] = c;
                j++;
                SDL_BlitSurface(imgsol, NULL, ecran, &pos);
                pos.x += LC;
                break;
            //mur
            case '#':
                tabNiveau[i*N + j] = c;
                j++;
                SDL_BlitSurface(imgmur, NULL, ecran, &pos);
                pos.x += LC;
                break;
            //caisse1
            case '$':
                tabNiveau[i*N + j] = c;
                j++;
                SDL_BlitSurface(imgcaisse1, NULL, ecran, &pos);
                pos.x += LC;
                break;
            //caisse2
            case '*':
                tabNiveau[i*N + j] = c;
                j++;
                SDL_BlitSurface(imgcaisse2, NULL, ecran, &pos);
                pos.x += LC;
                break;
            //dest
            case '.':
                tabNiveau[i*N + j] = c;
                j++;
                SDL_BlitSurface(imgdest, NULL, ecran, &pos);
                pos.x += LC;
                break;
            //perso
            case '@':
                tabNiveau[i*N + j] = c;
                j++;
                SDL_BlitSurface(imgperso, NULL, ecran, &pos);
                positionperso = pos;
                pos.x += LC;
                break;
            //perso sur dest
            case '+':
                tabNiveau[i*N + j] = c;
                j++;
                SDL_BlitSurface(imgpersodest, NULL, ecran, &pos);
                pos.x += LC;
                break;

            case '\n':
                i++;
                j = 0;
                pos.x = 0;
                pos.y += LC;
                break;
        }
    }
    SDL_Flip(ecran);
}

void boucleEv(){
    int cont = 1;
    int i = positionperso.y/LC;
    int j = positionperso.x/LC;
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
                        move(&i,&j,0,-1);
                        cont = win();
                        break;

                    case SDLK_DOWN:
                        //y+1
                        move(&i,&j,0,1);
                        cont = win();
                        break;

                    case SDLK_LEFT:
                        //x-1
                        move(&i,&j,-1,0);
                        cont = win();
                        break;

                    case SDLK_RIGHT:
                        //x+1
                        move(&i,&j,1,0);
                        cont = win();
                        break;

                    case 'r':
                        //restart level
                        restart(1);
                        i = positionperso.y/LC;
                        j = positionperso.x/LC;
                        break;

                    //affiche tab (debug)
                    case 'd':
                        printf("\ntab = \n");
                        affichetab(tabNiveau);
                        break;

                    case 'q':
                        cont = 0;
                        break;
                }
        }
    }
}

void restart(int lv){
    char filename[8];
    sprintf(filename, "niveau%d", lv);
    FILE *flot = fopen(filename, "r");
    if(flot == NULL){
        printf("pb ouverture fichier en lecture\n");
        exit(1);
    }
    creationniveau1(flot);
    fclose(flot);
}

void movecaisse(int indexmove2, int x, int y){
    if(tabNiveau[indexmove2] == 's'){
        tabNiveau[indexmove2] = '$';
        updatechar('$', indexmove2);
    }
    else{
        tabNiveau[indexmove2] = '*';
        updatechar('*', indexmove2);
    }
}

int canMoveCaisse(int indexmove2){
    return tabNiveau[indexmove2] != '#' && tabNiveau[indexmove2] != '$' && tabNiveau[indexmove2] != '*';
}

void updatechar(char toupdate, int index){
    //char chars[7]= {'s','$','#','*','+','.','@'};
    int y = index / N;
    int x = index - (y * N);
    SDL_Rect rect;
    rect.x = x*LC;
    rect.y = y*LC;
    //todo make struct {char, sdlimage} and make func to get sdl image with char
    switch(toupdate){
        case 's':
            SDL_BlitSurface(imgsol, NULL, ecran, &rect); // display s
            break;
        case '$':
            SDL_BlitSurface(imgcaisse1, NULL, ecran, &rect); // display $
            break;
        case '#':
            SDL_BlitSurface(imgmur, NULL, ecran, &rect); // display #
            break;
        case '*':
            SDL_BlitSurface(imgcaisse2, NULL, ecran, &rect); // display *
            break;
        case '+':
            SDL_BlitSurface(imgpersodest, NULL, ecran, &rect); // display +
            break;
        case '.':
            SDL_BlitSurface(imgdest, NULL, ecran, &rect); // display .
            break;
        case '@':
            SDL_BlitSurface(imgperso, NULL, ecran, &rect); // display @
            break;
    }
}

void move(int *i, int *j, int x, int y){
    int curentIndex = (*i)*N + (*j);
    int indexmove1 = ((*i)+y)*N + (*j)+x;
    int indexmove2 = ((*i)+(2*y))*N + (*j)+(2*x);
    switch(tabNiveau[indexmove1]){

        //mur
        case '#':
            break;
        //caisse1
        case '$':
            if(canMoveCaisse(indexmove2)){
                //move caisse
                movecaisse(indexmove2, x, y);
                moveperso(i,j,x,y,'@');
            }
            break;
        //caisse2
        case '*':
            if(canMoveCaisse(indexmove2)){
                movecaisse(indexmove2,x,y);
                moveperso(i,j,x,y,'+');
            }
            break;
        //dest
        case '.':
            moveperso(i,j,x,y,'+');
            break;

        case 's':
            moveperso(i,j,x,y,'@');
            break;
    }
}

void moveperso(int *i, int *j, int x, int y, char movenext){
    
    int curentindex = (*i)*N + (*j);
    int indexmove1 = ((*i)+y)*N + (*j)+x;
    if(tabNiveau[curentindex] == '+'){
        tabNiveau[curentindex] = '.';
        updatechar('.', curentindex);
    }
    else{
        tabNiveau[curentindex] = 's';
        updatechar('s', curentindex);
    }
    tabNiveau[indexmove1] = movenext;
    *j += x;
    *i += y;
    updatechar(movenext, indexmove1);
    dessine();
}

void dessine(){
    SDL_Flip(ecran);
}


int win(){
    for(int i = 0; i < 110; i++){
        if(tabNiveau[i] == '$'){
            return 1;
        } 
    }
    return 0;
}

void affichetab(char tab[]){
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 10; j++){
            printf("%c", tab[i*N+j]);
        }
        printf("\n");
    }
}