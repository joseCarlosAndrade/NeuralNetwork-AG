#ifndef TWOPLAYERGAME_H
#define TWOPLAYERGAME_H

#include <stdlib.h>
#include <Eigen/Core>
#include "DenseNetwork.h"

using namespace std;
using namespace Eigen;

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
        virtual int GetRandomValidInput(VectorXd& gameState) = 0;
        int * GetPlaysInputs(VectorXd& playsProbs);

        void SwitchPlayer();
        bool CheckComStructure(DenseNetwork *com);

    public:
        TwoPlayerGame(int boardRows, int boardCols, int gameStateLen, int playInputLen);

        int GetGameStateLen();
        int GetPlayInputLen();

        game_status PlayerVSPlayer();
        game_status PlayerVSRandom(bool playerFirst, bool verbose);
        game_status PlayerVSCom(DenseNetwork *com, int *out_errors, bool playerFirst, bool verbose);
        game_status ComVSRandom(DenseNetwork *com, int *out_errors, bool comFirst, bool verbose);
        game_status ComVSCom(DenseNetwork *com1, DenseNetwork *com2, int *out_errors1, int *out_errors2, bool verbose);

        virtual ~TwoPlayerGame();
};

#endif 