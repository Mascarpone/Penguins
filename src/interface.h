#ifndef _INTERFACE_H
#define _INTERFACE_H



/*** CONSTANT VARIABLES ***/

#define EMPTY (-1) /**< Used when there is no player on a tile */
#define WATER (-2) /**< Used when a tile is not in the game anymore */



/*** CLIENT-SERVER COMMUNICATIONS ***/

/*
Every client will be loaded dynamically.
place_pawn() is called until there isn't pawns to place anymore in the beginning.
play() is called each turn after.
Clients have access to the server functions defined below.
 */

/** \fn void place_pawn(int * dst)
 \brief Every client must implement a function indicating where it wants to place its pawns in the beginning of the game
 \param A pointer to an integer used to return the id of the tile where the client wants to place its pawn
 */
void place_pawn(int * dst);

/** \fn void play(int * src, int * dst)
 \brief Every client must implement a function indicating how it wants to move its pawns during the game
 \param A pointer to an integer indicating the id of the starting tile
 \param A pointer to an integer used to return the id of the ending tile
 */
void play(int * src, int * dst);

/** \fn char * get_client_name()
 \brief Every client must implement a function giving its name
 \return A character list ending with '\0' indicating the strategy name
 */
char * get_client_name();



/*** FUNCTIONS THAT CAN BE USED BY CLIENTS AND WHICH ARE IMPLEMENTED BY THE SERVER ***/

/** \fn int nb_unplaced_pawns()
 \brief Indicates to the current player at the beginning of the game how much pawns are still to place
 \return The number of pawns that are not placed on the board yet
 */
int nb_unplaced_pawns();

/** \fn int nb_players()
 \return The total number of players
 */
int nb_players();

/** \fn int who_am_i()
 \return The id of the current player
 */
int who_am_i();

/** \fn int nb_neighbours(int tile)
 \brief Indicates the number of tiles neighbouring the one referred (it may change during the game)
 \param The id of the tile
 \return The number of neighbouring tiles
 */
int nb_neighbours(int tile);

/** \fn int nb_tiles()
 \return The total number of tiles in the beginning of the game
 */
int nb_tiles();

/** \fn int nb_pawns(int player)
 \brief Indicates the number of pawns still available for the player referred
 \param The id of the player
 \return The number of pawns available
 */
int nb_pawns(int player);

/** \fn int pawns_positions(int player, int ** positions)
 \brief Writes in positions[] the tile ids on which are the player pawns ; the table is dynamically allocated
 \param The id of the player
 \param A pointer to a table that will be set in the function
 \return The size of the table positions dynamically allocated (= nb_pawns(player))
 */
int pawns_positions(int player, int ** positions);

/** \fn int tile_neighbours(int tile, int ** neighbours)
 \brief Writes in neighbours[] the tile ids of the neighbouring tiles of the one referred ; the table is dynamically allocated
 \param The id of the tile
 \param A pointer to a table that will be set in the function
 \return The size of the table neighbours dynamically allocated (= nb_neighbours(tile))
 */
int tile_neighbours(int tile, int ** neighbours);

/** \fn int tile_ahead(int previous, int current)
 \brief Indicates the id of the tile in front of 'previous' when the pawn is on 'current'
 \param The id of the tile where pawn comes from
 \param The id of the tile where the pawn is on currenty
 \return The id of tile where the pawn can go on or WATER if there is no tile ahead
 */
int tile_ahead(int previous, int current);

/** \fn int score(int player)
 \param The id of the player
 \return The number of fish that have been collected by the player by now
 */
int score(int player);

/** \fn int nb_fish(int tile)
 \param The id of the tile
 \return The number of fish on the tile
 */
int nb_fish(int tile);

/** \fn int occupant(int tile)
 \brief Indicates the id of the player on the tile referred
 \param The id of the tile
 \return The id of the player or EMPTY if there is no player on the tile or WATER if the tile isn't in the game anymore
 */
int occupant(int tile);

/** \fn int nb_sides(int tile)
 \brief Each tile has a static number of sides in the beginning of the game (every tiles have not always the same number of sides)
 \param The id of the tile
 \return The number of sides of the tile
 */
int nb_sides(int tile);



#endif
