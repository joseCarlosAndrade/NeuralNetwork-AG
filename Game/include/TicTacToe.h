#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <Eigen/Core> 
#include "MiniDNN.h"
#include "TwoPlayerGame.h"

using namespace std;
using namespace Eigen;
using namespace MiniDNN;

class TicTacToe : public TwoPlayerGame {
    protected:
        bool IsSpaceValid(int input) override;
        void PutPiece(int input) override;
        game_status CheckGameStatus() override;
        void PrintBoard() override;

        VectorXd GetGameState() override;

    public:
        TicTacToe();
        ~TicTacToe();
};

#endif 