#ifndef _PARSEMAP_H_
#define _PARSEMAP_H_

//Actually not used at all, maaaaybe
//int parseTo(FILE * filename, char s);

#include <stdio.h>
#include <stdlib.h>
#include "../server.h"
#include "../graph/graph.h"

/** \fn struct graph * parseMap(char* filename)
    \brief Parse the map from the filename
    \param filename is the name of the file ie map.txt
    \return a pointer to a graph constructed from the map info
*/
struct board parseMap(char* filename);

#endif
