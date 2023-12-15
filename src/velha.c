#include"../include/velha.h"
#include<stdio.h>


Game * initialize_game() {
    Game * game = (Game*)calloc(1, sizeof(Game));
    assert(game != NULL);

    game->player = P_1;
    game->game_status = ON;
    
    for (int i = 0; i < 9; i++) game->board[i] = 0;
    
    return game;
}

int put_piece(Game *game, int pos) {
    if ( pos <0 || pos > 8) return 0;
    if (game->board[pos] != 0) return 0; // checks if posistion is valid

    // int piece = (game->player == P_1) ? 'X' : 'O';
    game->board[pos] = game->player;
    game->player *= -1;

    return 1;
}

void check_game_state(Game* game) {
    // check rows 0 1 2 | 3 4 5 | 6 7 8
    for (int i = 0; i <= 6; i += 3) {
        if (game->board[i+0] == game->board[i+1] && game->board[i+0]!=0) 
            if (game->board[i+0] == game->board[i+2]) {
                game->game_status = VICTORY;
                return;
            }
    }

    // check columns 0 3 6 | 1 4 7 | 2 5 8
    for (int i = 0; i < 3; i++) {
        if (game->board[i+0] == game->board[i+3] && game->board[i+0]!=0) 
            if (game->board[i+0] == game->board[i+6]) {
                game->game_status = VICTORY;
                return;
            }
    }

    // check diagonals
    if (game->board[0] == game->board[4] && game->board[0]!=0)
        if (game->board[0] == game->board[8]) {
            game->game_status = VICTORY;
            return;
        }

    if (game->board[2] == game->board[4] && game->board[2]!=0)
        if (game->board[2] == game->board[6]) {
            game->game_status = VICTORY;
            return;
        }

    // check tie (if it hits here, it means no one won so far)
    for (int i = 0; i < 9; i ++) {
        if (game->board[i] == 0) return; 
    }       

    game->game_status = TIE;
    return;
}


void print_board(Game * game) {
    //char * p = "O X";
    /*printf(
    "\n %c | %c | %c   |   0 | 1 | 2 \n___________  |\n %c | %c | %c   |   3 | 4 | 5 \n___________  |\n %c | %c | %c   |   6 | 7 | 8 \n",
    p[game->board[0]+1],
    p[game->board[1]+1],
    p[game->board[2]+1],
    p[game->board[3]+1],
    p[game->board[4]+1],
    p[game->board[5]+1],
    p[game->board[6]+1],
    p[game->board[7]+1],
    p[game->board[8]+1]
    );*/
}

int * get_board(Game *game) {
    return game->board;
}
