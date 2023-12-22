#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <Eigen/Core> 
#include "TwoPlayerGame.h"

using namespace std;
using namespace Eigen;

class TicTacToe : public TwoPlayerGame {
    protected:
        bool IsSpaceValid(int input) override;
        void PutPiece(int input) override;
        game_status CheckGameStatus() override;
        void PrintBoard() override;

        VectorXd GetGameState() override;
        int GetRandomValidInput(VectorXd& gameState) override;

    public:
        TicTacToe();
        ~TicTacToe();
};

#endif 