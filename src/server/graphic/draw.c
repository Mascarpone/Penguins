#include "draw.h"

// store in mem the minimum and maximum value of x for a given y
// mem must be initialized to -1 at the begining of the drawing
// for a given y, mem[2*y] is the minimum value of x drawn
// for a given y, mem[2*y+1] is the maximum value of x drawn
// points on line y with x coordinate between mem[2*y] and mem[2*y+1] are
// inside the polygon drawn by draw_polygon()
void maj_mem(int * mem, SDL_Surface * s, int x, int y) {
    if(mem == NULL) {
        return;
    }
    if(y < 2 * (((s->w < s->h)? s->w : s->h)-2)) {
        if(mem[2*y] == -1) {
            mem[2*y]   = x;
            mem[2*y+1] = x;
        }
        else if(x < mem[2*y]) {
            mem[2*y] = x;
        }
        else if(x > mem[2*y+1]) {
            mem[2*y] = x;
        }
    }
}

// draw pixel at coordinates (x,y) in color c
void draw_pixel_mem(SDL_Surface * s, SDL_Color c, int x, int y, int * mem) {
    SDL_Rect r = {x, y, 1, 1};
    Uint32 pix = SDL_MapRGBA(s->format, c.r, c.g, c.b, c.a);
    maj_mem(mem, s, x, y);
    SDL_FillRect(s, &r, pix);
}

void draw_HLine_mem(SDL_Surface * s, SDL_Color c, int x1, int x2, int y, int * mem) {
    if(x1 > x2) {
        int swap = x1; x1 = x2; x2 = swap;
    }
    for(int x = x1; x <= x2; x++) {
        draw_pixel_mem(s, c, x, y, mem);
    }
}

void draw_VLine_mem(SDL_Surface * s, SDL_Color c, int x, int y1, int y2, int * mem) {
    if(y1 > y2) {
        int swap = y1; y1 = y2; y2 = swap;
    }
    for(int y = y1; y <= y2; y++) {
        draw_pixel_mem(s, c, x, y, mem);
    }
}

// draw the line joining (x1,y1) and (x2,y2)
void draw_line_mem(SDL_Surface * s, SDL_Color c, int x1, int y1, int x2, int y2, int * mem) {
    
    if(y1 == y2) { // horizontal line
        draw_HLine_mem(s, c, x1, x2, y1, mem);
    }
    
    if(x1 == x2) { // vertical line
        draw_VLine_mem(s, c, x1, y1, y2, mem);
    }
    
    else if(abs(y2-y1) <= abs(x2-x1)) { // parcours selon les x
        
        if(x1 > x2) {
            int swap;
            swap = x1; x1 = x2; x2 = swap;
            swap = y1; y1 = y2; y2 = swap;
        }
        
        int dy = y2 - y1, dx = x2 - x1;
        for(int x = x1; x <= x2; x++) {
            int y = y1 + (dy*(x-x1)) / dx;
            draw_pixel_mem(s, c, x, y, mem);
        }
        
    } else { // parcours selon les y
        
        if(y1 > y2) {
            int swap;
            swap = x1; x1 = x2; x2 = swap;
            swap = y1; y1 = y2; y2 = swap;
        }
        
        int dy = y2 - y1, dx = x2 - x1;
        for(int y = y1; y <= y2; y++) {
            int x = x1 + (dx*(y-y1)) / dy;
            draw_pixel_mem(s, c, x, y, mem);
        }
    }
    
    // draw extremities just in case
    draw_pixel_mem(s, c, x1, y1, mem);
    draw_pixel_mem(s, c, x2, y2, mem);
}

// draw and fill a regular polygon in color c with n sides (n >= 2),
// rotating it of origin radians
void draw_polygon(SDL_Surface * s, int n, float origin, SDL_Color c) {
    if(n <= 1) return;
    
    // size, center, and so on of the *square* in which we are going to draw
    int size = ((s->w < s->h)? s->w : s->h) - 5; // - 2 to avoid overflows on right and bottom sides ?
    int offsetX = (s->w - size - 2) / 2; // offsets align the square in which we are drawing if the surface is not a square.
    int offsetY = (s->h - size - 2) / 2;
    int centerX = offsetX + size/2 ;
    int centerY = offsetY + size/2 ;
    int radius = size/2;

    // computes the n points around the polygon
    int xs[n];
    int ys[n];
    for(int i = 0; i < n; i++) {
        xs[i] = centerX + (int)(radius * cos((2 * PI * i)/n + origin));
        ys[i] = centerY - (int)(radius * sin((2 * PI * i)/n + origin));
    }
    
    // link the points between them and find for each line 'y' where the
    // inside of the polygon starts and where it ends with mem.
    int mem[2*s->h];
    for(int i = 0; i < 2*s->h; i++) {
        mem[i] = -1; // init
    }

    for(int i = 0; i < n-1; i++) {
        draw_line_mem(s, c, xs[i], ys[i], xs[i+1], ys[i+1], mem);
    }
    draw_line_mem(s, c, xs[n-1], ys[n-1], xs[0], ys[0], mem);

    // fill the inside
    for(int i = 0; i < s->h; i++) {
        if(mem[2*i] != -1) {
            draw_line_mem(s, c, mem[2*i], i, mem[2*i+1], i, NULL);
        }
    }
}





/* reverse:  reverse string s in place */
void reverse(char s[])
{
    int i, j;
    char c;
    
    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* itoa:  convert n to characters in s */
void itoa(int n, char s[])
{
    int i, sign;
    
    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}




void draw_fish(SDL_Surface * s, int n) {
    
    SDL_Color WHITE = {255, 255, 255};
    
    TTF_Font * number_font = TTF_OpenFont("./rsc/image/numbers.ttf", 8);
    char num[10];
    char rest[3] = {' ', 'x', '\0'};
    itoa(n, num);
    strcat(num, rest);
    SDL_Surface * number = TTF_RenderText_Blended(number_font, num, WHITE);
    SDL_Rect number_pos = {.x = 8, .y = 18};
    
    TTF_Font * fish_font = TTF_OpenFont("./rsc/image/fish_font.ttf", 8);
    char fish[2];
    fish[0] = 'A' + n % 26;
    fish[1] = '\0';
    SDL_Surface * text = TTF_RenderText_Blended(fish_font, fish, WHITE);
    SDL_Rect fish_pos = {.x = 28, .y = 20};
    
    SDL_BlitSurface(number, NULL, s, &number_pos);
    SDL_FreeSurface(number);
    SDL_BlitSurface(text, NULL, s, &fish_pos);
    SDL_FreeSurface(text);
    
    TTF_CloseFont(number_font);
    TTF_CloseFont(fish_font);
}


void draw_player(SDL_Surface * s, int n) {
    if (n > 4 || n < 0) {
        fprintf(stderr, "There is no pattern for this player\n");
        return;
    }
    
    // find the name of the picture file
    char number[4];
    itoa(n, number);
    char path[50], ext[5];
    strcpy(path, "./rsc/image/player");
    strcat(path, number);
    strcpy(ext, ".bmp");
    strcat(path, ext);
    
    // draw the file
    SDL_Surface * player = SDL_LoadBMP(path);
    SDL_SetColorKey(player, SDL_TRUE, SDL_MapRGB(player->format, 0, 0, 255));
    SDL_Rect mid = {.x = (s->w - 2 - player->w)/2, .y = (s->h - 2 - player->h)/2};
    SDL_BlitSurface(player, NULL, s, &mid);
    
    SDL_FreeSurface(player);
}


