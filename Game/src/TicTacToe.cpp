#include "TicTacToe.h"

bool TicTacToe::IsSpaceValid(int input) {
    if(input < 0 || input > 8) return false;
    int row = (int) input / 3;
    int col = input % 3;
    return this->board[row][col] == 0;
}

void TicTacToe::PutPiece(int input) {
    int row = (int) input / 3;
    int col = input % 3;
    this->board[row][col] = 1;
}

game_status TicTacToe::CheckGameStatus() {
    // check rows
    for(int i=0 ; i<3 ; i++) {
        if(this->board[i][0] != 0 && this->board[i][0] == this->board[i][1] && this->board[i][0] == this->board[i][2]) {
            if(this->board[i][0] == 1) {
                return (game_status) (this->turnPlayer);
            }
            else {
                return (game_status) (3 - this->turnPlayer);
            }
        }
    }

    // check columns
    for(int i=0 ; i<3 ; i++) {
        if(this->board[0][i] != 0 && this->board[0][i] == this->board[1][i] && this->board[0][i] == this->board[2][i]) {
            if(this->board[0][i] == 1) {
                return (game_status) (this->turnPlayer);
            }
            else {
                return (game_status) (3 - this->turnPlayer);
            }
        }
    }

    // check diagonals
    if(this->board[0][0] != 0 && this->board[0][0] == this->board[1][1] && this->board[0][0] == this->board[2][2]) {
        if(this->board[0][0] == 1) {
            return (game_status) (this->turnPlayer);
        }
        else {
            return (game_status) (3 - this->turnPlayer);
        }
    }
    if(this->board[0][2] != 0 && this->board[0][2] == this->board[1][1] && this->board[0][2] == this->board[2][0]) {
        if(this->board[0][2] == 1) {
            return (game_status) (this->turnPlayer);
        }
        else {
            return (game_status) (3 - this->turnPlayer);
        }
    }

    // check tie
    for(int i=0; i<3; i++) {
        for(int j=0 ; j<3 ; j++) {
            if(this->board[i][j] == 0) {
                return ONGOING; 
            }
        }
    }

    return TIE;
}

void TicTacToe::PrintBoard() {
    const char *p = (this->turnPlayer == 1) ? "O X" : "X O";

    cout << endl;
    for(int i=0 ; i<3 ; i++) {
        cout << " " << p[this->board[i][0]+1] << " | " << p[this->board[i][1]+1] << " | " << p[this->board[i][2]+1] << " " << endl;
        if(i != 2) cout << "-----------" << endl;
    }
    cout << endl;
}

VectorXd TicTacToe::GetGameState() {
   VectorXd gameState(9);
   for(int i=0 ; i<9 ; i++) {
        int row = (int) i / 3;
        int col = i % 3;
        gameState[i] = this->board[row][col];
   }
   return gameState;
}

TicTacToe::TicTacToe()
: TwoPlayerGame(3, 3, 9, 9) {

}

TicTacToe::~TicTacToe() {

}