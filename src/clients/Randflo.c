#include "../interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



char * get_client_name() {
    return "Randflo";
}

void place_pawn(int * dst) {
    srand(time(NULL));
    
    // find the tiles with only one fish and where there isn't already a player
    int n = 0;
    int * onefish = malloc(sizeof(int));
    
    for (int i = 0; i < nb_tiles(); i++) {
        if (occupant(i) == EMPTY && nb_fish(i) == 1) {
            onefish[n] = i;
            n++;
            onefish = realloc(onefish, sizeof(int) * (n + 1));
        }
    }
    
    *dst = onefish[rand() % n];
    
    free(onefish);
}

void play(int * src, int * dst) {
    srand(time(NULL));
    
    // choose a random pawn
    int * positions = NULL;
    int n = pawns_positions(who_am_i(), &positions);
    int src_rand = positions[rand() % n];
    free(positions);
    
    // choose a random destination
    int k = 0;
    int * moves = malloc(sizeof(int));
    
    int * neighbours = NULL;
    int m = tile_neighbours(src_rand, &neighbours);
    
    for (int i = 0; i < m; i++) {
        if (occupant(neighbours[i]) == EMPTY) {
            moves[k] = neighbours[i];
            k++;
            moves = realloc(moves, sizeof(int) * (k + 1));
            
            int current = neighbours[i];
            int prev = src_rand;
            int a = tile_ahead(prev, current);
            while (a >= 0 && occupant(a) == EMPTY) {
                moves[k] = a;
                k++;
                moves = realloc(moves, sizeof(int) * (k + 1));
                
                prev = current;
                current = a;
                a = tile_ahead(prev, current);
            }
        }
    }
    
    *src = src_rand;
    *dst = moves[rand() % k];
    free(moves);
}

