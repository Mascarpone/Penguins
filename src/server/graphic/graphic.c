#include "graphic.h"


/** \fn void print_board(struct board *)
 \brief Shows the current state of the board 
 \param A pointer to the board
 */
void print_board(struct board * b, struct Display * d) {
    
    // clear
    SDL_SetRenderDrawColor(d->r, 131, 223, 246, 255);
    SDL_RenderClear(d->r);
    
    SDL_Surface * s = SDL_CreateRGBSurface(0, WIDTH, HEIGHT,
                                           32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
    // draw the tiles
    for (int i = 0; i < global.MAX_TILES; i++) {
        draw_tile(s, &b->tiles[i]);
    }
    
    SDL_Texture * tex = SDL_CreateTextureFromSurface(d->r, s);
    SDL_FreeSurface(s);
    
    // Center the map
    int l = sqrt(global.MAX_TILES) * 50;
    SDL_Rect dst = {.x = (WIDTH - l)/2, .y = (HEIGHT - l)/2, .w = WIDTH, .h = HEIGHT};
    SDL_RenderCopy(d->r, tex, NULL, &dst);
    SDL_DestroyTexture(tex);
    
    print_scores(d, b);
    
    SDL_RenderPresent(d->r);
}


/** \fn void print_scores(struct board *)
 \brief Shows the current scores
 \param A pointer to the board
 */
void print_scores(struct Display * d, struct board * b) {
    
    SDL_Surface * s = SDL_CreateRGBSurface(0, WIDTH, HEIGHT,
                                           32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
    
    SDL_Color C = {210, 40, 65};
    
    TTF_Font * number_font = TTF_OpenFont("./rsc/image/numbers.ttf", 22);
    TTF_Font * fish_font = TTF_OpenFont("./rsc/image/fish_font.ttf", 22);
    for (int i = 0; i < global.NB_PLAYERS; i++) {
        char num[10];
        char rest[3] = {' ', 'x', '\0'};
        itoa(b->scores[i].nb_fish, num);
        strcat(num, rest);
        SDL_Surface * number = TTF_RenderText_Blended(number_font, num, C);
        SDL_Rect number_pos = {.x = WIDTH - 180, .y = HEIGHT - 90 - 24 * (global.NB_PLAYERS - i)};
        
        char fish[2];
        fish[0] = 'A' + i % 26;
        fish[1] = '\0';
        SDL_Surface * text = TTF_RenderText_Blended(fish_font, fish, C);
        SDL_Rect fish_pos = {.x = WIDTH - 130, .y = HEIGHT - 90 - 23 * (global.NB_PLAYERS - i)};
        
        SDL_BlitSurface(number, NULL, s, &number_pos);
        SDL_FreeSurface(number);
        SDL_BlitSurface(text, NULL, s, &fish_pos);
        SDL_FreeSurface(text);
    }
    
    TTF_CloseFont(number_font);
    TTF_CloseFont(fish_font);
    
    SDL_Texture * tex = SDL_CreateTextureFromSurface(d->r, s);
    SDL_FreeSurface(s);
    
    SDL_Rect dst = {.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT};
    
    SDL_RenderCopy(d->r, tex, NULL, &dst);
}



/** \fn void print_winner(struct board *, char * winner)
 \brief Shows the scores and who has won the game
 \param A pointer to the board
 \param The name of the player
 */
void print_winner(struct Display * d, char * winner){
    // clear
    SDL_SetRenderDrawColor(d->r, 131, 223, 246, 255);
    SDL_RenderClear(d->r);
    
    SDL_Surface * s = SDL_CreateRGBSurface(0, WIDTH, HEIGHT,
                                           32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
    
    SDL_Color C = {210, 40, 65};
    TTF_Font * font = TTF_OpenFont("./rsc/image/numbers.ttf", 40);
    char message[8] = " wins !";
    char cpy[100];
    strcpy(cpy, winner);
    strcat(cpy, message);
    SDL_Surface * text = TTF_RenderText_Blended(font, cpy, C);
    SDL_Rect pos = {.x = (WIDTH - (strlen(winner) + 8) * 40)/2, .y = HEIGHT/2 - 50};
    
    SDL_BlitSurface(text, NULL, s, &pos);
    SDL_FreeSurface(text);

    TTF_CloseFont(font);
    
    SDL_Texture * tex = SDL_CreateTextureFromSurface(d->r, s);
    SDL_FreeSurface(s);
    
    SDL_Rect dst = {.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT};
    
    SDL_RenderCopy(d->r, tex, NULL, &dst);
    SDL_RenderPresent(d->r);
    SDL_Delay(3000);
}

/** \fn void print_cheater(struct board *, char * cheater)
 \brief Shows the scores and who has cheated
 \param A pointer to the board
 \param The name of the cheater
 */
void print_cheater(struct Display * d, char * cheater){
    
    SDL_Surface * s = SDL_CreateRGBSurface(0, WIDTH, HEIGHT,
                                           32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
    
    SDL_Color C = {210, 40, 65};
    TTF_Font * font = TTF_OpenFont("./rsc/image/numbers.ttf", 20);
    char message[10] = " cheated !";
    char cpy[100];
    strcpy(cpy, cheater);
    strcat(cpy, message);
    SDL_Surface * text = TTF_RenderText_Blended(font, cpy, C);
    SDL_Rect pos = {.x = WIDTH - 160, .y = HEIGHT - 90 - 23 * (global.NB_PLAYERS + 1)};
    
    SDL_BlitSurface(text, NULL, s, &pos);
    SDL_FreeSurface(text);
    
    TTF_CloseFont(font);
    
    SDL_Texture * tex = SDL_CreateTextureFromSurface(d->r, s);
    SDL_FreeSurface(s);
    
    SDL_Rect dst = {.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT};
    
    SDL_RenderCopy(d->r, tex, NULL, &dst);
}

