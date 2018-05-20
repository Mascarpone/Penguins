#ifndef _GRAPHIC_H
#define _GRAPHIC_H

#include "../server.h"
#include "display.h"
#include <SDL2/SDL.h>
#include <stdio.h>


/** \fn void print_board(struct board *)
 \brief Shows the current state of the board 
 \param A pointer to the board
 */
void print_board(struct board *, struct Display *);

/** \fn void print_scores(struct board *)
 \brief Shows the current scores
 \param A pointer to the display structure
 \param A pointer to the board
 */
void print_scores(struct Display * d, struct board * b);

/** \fn void print_winner(struct board *, char * winner)
 \brief Shows the scores and who has won the game
 \param A pointer to the board
 \param The name of the player
 */
void print_winner(struct Display *, char * winner);

/** \fn void print_cheater(struct board *, char * cheater)
 \brief Shows the scores and who has cheated
 \param A pointer to the board
 \param The name of the cheater
 */
void print_cheater(struct Display *, char * cheater);



#endif
