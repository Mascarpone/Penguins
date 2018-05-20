#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int getNbPair(int idTile, int nbTiles, int nbSide, int large){
  int nbPair = 1;
  if(nbSide == 4){
    nbPair = 4;
    if(idTile < large  || idTile >= (nbTiles - large)){
      nbPair -= 1;
      }
    if( (idTile % large) == 0 || ((idTile + 1) % large) == 0){
      nbPair -= 1;
        if(idTile == 1)
        nbPair++;
    }
  }
  return nbPair;
}

//Maps commencent a zero
void populatePairs(FILE* map, int idTile,int nbTiles, int nbSide, int large){
  int pair[2] = {0,0};
  int nbPair = getNbPair(idTile, nbTiles, nbSide, large);

  time_t t;
  srand((unsigned) time(&t));
  int score = rand()%20;
  fprintf(map, "%d %d %d %d\n",idTile, nbSide,nbPair, score);
  int test[4] = {0,0,0,0};

  for(int i = 0; i < nbPair; i++){
    if( (test[0] == 0) && (idTile - 1) >= 0 && !( (idTile % large) == 0)){
      pair[0] = idTile - 1;
      pair[1] = idTile + 1;
      test[0] = 1;
      if(( (idTile+1) % large) == 0){
        pair[1] = -2;
      }
    }else if( (test[1] == 0) && (idTile + 1 < nbTiles) && !( (idTile+1) % large == 0)){
      pair[0] = idTile + 1;
      pair[1] = idTile - 1;
      test[1] = 1;
      if( (idTile % large) == 0){
        pair[1] = -2;
      }
    }else if( (test[2] == 0) && ((idTile + large) < nbTiles) ){
      pair[0] = idTile + large;
      pair[1] = idTile - large;
      test[2] = 1;
      if( idTile < large){
        pair[1] = -2;
      }
    }else if( (test[3] == 0) && (idTile - large >= 0 )){
      pair[0] = idTile - large;
      pair[1] = idTile + large;
      test[3] = 1;
      if( idTile > (nbTiles - 1 - large)){
        pair[1] = -2;
      }
    }
    fprintf(map, "%d|%d\n", pair[0], pair[1]);
  }
}

int main(int argc, char ** argv){
  if(argc < 3){
    printf("plz give 4 args: nbTiles, nbSides, large, mode (1 if intelligent)\n");
    return 0;
  }
  int nbTiles = atoi(argv[1]);
  int nbSide = atoi(argv[2]);
  int large = atoi(argv[3]);
  int mode = atoi(argv[4]);
  int idTile = 0;
  int nbPair = 0;
  int pair[2];
  FILE * map = NULL;
  map = fopen("map.txt", "w");

  time_t t;
  srand((unsigned) time(&t));

  fprintf(map, "%d\n",nbTiles);
  for(int i = 0; i < nbTiles ;i++){
    if(mode == 1){
      //Intelligent random
      populatePairs(map,idTile, nbTiles, nbSide, large);
    }else{
      int score = rand()%20;
      fprintf(map, "%d %d %d %d\n",idTile, nbSide,nbPair, 0);
      //Slowpoke random
      for(int k = 0; k < nbPair; k++){

        pair[0] = 1 + rand() % nbTiles;
        pair[1] = 1 + rand() % nbTiles;
        fprintf(map, "%d|%d\n", pair[0], pair[1]);
     }
    }
    idTile++;
  }
return 0;
}
