#include<stdio.h>
#include<stdlib.h>
#include"../include/velha.h"

int main(int argc, char ** argv){

    Game * game = initialize_game();
    print_board(game);

    while (game->game_status == ON) {
        int pos;
        scanf(" %d", &pos);

        while( !put_piece(game, pos) ) {
            printf("Position not valid. Try again. \n\n");
            scanf(" %d", &pos); 
        }    

        check_game_state(game);
        print_board(game);
    }

    char * p = "O X";
    printf("\nFinished! Game status: %d.\nCurrent player: %c\n", game->game_status, p[game->player*-1 + 1]);
}