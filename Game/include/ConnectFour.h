#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include <Eigen/Core> 
#include "TwoPlayerGame.h"

using namespace std;
using namespace Eigen;

class ConnectFour : public TwoPlayerGame {
    protected:
        bool IsSpaceValid(int input) override;
        void PutPiece(int input) override;
        game_status CheckGameStatus() override;
        void PrintBoard() override;

        VectorXd GetGameState() override;
        int GetRandomValidInput(VectorXd& gameState) override;

    public:
        ConnectFour();
        ~ConnectFour();
};

#endif 