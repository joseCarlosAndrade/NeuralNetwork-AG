#include "TwoPlayerGame.h"
#include "TicTacToe.h"

int main(int argc, char ** argv) {
    TwoPlayerGame *game = new TicTacToe();
    
    game_status res = game->PlayerVSPlayer();
    if(res == TIE) {
        cout << "Empatou!" << endl;
    }
    else {
        cout << "O Jogador " << (int) res << " venceu!" << endl;
    }

    delete game;
}