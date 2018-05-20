#ifndef CNEPONDER_H
#define CNEPONDER_H

#include <stdio.h>
#include <stdlib.h>
#include "../interface.h"

struct path {
  int idTileSrc; //Source of path
  int firstIdTilePath;//First tile of this path
  int idTileMax; //self
  float mass; //rating
};

/** \fn char * get_client_name()
 \brief Gives the strategy's name
 \return Returns the strategy's name
 */
char * get_client_name();

/** \fn struct path ponderPath(int currentTile, int goingToTile)
 \brief Ponder the path given to get its relative mass from the number of fish on it
 \param The id of the tile where the pawn is on currently
 \param The id of the first tile of the path pondered
 \return The structure of a path with its mass computed, source tile, max tile and first tile
 */
struct path ponderPath(int currentTile, int goingToTile);

/** \fn struct path findBestPath(int idTile)
 \brief Gives the best bath from the neiborhood of the tile
 \param The id of the tile where the pawn is on currently
 \return The structure of the best path with its mass, source tile, max tile and first tile
 */
struct path findBestPath(int idTile);

/** \fn int prediction(int currentPos, int n)
 \brief Predict the best tiles for the next n turns from the current position
 \param The id of the tile where the pawn is on currently
 \param The number of the turns predicted
 \return The number of the fish predicted to be eaten the next turns
 */
int prediction(int currentPos, int n);

/** \fn int getOneFishers(int ** oneFish)
 \brief Get the tiles with only one fish on it to place the pawns during initialization.
 \param The address of the pointer to stock the id of the tiles with only one fish on it
 \return The number of the tiles with only one fish on it
 */
int getOneFishers(int ** oneFish);

/** \fn void place_pawn(int * dst)
 \brief Called by server, makes the initialization of the game by placing this strategy's pawns.
 \param the id of the tile to place one of this strategy's pawn.
 */
void place_pawn(int * dst);

/** \fn void play(int * src,int * dst)
 \brief Called by server, search for the best play to do during a turn and tells the server to do so
 \param The id of the tile where the strategy's pawn is, to be moved
 \param The id of the tile where the strategy's pawns is to be moved to
 */
void play(int * src,int * dst);

#endif
