#include "CNEPonder.h"
#include "../interface.h"
#include <assert.h>

//Global var
int *src, *dst;


char * get_client_name(){
    return "CNEPonder";
}

struct path ponderPath(int currentTile, int goingToTile){
    struct path thisPath;
    thisPath.idTileSrc = currentTile;
    thisPath.firstIdTilePath = goingToTile;
    int current = goingToTile;
    int before = currentTile;
    int ahead;
    int mass = 0;
    int i = 0;
    int currentMass = 0;
    int max = 0;

    for(i = 0; occupant(current) == EMPTY; i++){
        currentMass = nb_fish(current);
        if(currentMass > max){
            max = currentMass;
            thisPath.idTileMax = current;
        }
        mass += currentMass;
        ahead = tile_ahead(before,current);
        before = current;
        current = ahead;
    }
    if(i == 0){
      thisPath.mass = 0;
    }else{
      thisPath.mass /= (float)i;
      thisPath.mass += 2 * max;
    }
    return thisPath;
}



struct path findBestPath(int idTile){
    int nbNeigh = nb_neighbours(idTile);
    int * neigh = NULL;
    struct path * allPath = malloc(sizeof(struct path) * nbNeigh);
    struct path bestPath;

    bestPath.mass = 0;
    neigh = malloc(sizeof(int) * nbNeigh);
    tile_neighbours(idTile, &neigh);

    for(int i = 0; i < nbNeigh; i++){
        allPath[i] = ponderPath(idTile,neigh[i]);
        if(allPath[i].mass > bestPath.mass){
            bestPath = allPath[i];
        }

    }
    free(allPath);
    free(neigh);
    return bestPath;
}


int prediction(int currentPos, int n){
  int predictedFish = 0;
  int nextTile = currentPos;
  struct path nextPath;

  for(int k = 0; k < n; k++){
    nextPath = findBestPath(currentPos);
    nextTile = nextPath.idTileMax;
    predictedFish += nb_fish(nextTile);
  }
  return predictedFish;
}


int getOneFishers(int ** oneFish_p){

    int nbOneFish = 0;
    int * temp = malloc(sizeof(int));
    for(int i = 0 ; i < nb_tiles(); i++){
        if (nb_fish(i) == 1){
            nbOneFish++;
            temp = realloc(temp, sizeof(int) * nbOneFish);
            temp[nbOneFish - 1] = i;
        }
    }

    *oneFish_p = temp;

    return nbOneFish;
}

void place_pawn(int * dst){

    int * oneFish = NULL;

    //Get the tiles with one fish
    int n = getOneFishers(&oneFish);
    assert(oneFish != NULL);

    for (int i = 0; i < n; i++) {
        if(occupant(oneFish[i]) == EMPTY){
            *dst = oneFish[i];
        }

    }

    free(oneFish);

    /*
     for(int l = 0; l < nbOneFish; l++){
      prediction(l)
     }
     */

    //get the One fishes idTiles, find the one which is the most promising -> $$$

}


void play(int * src,int * dst){
    int me = who_am_i();
    int nbMyPawns = nb_pawns(me);
    int * positions = malloc(sizeof(int) * nbMyPawns);
    struct path * leeroy = malloc(sizeof(struct path) * nbMyPawns * nb_sides(nb_tiles()-1));
    struct path best;

    best.mass = 0;
    pawns_positions(me, &positions);

    for(int i = 0; i < nbMyPawns; i++){
        leeroy[i] = findBestPath(positions[i]);
        if (leeroy[i].mass > best.mass){
            best = leeroy[i];
        }
    }
    *src = best.idTileSrc;
    *dst = best.idTileMax;
    free(positions);
    free(leeroy);
}
