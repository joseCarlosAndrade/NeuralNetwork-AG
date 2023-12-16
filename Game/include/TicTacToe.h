#ifndef TICTACTOE_H
#define TICTACTOE_H

#include "MiniDNN.h"
#include "TwoPlayerGame.h"

using namespace std;
using namespace MiniDNN;

class TicTacToe : public TwoPlayerGame {
    protected:
        bool IsSpaceValid(int input) override;
        void PutPiece(int input) override;
        game_status CheckGameStatus() override;
        void PrintBoard() override;

        Eigen::VectorXd GetGameState() override;

    public:
        TicTacToe();
        ~TicTacToe();
};

#endif 