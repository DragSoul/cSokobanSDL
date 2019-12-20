#include "sokoban.h"

int main(int argc, char ** argv){
    imgperso = SDL_LoadBMP("images/joseph_pixel.bmp");
    imgcaisse1 = SDL_LoadBMP("images/caisse.bmp");
    imgcaisse2 = SDL_LoadBMP("images/caissesombre.bmp");
    imgsol = SDL_LoadBMP("images/sol.bmp");
    imgdest = SDL_LoadBMP("images/solcible.bmp");
    imgmur = SDL_LoadBMP("images/mur.bmp");
    if(imgperso == NULL || imgcaisse1 == NULL ||imgcaisse2 == NULL ||imgsol == NULL ||imgdest == NULL ||imgmur == NULL){
        printf("pas trouvé img\n");
        exit(1);
    }
    srand(time(NULL));
    positionperso.x=(WIDTH/2)-(LC/2);
    positionperso.y=(HEIGHT/2)-(LC/2);
    // Init
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr,"\nUnable to initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if((ecran = SDL_SetVideoMode(WIDTH,HEIGHT,32, SDL_HWSURFACE)) == NULL){
        fprintf(stderr,"Erreur VideoMode %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    FILE *flot = fopen(argv[1], "r");
    if(flot == NULL){
        printf("pb ouverture fichier en lecture\n");
        exit(1);
    }
    //rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, LC, LC, 32, 0, 0, 0, 0);
    //SDL_FillRect(rectangle, NULL, SDL_MapRGB(rectangle->format, 255, 255, 255));
    // Légende de la fenêtre
    SDL_WM_SetCaption("Sokoban", NULL);
    creationniveau1(flot);
    
    dessine();
    SDL_Flip(ecran);
    boucleEv();
    // Quit
    SDL_Quit();
    fclose(flot);
    return EXIT_SUCCESS;
}

void creationniveau1(FILE *flot){
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_Flip(ecran);
    char c;
    int i = 0;
    SDL_Rect pos;
    pos.x = 0;
    pos.y = 0;
    while((c = fgetc(flot)) != EOF){
        switch(c){
            case 's':
                SDL_BlitSurface(imgsol, NULL, ecran, &pos);
                pos.x += LC;
                break;
            case '#':
                SDL_BlitSurface(imgmur, NULL, ecran, &pos);
                pos.x += LC;
                break;
            case '$':
                SDL_BlitSurface(imgcaisse1, NULL, ecran, &pos);
                pos.x += LC;
                break;
            case '*':
                SDL_BlitSurface(imgcaisse2, NULL, ecran, &pos);
                pos.x += LC;
                break;
            case '.':
                SDL_BlitSurface(imgdest, NULL, ecran, &pos);
                pos.x += LC;
                break;
            case '@':
                SDL_BlitSurface(imgperso, NULL, ecran, &pos);
                positionperso = pos;
                pos.x += LC;
                break;
            case '\n':
                pos.x = 0;
                pos.y += LC;
                break;
        }
    }
    SDL_Flip(ecran);
}

void boucleEv(){
    int cont = 1;
    SDL_Event event;
    while(cont){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                cont = 0;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        if(positionperso.y >= LC){
                            positionperso.y = positionperso.y-LC;
                        }else{
                            positionperso.y = 0;
                        }
                        dessine();
                        break;
                    case SDLK_DOWN:
                        if(positionperso.y+LC < HEIGHT-LC){
                            positionperso.y += LC;
                        }else{
                            positionperso.y = HEIGHT-LC-1;
                        }
                        dessine();
                        break;

                    case SDLK_LEFT:
                        if(positionperso.x >= LC){
                            positionperso.x -= LC;
                        }else{
                            positionperso.x = 0;
                        }
                        dessine();
                        break;
                    case SDLK_RIGHT:
                        if(positionperso.x+LC < WIDTH-LC){
                            positionperso.x += LC;
                        }else{
                            positionperso.x = WIDTH-LC-1;
                        }
                        dessine();
                        break;
                    case 'q':
                        cont = 0;
                        break;
                }
        }
    }
}


void dessine(){
    //SDL_FillRect(ecran, NULL,SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(imgperso, NULL, ecran, &positionperso);
    SDL_Flip(ecran);
}