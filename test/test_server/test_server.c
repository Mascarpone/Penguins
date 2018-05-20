#include "../../src/server/server.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>



// Debug function
void print_board_state(struct board * b) {
    printf("State of the board : \n");
    printf("Global vars : \n");
    printf("MAX_NEIGHBOURS : %d \n", global.MAX_NEIGHBOURS);
    printf("MAX_TILES : %d \n", global.MAX_TILES);
    printf("NB_PLAYERS : %d \n", global.NB_PLAYERS);
    printf("NB_PAWNS : %d \n", global.NB_PAWNS);
    printf("Board : \n");
    printf("pawns_positions : PLAYER - Positions \n");
    for (int i = 0; i < global.NB_PLAYERS; i++) {
        printf("%d - ", i);
        for (int j = 0; j < global.NB_PAWNS; j++) {
            printf("%d ", b->pawns_positions[i][j]);
        }
        printf("\n");
    }
    printf("Current player : %d\n", b->current_player);
    printf("Scores : ");
    for (int i = 0; i < global.NB_PLAYERS; i++) {
        printf("%d ", b->scores[i].nb_fish);
    }
    printf("\n");
}



/* server functions */

void test__board_init() {
    struct board * b = board_init("./rsc/maps/map1.txt", 1, 1);
    assert(b != NULL);
    
    //print_board_state(b);
    
    free_board(b);
    printf("test__board_init : PASSED\n");
}

void test__check_place_pawn() {
    struct board * b = board_init("./rsc/maps/map1.txt", 1, 1);
    assert(check_place_pawn(b, 0));
    place(b, 0);
    assert(check_place_pawn(b, 0) == 0);
    
    free_board(b);
    printf("test__check_place_pawn : PASSED\n");
}

void test__place() {
    struct board * b = board_init("./rsc/maps/map1.txt", 1, 1);
    place(b, 0);
    assert(occupant(0) == who_am_i());
    
    free_board(b);
    printf("test__place : PASSED\n");
}

void test__is_alive() {
    struct board * b1 = board_init("./rsc/maps/map1.txt", 1, 1);
    assert(is_alive(b1, who_am_i()) == 0);
    place(b1, 0);
    assert(is_alive(b1, who_am_i()));
    free_board(b1);
    
    struct board * b2 = board_init("./rsc/maps/map2.txt", 1, 1);
    place(b2, 0);
    assert(is_alive(b2, who_am_i()) == 0);
    assert(score(who_am_i()) == 1);
    free_board(b2);
    
    printf("test__is_alive : PASSED\n");
}

void test__check_play() {
    struct board * b = board_init("./rsc/maps/map2.txt", 1, 3);
    place(b, 0);
    assert(check_play(b, 0, 1) == 0);
    place(b, 1);
    assert(check_play(b, 1, 2));
    assert(check_play(b, 1, 3) == 0);
    assert(check_play(b, 1, 4));
    assert(check_play(b, 1, 5));
    place(b, 4);
    assert(check_play(b, 1, 4) == 0);
    
    free_board(b);
    printf("test__check_play : PASSED\n");
}

void test__move() {
    struct board * b = board_init("./rsc/maps/map2.txt", 1, 3);
    place(b, 1);
    move(b, 1, 4);
    
    assert(occupant(1) == WATER);
    assert(occupant(4) == who_am_i());
    
    int * neighbours = NULL;
    int n = tile_neighbours(2, &neighbours);
    for (int i = 0; i < n; i++) {
        assert(neighbours[i] != 1);
    }
    
    free(neighbours);
    free_board(b);
    
    printf("test__move : PASSED\n");
}

void test__win() {
    struct board * b1 = board_init("./rsc/maps/map1.txt", 1, 1);
    place(b1, 0);
    assert(win(b1) == -1);
    free_board(b1);
    
    struct board * b2 = board_init("./rsc/maps/map2.txt", 1, 1);
    place(b2, 0);
    //assert(score(who_am_i()) == 1);
    assert(win(b2) == who_am_i());
    free_board(b2);
    
    struct board * b3 = board_init("./rsc/maps/map3.txt", 2, 1);
    place(b3, 0);
    b3->current_player = (b3->current_player + 1) % global.NB_PLAYERS;
    place(b3, 1);
    assert(win(b3) == -2);
    add_points(b3, who_am_i(), 1);
    assert(win(b3) == who_am_i());
    free_board(b3);
    
    printf("test__win : PASSED\n");
}

void test__add_points() {
    struct board * b = board_init("./rsc/maps/map1.txt", 1, 1);
    add_points(b, who_am_i(), 2);
    assert(b->scores[who_am_i()].nb_fish == 2);
    assert(b->scores[who_am_i()].nb_tiles == 1);
    free_board(b);
    
    printf("test__add_points : PASSED\n");
}



/* interface functions */

void test__nb_unplaced_pawns() {
    struct board * b = board_init("./rsc/maps/map1.txt", 1, 1);
    assert(nb_unplaced_pawns() == 1);
    
    free_board(b);
    printf("test__nb_unplaced_pawns : PASSED\n");
}

void test__who_am_i() {
    struct board * b = board_init("./rsc/maps/map1.txt", 1, 1);
    assert(who_am_i() == 0);
    
    free_board(b);
    printf("test__who_am_i : PASSED\n");
}

void test__nb_players() {
    struct board * b = board_init("./rsc/maps/map1.txt", 1, 1);
    assert(nb_players() == 1);
    
    free_board(b);
    printf("test__nb_players : PASSED\n");
}

void test__nb_tiles() {
    struct board * b = board_init("./rsc/maps/map1.txt", 1, 1);
    assert(nb_tiles() == 3);
    
    free_board(b);
    printf("test__nb_tiles : PASSED\n");
}

void test__nb_pawns() {
    struct board * b = board_init("./rsc/maps/map1.txt", 1, 1);
    assert(nb_pawns(who_am_i()) == 0);
    b->pawns_positions[who_am_i()][0] = 0;
    assert(nb_pawns(who_am_i()) == 1);
    
    free_board(b);
    printf("test__nb_pawns : PASSED\n");
}

void test__nb_neighbours() {
    struct board * b = board_init("./rsc/maps/map1.txt", 1, 1);
    assert(nb_neighbours(0) == 2);
    
    free_board(b);
    printf("test__nb_neighbours : PASSED\n");
}

void test__pawns_positions() {
    struct board * b = board_init("./rsc/maps/map1.txt", 1, 1);
    int me = who_am_i();
    b->pawns_positions[me][0] = 0;
    int * pos = NULL;
    assert(pawns_positions(me, &pos) == nb_pawns(me));
    assert(pos[me] == 0);
    
    free(pos);
    free_board(b);
    printf("test__pawns_positions : PASSED\n");
}

void test__tile_neighbours() {
    struct board * b = board_init("./rsc/maps/map1.txt", 1, 1);
    int * nei = NULL;
    assert(tile_neighbours(0, &nei) == nb_neighbours(0));
    assert((nei[0] == 1) || (nei[0] == 2));
    assert((nei[1] == 1) || (nei[1] == 2));
    
    free(nei);
    free_board(b);
    printf("test__tile_neighbours : PASSED\n");
}

void test__tile_ahead() {
    struct board * b1 = board_init("./rsc/maps/map1.txt", 1, 1);
    assert(tile_ahead(1, 0) == WATER);
    assert(tile_ahead(2, 0) == WATER);
    assert(tile_ahead(0, 1) == WATER);
    assert(tile_ahead(0, 2) == WATER);
    free_board(b1);
    
    struct board * b2 = board_init("./rsc/maps/map2.txt", 1, 1);
    assert(tile_ahead(1, 2) == 4);
    assert(tile_ahead(4, 2) == 1);
    free_board(b2);
    
    printf("test__tile_ahead : PASSED\n");
}

void test__score() {
    struct board * b = board_init("./rsc/maps/map1.txt", 1, 1);
    assert(score(who_am_i()) == 0);
    add_points(b, who_am_i(), 1);
    assert(score(who_am_i()) == 1);
    
    free_board(b);
    printf("test__score : PASSED\n");
}

void test__nb_fish() {
    struct board * b = board_init("./rsc/maps/map1.txt", 1, 1);
    assert(nb_fish(0) == 1);
    assert(nb_fish(1) == 53);
    assert(nb_fish(2) == 64);
    
    free_board(b);
    printf("test__nb_fish : PASSED\n");
}

void test__occupant() {
    struct board * b = board_init("./rsc/maps/map1.txt", 1, 1);
    assert(occupant(0) == EMPTY);
    place(b, 0);
    assert(occupant(0) == 0);
    
    free_board(b);
    printf("test__occupant : PASSED\n");
}

void test__nb_sides() {
    struct board * b = board_init("./rsc/maps/map1.txt", 1, 1);
    assert(nb_sides(0) == 4);
    
    free_board(b);
    printf("test__nb_sides : PASSED\n");
}





int main() {
    test__board_init();
    
    // interface
    test__nb_unplaced_pawns();
    test__who_am_i();
    test__nb_players();
    test__nb_tiles();
    test__nb_pawns();
    test__nb_neighbours();
    test__pawns_positions();
    test__tile_neighbours();
    test__tile_ahead();
    test__score();
    test__nb_fish();
    test__occupant();
    test__nb_sides();
    
    // server
    test__check_place_pawn();
    test__place();
    test__is_alive();
    test__check_play();
    test__move();
    test__win();
    test__add_points();
    
    return EXIT_SUCCESS;
}
