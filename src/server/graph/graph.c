#include <stdio.h>
#include <stdlib.h>

#define MAX_TILE 100

//****Structures****

/** \struct graph
 \brief structure describing the graph 
 */
struct graph{
    //first is the actual tile
    //second is the previous tile
    int matrix[MAX_TILE][MAX_TILE];
};

//****Functions****


//DEBUG
void print_graph(struct graph* s) {
    for (int i = 0; i < MAX_TILE; i++) {
        for (int j = 0; j < MAX_TILE; j++) {
            fprintf(stderr, "%d ", s->matrix[i][j]);
        }
        fprintf(stderr, "\n");
    }
}


/** \fn struct graph* gr_init (void)
    \brief Creates and initializes a new graph
    \param None
    \return a struct graph*, the address of a newly allocated graph 
*/
struct graph* gr_init(void){
    struct graph* s = malloc(sizeof(struct graph));
    for (int i = 0; i < MAX_TILE; ++i)
        for (int j = 0; j < MAX_TILE; ++j){
            s->matrix[i][j] = -1;
        }
    return s;
}

/** \fn void gr_free (struct graph* s)
    \brief Frees a graph
    \param struct graph* s is the graph to free
    \return Nothing
*/
void gr_free(struct graph* s){
    free(s);
}


/** \fn void gr_add_tile (struct graph* s, int tile_ID, int* neighbours, int size)
    \brief Adds a tile with its neighbours in the graph
    \param struct graph* s is the graph to act on, int tile_ID is the tile to add, int* neighbour is the list of its paired neighbours (by two adjacent positions) and int size is the size of the previous list
    \return Nothing 
*/
//Doesn't replace tiles already in graph, size is the size of int* neighbours
//neighbours is sort by pair : each tile is next to its 'tile ahead'
void gr_add_tile(struct graph* s, int tile_ID, int* neighbours, int size){
    for (int i = 0; i < size; i += 2) {
        if (neighbours[i] == -2) {
            s->matrix[tile_ID][neighbours[i+1]] = neighbours[i];
        }
        if (neighbours[i+1] == -2) {
            s->matrix[tile_ID][neighbours[i]] = neighbours[i+1];
        }
        if ((neighbours[i] != -2) && (neighbours[i+1] != -2)) {
            s->matrix[tile_ID][neighbours[i]] = neighbours[i+1];
            s->matrix[tile_ID][neighbours[i+1]] = neighbours[i];
        }
    }
}

/** \fn int gr_rm_tile (struct graph* s, int tile)
    \brief Removes a tile from the graph
    \param struct graph* s is the graph to act on and int tile is the tile to remove
    \return an integer coding error number
*/
//removes a tile
int gr_rm_tile(struct graph* s, int tile){

    for (int i = 0; i < MAX_TILE; ++i) {
        // remove its neighbours
        s->matrix[tile][i] = -1;
        // remove it from other tiles neighbours
        s->matrix[i][tile] = -1;
    }

    return 1;
}

/** \fn int gr_get_tile_ahead (struct graph* s, int line, int column)
    \brief Gets the tile paired with the parameter
    \param struct graph* s is the graph to act on, int line is the tile neighbouring the result and int column, which is the tile which pair is returned
    \return an integer representing the ID of the tile ahead of int line, paired with int column. Returns -2 if there is no such tile.
*/
//line is the actual tile, column is the previous tile. Returned value : -2 means there is no tile ahead.
int gr_get_tile_ahead(struct graph* s, int line, int column){
    if(line < 0 || line > MAX_TILE || column < 0 || column > MAX_TILE || s->matrix[line][column] == column)
        return -2;
    return s->matrix[line][column];
}


/** \fn int gr_get_nb_neighbours (struct graph* s, int tile)
    \brief Gets the number of neighbours of a tile
    \param struct graph* s is the graph to act on and int tile is the tile to get neighbours from
    \return an integer representing the number of neighbours of the tile, 0 by default
*/
int gr_get_nb_neighbours(struct graph* s, int tile){
    int res = 0;
    for(int i = 0; i < MAX_TILE; ++i) {
        if(s->matrix[tile][i] != -1) {
            ++res;
        }
    }
    
    return res;
}

/** \fn int gr_get_neighbours (struct graph* s, int tile, int* * neighbours_tab)
    \brief Gets the list of neighbours of a tile
    \param struct graph* s is the graph to act on, int tile is the tile to get neighbours from and int* * neighbours_tab is the address of a newly allocated array which the function fills
    \return an integer representing the size of the list
*/
//Returns the list of neighbours in a newly allocated array
//Returns the size of the list
int gr_get_neighbours(struct graph* s, int tile, int ** p_neighbours) {
    int n = 0;
    int* res = malloc(sizeof(int));
    for (int j = 0; j < MAX_TILE; ++j) {
        if(s->matrix[tile][j] != -1) {
            res[n] = j;
            n++;
            res = realloc(res, sizeof(int) * (n + 1));
        }
    }
    
    *p_neighbours = res;
    
    return n;
}

