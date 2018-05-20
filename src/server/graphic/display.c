#include "graphic.h"

int HEIGHT = 480;
int WIDTH = 720;



void wait_event(struct Display * D) {
    int c = 1;
    SDL_Event event;
    while (c) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                c = 0;
                display_free(D);
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_RETURN) {
                    c = 0;
                }
                break;
            default:
                break;
        }
    }
}



int display_init(struct Display * D) {
    
    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stderr, "SDL initialization failure (%s)\n", SDL_GetError());
        return ERROR;
    }
    
    if(TTF_Init() == -1) {
        fprintf(stderr, "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return ERROR;
    }
    
    /* Open the window */
    D->w = SDL_CreateWindow("Penguins - 1330",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            WIDTH,
                            HEIGHT,
                            SDL_WINDOW_RESIZABLE);
    
    if (D->w == NULL) {
        fprintf(stderr, "Error in the Window creation process : %s\n", SDL_GetError());
        return ERROR;
    }
    
    D->r = SDL_CreateRenderer(D->w, -1, SDL_RENDERER_PRESENTVSYNC);
    if(D->r != NULL) {
        /* icon */
        SDL_Surface * icon = SDL_LoadBMP("./rsc/image/icon.bmp");
        SDL_SetWindowIcon(D->w, icon);
        SDL_FreeSurface(icon);
        
        /* screen */
        SDL_SetRenderDrawColor(D->r, 131, 223, 246, 255);
        SDL_RenderFillRect(D->r, NULL);
        
        /* title */
        SDL_Surface * title = SDL_LoadBMP("./rsc/image/title.bmp");
        SDL_Rect posTitle = {   .x = (WIDTH - 480) / 2,
                                .y = (HEIGHT - 480) / 2,
                                .w = 480,
                                .h = 480 };
        SDL_Texture * tex = SDL_CreateTextureFromSurface(D->r, title);
        SDL_FreeSurface(title);
        SDL_RenderCopy(D->r, tex, NULL, &posTitle);
        SDL_DestroyTexture(tex);
        SDL_RenderPresent(D->r);
        
        SDL_Delay(1000);
        SDL_RenderFillRect(D->r, NULL);
        SDL_RenderPresent(D->r);
        
        wait_event(D);
    } else {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n",  SDL_GetError());
        return ERROR;
    }
    
    return OK;
}



void display_free(struct Display * D) {
    
    // /!\ Do not forget to free all textures !
    
    //Destroy window
    SDL_DestroyRenderer(D->r);
    D->r = NULL;
    SDL_DestroyWindow(D->w);
    D->w = NULL;
    
    //Quit SDL subsystems
    TTF_Quit();
    SDL_Quit();
}


int g_n = 3; // nb sides polygon
float g_o = 0.; // origin polygon

// draw the content of the window
void draw_tile(SDL_Surface * s, struct tile * t) {

    if (t->player == WATER) {
        return;
    }
    
    // create a transparent surface
    SDL_Surface * surf = SDL_CreateRGBSurface(0, 50, 50, // size of the square surrounding a tile
                                              32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
    // find the position of the tile
    SDL_Rect dst = {.w = 48, .h = 48};
    dst.x = t->posx - 25;
    dst.y = t->posy - 25;
    
    // draw the shape of the tile
    g_n = t->nb_sides;
    g_o = 0.;
    draw_polygon(surf, g_n, g_o, BLUE);
    
    // draw the number of fish
    draw_fish(surf, t->fish);
    
    // draw the player pawn
    if (t->player != EMPTY) {
        draw_player(surf, t->player);
    }
    
    SDL_BlitSurface(surf, NULL, s, &dst);
    SDL_FreeSurface(surf);
}

