#ifndef _SERVER_H
#define _SERVER_H

#include <stdio.h>
#include <stdlib.h>

#include "../interface.h"
#include "./graph/graph.h"

#define ROOT

/*** STRUCTURES ***/

/**
 \struct tile
 */
struct tile {
    int n; /**< The id of the tile */
    int nb_sides; /**< The number of sides of the tile */
    int player; /**< The id of the player on the tile or EMPTY or WATER */
    int fish; /**< The number of fish/points on the tile */
    int posx; /**< x coordinate for the graphic interface */
    int posy; /**< y coordinate for the graphic interface */
};

/**
 \struct board
 */
struct board {
    int ** pawns_positions; /**< A 2 dimensions table such that pawns_positions[player][pawn_number] is the tile id on which the pawn is situated or EMPTY if the pawn isn't in the game antmore */
    int current_player; /**< The id of the current player */
    struct graph * ahead; /**< A graph which can be used with the abstract data type functions in ./graph/graph.h and which represents the 'ahead' matches of the tiles */
    struct tile * tiles; /**< A table of all the tiles of the board set at the beginning of the game */
    struct score * scores; /**< A table with the score of each player */
};

/**
 \struct score
 */
struct score {
    int nb_fish; /**< The number of fish collected by now */
    int nb_tiles; /**< The number of tiles collected by now */
};

/**
 \struct state
 \brief The global state of the board where only the struct board change during the game
 */
struct state {
    int MAX_NEIGHBOURS; /**< The maximum number of sides of the tiles*/
    int MAX_TILES; /**< The number of tiles at the beginning of the game */
    int NB_PLAYERS; /**< The number of players in the game */
    int NB_PAWNS; /**< The number of pawns initialy attributed to each player */

    struct board * ICE; /**< The board */
} global;



/*** FUNCTIONS ***/

/** \fn struct board * board_init(char *path_to_map, int nb_player, int nb_pawns)
 \brief Initialize the board
 \param The path to the .txt file that describes the map
 \param The number of player in the game
 \param The number of pawns distributed to each player
 \return A pointer to the initialized board
 */
struct board * board_init(char *path_to_map, int nb_player, int nb_pawns);

/** \fn check_place_pawn(struct board *, int)
 \param A pointer to the board
 \param A tile id
 \return An integer indicating wether the move place_pawn(tile) is authorized or not
 */
int check_place_pawn(struct board *, int);

/** \fn void place(struct board *, int)
 \brief Place a pawn of the current player on the tile referred
 \param A pointer to the board
 \param The id of the tile
 */
void place(struct board *, int);

/** \fn int is_alive(struct board *, int)
 \brief Check if the player can still play ; if a pawn is blocked, it gives the points and removes the pawn
 \param A pointer to the board
 \param The id of the player
 \return An integer indicating wether the player can still play or not
 */
int is_alive(struct board *, int);

/** \fn int check_play(struct board *, int src, int dst)
 \param A pointer to the board
 \param The id of the starting tile
 \param The if of the ending tile
 \return An integer indicating wether the move play(src, dst) is authorized or not
 */
int check_play(struct board *, int src, int dst);

/** \fn void move(struct board *, int src, int dst)
 \brief Moves a pawn from src to dst and adds the points to the current player thanks to add_points()
 \param A pointer to the board
 \param The id of the starting tile
 \param The id of the ending tile
 */
void move(struct board *, int src, int dst);

/** \fn int win(struct board *)
 \brief Test the end of the game
 \param A pointer to the board
 \return The id of the player who has won the game or -1 if there is no winner yet
 */
int win(struct board *);

/** \fn void remove_player(struct board *, int player)
 \brief Removes a player out of the game
 \param A pointer to the board
 \param The player id
 */
void remove_player(struct board *, int player);

/** \fn void add_points(struct board *, int player, int points)
 \brief Adds the points to the score of the player referred and adds 1 to his taken tiles number
 \param A pointer to the board
 \param The player id
 \param The number of points
 */
void add_points(struct board *, int player, int points);

/** \fn void free_board(struct board *)
 \brief Frees the memory dynamically allocated in the struct board
 \param A pointer to the board
 */
void free_board(struct board *);



#endif
