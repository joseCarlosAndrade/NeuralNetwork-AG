#include "TwoPlayerGame.h"
#include "TicTacToe.h"

int main(int argc, char ** argv) {
    TwoPlayerGame *game = new TicTacToe();
    game->PlayerVSPlayer();
    delete game;
}