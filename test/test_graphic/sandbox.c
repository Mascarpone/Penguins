#include "../../src/server/graphic/graphic.h"
#include <stdlib.h>
#include <stdio.h>



int main() {
    
    struct board * b = board_init("./rsc/maps/mapHexa36.txt", 1, 1);
    
    struct Display d;
    
    if(display_init(&d) != OK){
        fprintf(stderr, "An error occured, the program is aborting...\n");
        return EXIT_FAILURE;
    }
    
    b->tiles[1].player = 2;
    
    print_board(b, &d);
    wait_event(&d);
    display_free(&d);
    
    return EXIT_SUCCESS;
}
