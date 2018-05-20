#include "parseMap.h"

/* Actually not used at all, maaaaybe
 int parseTo(FILE * filename, char s){
 int i = 0;
 char str[100] = {0};
 do{
 str[i] = fgetc(filename);
 i++;
 }while(str[i-1] != s);
 return atoi(str);
 }
 */


/** \fn struct graph * parseMap(char* filename)
 \brief Parse the map from the filename
 \param filename is the name of the file ie map.txt
 \return a pointer to a graph constructed from the map info
 */
struct board parseMap(char* filename) {
    
    FILE * map = NULL;
    map = fopen(filename, "r");
    if(map == NULL){
        printf("Fail to open");
        exit(1);
    }
    
    int nbTiles, nbSides, idTile, nbPair, nbEat, xpos, ypos;
    int * neighbours = NULL;
    int bigNeighbours = 0;
    int cursor = 0;
    
    struct board bd;
    
    fscanf(map, "%d", &nbTiles);
    struct tile * T = malloc(nbTiles * sizeof(struct tile));
    bd.ahead = gr_init();
    
    for(int i = 0; i < nbTiles; i++){
        
        fscanf(map, "%d %d %d %d | %d %d\n", &idTile, &nbSides, &nbPair, &nbEat, &xpos, &ypos);
        
        if(nbSides > bigNeighbours){
            bigNeighbours = nbSides;
        }
        
        T[i].n = idTile;
        T[i].nb_sides = nbSides;
        T[i].fish = nbEat;
        T[i].player = EMPTY;
        T[i].posx = xpos;
        T[i].posy = ypos;
        
        neighbours = malloc(2 * sizeof(int) * nbPair);
        for(int k = 0; k < nbPair; k++){
            fscanf(map, "%d|%d\n", &neighbours[cursor], &neighbours[cursor+1]);
            cursor += 2;
        }
        
        gr_add_tile(bd.ahead, idTile, neighbours, nbPair*2);
        cursor = 0;
        free(neighbours);
    }
    
    
    global.MAX_TILES = nbTiles;
    global.MAX_NEIGHBOURS = bigNeighbours;
    bd.tiles = T;
    fclose(map);
    return bd;
}
