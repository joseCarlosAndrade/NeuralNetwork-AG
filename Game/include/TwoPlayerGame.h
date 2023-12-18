#ifndef TWOPLAYERGAME_H
#define TWOPLAYERGAME_H

#include <Eigen/Core> 
#include "MiniDNN.h"

using namespace std;
using namespace Eigen;
using namespace MiniDNN;

typedef enum {
    ONGOING = -1,
    TIE = 0,
    P1_VICTORY = 1,
    P2_VICTORY = 2
} game_status;

class TwoPlayerGame {
    protected:
        int **board;
        int boardRows, boardCols;
        int gameStateLen, playInputLen;

        int turnPlayer;

        virtual bool IsSpaceValid(int input) = 0;
        virtual void PutPiece(int input) = 0;
        virtual game_status CheckGameStatus() = 0;
        virtual void PrintBoard() = 0;

        virtual VectorXd GetGameState() = 0;
        int * GetPlaysInputs(VectorXd& playsProbs);

        void SwitchPlayer();

    public:
        TwoPlayerGame(int boardRows, int boardCols, int gameStateLen, int playInputLen);

        int GetGameStateLen();
        int GetPlayInputLen();

        game_status PlayerVSPlayer();
        game_status PlayerVSCom(Network *com, int *out_errors, bool verbose);
        game_status ComVSCom(Network *com1, Network *com2, int *out_errors1, int *out_errors2, bool verbose);

        virtual ~TwoPlayerGame();
};

#endif 