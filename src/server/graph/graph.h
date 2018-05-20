#ifndef _GRAPH_H
#define _GRAPH_H

//****Structures****

struct graph;

//****Functions****

struct graph* gr_init(void);

void gr_free(struct graph* s);

//Doesn't replace tiles already in graph, size is the size of int* neighbours
void gr_add_tile(struct graph* s, int tile_ID, int* neighbours, int size);

//removes a tile
int gr_rm_tile(struct graph* s, int tile);

//line is the actual tile, column is the previous tile. Returned value : -2 means there is no tile ahead.
int gr_get_tile_ahead(struct graph* s, int line, int column);

int gr_get_nb_neighbours(struct graph* s, int tile);

//Returns the list of neighbours in a newly allocated array
int gr_get_neighbours(struct graph* s, int tile, int ** p_neighbours);

//DEBUG
void print_graph(struct graph* s);


#endif
