#include "TwoPlayerGame.h"
#include "TicTacToe.h"
#include "DenseNetwork.h"
#include "Player.h"

using namespace std;

int main() {
    TwoPlayerGame *game = new TicTacToe();
    DenseNetwork network = DenseNetwork("evol_data/bestInfo.txt");
    Player<TicTacToe> *player = new Player<TicTacToe>(network);

    int errors = 0;
    game_status res = game->PlayerVSCom(player->GetAI(), &errors, true, true);

    if(res == P1_VICTORY) {
        cout << "Jogador 1 venceu!" << endl;
    }
    else if(res == P2_VICTORY) {
        cout << "Jogador 2 venceu!" << endl;
    }
    else {
        cout << "Empatou!" << endl;
    }

    cout << "\nwrong moves: " << errors << endl;
    return 0;
}