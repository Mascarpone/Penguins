#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "../interface.h"
#include "server.h"
#include "./graphic/graphic.h"

/** \struct client_t
 \brief structure describing a client
 */
typedef struct{
    void (*place_pawn)(int *);
    void (*play)(int *, int *);
    char * (*get_client_name)(void);
    void *desc;
} client_t;

/** \fn void free_client(client_t *client)
 \brief Frees a client and release memory
 */
void free_client(client_t *client) {
    dlclose(client->desc);
    free(client);
}

/** \fn client_t *create_client(char *libname)
 \brief Creates a client : one per library
 */
client_t *create_client(char *libname) {
    void *desc;
    client_t *client;
    
    /* open the library and check errors */
    if((desc = dlopen(libname, RTLD_NOW)) == NULL){
        fprintf(stderr, "Error loading %s : %s\n", libname, dlerror());
        exit(-1);
    }
    
    /* Allocate and fill the client structure */
    client = (client_t *) malloc(sizeof(*client));
    
    /* Get the adress of each relevant symbol */
    client->place_pawn = (void (*)(int *))dlsym(desc, "place_pawn");
    
    /* Check if the symbols have been correctly retreived */
    if(!client->place_pawn){
        fprintf(stderr, "Error! No symbol 'place_pawn' in %s : %s\n", libname, dlerror());
        free_client(client);
        exit(-1);
    }
    
    client->play = (void (*)(int *, int *))dlsym(desc, "play");
    
    if(!client->play){
        fprintf(stderr, "Error! No symbol 'play' in %s : %s\n", libname, dlerror());
        free_client(client);
        exit(-1);
    }
    
    client->get_client_name = (char * (*)(void))dlsym(desc, "get_client_name");
    
    if(!client->play){
        fprintf(stderr, "Error! No symbol 'get_client_name' in %s : %s\n", libname, dlerror());
        free_client(client);
        exit(-1);
    }
    
    client->desc = desc;
    
    return client;
}



int main(int argc, char ** argv){
    
    client_t * clients[10];
    int src, dst;
    
    /* create a client per library */
    for (int i = 1; i < argc; i++) {
        clients[i - 1] = create_client(argv[i]);
    }
    
    
    
    /* Initialize the board */
    int nb_pawns_init = 2;
    struct board * b = board_init("./rsc/maps/mapHexa36.txt", argc - 1, nb_pawns_init);
    
    struct Display d;
    if (display_init(&d) != OK) {
        fprintf(stderr, "An error occured, the program is aborting...\n");
        return EXIT_FAILURE;
    }
    
    print_board(b, &d);
    wait_event(&d);
    
    int pawns_to_place = (argc - 1) * nb_pawns_init;
    
    /* place the pawns */
    while (pawns_to_place) { /* check if all the pawns have been placed at the beginning */
        
        if (nb_unplaced_pawns()) { /* check if the current player has still pawns to place */
            
            /* ask where the client wants to place a pawn */
            clients[b->current_player]->place_pawn(&dst);
            
            if (check_place_pawn(b, dst)) { /* check if the move is allowed by the rules */
                place(b, dst); /* modify the board with the allowed move */
                pawns_to_place--;
            } else {
                print_cheater(&d, argv[b->current_player + 1]); /* prints the scores and tell who tried to cheat */
                fprintf(stderr, "\n %s has cheated (trying to place a pawn on %d) !\n", clients[b->current_player]->get_client_name(), dst);
                remove_player(b, b->current_player);
            }
            
            /* Show the board at the new state */
            print_board(b, &d);
            wait_event(&d);
            
        }
        
        /* change the current player */
        b->current_player = (b->current_player + 1) % (argc - 1);
        
    }
    
    /* set the first player for the second part of the game */
    b->current_player = 0;
    
    /* play */
    while (win(b) < 0) { /* win() returns the player who's won or -1 if there is no winner yet or -2 when there is a draw */
        
        if (is_alive(b, b->current_player)) { /* check if the current player can still play */
            
            /* ask what move the client wants to play */
            clients[b->current_player]->play(&src, &dst);
            
            if (check_play(b, src, dst)) { /* check if the move is allowed by the rules */
                move(b, src, dst); /* modify the board with the allowed move and adds the points*/
            } else {
                print_cheater(&d, clients[b->current_player]->get_client_name()); /* prints the scores and tell who tried to cheat */
                fprintf(stderr, "\n %s has cheated (trying to move from %d to %d) !\n", clients[b->current_player]->get_client_name(), src, dst);
                remove_player(b, b->current_player);
            }
            
            /* Show the board at the new state */
            print_board(b, &d);
            wait_event(&d);
            
        }
        
        /* change the current player */
        b->current_player = (b->current_player + 1) % (argc - 1);
        
    }
    
    print_board(b, &d);
    wait_event(&d);
    
    /* Victory message */
    fprintf(stderr, "\n %s (aka player %d) has won !\n", clients[win(b)]->get_client_name(), win(b));
    print_winner(&d, clients[win(b)]->get_client_name()); /* prints the scores and tell who's the winner */
    
    
    
    /* free all clients */
    for (int i = 0; i < argc - 1; i++) {
        free_client(clients[i]);
    }
    
    /* free the memory allocated by the board */
    display_free(&d);
    free_board(b);
    
    return EXIT_SUCCESS;
}
