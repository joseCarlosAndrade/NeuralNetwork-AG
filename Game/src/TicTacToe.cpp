#include "TicTacToe.h"

bool TicTacToe::IsSpaceValid(int input) {
    if ( input <0 || input > 8) return 0;
    int input_x = input%3;
    int input_y = (int)input/3;
    if (this->board[input_x][input_y] != 0) return 0; // checks if posistion is valid
    return 1;
}

void TicTacToe::PutPiece(int input){}


game_status TicTacToe::CheckGameStatus(){}

void TicTacToe::PrintBoard(){}


Eigen::VectorXd GetGameState(){}