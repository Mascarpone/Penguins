#include "server.h"
#include <assert.h>

#include "./map/parseMap.h"
#include "./graph/graph.h"



/*** INTERFACE FUNCTIONS ***/

// Number of unplaced pawns for the current player (at the beginning of the game)
int nb_unplaced_pawns() {
    return global.NB_PAWNS - nb_pawns(global.ICE->current_player);
}

// Players number
int nb_players() {
    return global.NB_PLAYERS;
}

// Current player id
int who_am_i() {
    return global.ICE->current_player;
}

// The number of neighbouring tiles of the one referred (it may change during the game)
int nb_neighbours(int tile) {
       return gr_get_nb_neighbours(global.ICE->ahead, tile);
}

// The initial tile number
int nb_tiles() {
    return global.MAX_TILES;
}

// The number of remaining pawns for the player referred
int nb_pawns(int player) {
    int n = 0;
    
    for (int i = 0; i < global.NB_PAWNS; i++) {
        if (global.ICE->pawns_positions[player][i] != EMPTY) {
            n++;
        }
    }
    
    return n;
}

// Writes in positions[] the tile ids on which are the player pawns
// Returns the size of the table positions dynamically allocated (= nb_pawns(player))
int pawns_positions(int player, int ** p_positions) {
    int n = 0;
    int * pos = malloc(nb_pawns(player) * sizeof(int));
    assert(pos != NULL);
    
    for (int i = 0; i < global.NB_PAWNS; i++) {
        if (global.ICE->pawns_positions[player][i] != EMPTY) {
            pos[n] = global.ICE->pawns_positions[player][i];
            n++;
        }
    }
    
    *p_positions = pos;
    
    return n;
}

// Writes in neighbours[] the tile ids of the neighbouring tiles of the one referred
// Returns the size of the table neighbours dynamically allocated (= nb_neighbours(tile))
int tile_neighbours(int tile, int ** p_neighbours) {
    int n = gr_get_neighbours(global.ICE->ahead, tile, p_neighbours);
    assert(p_neighbours != NULL);
    
    return n;
}

// Returns the id of tile where the pawn can go on or WATER if there is no tile ahead
int tile_ahead(int previous, int current) {
    return gr_get_tile_ahead(global.ICE->ahead, current, previous);
}

// The number of fish that have been collected by the player by now
int score(int player) {
    return global.ICE->scores[player].nb_fish;
}

// The number of fish on the tile
int nb_fish(int tile) {
    assert(global.ICE->tiles[tile].player != WATER);
    
    return global.ICE->tiles[tile].fish;
}

// The id of the player or EMPTY if there is no player on the tile or WATER if the tile isn't in the game anymore
int occupant(int tile) {
    return global.ICE->tiles[tile].player;
}

// The number of sides of the tile
int nb_sides(int tile) {
    return global.ICE->tiles[tile].nb_sides;
}


/*** SERVER FUNCTIONS ***/

// Initialize the board
// Returns a pointer to the initialized board
struct board * board_init(char *path_to_map, int nb_players, int nb_pawns) {
    
    // initialization of the tiles and the graph according to the map
    struct board B = parseMap(path_to_map);
    
    // initialization of the constant values
    global.NB_PLAYERS = nb_players;
    global.NB_PAWNS = nb_pawns;
    
    struct score * s = malloc(sizeof(struct score) * nb_players);
    for (int i = 0; i < nb_players; i++) {
        s[i].nb_fish = 0;
        s[i].nb_tiles = 0;
    }
    B.scores = s;
    
    int ** pp = malloc(sizeof(int *) * nb_players);
    for (int i = 0; i < nb_players; i++) {
        pp[i] = malloc(sizeof(int) * nb_pawns);
        for (int j = 0; j < nb_pawns; j++) {
            pp[i][j] = EMPTY;
        }
    }
    B.pawns_positions = pp;
    
    B.current_player = 0;
    
    struct board * b = malloc(sizeof(struct board));
    *b = B;
    
    global.ICE = b;
    
    return b;
}

// Check the validity of place_pawn(dst)
int check_place_pawn(struct board * b, int dst) {
    int r1 = (occupant(dst) == EMPTY);
    int r2 = (b->tiles[dst].fish == 1);
    return (r1 && r2);
}

// Place a pawn of the current player on the tile referred
void place(struct board * b, int dst) {
    int p = who_am_i();
    b->tiles[dst].player = p;
    
    int i = 0;
    while (b->pawns_positions[p][i] != EMPTY) {
        i++;
    }
    b->pawns_positions[p][i] = dst;
}

// Check if the player can still play
// if a pawn is blocked, it gives the points and removes the pawn.
int is_alive(struct board * b, int player) {
    int r = nb_pawns(player);
    for (int i = 0; i < global.NB_PAWNS; i++) {
        int tile = b->pawns_positions[player][i];
        
        if (tile != EMPTY) {
            int * neighbours = NULL;
            int n = tile_neighbours(tile, &neighbours);
            int l = 0;
            for (int j = 0; j < n; j++) {
                if (occupant(neighbours[j]) == EMPTY) {
                    l = 1;
                    break;
                }
            }
            
            if (l == 0) {
                add_points(b, player, b->tiles[tile].fish);
                gr_rm_tile(b->ahead, tile);
                b->tiles[tile].player = WATER;
                b->pawns_positions[player][i] = EMPTY;
                r--;
            }
            
            free(neighbours);
        }
    }
    
    return r;
}
 
// Check the validity of play(src, dst)
int check_play(struct board * b, int src, int dst) {
    
    // test all directions
    int * neighbours = NULL;
    int n = tile_neighbours(src, &neighbours);
    
    while (n > 0) {
        int prev = src;
        int pos = neighbours[n - 1];
        int next;
        
        // when the player moves to the tile next to him
        if (pos == dst && occupant(pos) == EMPTY) {
            return 1;
        }
        
        while ((next = tile_ahead(prev, pos)) >= 0) {
            if (occupant(next) != EMPTY) {
                break;
            } else {
                prev = pos;
                pos = next;
            }
            
            if (next == dst) {
                return 1;
            }
        }
        n--;
    }
    
    free(neighbours);
    return 0;
}

// Moves a pawn from src to dst
// and adds the points to the current player thanks to add_points()
void move(struct board * b, int src, int dst) {
    int p = b->current_player;
    for (int i = 0; i < global.NB_PAWNS; i++) {
        if (b->pawns_positions[p][i] != EMPTY && b->pawns_positions[p][i] == src) {
            b->pawns_positions[p][i] = dst;
            break;
        }
    }
    add_points(b, p, b->tiles[src].fish);
    gr_rm_tile(b->ahead, src);
    b->tiles[src].player = WATER;
    b->tiles[dst].player = p;
}

// Test the end of the game
// Returns the id of the player who's won or -1 if there is no winner or -2 if there is a draw
int win(struct board * b) {
    
    // Test if the game is over
    for (int i = 0; i < global.NB_PLAYERS; i++) {
        if (is_alive(b, i)) {
            return -1;
        }
    }
    
    // Find the winner
    int w_f = -1;
    int w_t = -1;
    int w = -1;
    for (int i = 0; i < global.NB_PLAYERS; i++) {
        if (b->scores[i].nb_fish > w_f) {
            w_f = b->scores[i].nb_fish;
            w_t = b->scores[i].nb_tiles;
            w = i;
        }
        else if (b->scores[i].nb_fish == w_f) {
            if (b->scores[i].nb_tiles > w_t) {
                w_t = b->scores[i].nb_tiles;
                w = i;
            }
            else if (b->scores[i].nb_tiles == w_t) {
                w = -2;
            }
        }
    }
    
    return w;
}

/** \fn void remove_player(struct board *, int player)
 \brief Removes a player out of the game
 \param A pointer to the board
 \param The player id
 */
void remove_player(struct board * b, int player) {
    int * positions = NULL;
    int n = pawns_positions(player, &positions);
    
    for (int i = 0; i < n; i++) {
        add_points(b, player, b->tiles[positions[i]].fish);
        gr_rm_tile(b->ahead, positions[i]);
        b->tiles[positions[i]].player = WATER;
        b->pawns_positions[player][i] = EMPTY;
    }
    
    free(positions);
}

// Adds the points to the score of the player referred
// Adds 1 to his collected tiles number
void add_points(struct board * b, int player, int points) {
    b->scores[player].nb_fish += points;
    b->scores[player].nb_tiles++;
}

// Frees the memory allocated
void free_board(struct board * b) {
    for (int i = 0; i < global.NB_PLAYERS; i++) {
        free(b->pawns_positions[i]);
    }
    free(b->pawns_positions);
    free(b->ahead);
    free(b->tiles);
    free(b->scores);
    free(b);
}





