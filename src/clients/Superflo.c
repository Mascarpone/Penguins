#include "../interface.h"
#include <stdio.h>
#include <stdlib.h>



char * get_client_name() {
    return "Superflo";
}

struct move {
    int src;
    int dst;
    int rent;
};

int rentability(int tile) {
    int max = nb_fish(tile);
    int * neighbours = NULL;
    int n = tile_neighbours(tile, &neighbours);
    
    for (int i = 0; i < n; i++) {
        int s = nb_fish(tile);
        if (occupant(neighbours[i]) == EMPTY) {
            s += nb_fish(neighbours[i]);
            int current = neighbours[i];
            int prev = tile;
            int next = tile_ahead(prev, current);
            while (occupant(next) == EMPTY) {
                s += nb_fish(next);
                prev = current;
                current = next;
                next = tile_ahead(prev, current);
            }
            if (s > max) {
                max = s;
            }
        }
    }
    
    free(neighbours);
    return max;
}

void place_pawn(int * dst) {
    int n = nb_tiles();
    int rent = 0;
    int my_dst = -2;
    for (int i = 0; i < n; i++) {
        if (occupant(i) == EMPTY && nb_fish(i) == 1) {
            int r = rentability(i);
            if (r > rent) {
                rent = r;
                my_dst = i;
            }
        }
    }
    
    *dst = my_dst;
}

void play(int * src, int * dst) {
    int * positions =  NULL;
    int n_p = pawns_positions(who_am_i(), &positions);
    struct move best_move_per_pawn[n_p];
    
    for (int i = 0; i < n_p; i++) {
        best_move_per_pawn[i].src = positions[i];
        best_move_per_pawn[i].dst = -2;
        best_move_per_pawn[i].rent = 0;
        int * neighbours = NULL;
        int n_n = tile_neighbours(positions[i], &neighbours);
        int r = 0;
        
        for (int j = 0; j < n_n; j++) {
            if (occupant(neighbours[j]) == EMPTY) {
                r = rentability(neighbours[j]);
                if (r > best_move_per_pawn[i].rent) {
                    best_move_per_pawn[i].rent = r;
                    best_move_per_pawn[i].dst = neighbours[j];
                }
                
                int current = neighbours[j];
                int prev = positions[i];
                int next = tile_ahead(prev, current);
                while (occupant(next) == EMPTY) {
                    r = rentability(next);
                    if (r > best_move_per_pawn[i].rent) {
                        best_move_per_pawn[i].rent = r;
                        best_move_per_pawn[i].dst = next;
                    }
                    prev = current;
                    current = next;
                    next = tile_ahead(prev, current);
                }
            }
        }
        
        free(neighbours);
    }
    
    free(positions);
    
    struct move best = {.src = -2, .dst = -2, .rent = 0};
    for (int i = 0; i < n_p; i++) {
        if (best_move_per_pawn[i].rent > best.rent) {
            best.src = best_move_per_pawn[i].src;
            best.dst = best_move_per_pawn[i].dst;
            best.rent = best_move_per_pawn[i].rent;
        }
    }
 
    *src = best.src;
    *dst = best.dst;
}































