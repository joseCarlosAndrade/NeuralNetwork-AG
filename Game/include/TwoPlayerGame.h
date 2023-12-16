#ifndef TWOPLAYERGAME_H
#define TWOPLAYERGAME_H

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

        virtual int * GetGameState() = 0;
        int * GetPlaysInputs(int *playsProbs);

        void SwitchPlayer();

    public:
        TwoPlayerGame(int boardRows, int boardCols, int gameStateLen, int playInputLen);

        int GetGameStateLen();
        int GetPlayInputLen();

        game_status PlayerVSPlayer();
        game_status PlayerVSCom(Network com, int *errors);
        game_status ComVSCom(Network com1, Network com2, int *errors1, int *errors2);

        ~TwoPlayerGame();
}

#endif //TWOPLAYERGAME_H