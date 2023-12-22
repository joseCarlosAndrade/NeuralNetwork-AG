#include "TwoPlayerGame.h"
#include "TicTacToe.h"

int main(int argc, char ** argv) {
    TwoPlayerGame *game = new TicTacToe();
    game_status res = game->PlayerVSPlayer();

    if(res == P1_VICTORY) {
        cout << "Jogador 1 venceu!" << endl;
    }
    else if(res == P2_VICTORY) {
        cout << "Jogador 2 venceu!" << endl;
    }
    else {
        cout << "Empatou!" << endl;
    }

    delete game;
}