#include<assert.h>
#include<stdlib.h>

#ifndef _VELHA_H
#define _VELHA_H

#define P_1 1 // X
#define P_2 -1 // O

enum _game_status{ON, TIE, VICTORY};

typedef struct _game Game;

typedef enum _game_status GameStatus;

struct _game {
    int board[9];
    int player;
    GameStatus game_status;
};


/* Initializes the game, returning a pointer to the `Game` type and 
setting the `player` to player 1 and the board to 0 */
Game * initialize_game();

/* Puts the current players piece on the `pos` position on the board and, if sucessfull, changes the player

@param[in] game Game board
@param[in] pos Piece position
@return int `1` if successfull, `0` (false) if not (position already occupied)
*/
int put_piece(Game * game, int pos);

/* Checks the current board to detect the next game state, being `ON`, `VICTORY`, `TIE`.
If needed, its `game_status` attribute is changed.

@param[in] game Game board */
void check_game_state(Game* game);

/* Prints the board in plain ASCII (for human playing).
@param[in] game Game board */
void print_board(Game *game);

/* Get the board as an array of -1, 0 and 1 (O, nothing and X, respectively)

@param[in] game Game board 
@return int[9] An array that represents the current state of the board */
int * get_board(Game *game);

#endif
