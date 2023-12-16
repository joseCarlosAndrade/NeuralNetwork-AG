#ifndef TWOPLAYERGAME_H
#define TWOPLAYERGAME_H

#include "MiniDNN.h"

using namespace MiniDNN;

typedef enum { ONGOING, TIE, P1_VICTORY, P2_VICTORY } game_status;

class TwoPlayerGame {
    protected:
        int **board;
        int boardRows, boardCols;
        int gameStateLen, playInputLen;

        int turn_player;

        virtual bool IsSpaceValid(int input) = 0;
        virtual void PutPiece(int input) = 0;
        virtual game_status CheckGameStatus() = 0;
        virtual void PrintBoard() = 0;

        virtual Eigen::VectorXd * GetGameState() = 0;
        int * GetPlaysInputs(Eigen::VectorXd *playsProbs);

        void SwitchPlayer();

    public:
        TwoPlayerGame(int boardRows, int boardCols, int gameStateLen, int playInputLen);

        int GetGameStateLen();
        int GetPlayInputLen();

        game_status PlayerVSPlayer();
        game_status PlayerVSCom(Network *com, int *out_errors);
        game_status ComVSCom(Network *com1, Network *com2, int *out_errors1, int *out_errors2);

        ~TwoPlayerGame();
};

#endif 