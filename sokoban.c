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
    //rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, LC, LC, 32, 0, 0, 0, 0);
    //SDL_FillRect(rectangle, NULL, SDL_MapRGB(rectangle->format, 255, 255, 255));
    // Légende de la fenêtre
    SDL_WM_SetCaption("Sokoban", NULL);
    creationniveau1(flot);
    
    dessine();
    SDL_Flip(ecran);
    boucleEv();


    freeImg();
    SDL_Quit();
    fclose(flot);
    return EXIT_SUCCESS;
}

void loadImg(){
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
}

void freeImg(){
    SDL_FreeSurface(imgperso);
    SDL_FreeSurface(imgcaisse1);
    SDL_FreeSurface(imgcaisse2);
    SDL_FreeSurface(imgsol);
    SDL_FreeSurface(imgdest);
    SDL_FreeSurface(imgmur);
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
            case 's':
                tabNiveau[i*N + j] = c;
                j++;
                SDL_BlitSurface(imgsol, NULL, ecran, &pos);
                pos.x += LC;
                break;
            case '#':
                tabNiveau[i*N + j] = c;
                j++;
                SDL_BlitSurface(imgmur, NULL, ecran, &pos);
                pos.x += LC;
                break;
            case '$':
                tabNiveau[i*N + j] = c;
                j++;
                SDL_BlitSurface(imgcaisse1, NULL, ecran, &pos);
                pos.x += LC;
                break;
            case '*':
                tabNiveau[i*N + j] = c;
                j++;
                SDL_BlitSurface(imgcaisse2, NULL, ecran, &pos);
                pos.x += LC;
                break;
            case '.':
                tabNiveau[i*N + j] = c;
                j++;
                SDL_BlitSurface(imgdest, NULL, ecran, &pos);
                pos.x += LC;
                break;
            case '@':
                tabNiveau[i*N + j] = c;
                j++;
                SDL_BlitSurface(imgperso, NULL, ecran, &pos);
                positionperso = pos;
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

//création de niveau sans garder en mémoire
/*void creationniveau1(FILE *flot){
    char c;
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
}*/

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
                        //caisse
                        if(tabNiveau[(i-1)*N + j] == '#'){
                            /* code */
                        }
                        else{
                            tabNiveau[i*N + j] = 's';
                            i -= 1;
                            tabNiveau[i*N + j] = '@';
                            SDL_BlitSurface(imgsol, NULL, ecran, &positionperso);
                            positionperso.y -= LC;
                            dessine();
                        }
                        break;

                    case SDLK_DOWN:
                        //caisse
                        if(tabNiveau[(i+1)*N + j] == '#'){
                            /* code */
                        }
                        else{
                            tabNiveau[i*N + j] = 's';
                            i += 1;
                            tabNiveau[i*N + j] = '@';
                            SDL_BlitSurface(imgsol, NULL, ecran, &positionperso);
                            positionperso.y += LC;
                            dessine();
                        }
                        break;

                    case SDLK_LEFT:
                        //caisse
                        if(tabNiveau[i*N + j-1] == '#'){
                            /* code */
                        }
                        else{
                            tabNiveau[i*N + j] = 's';
                            j -= 1;
                            tabNiveau[i*N + j] = '@';
                            SDL_BlitSurface(imgsol, NULL, ecran, &positionperso);
                            positionperso.x -= LC;
                            dessine();
                        }
                        break;

                    case SDLK_RIGHT:
                        //caisse
                        if(tabNiveau[i*N + j+1] == '#'){
                            /* code */
                        }
                        else{
                            tabNiveau[i*N + j] = 's';
                            j += 1;
                            tabNiveau[i*N + j] = '@';
                            SDL_BlitSurface(imgsol, NULL, ecran, &positionperso);
                            positionperso.x += LC;
                            dessine();
                        }
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