#include "DenseNetwork.h"
#include "Player.h"
#include "TwoPlayerGame.h"
#include "TicTacToe.h"
#include <stdlib.h> 

using namespace std;

int main() {
    srand(time(NULL));

    vector<int> netStructure = {9, 16, 16, 9};
    Player<TicTacToe>::SetNetStructure(netStructure);

    Player<TicTacToe> *com = new Player<TicTacToe>();
    TwoPlayerGame *game = new TicTacToe();

    int errors = 0;
    game->ComVSRandom(com->GetAI(), &errors, true, true);

    delete game;
    delete com;
}